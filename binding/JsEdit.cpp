#include "Util.h"

namespace duijs {


static Value setMaxChar(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetMaxChar(args[0].ToUint32());
	return null_value;
}

static Value getMaxChar(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetMaxChar());
}


static Value setReadOnly(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetReadOnly(args[0].ToBool());
	return null_value;
}

static Value isReadOnly(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsReadOnly());
}

static Value setPasswordMode(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetPasswordMode(args[0].ToBool());
	return null_value;
}

static Value isPasswordMode(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsPasswordMode());
}


static Value setPasswordChar(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	if(str.len())
		pThis->SetPasswordChar(str.str()[0]);
	return null_value;
}

static Value getPasswordChar(CEditUI* pThis, Context& context, ArgList& args) {
	TCHAR str[2];
	str[0] = pThis->GetPasswordChar();
	str[1] = '\0';
	return toValue(context, str);
}

static Value setNumberOnly(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetNumberOnly(args[0].ToBool());
	return null_value;
}

static Value isNumberOnly(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsNumberOnly());
}

static Value getWindowStyls(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetWindowStyls());
}

static Value getNormalImage(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetNormalImage());
}

static Value setNormalImage(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetNormalImage(CDuiString(str.str(),str.len()));
	return null_value;
}

static Value getHotImage(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotImage());
}

static Value setHotImage(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetHotImage(CDuiString(str.str(), str.len()));
	return null_value;
}

static Value getFocusedImage(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFocusedImage());
}

static Value setFocusedImage(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetFocusedImage(CDuiString(str.str(), str.len()));
	return null_value;
}

static Value getDisabledImage(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledImage());
}

static Value setDisabledImage(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetDisabledImage(CDuiString(str.str(), str.len()));
	return null_value;
}


static Value setNativeEditBkColor(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetNativeEditBkColor(args[0].ToUint32());
	return null_value;
}

static Value getNativeEditBkColor(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(uint32_t)pThis->GetNativeEditBkColor());
}

static Value setNativeEditTextColor(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetNativeEditTextColor(args[0].ToUint32());
	return null_value;
}

static Value getNativeEditTextColor(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetNativeEditTextColor());
}


static Value setAutoSelAll(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoSelAll(args[0].ToBool());
	return null_value;
}

static Value isAutoSelAll(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsAutoSelAll());
}

static Value setSel(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetSel(args[0].ToInt32(), args[1].ToInt32());
	return null_value;
}

static Value setSelAll(CEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelAll();
	return null_value;
}

static Value setReplaceSel(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetReplaceSel(CDuiString(str.str(), str.len()));
	return null_value;
}

static Value setTipValue(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetTipValue(CDuiString(str.str(), str.len()));
	return null_value;
}


static Value getTipValue(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTipValue());
}


static Value setTipValueColor(CEditUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetTipValueColor(CDuiString(str.str(), str.len()));
	return null_value;
}

static Value getTipValueColor(CEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetTipValueColor());
}



void RegisterEdit(qjs::Module* module) {
	DEFINE_CONTROL2(CEditUI, CLabelUI, "Edit");
	ADD_FUNCTION(setMaxChar);
	ADD_FUNCTION(getMaxChar);
	ADD_FUNCTION(setReadOnly);
	ADD_FUNCTION(isReadOnly);
	ADD_FUNCTION(setPasswordMode);
	ADD_FUNCTION(isPasswordMode);
	ADD_FUNCTION(setPasswordChar);
	ADD_FUNCTION(getPasswordChar);
	ADD_FUNCTION(setNumberOnly);
	ADD_FUNCTION(isNumberOnly);
	ADD_FUNCTION(getWindowStyls);
	ADD_FUNCTION(getNormalImage);
	ADD_FUNCTION(setNormalImage);
	ADD_FUNCTION(getHotImage);
	ADD_FUNCTION(setHotImage);
	ADD_FUNCTION(getFocusedImage);
	ADD_FUNCTION(setFocusedImage);
	ADD_FUNCTION(getDisabledImage);
	ADD_FUNCTION(setDisabledImage);
	ADD_FUNCTION(setNativeEditBkColor);
	ADD_FUNCTION(getNativeEditBkColor);
	ADD_FUNCTION(setNativeEditTextColor);
	ADD_FUNCTION(getNativeEditTextColor);
	ADD_FUNCTION(setAutoSelAll);
	ADD_FUNCTION(isAutoSelAll);
	ADD_FUNCTION(setSel);
	ADD_FUNCTION(setSelAll);
	ADD_FUNCTION(setReplaceSel);
	ADD_FUNCTION(setTipValue);
	ADD_FUNCTION(getTipValue);
	ADD_FUNCTION(setTipValueColor);
	ADD_FUNCTION(getTipValueColor);
}


}//namespace

