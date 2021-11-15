#include "thread.h"

#ifdef _WIN32
#include <Windows.h>

// As seen on MSDN.
// http://msdn.microsoft.com/en-us/library/xcb2z8hs(VS.71).aspx
#define MSDEV_SET_THREAD_NAME  0x406D1388
typedef struct tagTHREADNAME_INFO {
	DWORD dwType;
	LPCSTR szName;
	DWORD dwWorkThreadID;
	DWORD dwFlags;
} THREADNAME_INFO;

void SetThreadName(DWORD dwWorkThreadID, LPCSTR szWorkThreadName) {
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = szWorkThreadName;
	info.dwWorkThreadID = dwWorkThreadID;
	info.dwFlags = 0;

	__try {
		RaiseException(MSDEV_SET_THREAD_NAME, 0, sizeof(info) / sizeof(DWORD),
			reinterpret_cast<ULONG_PTR*>(&info));
	}
	__except (EXCEPTION_CONTINUE_EXECUTION) {
	}
}
#endif

Thread::Thread(const char* name) {
	if (name)
		name_ = name;
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
#if defined(WIN32) && defined(_DEBUG)
		SetThreadName(GetCurrentThreadId(), name_.c_str());
#endif
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


ThreadManager* ThreadManager::s_instance_ = NULL;

ThreadManager* ThreadManager::Instance() {
	if (!s_instance_)
		s_instance_ = new ThreadManager();
	return s_instance_;
}

void ThreadManager::DestroyInstance() {
	delete s_instance_;
	s_instance_ = nullptr;
}

void ThreadManager::PostTask(TID tid, Task task) {
	threads_[tid]->PostTask(task);
}

ThreadManager::ThreadManager() {
	threads_[kIO] = new Thread("IO_Thread");
	threads_[kStorage] = new Thread("Storage_Thread");
	threads_[kImage] = new Thread("Image_Thread");
	for (auto& thread:threads_) {
		thread->Start();
	}
}


ThreadManager::~ThreadManager() {
	for (auto& thread : threads_) {
		thread->Stop();
		thread->Join();
		delete thread;
	}
}