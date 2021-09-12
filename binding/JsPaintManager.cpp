#include "Util.h"

namespace duijs {

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


static Value getRoot(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRoot());
}

static Value findControl(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	if (args[0].IsString()) {
		auto str = args[0].ToString();
		return toValue(context, pThis->FindControl(CDuiString(str.str(), str.len())));
	}
	return toValue(context, pThis->FindControl(toPoint(args[0])));
}

static Value findSubControlByPoint(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	CControlUI* parent = toControl(args[0]);
	return toValue(context, pThis->FindSubControlByPoint(parent,toPoint(args[1])));
}

static Value findSubControlByName(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	CControlUI* parent = toControl(args[0]);

	auto str = args[1].ToString();
	return toValue(context, 
		pThis->FindSubControlByName(parent, CDuiString(str.str(), str.len())));
}

static Value findSubControlByClass(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	CControlUI* parent = toControl(args[0]);
	auto str = args[1].ToString();
	return toValue(context,
		pThis->FindSubControlByClass(parent, CDuiString(str.str(), str.len()),args[2].ToInt32()));

}

static Value findSubControlsByClass(CPaintManagerUI* pThis, Context& context, ArgList& args) {
	CControlUI* parent = toControl(args[0]);
	auto str = args[1].ToString();
	CStdPtrArray* list = pThis->FindSubControlsByClass(parent, CDuiString(str.str(), str.len()));

	auto js_list = context.NewArray();
	for (int i = 0; i < list->GetSize(); ++i) {
		CControlUI* ctrl = (CControlUI*)list->GetAt(i);
		js_list.SetProperty(i, toValue(context,ctrl));
	}
	return js_list;
}




void RegisterPaintManager(Module* module) {

	DEFINE_CONTROL(CPaintManagerUI, "PaintManager");

	ADD_FUNCTION(isUpdateNeeded);
	ADD_FUNCTION(needUpdate);
	ADD_FUNCTION(invalidate);
	ADD_FUNCTION(getName);
	ADD_FUNCTION(getHoverTime);

	ADD_FUNCTION(getMousePos);
	ADD_FUNCTION(getClientSize);
	ADD_FUNCTION(getInitSize);
	ADD_FUNCTION(getSizeBox);
	ADD_FUNCTION(setSizeBox);
	ADD_FUNCTION(getCaptionRect);
	ADD_FUNCTION(setCaptionRect);
	ADD_FUNCTION(getRoundCorner);
	ADD_FUNCTION(setRoundCorner);
	ADD_FUNCTION(getMinInfo);
	ADD_FUNCTION(setMinInfo);
	ADD_FUNCTION(getMaxInfo);
	ADD_FUNCTION(setMaxInfo);
	ADD_FUNCTION(isShowUpdateRect);
	ADD_FUNCTION(setShowUpdateRect);
	ADD_FUNCTION(isNoActivate);
	ADD_FUNCTION(setNoActivate);

	ADD_FUNCTION(getOpacity);
	ADD_FUNCTION(setOpacity);
	ADD_FUNCTION(isLayered);
	ADD_FUNCTION(setLayered);
	ADD_FUNCTION(getLayeredInset);
	ADD_FUNCTION(setLayeredInset);
	ADD_FUNCTION(getLayeredOpacity);
	ADD_FUNCTION(setLayeredOpacity);
	ADD_FUNCTION(getLayeredImage);
	ADD_FUNCTION(setLayeredImage);
	ADD_FUNCTION(isUseGdiplusText);
	ADD_FUNCTION(setUseGdiplusText);

	ADD_FUNCTION(getGdiplusTextRenderingHint);
	ADD_FUNCTION(setGdiplusTextRenderingHint);
	ADD_FUNCTION(getRoot);
	ADD_FUNCTION(findControl);
	ADD_FUNCTION(findSubControlByPoint);
	ADD_FUNCTION(findSubControlByName);
	ADD_FUNCTION(findSubControlByClass);
	ADD_FUNCTION(findSubControlsByClass);
}


}//namespace

