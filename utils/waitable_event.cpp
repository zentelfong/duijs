#include "waitable_event.h"
#include <errno.h>
#include <time.h>


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
