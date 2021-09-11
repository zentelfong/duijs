#include "Util.h"

namespace duijs {


static Value isHorizontal(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsHorizontal());
}

static Value setHorizontal(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetHorizontal(args[0].ToBool());
	return undefined_value;
}

static Value getScrollRange(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetScrollRange());
}

static Value setScrollRange(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetScrollRange(args[0].ToInt32());
	return undefined_value;
}

static Value getScrollPos(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetScrollPos());
}

static Value setScrollPos(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetScrollPos(args[0].ToInt32());
	return undefined_value;
}

static Value getLineSize(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLineSize());
}

static Value setLineSize(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetLineSize(args[0].ToInt32());
	return undefined_value;
}

static Value getShowButton1(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetShowButton1());
}

static Value setShowButton1(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowButton1(args[0].ToBool());
	return undefined_value;
}

static Value getButton1NormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton1NormalImage());
}

static Value setButton1NormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton1NormalImage(JsString(args[0]));
	return undefined_value;
}


static Value getButton1HotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton1HotImage());
}

static Value setButton1HotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton1HotImage(JsString(args[0]));
	return undefined_value;
}

static Value getButton1PushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton1PushedImage());
}

static Value setButton1PushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton1PushedImage(JsString(args[0]));
	return undefined_value;
}

static Value getButton1DisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton1DisabledImage());
}

static Value setButton1DisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton1DisabledImage(JsString(args[0]));
	return undefined_value;
}

static Value getShowButton2(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetShowButton2());
}

static Value setShowButton2(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowButton2(args[0].ToBool());
	return undefined_value;
}

static Value getButton2NormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton2NormalImage());
}

static Value setButton2NormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton2NormalImage(JsString(args[0]));
	return undefined_value;
}


static Value getButton2HotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton2HotImage());
}

static Value setButton2HotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton2HotImage(JsString(args[0]));
	return undefined_value;
}

static Value getButton2PushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton2PushedImage());
}

static Value setButton2PushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton2PushedImage(JsString(args[0]));
	return undefined_value;
}

static Value getButton2DisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetButton2DisabledImage());
}

static Value setButton2DisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetButton2DisabledImage(JsString(args[0]));
	return undefined_value;
}

static Value getThumbNormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetThumbNormalImage());
}

static Value setThumbNormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetThumbNormalImage(JsString(args[0]));
	return undefined_value;
}

static Value getThumbHotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetThumbHotImage());
}

static Value setThumbHotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetThumbHotImage(JsString(args[0]));
	return undefined_value;
}

static Value getThumbPushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetThumbPushedImage());
}

static Value setThumbPushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetThumbPushedImage(JsString(args[0]));
	return undefined_value;
}

static Value getThumbDisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetThumbDisabledImage());
}

static Value setThumbDisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetThumbDisabledImage(JsString(args[0]));
	return undefined_value;
}


static Value getRailNormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRailNormalImage());
}

static Value setRailNormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetRailNormalImage(JsString(args[0]));
	return undefined_value;
}


static Value getRailHotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRailHotImage());
}

static Value setRailHotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetRailHotImage(JsString(args[0]));
	return undefined_value;
}

static Value getRailPushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRailPushedImage());
}

static Value setRailPushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetRailPushedImage(JsString(args[0]));
	return undefined_value;
}

static Value getRailDisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRailDisabledImage());
}

static Value setRailDisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetRailDisabledImage(JsString(args[0]));
	return undefined_value;
}

static Value getBkNormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBkNormalImage());
}

static Value setBkNormalImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkNormalImage(JsString(args[0]));
	return undefined_value;
}

static Value getBkHotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBkHotImage());
}

static Value setBkHotImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkHotImage(JsString(args[0]));
	return undefined_value;
}

static Value getBkPushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBkPushedImage());
}

static Value setBkPushedImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkPushedImage(JsString(args[0]));
	return undefined_value;
}


static Value getBkDisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBkDisabledImage());
}

static Value setBkDisabledImage(CScrollBarUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkDisabledImage(JsString(args[0]));
	return undefined_value;
}


void RegisterScrollBar(qjs::Module* module) {
	DEFINE_CONTROL2(CScrollBarUI, CControlUI, "ScrollBar");
	ADD_FUNCTION(isHorizontal);
	ADD_FUNCTION(setHorizontal);
	ADD_FUNCTION(getScrollRange);
	ADD_FUNCTION(setScrollRange);
	ADD_FUNCTION(getScrollPos);
	ADD_FUNCTION(setScrollPos);
	ADD_FUNCTION(getLineSize);
	ADD_FUNCTION(setLineSize);
	ADD_FUNCTION(getShowButton1);
	ADD_FUNCTION(setShowButton1);
	ADD_FUNCTION(getButton1NormalImage);
	ADD_FUNCTION(setButton1NormalImage);
	ADD_FUNCTION(getButton1HotImage);
	ADD_FUNCTION(setButton1HotImage);
	ADD_FUNCTION(getButton1PushedImage);
	ADD_FUNCTION(setButton1PushedImage);
	ADD_FUNCTION(getButton1DisabledImage);
	ADD_FUNCTION(setButton1DisabledImage);
	ADD_FUNCTION(getShowButton2);
	ADD_FUNCTION(setShowButton2);
	ADD_FUNCTION(getButton2NormalImage);
	ADD_FUNCTION(setButton2NormalImage);
	ADD_FUNCTION(getButton2HotImage);
	ADD_FUNCTION(setButton2HotImage);
	ADD_FUNCTION(getButton2PushedImage);
	ADD_FUNCTION(setButton2PushedImage);
	ADD_FUNCTION(getButton2DisabledImage);
	ADD_FUNCTION(setButton2DisabledImage);
	ADD_FUNCTION(getThumbNormalImage);
	ADD_FUNCTION(setThumbNormalImage);
	ADD_FUNCTION(getThumbHotImage);
	ADD_FUNCTION(setThumbHotImage);
	ADD_FUNCTION(getThumbPushedImage);
	ADD_FUNCTION(setThumbPushedImage);
	ADD_FUNCTION(getThumbDisabledImage);
	ADD_FUNCTION(setThumbDisabledImage);
	ADD_FUNCTION(getRailNormalImage);
	ADD_FUNCTION(setRailNormalImage);
	ADD_FUNCTION(getRailHotImage);
	ADD_FUNCTION(setRailHotImage);
	ADD_FUNCTION(getRailPushedImage);
	ADD_FUNCTION(setRailPushedImage);
	ADD_FUNCTION(getRailDisabledImage);
	ADD_FUNCTION(setRailDisabledImage);
	ADD_FUNCTION(getBkNormalImage);
	ADD_FUNCTION(setBkNormalImage);
	ADD_FUNCTION(getBkHotImage);
	ADD_FUNCTION(setBkHotImage);
	ADD_FUNCTION(getBkPushedImage);
	ADD_FUNCTION(setBkPushedImage);
	ADD_FUNCTION(getBkDisabledImage);
	ADD_FUNCTION(setBkDisabledImage);
}


}//namespace
