#pragma once
#include "quickjs/qjs.h"
#include <functional>

namespace duijs {

class TaskManager;

typedef std::function<void(qjs::Context* context)> js_task_t;

class JsEngine {
public:
	JsEngine();
	~JsEngine();

	bool Init();
	void RunLoop();

	bool Excute(const char* input, const char* filename);
	void PostTask(js_task_t task);
private:
	qjs::Runtime* runtime_;
	qjs::Context* context_;
	TaskManager* manager_;
};


}//namespace


