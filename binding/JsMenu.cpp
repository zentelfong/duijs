#include "Util.h"
#include "JsWindow.h"


namespace duijs {


static Value create(CMenuWnd* pThis, Context& context, ArgList& args) {
	JsWindow* mainWnd = Class<JsWindow>::ToC(args[0]);
	if (!mainWnd) {
		return context.ThrowTypeError("arg0 needs window");
	}

	POINT point;
	if (!args[2].IsObject()) {
		GetCursorPos(&point);
	} else {
		point = toPoint(args[2]);
	}

	DWORD dwAlignment = eMenuAlignment_Left | eMenuAlignment_Top;
	if (args[3].IsNumber()) {
		dwAlignment = args[3].ToUint32();
	}

	CStdStringPtrMap* pMenuCheckInfo = nullptr;
	if (args[4].IsObject()) {
		auto properties = args[4].GetProperties();
		pMenuCheckInfo = new CStdStringPtrMap();
		for (auto pro : properties) {
			MenuItemInfo* info = new MenuItemInfo();
			CDuiString name(pro.first.c_str());
			lstrcpy(info->szName, name);
			info->bChecked = pro.second.ToBool();
			pMenuCheckInfo->Set(name, info);
		}
	}

	if (args[1].IsString()) {
		JsString name(args[1]);
		pThis->Init(NULL, STRINGorID(name), point, mainWnd->manager(), pMenuCheckInfo, dwAlignment);
	} else {
		pThis->Init(NULL, STRINGorID(args[1].ToUint32()), point, mainWnd->manager(), pMenuCheckInfo, dwAlignment);
	}

	delete pMenuCheckInfo;
	return undefined_value;
}


static Value close(CMenuWnd* pThis, Context& context, ArgList& args) {
	pThis->Close(args[0].ToUint32());
	return undefined_value;
}

static Value root(CMenuWnd* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetMenuUI());
}

static Value resizeMenu(CMenuWnd* pThis, Context& context, ArgList& args) {
	pThis->ResizeMenu();
	return undefined_value;
}

static Value resizeSubMenu(CMenuWnd* pThis, Context& context, ArgList& args) {
	pThis->ResizeSubMenu();
	return undefined_value;
}

static Value setDPI(CMenuWnd* pThis, Context& context, ArgList& args) {
	pThis->setDPI(args[0].ToInt32());
	return undefined_value;
}




static Value setLineType(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetLineType();
	return undefined_value;
}

static Value setLineColor(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetLineColor(args[0].ToUint32());
	return undefined_value;
}

static Value getLineColor(CMenuElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetLineColor());
}


static Value setLinePadding(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetLinePadding(toRect(args[0]));
	return undefined_value;
}

static Value getLinePadding(CMenuElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLinePadding());
}


static Value setIcon(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetIcon(JsString(args[0]));
	return undefined_value;
}

static Value setIconSize(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetIconSize(args[0].ToInt32(),args[1].ToInt32());
	return undefined_value;
}


static Value setChecked(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetChecked(args[0].ToBool());
	return undefined_value;
}

static Value getChecked(CMenuElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetChecked());
}

static Value setCheckItem(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetCheckItem(args[0].ToBool());
	return undefined_value;
}

static Value getCheckItem(CMenuElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCheckItem());
}

static Value setShowExplandIcon(CMenuElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowExplandIcon(args[0].ToBool());
	return undefined_value;
}


void RegisterMenu(qjs::Module* module) {
	{
		auto ctrl = module->ExportClass<CMenuWnd>("MenuWnd");
		ctrl.Init(nullptr);

		ADD_FUNCTION(create);
		ADD_FUNCTION(close);

		ADD_FUNCTION(root);
		ADD_FUNCTION(resizeMenu);
		ADD_FUNCTION(resizeSubMenu);
		ADD_FUNCTION(setDPI);

	}


	{
		DEFINE_CONTROL2(CMenuUI, CListUI, "Menu");
	}

	{

		DEFINE_CONTROL2(CMenuElementUI, CListContainerElementUI, "MenuElement");
		ADD_FUNCTION(setLineType);
		ADD_FUNCTION(setLineColor);
		ADD_FUNCTION(getLineColor);
		ADD_FUNCTION(setLinePadding);
		ADD_FUNCTION(getLinePadding);
		ADD_FUNCTION(setIcon);
		ADD_FUNCTION(setIconSize);
		ADD_FUNCTION(setChecked);
		ADD_FUNCTION(setCheckItem);
		ADD_FUNCTION(getCheckItem);
		ADD_FUNCTION(setShowExplandIcon);
	}

}


}//namespace
