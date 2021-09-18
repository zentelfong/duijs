#include "binding/JsEngine.h"
#include <objbase.h>
#include "Utils/CrashDump.h"
#include "duilib/UIlib.h"


//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow){
int main() {
	CrashDump crash_dump;
	if (CoInitialize(NULL) != 0) {
		printf("CoInitialize error");
		return -1;
	}

	//DuiLib::CPaintManagerUI::SetInstance(hInstance);

	int nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (nArgs == 2) {
		DuiLib::CPaintManagerUI::SetResourceZip(szArglist[1], true);
	} else {
		DuiLib::CPaintManagerUI::SetResourcePath(_T("../skin/"));
	}

	duijs::JsEngine engine;
	engine.Init();

	bool rslt = engine.Excute("import {} from 'debug.js'", "<eval>");
	if (!rslt) {
		return -1;
	}
	engine.RunLoop();
	CoUninitialize();
	return 0;
}




