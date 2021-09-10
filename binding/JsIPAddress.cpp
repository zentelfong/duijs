#include "Util.h"

namespace duijs {


static Value getIP(CIPAddressUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(uint32_t)pThis->GetIP());
}


static Value setIP(CIPAddressUI* pThis, Context& context, ArgList& args) {
	pThis->SetIP(args[0].ToUint32());
	return undefined_value;
}


static Value isReadOnly(CIPAddressUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->IsReadOnly());
}


static Value setReadOnly(CIPAddressUI* pThis, Context& context, ArgList& args) {
	pThis->SetReadOnly(args[0].ToBool());
	return undefined_value;
}

static Value updateText(CIPAddressUI* pThis, Context& context, ArgList& args) {
	pThis->UpdateText();
	return undefined_value;
}



void RegisterIPAddress(qjs::Module* module) {
	DEFINE_CONTROL2(CIPAddressUI, CLabelUI, "IPAddress");
	ADD_FUNCTION(getIP);
	ADD_FUNCTION(setIP);
	ADD_FUNCTION(isReadOnly);
	ADD_FUNCTION(setReadOnly);
	ADD_FUNCTION(updateText);
}


}//namespace
