#include "Util.h"

namespace duijs {


static Value setAutoPlay(CGifAnimUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoPlay(args[0].ToBool());
	return null_value;
}


static Value isAutoPlay(CGifAnimUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->IsAutoPlay());
}


static Value setAutoSize(CGifAnimUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoSize(args[0].ToBool());
	return null_value;
}


static Value isAutoSize(CGifAnimUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsAutoSize());
}


static Value playGif(CGifAnimUI* pThis, Context& context, ArgList& args) {
	pThis->PlayGif();
	return null_value;
}


static Value pauseGif(CGifAnimUI* pThis, Context& context, ArgList& args) {
	pThis->PauseGif();
	return null_value;
}

static Value stopGif(CGifAnimUI* pThis, Context& context, ArgList& args) {
	pThis->StopGif();
	return null_value;
}


void RegisterGifAnim(qjs::Module* module) {
	DEFINE_CONTROL2(CGifAnimUI, CControlUI, "GifAnim");
	ADD_FUNCTION(setAutoPlay);
	ADD_FUNCTION(isAutoPlay);
	ADD_FUNCTION(setAutoSize);
	ADD_FUNCTION(isAutoSize);
	ADD_FUNCTION(playGif);
	ADD_FUNCTION(pauseGif);
	ADD_FUNCTION(stopGif);
}


}//namespace
