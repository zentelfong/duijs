#include "Util.h"

namespace duijs {

static Value getTextStyle(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetTextStyle());
}

static Value setTextStyle(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextStyle(args[0].ToUint32());
	return undefined_value;
}


static Value getTextColor(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetTextColor());
}

static Value setTextColor(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getDisabledTextColor(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledTextColor());
}

static Value setDisabledTextColor(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getFont(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (int32_t)pThis->GetFont());
}

static Value setFont(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetFont(args[0].ToInt32());
	return undefined_value;
}


static Value getTextPadding(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTextPadding());
}

static Value setTextPadding(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextPadding(toRect(args[0]));
	return undefined_value;
}

static Value isShowHtml(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsShowHtml());
}

static Value setShowHtml(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowHtml(args[0].ToBool());
	return undefined_value;
}


static Value getAutoCalcWidth(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetAutoCalcWidth());
}

static Value setAutoCalcWidth(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoCalcWidth(args[0].ToBool());
	return undefined_value;
}

static Value getAutoCalcHeight(CLabelUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetAutoCalcHeight());
}

static Value setAutoCalcHeight(CLabelUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoCalcHeight(args[0].ToBool());
	return undefined_value;
}

void RegisterLabel(qjs::Module* module) {
	DEFINE_CONTROL2(CLabelUI, CControlUI, "Label");
	ADD_FUNCTION(getTextStyle);
	ADD_FUNCTION(setTextStyle);
	ADD_FUNCTION(getTextColor);
	ADD_FUNCTION(setTextColor);
	ADD_FUNCTION(getDisabledTextColor);
	ADD_FUNCTION(setDisabledTextColor);
	ADD_FUNCTION(getFont);
	ADD_FUNCTION(setFont);
	ADD_FUNCTION(getTextPadding);
	ADD_FUNCTION(setTextPadding);
	ADD_FUNCTION(isShowHtml);

	ADD_FUNCTION(setShowHtml);
	ADD_FUNCTION(getAutoCalcWidth);
	ADD_FUNCTION(setAutoCalcWidth);
	ADD_FUNCTION(getAutoCalcHeight);
	ADD_FUNCTION(setAutoCalcHeight);

}




}//namespace


