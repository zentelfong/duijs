#include "Util.h"

namespace duijs {


static Value getIP(CIPAddressExUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetIP());
}


static Value setIP(CIPAddressExUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetIP(CDuiString(str.str(),str.len()));
	return undefined_value;
}



void RegisterIPAddressEx(qjs::Module* module) {
	DEFINE_CONTROL2(CIPAddressExUI, CLabelUI, "IPAddressEx");
	ADD_FUNCTION(getIP);
	ADD_FUNCTION(setIP);
}


}//namespace
