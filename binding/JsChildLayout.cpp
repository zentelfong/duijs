#include "Util.h"

namespace duijs {

static Value setChildLayoutXML(CChildLayoutUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetChildLayoutXML(CDuiString(str.str(),str.len()));
	return null_value;
}

static Value getChildLayoutXML(CChildLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetChildLayoutXML());
}

void RegisterChildLayout(qjs::Module* module) {
	DEFINE_CONTROL2(CChildLayoutUI, CContainerUI, "ChildLayout");
	ADD_FUNCTION(setChildLayoutXML);
	ADD_FUNCTION(getChildLayoutXML);
}


}//namespace
