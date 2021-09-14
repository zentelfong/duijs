#pragma once
#include <functional>
#include <queue>
#include <mutex>
#include <unordered_map>
#include "quickjs/qjs.h"


namespace duijs {

typedef std::function<void()> js_task_t;
class TaskWindow;

class TaskManager {
public:
	TaskManager(qjs::Context* context);
	~TaskManager();

	void PostTask(js_task_t task);

	uint32_t PostDelayTask(js_task_t task,uint32_t delay);
	void ResetDelayTask(uint32_t id,js_task_t task, uint32_t delay);
	bool CancelDelayTask(uint32_t id);
private:
	friend class TaskWindow;
	void ExcuteTasks();
	void OnTimer(uint32_t id);
	js_task_t PopTask();
	js_task_t PopTimerTask(uint32_t id);

	TaskWindow* task_window_;
	qjs::Context* context_;
	uint32_t last_timer_id_;
	std::mutex lock_;
	std::queue<js_task_t> tasks_;
	std::unordered_map<uint32_t, js_task_t> timer_tasks_;
};


}//namespace


