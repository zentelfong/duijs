#include "waitable_event.h"
#include <errno.h>
#include <time.h>
#include <chrono>

void AutoResetWaitableEvent::Signal() {
  std::lock_guard<std::mutex> locker(mutex_);
  signaled_ = true;
  cv_.notify_one();
}

void AutoResetWaitableEvent::Reset() {
  std::lock_guard<std::mutex> locker(mutex_);
  signaled_ = false;
}

void AutoResetWaitableEvent::Wait() {
  std::unique_lock<std::mutex> locker(mutex_);
  while (!signaled_) {
    cv_.wait(locker);
  }
  signaled_ = false;
}


bool AutoResetWaitableEvent::WaitWithTimeout(int32_t timeout) {
    std::unique_lock<std::mutex> locker(mutex_);

    if (signaled_) {
        signaled_ = false;
        return false;
    }

    // We may get spurious wakeups.
    auto start  = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();

    while (true) {
        if (std::cv_status::timeout ==
            cv_.wait_for(
                locker, std::chrono::milliseconds(timeout))) {
            return true;  // Definitely timed out.
        }

        // We may have been awoken.
        if (signaled_) {
            break;
        }

        // Or the wakeup may have been spurious.
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();

        // It's possible that we may have timed out anyway.
        if (now >= start + timeout) {
            return true;
        }
    }

    signaled_ = false;
    return false;
}

