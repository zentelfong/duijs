#include "Util.h"

namespace duijs {


static Value isShowText(CProgressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsShowText());
}

static Value setShowText(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowText(args[0].ToBool());
	return undefined_value;
}


static Value isHorizontal(CProgressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsHorizontal());
}

static Value setHorizontal(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetHorizontal(args[0].ToBool());
	return undefined_value;
}


static Value isStretchForeImage(CProgressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsStretchForeImage());
}

static Value setXMirror(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetXMirror(args[0].ToBool());
	return undefined_value;
}


static Value setStretchForeImage(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetStretchForeImage(args[0].ToBool());
	return undefined_value;
}

static Value getMinValue(CProgressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMinValue());
}

static Value setMinValue(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetMinValue(args[0].ToInt32());
	return undefined_value;
}

static Value getMaxValue(CProgressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMaxValue());
}

static Value setMaxValue(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetMaxValue(args[0].ToInt32());
	return undefined_value;
}

static Value getValue(CProgressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetValue());
}

static Value setValue(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->SetValue(args[0].ToInt32());
	return undefined_value;
}

static Value updateText(CProgressUI* pThis, Context& context, ArgList& args) {
	pThis->UpdateText();
	return undefined_value;
}


void RegisterProgress(qjs::Module* module) {
	DEFINE_CONTROL2(CProgressUI, CLabelUI, "Progress");
	ADD_FUNCTION(isShowText);
	ADD_FUNCTION(setShowText);
	ADD_FUNCTION(isHorizontal);
	ADD_FUNCTION(setHorizontal);
	ADD_FUNCTION(isStretchForeImage);
	ADD_FUNCTION(setXMirror);
	ADD_FUNCTION(setStretchForeImage);
	ADD_FUNCTION(getMinValue);
	ADD_FUNCTION(setMinValue);
	ADD_FUNCTION(getMaxValue);
	ADD_FUNCTION(setMaxValue);
	ADD_FUNCTION(getValue);
	ADD_FUNCTION(setValue);
	ADD_FUNCTION(updateText);
}


}//namespace
