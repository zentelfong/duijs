#include "Util.h"
#include "JsWindow.h"

namespace duijs {

static CTrayIcon* createTray(qjs::Context& context, qjs::ArgList& args) {
	return new CTrayIcon();
}

static void deleteTray(CTrayIcon* w) {
	delete w;
}

static Value createTrayIcon(CTrayIcon* pThis, Context& context, ArgList& args) {
	JsWindow* window = Class<JsWindow>::ToC(args[0]);
	if (!window) {
		return context.ThrowTypeError("arg0 need window");
	}

	pThis->CreateTrayIcon(*window,args[1].ToInt32(),JsString(args[2]), args[3].ToInt32());
	return undefined_value;
}

static Value deleteTrayIcon(CTrayIcon* pThis, Context& context, ArgList& args) {
	pThis->DeleteTrayIcon();
	return undefined_value;
}

static Value setTooltipText(CTrayIcon* pThis, Context& context, ArgList& args) {

	if (args[0].IsString()) {
		auto tip = args[0].ToString();
		pThis->SetTooltipText(CDuiString(tip.str(), tip.len()));
	} else {
		pThis->SetTooltipText(args[0].ToUint32());
	}
	return undefined_value;
}


static Value getTooltipText(CTrayIcon* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTooltipText());
}


static Value setIcon(CTrayIcon* pThis, Context& context, ArgList& args) {
	bool rslt;
	if (args[0].IsString()) {
		auto file = args[0].ToString();
		rslt = pThis->SetIcon(CDuiString(file.str(), file.len()));
	}
	else {
		rslt = pThis->SetIcon(args[0].ToUint32());
	}
	return context.NewBool(rslt);
}

static Value setHideIcon(CTrayIcon* pThis, Context& context, ArgList& args) {
	pThis->SetHideIcon();
	return undefined_value;
}

static Value setShowIcon(CTrayIcon* pThis, Context& context, ArgList& args) {
	pThis->SetShowIcon();
	return undefined_value;
}

static Value removeIcon(CTrayIcon* pThis, Context& context, ArgList& args) {
	pThis->RemoveIcon();
	return undefined_value;
}

static Value enabled(CTrayIcon* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->Enabled());
}

static Value isVisible(CTrayIcon* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsVisible());
}


void RegisterTrayIcon(qjs::Module* module) {
	auto ctrl = module->ExportClass<CTrayIcon>("TrayIcon");
	ctrl.Init<deleteTray>();
	ctrl.AddCtor<createTray>();
	ADD_FUNCTION(createTrayIcon);
	ADD_FUNCTION(deleteTrayIcon);
	ADD_FUNCTION(setTooltipText);
	ADD_FUNCTION(getTooltipText);
	ADD_FUNCTION(setIcon);
	ADD_FUNCTION(setHideIcon);

	ADD_FUNCTION(setShowIcon);
	ADD_FUNCTION(removeIcon);
	ADD_FUNCTION(enabled);
	ADD_FUNCTION(isVisible);
}


}//namespace

