#pragma once
#include <functional>
#include <queue>
#include <mutex>
#include "quickjs/qjs.h"


namespace duijs {

typedef std::function<void(qjs::Context* context)> js_task_t;
class TaskWindow;

class TaskManager {
public:
	TaskManager(qjs::Context* context);
	~TaskManager();

	void PostTask(js_task_t task);

private:
	friend class TaskWindow;
	void ExcuteTasks();
	void Idle();
	js_task_t PopTask();

	TaskWindow* task_window_;
	qjs::Context* context_;
	std::mutex lock_;
	std::queue<js_task_t> tasks_;
};


}//namespace


