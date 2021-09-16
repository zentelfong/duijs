#include "Util.h"

namespace duijs {

static Value setBkImage(CRingUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetBkImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}


void RegisterRing(qjs::Module* module) {
	DEFINE_CONTROL2(CRingUI, CLabelUI, "Ring");
	ADD_FUNCTION(setBkImage);
}


}//namespace
