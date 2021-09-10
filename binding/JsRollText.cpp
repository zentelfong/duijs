#include "Util.h"

namespace duijs {


static Value beginRoll(CRollTextUI* pThis, Context& context, ArgList& args) {
	pThis->BeginRoll(args[0].ToInt32(), args[1].ToInt32(), args[2].ToInt32());
	return null_value;
}


static Value endRoll(CRollTextUI* pThis, Context& context, ArgList& args) {
	pThis->EndRoll();
	return null_value;
}


void RegisterRollText(qjs::Module* module) {
	DEFINE_CONTROL2(CRollTextUI, CLabelUI, "RollText");
	ADD_FUNCTION(beginRoll);
	ADD_FUNCTION(endRoll);
}


}//namespace
