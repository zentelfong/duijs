#include "Util.h"

namespace duijs {

static Value getNormalImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetNormalImage());
}

static Value setNormalImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetNormalImage(CDuiString(img.str(),img.len()));
	return undefined_value;
}

static Value getHotImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotImage());
}

static Value setHotImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetHotImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}

static Value getPushedImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetPushedImage());
}

static Value setPushedImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetPushedImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}

static Value getFocusedImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFocusedImage());
}

static Value setFocusedImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetFocusedImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}

static Value getDisabledImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledImage());
}

static Value setDisabledImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetDisabledImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}

static Value getHotForeImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotForeImage());
}

static Value setHotForeImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetHotForeImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}


static Value getStateCount(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetStateCount());
}

static Value setStateCount(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetStateCount(args[0].ToInt32());
	return undefined_value;
}

static Value getStateImage(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetStateImage());
}

static Value setStateImage(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetStateImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}

static Value bindTabIndex(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->BindTabIndex(args[0].ToInt32());
	return undefined_value;
}

static Value bindTabLayoutName(CButtonUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->BindTabLayoutName(CDuiString(img.str(), img.len()));
	return undefined_value;
}


static Value bindTriggerTabSel(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->BindTriggerTabSel(args[0].ToInt32());
	return undefined_value;
}

static Value removeBindTabIndex(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->RemoveBindTabIndex();
	return undefined_value;
}

static Value getBindTabLayoutIndex(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBindTabLayoutIndex());
}

static Value getBindTabLayoutName(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBindTabLayoutName());
}

static Value setHotFont(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotFont(args[0].ToInt32());
	return undefined_value;
}

static Value getHotFont(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotFont());
}

static Value setPushedFont(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetPushedFont(args[0].ToInt32());
	return undefined_value;
}

static Value getPushedFont(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetPushedFont());
}

static Value setFocusedFont(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetFocusedFont(args[0].ToInt32());
	return undefined_value;
}

static Value getFocusedFont(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFocusedFont());
}

static Value setHotBkColor(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getHotBkColor(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetHotBkColor());
}


static Value setPushedBkColor(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetPushedBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getPushedBkColor(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetPushedBkColor());
}

static Value setDisabledBkColor(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getDisabledBkColor(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledBkColor());
}

static Value setHotTextColor(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getHotTextColor(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetHotTextColor());
}

static Value setPushedTextColor(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetPushedTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getPushedTextColor(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetPushedTextColor());
}


static Value setFocusedTextColor(CButtonUI* pThis, Context& context, ArgList& args) {
	pThis->SetFocusedTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getFocusedTextColor(CButtonUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetFocusedTextColor());
}



void RegisterButton(qjs::Module* module) {
	DEFINE_CONTROL2(CButtonUI, CLabelUI, "Button");
	ADD_FUNCTION(getNormalImage);
	ADD_FUNCTION(setNormalImage);
	ADD_FUNCTION(getHotImage);
	ADD_FUNCTION(setHotImage);
	ADD_FUNCTION(getPushedImage);
	ADD_FUNCTION(setPushedImage);
	ADD_FUNCTION(getFocusedImage);
	ADD_FUNCTION(setFocusedImage);
	ADD_FUNCTION(getDisabledImage);
	ADD_FUNCTION(setDisabledImage);
	ADD_FUNCTION(getHotForeImage);
	ADD_FUNCTION(setHotForeImage);
	ADD_FUNCTION(getStateCount);
	ADD_FUNCTION(setStateCount);
	ADD_FUNCTION(getStateImage);
	ADD_FUNCTION(setStateImage);
	ADD_FUNCTION(bindTabIndex);
	ADD_FUNCTION(bindTabLayoutName);
	ADD_FUNCTION(bindTriggerTabSel);
	ADD_FUNCTION(removeBindTabIndex);
	ADD_FUNCTION(getBindTabLayoutIndex);
	ADD_FUNCTION(getBindTabLayoutName);
	ADD_FUNCTION(setHotFont);
	ADD_FUNCTION(getHotFont);
	ADD_FUNCTION(setPushedFont);
	ADD_FUNCTION(getPushedFont);
	ADD_FUNCTION(setFocusedFont);
	ADD_FUNCTION(getFocusedFont);
	ADD_FUNCTION(setHotBkColor);
	ADD_FUNCTION(getHotBkColor);
	ADD_FUNCTION(setPushedBkColor);
	ADD_FUNCTION(getPushedBkColor);
	ADD_FUNCTION(setDisabledBkColor);
	ADD_FUNCTION(getDisabledBkColor);
	ADD_FUNCTION(setHotTextColor);
	ADD_FUNCTION(getHotTextColor);
	ADD_FUNCTION(setPushedTextColor);
	ADD_FUNCTION(getPushedTextColor);
	ADD_FUNCTION(setFocusedTextColor);
	ADD_FUNCTION(getFocusedTextColor);

}


}//namespace

