#include "binding/JsEngine.h"
#include <objbase.h>
#include "Utils/CrashDump.h"
#include "duilib/UIlib.h"


#if 0
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow){
#else
int main(int argc,const char* argv) {
#endif
	CrashDump crash_dump;
	if (CoInitialize(NULL) != 0) {
		printf("CoInitialize error");
		return -1;
	}

	DuiLib::CPaintManagerUI::SetResourcePath(_T("../skin/"));

	duijs::JsEngine engine;
	engine.Init();

	bool rslt = engine.Excute("import {} from 'test.js'", "<eval>");
	if (!rslt) {
		return -1;
	}


	engine.PostTask([](qjs::Context* c) {
		printf("run task\n");
		});


	engine.PostDelayTask([](qjs::Context* c) {
		printf("run delay task\n");
	}, 5000);

	engine.RunLoop();
	CoUninitialize();
	return 0;
}




