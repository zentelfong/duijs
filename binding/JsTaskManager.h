#pragma once
#include <functional>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <memory>

namespace duijs {

typedef std::function<void()> js_task_t;
class TaskWindow;

class TaskManager {
public:
	TaskManager();
	~TaskManager();

	//获取当前线程的taskmanager
	static TaskManager* GetCurrent();

	void PostTask(js_task_t task);

	uint32_t PostDelayTask(js_task_t task,uint32_t delay,bool repeat);
	void ResetDelayTask(uint32_t id,js_task_t task, uint32_t delay, bool repeat);
	bool CancelDelayTask(uint32_t id);
private:
	struct TimerTask {
		TimerTask(js_task_t t, bool r)
			:task(t),repeat(r)
		{
		}
		js_task_t task;
		bool repeat;
	};

	friend class TaskWindow;
	void ExcuteTasks();
	void OnTimer(uint32_t id);
	js_task_t PopTask();
	std::shared_ptr<TimerTask> PopTimerTask(uint32_t id);

	TaskWindow* task_window_;
	uint32_t last_timer_id_;
	std::mutex lock_;
	std::queue<js_task_t> tasks_;
	std::unordered_map<uint32_t, std::shared_ptr<TimerTask> > timer_tasks_;
};


}//namespace


