#include "Util.h"

namespace duijs {


static Value selectItem(CTabLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SelectItem(args[0].ToInt32());
	return null_value;
}

static Value getCurSel(CTabLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCurSel());
}

void RegisterTabLayout(qjs::Module* module) {
	DEFINE_CONTROL2(CTabLayoutUI, CContainerUI, "TabLayout");
	ADD_FUNCTION(selectItem);
	ADD_FUNCTION(getCurSel);
}


}//namespace
