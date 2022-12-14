#include "RateTracker.h"
#include <stddef.h>
#include <algorithm>
#include <assert.h>
#include <ctime>

static const uint32_t HALF = 0x80000000;

inline int32_t TimeDiff(uint32_t later, uint32_t earlier) {
    return later - earlier;
}

inline bool TimeIsLaterOrEqual(uint32_t earlier, uint32_t later) {
    int32_t diff = later - earlier;
    return (diff >= 0 && static_cast<uint32_t>(diff) < HALF);
}

RateTracker::RateTracker(uint32_t bucket_milliseconds, size_t bucket_count)
    : bucket_milliseconds_(bucket_milliseconds),
      bucket_count_(bucket_count),
      sample_buckets_(new size_t[bucket_count + 1]),
      total_sample_count_(0u),
      bucket_start_time_milliseconds_(~0u) {
  assert(bucket_milliseconds > 0u);
  assert(bucket_count > 0u);
}

RateTracker::~RateTracker() {
  delete[] sample_buckets_;
}

double RateTracker::ComputeRateForInterval(
    uint32_t interval_milliseconds) const {
  if (bucket_start_time_milliseconds_ == ~0u) {
    return 0.0;
  }
  uint32_t current_time = Time();
  // Calculate which buckets to sum up given the current time.  If the time
  // has passed to a new bucket then we have to skip some of the oldest buckets.
  uint32_t available_interval_milliseconds = std::min<uint32_t>(
      interval_milliseconds,
      bucket_milliseconds_ * static_cast<uint32_t>(bucket_count_));
  // number of old buckets (i.e. after the current bucket in the ring buffer)
  // that are expired given our current time interval.
  size_t buckets_to_skip;
  // Number of milliseconds of the first bucket that are not a portion of the
  // current interval.
  uint32_t milliseconds_to_skip;
  if (current_time >
      initialization_time_milliseconds_ + available_interval_milliseconds) {
    uint32_t time_to_skip =
        current_time - bucket_start_time_milliseconds_ +
        static_cast<uint32_t>(bucket_count_) * bucket_milliseconds_ -
        available_interval_milliseconds;
    buckets_to_skip = time_to_skip / bucket_milliseconds_;
    milliseconds_to_skip = time_to_skip % bucket_milliseconds_;
  } else {
    buckets_to_skip = bucket_count_ - current_bucket_;
    milliseconds_to_skip = 0u;
    available_interval_milliseconds =
        TimeDiff(current_time, initialization_time_milliseconds_);
    // Let one bucket interval pass after initialization before reporting.
    if (available_interval_milliseconds < bucket_milliseconds_) {
      return 0.0;
    }
  }
  // If we're skipping all buckets that means that there have been no samples
  // within the sampling interval so report 0.
  if (buckets_to_skip > bucket_count_ ||
      available_interval_milliseconds == 0u) {
    return 0.0;
  }
  size_t start_bucket = NextBucketIndex(current_bucket_ + buckets_to_skip);
  // Only count a portion of the first bucket according to how much of the
  // first bucket is within the current interval.
  size_t total_samples = ((sample_buckets_[start_bucket] *
      (bucket_milliseconds_ - milliseconds_to_skip)) +
      (bucket_milliseconds_ >> 1)) /
      bucket_milliseconds_;
  // All other buckets in the interval are counted in their entirety.
  for (size_t i = NextBucketIndex(start_bucket);
      i != NextBucketIndex(current_bucket_);
      i = NextBucketIndex(i)) {
    total_samples += sample_buckets_[i];
  }
  // Convert to samples per second.
  return static_cast<double>(total_samples * 1000u) /
      static_cast<double>(available_interval_milliseconds);
}

double RateTracker::ComputeTotalRate() const {
  if (bucket_start_time_milliseconds_ == ~0u) {
    return 0.0;
  }
  uint32_t current_time = Time();
  if (TimeIsLaterOrEqual(current_time, initialization_time_milliseconds_)) {
    return 0.0;
  }
  return static_cast<double>(total_sample_count_ * 1000u) /
      static_cast<double>(
          TimeDiff(current_time, initialization_time_milliseconds_));
}

size_t RateTracker::TotalSampleCount() const {
  return total_sample_count_;
}

void RateTracker::AddSamples(size_t sample_count) {
  EnsureInitialized();
  uint32_t current_time = Time();
  // Advance the current bucket as needed for the current time, and reset
  // bucket counts as we advance.
  for (size_t i = 0u; i <= bucket_count_ &&
      current_time >= bucket_start_time_milliseconds_ + bucket_milliseconds_;
      ++i) {
    bucket_start_time_milliseconds_ += bucket_milliseconds_;
    current_bucket_ = NextBucketIndex(current_bucket_);
    sample_buckets_[current_bucket_] = 0u;
  }
  // Ensure that bucket_start_time_milliseconds_ is updated appropriately if
  // the entire buffer of samples has been expired.
  bucket_start_time_milliseconds_ += bucket_milliseconds_ *
      ((current_time - bucket_start_time_milliseconds_) / bucket_milliseconds_);
  // Add all samples in the bucket that includes the current time.
  sample_buckets_[current_bucket_] += sample_count;
  total_sample_count_ += sample_count;
}

uint32_t RateTracker::Time() const {
    return (uint32_t)(std::clock() * 1000 / CLOCKS_PER_SEC);
}

void RateTracker::EnsureInitialized() {
  if (bucket_start_time_milliseconds_ == ~0u) {
    initialization_time_milliseconds_ = Time();
    bucket_start_time_milliseconds_ = initialization_time_milliseconds_;
    current_bucket_ = 0u;
    // We only need to initialize the first bucket because we reset buckets when
    // current_bucket_ increments.
    sample_buckets_[current_bucket_] = 0u;
  }
}

size_t RateTracker::NextBucketIndex(size_t bucket_index) const {
  return (bucket_index + 1u) % (bucket_count_ + 1u);
}

