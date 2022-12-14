#pragma once
#include "quickjs/qjs.h"
#include <functional>
#include <thread>

namespace duijs {

class TaskManager;

typedef std::function<void()> js_task_t;

class JsEngine {
public:
	JsEngine();
	~JsEngine();

	bool Init(wchar_t** argv,int argc);
	void RunLoop();

	bool Excute(const char* input, const char* filename);
	void PostTask(js_task_t task);

	uint32_t PostDelayTask(js_task_t task, uint32_t delay, bool repeat);
	void ResetDelayTask(uint32_t id, js_task_t task, uint32_t delay,bool repeat);
	bool CancelDelayTask(uint32_t id);

	qjs::Context* context() { return context_; }

	static JsEngine* get(qjs::Context& context);

	void Print(const char* str, size_t len);
private:
	qjs::Runtime* runtime_;
	qjs::Context* context_;
	TaskManager*  manager_;
	std::thread::id thread_id_;
};


}//namespace


