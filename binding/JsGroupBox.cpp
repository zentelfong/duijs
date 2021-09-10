#include "Util.h"

namespace duijs {


static Value setTextColor(CGroupBoxUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextColor(args[0].ToInt32());
	return null_value;
}


static Value getTextColor(CGroupBoxUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(uint32_t)pThis->GetTextColor());
}

static Value setDisabledTextColor(CGroupBoxUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledTextColor(args[0].ToInt32());
	return null_value;
}


static Value getDisabledTextColor(CGroupBoxUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledTextColor());
}

static Value setFont(CGroupBoxUI* pThis, Context& context, ArgList& args) {
	pThis->SetFont(args[0].ToInt32());
	return null_value;
}


static Value getFont(CGroupBoxUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFont());
}



void RegisterGroupBox(qjs::Module* module) {
	DEFINE_CONTROL2(CGroupBoxUI, CVerticalLayoutUI, "GroupBox");
	ADD_FUNCTION(setTextColor);
	ADD_FUNCTION(getTextColor);
	ADD_FUNCTION(setDisabledTextColor);
	ADD_FUNCTION(getDisabledTextColor);
	ADD_FUNCTION(setFont);
	ADD_FUNCTION(getFont);
}


}//namespace
