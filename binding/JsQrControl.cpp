#include "Util.h"

namespace duijs {


static Value saveImage(CQrControlUI* pThis, Context& context, ArgList& args) {

	return context.NewBool(pThis->SaveImage(JsString(args[0])));
}

void RegisterQrControl(qjs::Module* module) {
	DEFINE_CONTROL2(CQrControlUI, CControlUI, "QrControl");
	ADD_FUNCTION(saveImage);
}


}//namespace
