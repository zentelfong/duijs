#include "JsTask.h"
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
				manager_->Idle();
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
		return L"DuiJsTaskWindowClass";
	}
	TaskManager* manager_;
};


TaskManager::TaskManager(qjs::Context* context)
	:context_(context)
{
	task_window_ = new TaskWindow(this);
	task_window_->Create(NULL, _T("JSTaskWindow"), UI_WNDSTYLE_CONTAINER, UI_WNDSTYLE_CONTAINER);
}

TaskManager::~TaskManager() {
	task_window_->Close();
	task_window_->OnClose();
}

void TaskManager::PostTask(js_task_t task) {
	std::lock_guard<std::mutex> locker(lock_);
	tasks_.push(task);
	task_window_->PostMessage(WM_THREAD_MSG_ACTIVE, 0, 0);
}

void TaskManager::ExcuteTasks() {
	auto task = PopTask();
	while (task) {
		task(context_);
		task = PopTask();
	}
}

void TaskManager::Idle() {
	context_->ExecuteJobs();
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

}//namespace

