#include "Util.h"

namespace duijs {


static Value setSepWidth(CHorizontalLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SetSepWidth(args[0].ToInt32());
	return null_value;
}

static Value getSepWidth(CHorizontalLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetSepWidth());
}


static Value setSepImmMode(CHorizontalLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SetSepImmMode(args[0].ToBool());
	return null_value;
}

static Value isSepImmMode(CHorizontalLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsSepImmMode());
}


void RegisterHorizontalLayout(qjs::Module* module) {
	DEFINE_CONTROL2(CHorizontalLayoutUI, CContainerUI, "HorizontalLayout");
	ADD_FUNCTION(setSepWidth);
	ADD_FUNCTION(getSepWidth);
	ADD_FUNCTION(setSepImmMode);
	ADD_FUNCTION(isSepImmMode);
}


}//namespace
