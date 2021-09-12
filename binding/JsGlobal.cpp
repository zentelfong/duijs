#include "Util.h"

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
}

}//namespace
