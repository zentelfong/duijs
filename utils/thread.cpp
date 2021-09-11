#include "thread.h"


Thread::Thread() {
}

Thread::~Thread() {
}

void Thread::PostTask(Task task) {
	{
		std::lock_guard<std::mutex> locker(task_lock_);
		tasks_.push(task);
	}
	event_.Signal();
}


void Thread::Start() {
	quit_ = false;
	thread_.reset(new std::thread([this]() {
		while (!quit_) {
			auto task = PopTask();
			if (task) {
				task();
			} else {
				event_.Wait();
			}
		}
	}));
}


void Thread::Stop() {
	quit_ = true;
	event_.Signal();
}


void Thread::Join() {
	if(thread_)
		thread_->join();
}

Task Thread::PopTask() {
	std::lock_guard<std::mutex> locker(task_lock_);
	if (tasks_.empty()) {
		return nullptr;
	}
	else {
		auto task = tasks_.front();
		tasks_.pop();
		return task;
	}
}

