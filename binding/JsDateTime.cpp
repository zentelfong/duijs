#include "Util.h"

namespace duijs {

static Value setTime(CDateTimeUI* pThis, Context& context, ArgList& args) {
	auto time = toSysTime(args[0]);
	pThis->SetTime(&time);
	return null_value;
}

static Value getTime(CDateTimeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTime());
}


void RegisterDateTime(qjs::Module* module) {
	DEFINE_CONTROL2(CDateTimeUI, CLabelUI, "DateTime");
	ADD_FUNCTION(setTime);
	ADD_FUNCTION(getTime);
}

}//namespace
