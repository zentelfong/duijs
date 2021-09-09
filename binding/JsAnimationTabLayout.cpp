#include "Util.h"

namespace duijs {


static Value selectItem(CAnimationTabLayoutUI* pThis, Context& context, ArgList& args) {
	pThis->SelectItem(args[0].ToInt32());
	return null_value;
}

void RegisterAnimationTabLayout(qjs::Module* module) {
	DEFINE_CONTROL2(CAnimationTabLayoutUI, CTabLayoutUI, "AnimationTabLayout");
	ADD_FUNCTION(selectItem);
}


}//namespace
