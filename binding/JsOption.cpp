#include "Util.h"

namespace duijs {


static Value getSelectedImage(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedImage());
}

static Value setSelectedImage(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedImage(JsString(args[0]));
	return undefined_value;
}

static Value getSelectedHotImage(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedHotImage());
}

static Value setSelectedHotImage(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedHotImage(JsString(args[0]));
	return undefined_value;
}

static Value getSelectedPushedImage(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedPushedImage());
}

static Value setSelectedPushedImage(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedPushedImage(JsString(args[0]));
	return undefined_value;
}

static Value getSelectedTextColor(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelectedTextColor());
}

static Value setSelectedTextColor(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getSelectBkColor(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelectBkColor());
}

static Value setSelectedBkColor(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getSelectedForedImage(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedForedImage());
}

static Value setSelectedForedImage(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedForedImage(JsString(args[0]));
	return undefined_value;
}

static Value getSelectedStateCount(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetSelectedStateCount());
}

static Value setSelectedStateCount(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedStateCount(args[0].ToInt32());
	return undefined_value;
}

static Value getSelectedStateImage(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedStateImage());
}

static Value setSelectedStateImage(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedStateImage(JsString(args[0]));
	return undefined_value;
}

static Value getSelectedFont(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedFont());
}

static Value setSelectedFont(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedFont(args[0].ToInt32());
	return undefined_value;
}

static Value getGroup(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetGroup());
}

static Value setGroup(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->SetGroup(JsString(args[0]));
	return undefined_value;
}

static Value isSelected(COptionUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsSelected());
}

static Value selected(COptionUI* pThis, Context& context, ArgList& args) {
	pThis->Selected(args[0].ToBool());
	return undefined_value;
}


static Value setCheck(CCheckBoxUI* pThis, Context& context, ArgList& args) {
	pThis->SetCheck(args[0].ToBool());
	return undefined_value;
}


static Value getCheck(CCheckBoxUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->GetCheck());
}




void RegisterOption(qjs::Module* module) {
	{
		DEFINE_CONTROL2(COptionUI, CButtonUI, "Option");
		ADD_FUNCTION(getSelectedImage);
		ADD_FUNCTION(setSelectedImage);
		ADD_FUNCTION(getSelectedHotImage);
		ADD_FUNCTION(setSelectedHotImage);
		ADD_FUNCTION(getSelectedPushedImage);
		ADD_FUNCTION(setSelectedPushedImage);
		ADD_FUNCTION(getSelectedTextColor);
		ADD_FUNCTION(setSelectedTextColor);
		ADD_FUNCTION(getSelectBkColor);
		ADD_FUNCTION(setSelectedBkColor);
		ADD_FUNCTION(getSelectedForedImage);
		ADD_FUNCTION(setSelectedForedImage);
		ADD_FUNCTION(getSelectedStateCount);
		ADD_FUNCTION(setSelectedStateCount);
		ADD_FUNCTION(getSelectedStateImage);
		ADD_FUNCTION(setSelectedStateImage);
		ADD_FUNCTION(getSelectedFont);
		ADD_FUNCTION(setSelectedFont);
		ADD_FUNCTION(getGroup);
		ADD_FUNCTION(setGroup);
		ADD_FUNCTION(isSelected);
		ADD_FUNCTION(selected);

	}

	{
		DEFINE_CONTROL2(CCheckBoxUI, COptionUI, "CheckBox");
		ADD_FUNCTION(setCheck);
		ADD_FUNCTION(getCheck);
	}
}


}//namespace
