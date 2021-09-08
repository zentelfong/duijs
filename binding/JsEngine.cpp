#include "duilib/UIlib.h"
#include "JsEngine.h"

namespace duijs {
using namespace qjs;
using namespace DuiLib;

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

JsEngine::JsEngine() 
	:runtime_(NULL),context_(NULL)
{

}


JsEngine::~JsEngine() {
	delete context_;
	delete runtime_;
}

bool JsEngine::Init() {
	assert(!runtime_);
	assert(!context_);
	runtime_ = new qjs::Runtime();
	context_ = new qjs::Context(runtime_);

	auto module = context_->NewModule("DuiLib");
	RegisterConst(module);
	RegisterWindow(module);
	RegisterPaintManager(module);
	RegisterDialogBuilder(module);

	RegisterControl(module);
	RegisterLabel(module);
	RegisterButton(module);
	RegisterText(module);
	RegisterDateTime(module);
	RegisterColorPalette(module);

	RegisterContainer(module);
	RegisterCombo(module);
	RegisterComboBox(module);
	
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

}//namespace
