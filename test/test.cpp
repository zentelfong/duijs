#include "binding/JsEngine.h"
#include <objbase.h>
#include "Utils/CrashDump.h"

#if 0
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow){
#else
int main(int argc,const char* argv) {
#endif

	CrashDump crash_dump;
	CoInitialize(NULL);

	//CPaintManagerUI::SetInstance(hInstance);
	duijs::JsEngine engine;
	engine.Init();
	auto value = engine.Excute("import {} from '../js/test.js'", "<eval>");
	if (value.IsException()) {
		engine.DumpError();
	}
	engine.RunLoop();
	CoUninitialize();
	return 0;
}




