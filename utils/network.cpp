#include "network.h"

#include <libcurl/include/curl/curl.h>


void InitCurlLib() {
	static bool init = false;
	if (!init) {
		init = true;
		curl_global_init(CURL_GLOBAL_ALL);
	}
}


Network::Network() 
	:curlm_(nullptr), running_(false)
{
	InitCurlLib();
}

Network::~Network() {

}

void Network::Start() {
	if (!running_) {
		running_ = true;
		curlm_ = curl_multi_init();
		thread_.reset(new std::thread(std::bind(&Network::OnRun, this)));
	}
}

void Network::Stop() {
	if (running_) {
		running_ = false;
		curl_multi_wakeup(curlm_);
		thread_->join();
		curl_multi_cleanup(curlm_);
		curlm_ = nullptr;

	}
}


void Network::OnRun() {
	
	while (running_) {

		int handles = 0;
		do {
			CURLMcode mc = curl_multi_perform(curlm_, &handles);

			if (handles)
				/* wait for activity, timeout or "nothing" */
				mc = curl_multi_poll(curlm_, NULL, 0, 1000, NULL);

			if (mc)
				break;
		} while (handles);

		CURLMsg* msg;
		int msgs_left;
		while ((msg = curl_multi_info_read(curlm_, &msgs_left))) {
			if (msg->msg == CURLMSG_DONE) {
				CURL* curl = msg->easy_handle;


			}
		}

	}


}

void Network::Req(std::shared_ptr<Request> request) {
	std::lock_guard<std::mutex> lock(task_lock_);
	tasks_.push([this,request]() {
		CURL* curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");

			curl_multi_add_handle(curlm_, curl);
		}
	});
	curl_multi_wakeup(curlm_);
}


