#pragma once
#include "quickjs/qjs.h"
#include "Utils/WinImplBase.h"

namespace duijs {

using namespace DuiLib;
using namespace qjs;

class JsWindow:public WindowImplBase {
public:
	JsWindow(qjs::Context* context);
	~JsWindow();

	void Mark(JS_MarkFunc* mark_func);


private:
	qjs::Value events_;
};


}//namespace
