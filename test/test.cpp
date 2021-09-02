#include "binding/JsEngine.h"

int main(int argc,const char* argv) {
	duijs::JsEngine engine;
	engine.Init();
	auto value = engine.Excute("import {} from '../js/test.js'", "<eval>");
	if (value.IsException()) {
		engine.DumpError();
	}
	engine.RunLoop();
	return 0;
}




