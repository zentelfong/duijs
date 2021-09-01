#include "StdAfx.h"
#include "JsEngine.h"
#include "JsWindow.h"

namespace duijs {

using namespace DuiLib;

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

	return true;
}

qjs::Value JsEngine::Excute(const char* input, const char* filename) {
	return context_->Excute(input, strlen(input), filename);
}

void JsEngine::RunLoop() {

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
