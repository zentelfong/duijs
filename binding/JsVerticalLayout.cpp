#include "Util.h"

namespace duijs {


static Value setSepHeight(CVerticalLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SetSepHeight(args[0].ToInt32());
	return null_value;
}

static Value getSepHeight(CVerticalLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSepHeight());
}


static Value setSepImmMode(CVerticalLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SetSepImmMode(args[0].ToBool());
	return null_value;
}

static Value isSepImmMode(CVerticalLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsSepImmMode());
}


void RegisterVerticalLayout(qjs::Module* module) {
	DEFINE_CONTROL2(CVerticalLayoutUI, CContainerUI, "VerticalLayout");
	ADD_FUNCTION(setSepHeight);
	ADD_FUNCTION(getSepHeight);
	ADD_FUNCTION(setSepImmMode);
	ADD_FUNCTION(isSepImmMode);
}


}//namespace
