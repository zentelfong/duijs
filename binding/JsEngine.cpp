#include "StdAfx.h"
#include "JsEngine.h"

namespace duijs {
using namespace qjs;
using namespace DuiLib;

extern void RegisterPaintManager(Module* module);
extern void RegisterWindow(qjs::Module* module);
extern void RegisterControl(qjs::Module* module);

JsEngine::JsEngine() 
	:runtime_(NULL),context_(NULL)
{

}


JsEngine::~JsEngine() {
	delete context_;
	delete runtime_;
}

bool JsEngine::Init() {
	runtime_ = new qjs::Runtime();
	context_ = new qjs::Context(runtime_);

	auto module = context_->NewModule("DuiLib");
	RegisterWindow(module);
	RegisterPaintManager(module);
	RegisterControl(module);
	return true;
}

qjs::Value JsEngine::Excute(const char* input, const char* filename) {
	assert(context_);
	return context_->Excute(input, strlen(input), filename);
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
