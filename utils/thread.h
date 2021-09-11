#pragma once
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include "waitable_event.h"


using Task = std::function<void()>;

class Thread {
public:
	Thread();
	~Thread();

	void PostTask(Task task);
	void Start();
	void Stop();
	void Join();
private:
	Task PopTask();

	AutoResetWaitableEvent event_;

	std::atomic<bool> quit_;
	std::queue<Task> tasks_;
	std::mutex task_lock_;

	std::unique_ptr<std::thread> thread_;
};


