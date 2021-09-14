#include "binding/JsEngine.h"
#include <objbase.h>
#include "Utils/CrashDump.h"
#include "duilib/UIlib.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow){

	CrashDump crash_dump;
	if (CoInitialize(NULL) != 0) {
		printf("CoInitialize error");
		return -1;
	}

	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(_T("../skin/"));

	duijs::JsEngine engine;
	engine.Init();

	bool rslt = engine.Excute("import {} from 'test.js'", "<eval>");
	if (!rslt) {
		return -1;
	}
	engine.RunLoop();
	CoUninitialize();
	return 0;
}




