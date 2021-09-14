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


	}


}

void Network::CheckFinish() {
	CURLMsg* msg;
	int msgs_left;
	while ((msg = curl_multi_info_read(curlm_, &msgs_left))) {
		if (msg->msg == CURLMSG_DONE) {
			CURL* curl = msg->easy_handle;

		}
	}

}

void Network::Req(RefCountedPtr<Request> request) {
	std::lock_guard<std::mutex> lock(task_lock_);
	tasks_.push([this,request]() {
		CURL* curl = curl_easy_init();
		if (curl) {
			Request* req = request.get();

			curl_easy_setopt(curl, CURLOPT_URL, req->url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent_.c_str());
			curl_easy_setopt(curl, CURLOPT_COOKIE, req->cookie.c_str());
			curl_easy_setopt(curl, CURLOPT_ENCODING, "gzip, deflate");

			//ÉèÖÃ301¡¢302Ìø×ª¸úËælocation
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
			curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);


			req->AddRef();
			curl_easy_setopt(curl, CURLOPT_PRIVATE, req);

			if (req->type == Request::kPost) {
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req->post.data());
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, req->post.size());
			}

			if (!req->headers.empty()) {

				struct curl_slist* header = NULL;

				for (auto h : req->headers) {
					header = curl_slist_append(header,h.c_str());
				}
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
			}

			curl_multi_add_handle(curlm_, curl);
		}
	});
	curl_multi_wakeup(curlm_);
}


