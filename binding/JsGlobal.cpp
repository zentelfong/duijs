#include "Util.h"
#include "JsWindow.h"
#include <Locale.h>

namespace duijs {

//全局函数位于DuiLib模块中

static Value getInstancePath(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::GetInstancePath());
}

static Value getCurrentPath(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::GetCurrentPath());
}

static Value getResourcePath(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::GetResourcePath());
}

static Value getResourceZip(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::GetResourceZip());
}

static Value getResourceZipPwd(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::GetResourceZipPwd());
}

static Value isCachedResourceZip(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::IsCachedResourceZip());
}

static Value setCurrentPath(Context& context, ArgList& args) {
	auto path = args[0].ToString();
	CPaintManagerUI::SetCurrentPath(CDuiString(path.str(), path.len()));
	return undefined_value;
}

static Value setResourcePath(Context& context, ArgList& args) {
	auto path = args[0].ToString();
	CPaintManagerUI::SetResourcePath(CDuiString(path.str(), path.len()));
	return undefined_value;
}

static Value setResourceZip(Context& context, ArgList& args) {

	if (args.size() == 3) {
		auto path = args[0].ToString();
		auto pwd = args[1].ToString();
		CPaintManagerUI::SetResourceZip(CDuiString(path.str(), path.len()),
			args[2].ToBool(), CDuiString(pwd.str(), pwd.len()));
	}
	else if (args.size() == 2) {
		auto path = args[0].ToString();
		auto pwd = args[1].ToString();
		CPaintManagerUI::SetResourceZip(CDuiString(path.str(), path.len()), false,
			CDuiString(pwd.str(), pwd.len()));
	}
	else {
		auto path = args[0].ToString();
		CPaintManagerUI::SetResourceZip(CDuiString(path.str(), path.len()), false);
	}
	return undefined_value;
}

static Value setResourceType(Context& context, ArgList& args) {
	CPaintManagerUI::SetResourceType(args[0].ToInt32());
	return undefined_value;
}

static Value getResourceType(Context& context, ArgList& args) {
	return toValue(context, CPaintManagerUI::GetResourceType());
}

static Value reloadSkin(Context& context, ArgList& args) {
	CPaintManagerUI::ReloadSkin();
	return undefined_value;
}

static Value loadPlugin(Context& context, ArgList& args) {
	auto path = args[0].ToString();
	bool rslt = CPaintManagerUI::LoadPlugin(CDuiString(path.str(), path.len()));
	return context.NewBool(rslt);
}

static Value postQuitMessage(Context& context, ArgList& args) {
	PostQuitMessage(args[0].ToInt32());
	return undefined_value;
}

static Value runGC(Context& context, ArgList& args) {
	context.RunGC();
	return undefined_value;
}


static Value messageBox(Context& context, ArgList& args) {
	int rslt = 0;
	if (args[0].IsObject()) {
		JsWindow* wnd = Class<JsWindow>::ToC(args[0]);
		JsString text(args[1]);
		JsString caption(args[2]);
		rslt = MessageBox(wnd?wnd->GetHWND():nullptr, text,caption,args[3].ToUint32());
	}
	else {
		JsString text(args[0]);
		JsString caption(args[1]);
		rslt = MessageBox(nullptr, text, caption, args[2].ToUint32());
	}
	return context.NewInt32(rslt);
}

static Value setAllDPI(Context& context, ArgList& args) {
	CPaintManagerUI::SetAllDPI(args[0].ToInt32());
	return undefined_value;
}

static Value showConsole(Context& context, ArgList& args) {
	setlocale(LC_ALL, "chs");
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
	freopen("CONOUT$", "w+t", stderr);
	return undefined_value;
}


static Value getCommandLines(Context& context, ArgList& args) {

	int nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

	auto list = context.NewArray();
	for (int i = 0; i < nArgs; ++i) {
		list.SetProperty(i, toValue(context, szArglist[i]));
	}
	return list;
}


static Value exec(Context& context, ArgList& args) {
	if (args[0].IsString()) {
		auto str = args[0].ToString();
		return context.Excute(str.str(), str.len(),"<exec>");
	}
	return undefined_value;
}

static Value execFile(Context& context, ArgList& args) {
	if (args[0].IsString()) {
		auto file = args[0].ToString();
		
		DWORD buf_len;
		BYTE* buf;

#if _UNICODE
		TCHAR errorMsg[64];
		TCHAR* name = a2w(file.str(), CP_UTF8);
		buf = CResourceManager::LoadFile(name, &buf_len, errorMsg);
		delete[] name;
#else
		buf = CResourceManager::LoadFile(module_name, &buf_len, errorMsg);
#endif

		if (!buf) {
			return context.ThrowInternalError("cant load js:%s",file.str());
		}
		auto rtn = context.Excute((char*)buf, buf_len, file.str());
		delete[] buf;
		return rtn;
	}
	return undefined_value;
}



static Value getAppDataPath(Context& context, ArgList& args) {
	if (args[0].IsString()) {
		JsString name(args[0]);

		TCHAR path[MAX_PATH];
		if (SHGetSpecialFolderPath(NULL, path, CSIDL_LOCAL_APPDATA, TRUE)) {
			CDuiString appPath = path;
			appPath.Append(_T("\\"));
			appPath.Append(name);
			appPath.Append(_T("\\"));

			if (_taccess(appPath, 0) == -1) {
				_tmkdir(appPath);
			}
			return toValue(context, appPath);
		}
	}
	return undefined_value;
}

static Value loadLanguage(Context& context, ArgList& args) {
	if (args[0].IsString()) {
		JsString xml(args[0]);
		bool rslt = CResourceManager::GetInstance()->LoadLanguage(xml);
		return context.NewBool(rslt);
	}
	return undefined_value;
}

//清空文本缓存，需要调用loadLanguage重新加载
static Value resetTextMap(Context& context, ArgList& args) {
	CResourceManager::GetInstance()->ResetTextMap();
	return undefined_value;
}

static Value reloadText(Context& context, ArgList& args) {
	CResourceManager::GetInstance()->ReloadText();
	return undefined_value;
}

#define ADD_GLOBAL_FUNCTION(name) module->ExportFunc<name>(#name);


void RegisterGlobal(Module* module) {
	ADD_GLOBAL_FUNCTION(getInstancePath);
	ADD_GLOBAL_FUNCTION(getCurrentPath);
	ADD_GLOBAL_FUNCTION(getResourcePath);
	ADD_GLOBAL_FUNCTION(getResourceZip);
	ADD_GLOBAL_FUNCTION(getResourceZipPwd);
	ADD_GLOBAL_FUNCTION(isCachedResourceZip);
	ADD_GLOBAL_FUNCTION(setCurrentPath);
	ADD_GLOBAL_FUNCTION(setResourcePath);
	ADD_GLOBAL_FUNCTION(setResourceZip);
	ADD_GLOBAL_FUNCTION(setResourceType);
	ADD_GLOBAL_FUNCTION(getResourceType);
	ADD_GLOBAL_FUNCTION(reloadSkin);
	ADD_GLOBAL_FUNCTION(loadPlugin);
	ADD_GLOBAL_FUNCTION(postQuitMessage);
	ADD_GLOBAL_FUNCTION(runGC);
	ADD_GLOBAL_FUNCTION(exec);
	ADD_GLOBAL_FUNCTION(execFile);
	ADD_GLOBAL_FUNCTION(messageBox);
	ADD_GLOBAL_FUNCTION(showConsole);
	ADD_GLOBAL_FUNCTION(getCommandLines);

	ADD_GLOBAL_FUNCTION(getAppDataPath);
	ADD_GLOBAL_FUNCTION(loadLanguage);
	ADD_GLOBAL_FUNCTION(resetTextMap);
	ADD_GLOBAL_FUNCTION(reloadText);
	ADD_GLOBAL_FUNCTION(setAllDPI);
	

}

}//namespace
