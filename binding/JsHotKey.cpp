#include "Util.h"

namespace duijs {


static Value getNormalImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetNormalImage());
}

static Value setNormalImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetNormalImage(CDuiString(str.str(),str.len()));
	return undefined_value;
}

static Value getHotImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotImage());
}

static Value setHotImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetHotImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value getFocusedImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFocusedImage());
}

static Value setFocusedImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetFocusedImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getDisabledImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledImage());
}

static Value setDisabledImage(CHotKeyUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetDisabledImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getNativeBkColor(CHotKeyUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetNativeBkColor());
}

static Value setNativeBkColor(CHotKeyUI* pThis, Context& context, ArgList& args) {
	pThis->SetNativeBkColor(args[0].ToUint32());
	return undefined_value;
}


static Value getHotKey(CHotKeyUI* pThis, Context& context, ArgList& args) {
	WORD wVirtualKeyCode;
	WORD wModifiers;
	pThis->GetHotKey(wVirtualKeyCode, wModifiers);
	auto rslt = context.NewObject();
	rslt.SetPropertyInt32("keycode", wVirtualKeyCode);
	rslt.SetPropertyInt32("modifiers", wModifiers);
	return rslt;
}

static Value setHotKey(CHotKeyUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotKey(args[0].ToUint32(), args[1].ToUint32());
	return undefined_value;
}




void RegisterHotKey(qjs::Module* module) {
	DEFINE_CONTROL2(CHotKeyUI, CLabelUI, "HotKey");
	ADD_FUNCTION(getNormalImage);
	ADD_FUNCTION(setNormalImage);
	ADD_FUNCTION(getHotImage);
	ADD_FUNCTION(setHotImage);
	ADD_FUNCTION(getFocusedImage);
	ADD_FUNCTION(setFocusedImage);
	ADD_FUNCTION(getDisabledImage);
	ADD_FUNCTION(setDisabledImage);

	ADD_FUNCTION(getNativeBkColor);
	ADD_FUNCTION(setNativeBkColor);
	ADD_FUNCTION(getHotKey);
	ADD_FUNCTION(setHotKey);
}


}//namespace
