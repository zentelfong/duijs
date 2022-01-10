#include "duilib/UIlib.h"
#include "JsEngine.h"
#include "Util.h"
#include "JsTaskManager.h"
#include "async/thread.h"

namespace duijs {
using namespace qjs;
using namespace DuiLib;

extern void RegisterJSX(qjs::Context* context);
extern void RegisterDPI(Module* module);
extern void RegisterString(qjs::Module* module);
extern void RegisterGlobal(Module* module);
extern void RegisterConst(qjs::Module* module);
extern void RegisterPaintManager(Module* module);
extern void RegisterWindow(qjs::Module* module);
extern void RegisterControl(qjs::Module* module);
extern void RegisterLabel(qjs::Module* module);
extern void RegisterDialogBuilder(qjs::Module* module);
extern void RegisterContainer(qjs::Module* module);
extern void RegisterButton(qjs::Module* module);
extern void RegisterText(qjs::Module* module);
extern void RegisterCombo(qjs::Module* module);
extern void RegisterComboBox(qjs::Module* module);
extern void RegisterDateTime(qjs::Module* module);
extern void RegisterColorPalette(qjs::Module* module);
extern void RegisterTimer(qjs::Module* module);
extern void RegisterEdit(qjs::Module* module);
extern void RegisterFadeButton(qjs::Module* module);
extern void RegisterGifAnim(qjs::Module* module);
extern void RegisterHorizontalLayout(qjs::Module* module);
extern void RegisterVerticalLayout(qjs::Module* module);
extern void RegisterChildLayout(qjs::Module* module);
extern void RegisterTileLayout(qjs::Module* module);
extern void RegisterTabLayout(qjs::Module* module);
extern void RegisterAnimationTabLayout(qjs::Module* module);
extern void RegisterTrayIcon(qjs::Module* module);
extern void RegisterGroupBox(qjs::Module* module);
extern void RegisterHotKey(qjs::Module* module);
extern void RegisterIPAddress(qjs::Module* module);
extern void RegisterIPAddressEx(qjs::Module* module);
extern void RegisterList(qjs::Module* module);
extern void RegisterListElement(qjs::Module* module);
extern void RegisterListContainerElement(qjs::Module* module);
extern void RegisterMenu(qjs::Module* module);
extern void RegisterOption(qjs::Module* module);
extern void RegisterProgress(qjs::Module* module);

extern void RegisterRing(qjs::Module* module);
extern void RegisterRollText(qjs::Module* module);
extern void RegisterRichEdit(qjs::Module* module);
extern void RegisterScrollBar(qjs::Module* module);

extern void RegisterTreeNode(qjs::Module* module);
extern void RegisterTreeView(qjs::Module* module);
extern void RegisterStorage(qjs::Module* module);
extern void RegisterQrControl(qjs::Module* module);

extern void RegisterHttpClient(Module* module);
extern void RegisterFileDownload(qjs::Module* module);

extern JSModuleDef* jsModuleLoader(JSContext* ctx,
	const char* module_name, void* opaque);

JsEngine::JsEngine() 
	:runtime_(nullptr),context_(nullptr), manager_(nullptr)
{

}


JsEngine::~JsEngine() {

	delete manager_;
	manager_ = nullptr;
	delete context_;
	context_ = nullptr;
	delete runtime_;
	runtime_ = nullptr;

}

//解析命令行参数
void RegisterArgs(qjs::Context* ctx, wchar_t** argv, int argc) {
	qjs::Value args = ctx->NewObject();
	for (int i = 0; i < argc; ++i) {
		args.SetPropertyString(i, Wide2UTF8(argv[i]).c_str());
	}
	ctx->Global().SetProperty("args", args);
}


bool JsEngine::Init(wchar_t** argv, int argc) {
	assert(!runtime_);
	assert(!context_);

	thread_id_ = std::this_thread::get_id();

	runtime_ = new qjs::Runtime();
	context_ = new qjs::Context(runtime_);
	manager_ = new TaskManager();
	context_->SetUserData(this);

	JS_SetModuleLoaderFunc(runtime_->runtime(), NULL, jsModuleLoader, NULL);

	RegisterJSX(context_);

	auto module = context_->NewModule("DuiLib");
	RegisterArgs(context_, argv, argc);
	RegisterConst(module);
	RegisterGlobal(module);
	RegisterString(module);
	RegisterDPI(module);
	RegisterHttpClient(module);
	RegisterWindow(module);
	RegisterPaintManager(module);
	RegisterDialogBuilder(module);
	RegisterTimer(module);
	RegisterTrayIcon(module);

	RegisterControl(module);
	RegisterLabel(module);
	RegisterButton(module);
	RegisterFadeButton(module);
	RegisterText(module);
	RegisterDateTime(module);
	RegisterColorPalette(module);
	RegisterEdit(module);
	RegisterGifAnim(module);
	RegisterHotKey(module);
	RegisterIPAddress(module);
	RegisterIPAddressEx(module);
	RegisterOption(module);
	RegisterProgress(module);
	RegisterRing(module);
	RegisterRollText(module);
	RegisterQrControl(module);

	RegisterContainer(module);
	RegisterCombo(module);
	RegisterComboBox(module);
	RegisterHorizontalLayout(module);
	RegisterVerticalLayout(module);
	RegisterChildLayout(module);
	RegisterTileLayout(module);
	RegisterGroupBox(module);
	RegisterTabLayout(module);
	RegisterAnimationTabLayout(module);
	RegisterList(module);
	RegisterListElement(module);
	RegisterListContainerElement(module);
	RegisterMenu(module);
	RegisterRichEdit(module);
	RegisterScrollBar(module);
	RegisterTreeNode(module);
	RegisterTreeView(module);

	RegisterStorage(module);
	RegisterFileDownload(module);

	context_->SetLogFunc([this](const std::string& msg) {
		Print(msg.c_str(), msg.length());
		});

	ThreadManager::Instance()->RegisterUITaskHandler([this](std::function<void()> task) {
		manager_->PostTask(task);
		});
	return true;
}

bool JsEngine::Excute(const char* input, const char* filename) {
	assert(context_);
	auto value = context_->Excute(input, strlen(input), filename);
	if (value.IsException()) {
		context_->DumpError();
		return false;
	}
	return true;
}

void JsEngine::RunLoop() {
	assert(context_);
	MSG msg = { 0 };
	while (::GetMessage(&msg, NULL, 0, 0)) {
		if (!CPaintManagerUI::TranslateMessage(&msg)) {
			::TranslateMessage(&msg);
			try {
				::DispatchMessage(&msg);
				context_->ExecuteJobs();
			}
			catch (...) {
				DUITRACE(_T("EXCEPTION: %s(%d)\n"), __FILET__, __LINE__);
#ifdef _DEBUG
				throw "CPaintManagerUI::MessageLoop";
#endif
			}
		}
	}

}

void JsEngine::PostTask(js_task_t task) {
	manager_->PostTask(std::move(task));
}

uint32_t JsEngine::PostDelayTask(js_task_t task, uint32_t delay, bool repeat) {
	if (!manager_)
		return 0;
	return manager_->PostDelayTask(std::move(task), delay,repeat);
}

void JsEngine::ResetDelayTask(uint32_t id, js_task_t task, uint32_t delay, bool repeat) {
	if (manager_)
		manager_->ResetDelayTask(id,std::move(task), delay, repeat);
}

bool JsEngine::CancelDelayTask(uint32_t id) {
	if (!manager_)
		return false;
	return manager_->CancelDelayTask(id);
}

JsEngine* JsEngine::get(qjs::Context& context) {
	return (JsEngine*)context.user_data();
}

void JsEngine::Print(const char* str, size_t len) {
	auto debug = context_->Global().GetProperty("print");
	if (debug.IsFunction()) {
		debug.Call(context_->NewString(str, len));
	}
}


}//namespace
