#include "Util.h"

namespace duijs {


static Value setItemSize(CTileLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemSize(toSize(args[0]));
	return null_value;
}

static Value getItemSize(CTileLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemSize());
}


static Value setColumns(CTileLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SetColumns(args[0].ToInt32());
	return null_value;
}

static Value getColumns(CTileLayoutUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetColumns());
}


void RegisterTileLayout(qjs::Module* module) {
	DEFINE_CONTROL2(CTileLayoutUI, CContainerUI, "TabLayout");
	ADD_FUNCTION(setItemSize);
	ADD_FUNCTION(getItemSize);
	ADD_FUNCTION(setColumns);
	ADD_FUNCTION(getColumns);
}


}//namespace
