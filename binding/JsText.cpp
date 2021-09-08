#include "duilib/UIlib.h"
#include "Util.h"

namespace duijs {


static Value getLinkContent(CTextUI* pThis, Context& context, ArgList& args) {
	auto content = pThis->GetLinkContent(args[0].ToInt32());
	if (content)
		return toValue(context, *content);
	else
		return null_value;
}

void RegisterText(qjs::Module* module) {
	DEFINE_CONTROL2(CTextUI, CLabelUI, "Text");
	ADD_FUNCTION(getLinkContent);
}


}//namespace
