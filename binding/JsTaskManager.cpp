#include "JsTaskManager.h"
#include "duilib/UIlib.h"

namespace duijs {

using namespace DuiLib;

#define WM_THREAD_MSG_ACTIVE WM_USER+0x92


class TaskWindow :public CWindowWnd
{
public:
	TaskWindow(TaskManager* manager)
		:manager_(manager){
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_THREAD_MSG_ACTIVE:
			if(manager_)
				manager_->ExcuteTasks();
			return 0;
		case WM_TIMER:
			if (manager_)
				manager_->OnTimer(wParam);
			return 0;
		default:
			return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		}
	}

	void OnClose() {
		manager_ = nullptr;
	}
private:
	virtual LPCTSTR GetWindowClassName() const {
		return _T("DuiJsTaskWindowClass");
	}
	TaskManager* manager_;
};

static DWORD tls = TlsAlloc();

TaskManager* TaskManager::GetCurrent() {
	return (TaskManager*)TlsGetValue(tls);
}


TaskManager::TaskManager()
	:last_timer_id_(0)
{
	TlsSetValue(tls, this);
	task_window_ = new TaskWindow(this);
	task_window_->Create(NULL, _T("JSTaskWindow"), UI_WNDSTYLE_CONTAINER, UI_WNDSTYLE_CONTAINER,-1,-1,1,1);
}

TaskManager::~TaskManager() {
	TlsFree(tls);
	task_window_->Close();
	task_window_->OnClose();
}

void TaskManager::PostTask(js_task_t task) {
	std::lock_guard<std::mutex> locker(lock_);
	tasks_.push(task);
	task_window_->PostMessage(WM_THREAD_MSG_ACTIVE, 0, 0);
}

uint32_t TaskManager::PostDelayTask(js_task_t task, uint32_t delay, bool repeat) {
	uint32_t id = ::SetTimer(*task_window_, ++last_timer_id_, delay, nullptr);
	std::lock_guard<std::mutex> locker(lock_);
	timer_tasks_.insert(std::make_pair(id, std::make_shared<TimerTask>(task,repeat)));
	return id;
}

void TaskManager::ResetDelayTask(uint32_t id, js_task_t task, uint32_t delay, bool repeat) {
	assert(id > 0);
	::SetTimer(*task_window_, id, delay, nullptr);

	std::lock_guard<std::mutex> locker(lock_);
	timer_tasks_.insert(std::make_pair(id, std::make_shared<TimerTask>(task, repeat)));
}

bool TaskManager::CancelDelayTask(uint32_t id) {
	std::lock_guard<std::mutex> locker(lock_);
	auto find = timer_tasks_.find(id);
	if (find != timer_tasks_.end()) {
		timer_tasks_.erase(find);
		::KillTimer(*task_window_, id);
		return true;
	}
	return false;
}

void TaskManager::ExcuteTasks() {
	auto task = PopTask();
	while (task) {
		task();
		task = PopTask();
	}
}

void TaskManager::OnTimer(uint32_t id) {
	auto task = PopTimerTask(id);
	if (task) {
		task->task();
	}

	if (!task->repeat)
		::KillTimer(*task_window_, id);
}

js_task_t TaskManager::PopTask() {
	std::lock_guard<std::mutex> locker(lock_);
	if (tasks_.empty()) {
		return nullptr;
	}
	auto task = tasks_.front();
	tasks_.pop();
	return std::move(task);
}

std::shared_ptr<TaskManager::TimerTask> TaskManager::PopTimerTask(uint32_t id) {
	std::lock_guard<std::mutex> locker(lock_);
	auto find = timer_tasks_.find(id);
	if (find != timer_tasks_.end()) {
		std::shared_ptr<TimerTask> task = find->second;
		if(!task->repeat)
			timer_tasks_.erase(find);
		return task;
	}
	return nullptr;
}



}//namespace

