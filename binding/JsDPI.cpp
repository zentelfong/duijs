#include "Util.h"

namespace duijs {


static Value getMainMonitorDPI(Context& context, ArgList& args) {
	return context.NewInt32(CDPI::GetMainMonitorDPI());
}

static Value getDPIOfMonitorNearestToPoint(Context& context, ArgList& args) {
	return context.NewInt32(CDPI::GetDPIOfMonitorNearestToPoint(toPoint(args[0])));
}

static Value getDPIAwareness(CDPI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetDPIAwareness());
}

static Value setDPIAwareness(CDPI* pThis, Context& context, ArgList& args) {
	pThis->SetDPIAwareness((PROCESS_DPI_AWARENESS)args[0].ToUint32());
	return undefined_value;
}

static Value getDPI(CDPI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetDPI());
}

static Value getScale(CDPI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetScale());
}

static Value setScale(CDPI* pThis, Context& context, ArgList& args) {
	pThis->SetScale(args[0].ToUint32());
	return undefined_value;
}

static Value scale(CDPI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->Scale(args[0].ToInt32()));
}

static Value scaleBack(CDPI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->ScaleBack(args[0].ToInt32()));
}


void RegisterDPI(Module* module) {

	EXPORT_FUNCTION(getMainMonitorDPI);
	EXPORT_FUNCTION(getDPIOfMonitorNearestToPoint);
	EXPORT_CONST_VALUE(PROCESS_DPI_UNAWARE);
	EXPORT_CONST_VALUE(PROCESS_SYSTEM_DPI_AWARE);
	EXPORT_CONST_VALUE(PROCESS_PER_MONITOR_DPI_AWARE);

	DEFINE_CONTROL(CDPI, "Dpi");

	ADD_FUNCTION(getDPIAwareness);
	ADD_FUNCTION(setDPIAwareness);
	ADD_FUNCTION(getDPI);
	ADD_FUNCTION(getScale);
	ADD_FUNCTION(setScale);
	ADD_FUNCTION(scale);
	ADD_FUNCTION(scaleBack);
}


}