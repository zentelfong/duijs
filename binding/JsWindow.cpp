#include "JsWindow.h"

namespace duijs {
using namespace qjs;

JsWindow::JsWindow(Context* context, Value& this_obj)
	:context_(context),this_(this_obj)
{

}

JsWindow::~JsWindow() {
}


void JsWindow::Mark(JS_MarkFunc* mark_func) {

}


LPCTSTR JsWindow::GetWindowClassName(void) const {
	return _T("DUIJS");
}

CDuiString JsWindow::GetSkinFile() {
	Value result = this_.Invoke("getSkinFile");
	if (result.IsException()) {
		context_->DumpError();
	}
	auto str = result.ToString();
	return CDuiString(str.str(),str.len());
}

void JsWindow::InitResource() {
	if (this_.HasProperty("initResource")) {
		Value result = this_.Invoke("initResource");
		if (result.IsException()) {
			context_->DumpError();
		}
	}
}

void JsWindow::InitWindow() {
	if (this_.HasProperty("initWindow")) {
		Value result = this_.Invoke("initWindow");
		if (result.IsException()) {
			context_->DumpError();
		}
	}
}

void JsWindow::OnFinalMessage(HWND hWnd) {

	this_ = undefined_value;
}

void JsWindow::Notify(TNotifyUI& msg) {


}

//////////////////////////////////////////////////////////////////////

static JsWindow* newWindow(Context& context,Value& this_obj, ArgList& args) {
	return new JsWindow(&context, this_obj);
}

static void deleteWindow(JsWindow* w) {
	delete w;
}

static void markWindow(JsWindow* pThis, JS_MarkFunc* mark_func) {
	pThis->Mark(mark_func);
}

static Value createWindow(JsWindow* pThis, Context& context, ArgList& args) {
	JsWindow* parent = Class<JsWindow>::ToC(args[0]);
	auto name = args[1].ToString();
	HWND hWnd = pThis->CreateDuiWindow(parent? parent->GetHWND():NULL,
		CDuiString(name.str(),name.len()), args[2].ToUint32(),args[3].ToUint32());
	return context.NewBool(hWnd != NULL);
}

static Value closeWindow(JsWindow* pThis, Context& context, ArgList& args) {
	if(args.size() == 1)
		pThis->Close(args[0].ToUint32());
	else
		pThis->Close();
	return undefined_value;
}

void RegisterWindow(qjs::Module* module) {
	auto window = module->ExportClass<JsWindow>("Window");
	window.Init2<deleteWindow, markWindow>();
	window.AddCtor2<newWindow>();
	window.AddFunc<createWindow>("create");
	window.AddReleaseFunc<closeWindow>("close");

}

}//namespace


