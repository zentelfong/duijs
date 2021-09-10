#include "Util.h"

namespace duijs {


static Value getIndex(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetIndex());
}


static Value setIndex(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetIndex(args[0].ToInt32());
	return undefined_value;
}


static Value isSelected(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsSelected());
}


static Value select(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	pThis->Select(args[0].ToBool());
	return undefined_value;
}


static Value selectMulti(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	pThis->SelectMulti(args[0].ToBool());
	return undefined_value;
}


static Value expand(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	pThis->Expand(args[0].ToBool());
	return undefined_value;
}

static Value isExpanded(CListContainerElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsExpanded());
}




void RegisterListContainerElement(qjs::Module* module) {

	DEFINE_CONTROL2(CListContainerElementUI, CHorizontalLayoutUI, "ListContainerElement");
	ADD_FUNCTION(getIndex);
	ADD_FUNCTION(setIndex);
	ADD_FUNCTION(isSelected);
	ADD_FUNCTION(select);
	ADD_FUNCTION(selectMulti);
	ADD_FUNCTION(isExpanded);
	ADD_FUNCTION(expand);
}


}//namespace
