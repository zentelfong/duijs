#pragma once
#include <condition_variable>
#include <mutex>

// An event that can be signaled and waited on. This version automatically
// returns to the unsignaled state after unblocking one waiter. (This is similar
// to Windows's auto-reset Event, which is also imitated by Chromium's
// auto-reset |base::WaitableEvent|. However, there are some limitations -- see
// |Signal()|.) This class is thread-safe.
class AutoResetWaitableEvent final {
 public:
  AutoResetWaitableEvent() {}
  ~AutoResetWaitableEvent() {}

  // Put the event in the signaled state. Exactly one |Wait()| will be unblocked
  // and the event will be returned to the unsignaled state.
  //
  // Notes (these are arguably bugs, but not worth working around):
  // * That |Wait()| may be one that occurs on the calling thread, *after* the
  //   call to |Signal()|.
  // * A |Signal()|, followed by a |Reset()|, may cause *no* waiting thread to
  //   be unblocked.
  // * We rely on pthreads's queueing for picking which waiting thread to
  //   unblock, rather than enforcing FIFO ordering.
  void Signal();

  // Put the event into the unsignaled state. Generally, this is not recommended
  // on an auto-reset event (see notes above).
  void Reset();

  // Blocks the calling thread until the event is signaled. Upon unblocking, the
  // event is returned to the unsignaled state, so that (unless |Reset()| is
  // called) each |Signal()| unblocks exactly one |Wait()|.
  void Wait();

  bool WaitWithTimeout(int32_t ms);
 private:
  std::condition_variable cv_;
  std::mutex mutex_;

  // True if this event is in the signaled state.
  bool signaled_ = false;
};
