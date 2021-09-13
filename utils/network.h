#pragma once
#include <thread>
#include <memory>
#include <queue>
#include <atomic>
#include <mutex>
#include <functional>
#include "request.h"


class Network {
public:
	Network();
	~Network();

	void Start();
	void Stop();

	void Req(std::shared_ptr<Request> request);
private:
	void OnRun();
	void* curlm_;

	std::atomic<bool> running_;
	std::mutex task_lock_;
	std::queue<std::function<void()>> tasks_;
	std::unique_ptr<std::thread> thread_;
};

