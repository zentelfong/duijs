#include "binding/JsEngine.h"
#include "async/thread.h"
#include <objbase.h>
#include "Utils/CrashDump.h"
#include "duilib/UIlib.h"

BOOL FileExist(const TCHAR* pszFileName)
{
	BOOL bExist = FALSE;
	HANDLE hFile;

	if (NULL != pszFileName)
	{
		// Use the preferred Win32 API call and not the older OpenFile.
		hFile = CreateFile(
			pszFileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			0);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			// If the handle is valid then the file exists.
			CloseHandle(hFile);
			bExist = TRUE;
		}
	}

	return (bExist);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow){
	CrashDump crash_dump;
	if (CoInitialize(NULL) != 0) {
		printf("CoInitialize error");
		return -1;
	}

	DuiLib::CPaintManagerUI::SetInstance(hInstance);

	int nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (nArgs == 2) {
		DuiLib::CPaintManagerUI::SetResourceZip(szArglist[1], true);
	} else {
		//º”‘ÿskin.zip
		DuiLib::CDuiString path = DuiLib::CPaintManagerUI::GetInstancePath() + _T("skin.zip");
		if (FileExist(path)) {
			DuiLib::CPaintManagerUI::SetResourceZip(path, true);
		} else {
			DuiLib::CPaintManagerUI::SetResourcePath(_T("../skin/"));
		}
	}


	duijs::JsEngine engine;
	engine.Init(szArglist, nArgs);
	LocalFree(szArglist);


	bool rslt = engine.Excute("import {} from 'debug.js'", "<eval>");
	if (!rslt) {
		return -1;
	}
	engine.RunLoop();

	ThreadManager::DestroyInstance();
	DuiLib::CPaintManagerUI::Term();
	CoUninitialize();
	return 0;
}




