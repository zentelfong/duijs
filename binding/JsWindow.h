#pragma once
#include "quickjs/qjs.h"
#include "Utils/WinImplBase.h"

namespace duijs {

using namespace DuiLib;

class JsWindow:public WindowImplBase {
public:
	JsWindow(qjs::Context* context, qjs::Value& this_obj);
	~JsWindow();

	void Mark(JS_MarkFunc* mark_func);

protected:
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual CDuiString GetSkinFile();
	virtual void InitResource();
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
	virtual void Notify(TNotifyUI& msg);

private:
	qjs::Context* context_;
	qjs::Value this_;
};


void RegisterWindow(qjs::Module* module);

}//namespace
