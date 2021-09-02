#include "StdAfx.h"
#include "quickjs/qjs.h"
#include "Util.h"

namespace duijs {
using namespace qjs;
using namespace DuiLib;


static CPaintManagerUI* newPaintManager(Context& context, Value& this_obj, ArgList& args) {
	return new CPaintManagerUI();
}

static void deletePaintManager(CPaintManagerUI* w) {
}


static Value isUpdateNeeded(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->IsUpdateNeeded());
}

static Value needUpdate(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->NeedUpdate();
	return undefined_value;
}

static Value invalidate(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	if (args[0].IsObject()) {
		RECT rc = toRect(args[0]);
		pThis->Invalidate(rc);
	}
	else {
		pThis->Invalidate();
	}
	return undefined_value;
}

static Value getName(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetName());
}

static Value getHoverTime(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetHoverTime());
}

static Value setHoverTime(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetHoverTime(args[0].ToInt32());
	return undefined_value;
}


static Value getMousePos(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetMousePos());
}

static Value getClientSize(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetClientSize());
}

static Value getInitSize(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetInitSize());
}

static Value getSizeBox(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSizeBox());
}

static Value setSizeBox(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetSizeBox(toRect(args[0]));
	return undefined_value;
}


static Value getCaptionRect(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCaptionRect());
}

static Value setCaptionRect(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetCaptionRect(toRect(args[0]));
	return undefined_value;
}

static Value getRoundCorner(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRoundCorner());
}

static Value setRoundCorner(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetRoundCorner(args[0].ToInt32(),args[1].ToInt32());
	return undefined_value;
}


static Value getMinInfo(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMinInfo());
}

static Value setMinInfo(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetMinInfo(args[0].ToInt32(), args[1].ToInt32());
	return undefined_value;
}

static Value getMaxInfo(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMaxInfo());
}

static Value setMaxInfo(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetMaxInfo(args[0].ToInt32(), args[1].ToInt32());
	return undefined_value;
}

static Value isShowUpdateRect(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsShowUpdateRect());
}

static Value setShowUpdateRect(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowUpdateRect(args[0].ToBool());
	return undefined_value;
}


static Value isNoActivate(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsNoActivate());
}

static Value setNoActivate(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetNoActivate(args[0].ToBool());
	return undefined_value;
}


static Value getOpacity(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (int)pThis->GetOpacity());
}

static Value setOpacity(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetOpacity((BYTE)args[0].ToInt32());
	return undefined_value;
}

static Value isLayered(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsLayered());
}

static Value setLayered(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetLayered(args[0].ToBool());
	return undefined_value;
}


static Value getLayeredInset(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLayeredInset());
}

static Value setLayeredInset(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetLayeredInset(toRect(args[0]));
	return undefined_value;
}


static Value getLayeredOpacity(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (int)pThis->GetLayeredOpacity());
}

static Value setLayeredOpacity(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetLayeredOpacity((BYTE)args[0].ToInt32());
	return undefined_value;
}

static Value getLayeredImage(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetLayeredImage());
}

static Value setLayeredImage(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetLayeredImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value isUseGdiplusText(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsUseGdiplusText());
}

static Value setUseGdiplusText(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetUseGdiplusText(args[0].ToBool());
	return undefined_value;
}

static Value getGdiplusTextRenderingHint(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetGdiplusTextRenderingHint());
}

static Value setGdiplusTextRenderingHint(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	pThis->SetGdiplusTextRenderingHint(args[0].ToInt32());
	return undefined_value;
}


void RegisterPaintManager(Module* module) {
	auto mgr = module->ExportClass<CPaintManagerUI>("PaintManager");
	mgr.Init<deletePaintManager>();
	mgr.AddFunc<isUpdateNeeded>("isUpdateNeeded");
	mgr.AddFunc<needUpdate>("needUpdate");
	mgr.AddFunc<invalidate>("invalidate");
	mgr.AddFunc<getName>("getName");
	mgr.AddFunc<getHoverTime>("getHoverTime");

	mgr.AddFunc<getMousePos>("getMousePos");
	mgr.AddFunc<getClientSize>("getClientSize");
	mgr.AddFunc<getInitSize>("getInitSize");
	mgr.AddFunc<getSizeBox>("getSizeBox");
	mgr.AddFunc<setSizeBox>("setSizeBox");
	mgr.AddFunc<getCaptionRect>("getCaptionRect");
	mgr.AddFunc<setCaptionRect>("setCaptionRect");
	mgr.AddFunc<getRoundCorner>("getRoundCorner");
	mgr.AddFunc<setRoundCorner>("setRoundCorner");
	mgr.AddFunc<getMinInfo>("getMinInfo");
	mgr.AddFunc<setMinInfo>("setMinInfo");
	mgr.AddFunc<getMaxInfo>("getMaxInfo");
	mgr.AddFunc<setMaxInfo>("setMaxInfo");
	mgr.AddFunc<isShowUpdateRect>("isShowUpdateRect");
	mgr.AddFunc<setShowUpdateRect>("setShowUpdateRect");
	mgr.AddFunc<isNoActivate>("isNoActivate");
	mgr.AddFunc<setNoActivate>("setNoActivate");

	mgr.AddFunc<getOpacity>("getOpacity");
	mgr.AddFunc<setOpacity>("setOpacity");
	mgr.AddFunc<isLayered>("isLayered");
	mgr.AddFunc<setLayered>("setLayered");
	mgr.AddFunc<getLayeredInset>("getLayeredInset");
	mgr.AddFunc<setLayeredInset>("setLayeredInset");
	mgr.AddFunc<getLayeredOpacity>("getLayeredOpacity");
	mgr.AddFunc<setLayeredOpacity>("setLayeredOpacity");
	mgr.AddFunc<getLayeredImage>("getLayeredImage");
	mgr.AddFunc<setLayeredImage>("setLayeredImage");
	mgr.AddFunc<isUseGdiplusText>("isUseGdiplusText");
	mgr.AddFunc<setUseGdiplusText>("setUseGdiplusText");

	mgr.AddFunc<getGdiplusTextRenderingHint>("getGdiplusTextRenderingHint");
	mgr.AddFunc<setGdiplusTextRenderingHint>("setGdiplusTextRenderingHint");
}


}//namespace

