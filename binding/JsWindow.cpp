#include "JsWindow.h"

namespace duijs {


JsWindow::JsWindow(qjs::Context* context)
	:events_(context->NewObject())
{

}

JsWindow::~JsWindow() {

}


void JsWindow::Mark(JS_MarkFunc* mark_func) {
	events_.Mark(mark_func);
}



static JsWindow* newWindow(Context& context,ArgList& args) {
	return new JsWindow();
}


static void deleteWindow(JsWindow* w) {
}


void RegisterWindow(qjs::Module* module) {

	auto window = module->ExportClass<JsWindow>("Window");
	window.Init<deleteWindow>();
	window.AddCtor<newWindow>();

}





}//namespace


