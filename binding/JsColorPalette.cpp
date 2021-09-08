#include "Util.h"

namespace duijs {

static Value getSelectColor(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	return context.NewUint32(pThis->GetSelectColor());
}

static Value setSelectColor(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectColor(args[0].ToUint32());
	return undefined_value;
}

static Value getPalletHeight(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetPalletHeight());
}

static Value setPalletHeight(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	pThis->SetPalletHeight(args[0].ToInt32());
	return undefined_value;
}

static Value getBarHeight(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetBarHeight());
}

static Value setBarHeight(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	pThis->SetBarHeight(args[0].ToInt32());
	return undefined_value;
}

static Value getThumbImage(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetThumbImage());
}

static Value setThumbImage(CColorPaletteUI* pThis, Context& context, ArgList& args) {
	auto img = args[0].ToString();
	pThis->SetThumbImage(CDuiString(img.str(), img.len()));
	return undefined_value;
}

void RegisterColorPalette(qjs::Module* module) {
	DEFINE_CONTROL2(CColorPaletteUI, CControlUI, "ColorPalette");
	ADD_FUNCTION(getSelectColor);
	ADD_FUNCTION(setSelectColor);
	ADD_FUNCTION(getPalletHeight);
	ADD_FUNCTION(setPalletHeight);
	ADD_FUNCTION(getBarHeight);
	ADD_FUNCTION(setBarHeight);
	ADD_FUNCTION(getThumbImage);
	ADD_FUNCTION(setThumbImage);
}


}//namespace
