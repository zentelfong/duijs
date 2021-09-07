#include "duilib/UIlib.h"
#include "Util.h"

namespace duijs {

using namespace qjs;
using namespace DuiLib;

static CTextUI* newControl(Context& context, ArgList& args) {
	return new CTextUI();
}

static void deleteControl(CTextUI* w) {
}

static Value getLinkContent(CTextUI* pThis, Context& context, ArgList& args) {
	auto content = pThis->GetLinkContent(args[0].ToInt32());
	if (content)
		return toValue(context, *content);
	else
		return null_value;
}

void RegisterText(qjs::Module* module) {
	auto ctrl = module->ExportClass<CTextUI>("Text");
	ctrl.Init<deleteControl>(Class<CLabelUI>::class_id());
	ctrl.AddCtor<newControl>();
	ctrl.AddFunc<getLinkContent>("getLinkContent");
}


}//namespace
