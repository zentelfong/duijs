#include "Util.h"

namespace duijs {


static Value getIndex(CListElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetIndex());
}


static Value setIndex(CListElementUI* pThis, Context& context, ArgList& args) {
	pThis->SetIndex(args[0].ToInt32());
	return undefined_value;
}

static Value isSelected(CListElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsSelected());
}


static Value select(CListElementUI* pThis, Context& context, ArgList& args) {
	pThis->Select(args[0].ToBool());
	return undefined_value;
}


static Value selectMulti(CListElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SelectMulti(args[0].ToBool()));
}


static Value isExpanded(CListElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsExpanded());
}

static Value expand(CListElementUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->Expand(args[0].ToBool()));
}



void RegisterListElement(qjs::Module* module) {
	{
		DEFINE_VIRTUAL_CONTROL2(CListElementUI, CControlUI, "ListElement");
		ADD_FUNCTION(getIndex);
		ADD_FUNCTION(setIndex);
		ADD_FUNCTION(isSelected);
		ADD_FUNCTION(select);
		ADD_FUNCTION(selectMulti);
		ADD_FUNCTION(isExpanded);
		ADD_FUNCTION(expand);

	}

	{
		DEFINE_CONTROL2(CListLabelElementUI, CListElementUI, "ListLabelElement");
	}

	{
		DEFINE_CONTROL2(CListTextElementUI, CListElementUI, "ListTextElement");
	}

}


}//namespace
