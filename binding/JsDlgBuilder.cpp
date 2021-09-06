#include "duilib/UIlib.h"
#include "Util.h"

namespace duijs {
using namespace DuiLib;
using namespace qjs;


static CDialogBuilder* newDialogBuilder(Context& context, ArgList& args) {
	return new CDialogBuilder();
}

static void deleteDialogBuilder(CDialogBuilder* w) {
	delete w;
}


class JsDialogBuilderCallback:public IDialogBuilderCallback
{
public:
	JsDialogBuilderCallback(Context& context,Value func)
		:context_(context),func_(func)
	{
	}

	CControlUI* CreateControl(LPCTSTR pstrClass) override {
		Value rslt = func_.Call(toValue(context_,pstrClass));
		if (rslt.IsException()) {
			context_.DumpError();
			return nullptr;
		} else {
			return toControl(rslt);
		}
	}

private:
	Context& context_;
	Value func_;
};

static Value create(CDialogBuilder* pThis, Context& context, ArgList& args) {
	CControlUI* control = nullptr;
	IDialogBuilderCallback* callback = nullptr;
	CPaintManagerUI* manager = nullptr;
	CControlUI* parent = nullptr;

	if (args[0].IsString()) {
		auto name = toString(args[0]);
		auto type = toString(args[1]);
		if (args[2].IsFunction()) {
			callback = new JsDialogBuilderCallback(context, args[2]);
		}

		manager = Class<CPaintManagerUI>::ToC(args[3]);
		parent = toControl(args[4]);

		control = pThis->Create(STRINGorID(name), type, callback, manager, parent);

	} else if (args[0].IsNumber()) {
		auto id = args[0].ToUint32();
		auto type = toString(args[1]);
		if (args[2].IsFunction()) {
			callback = new JsDialogBuilderCallback(context, args[2]);
		}

		manager = Class<CPaintManagerUI>::ToC(args[3]);
		parent = toControl(args[4]);

		control = pThis->Create(STRINGorID(id), type, callback, manager, parent);
	} else {
		//callback,manager,parent
		if (args[0].IsFunction()) {
			callback = new JsDialogBuilderCallback(context, args[0]);
		}
		manager = Class<CPaintManagerUI>::ToC(args[1]);
		parent = toControl(args[2]);

		control = pThis->Create(callback, manager, parent);
	}

	delete callback;
	return toValue(context,control);
}


static Value getLastErrorMessage(CDialogBuilder* pThis, Context& context, ArgList& args) {
	TCHAR buffer[512];
	pThis->GetLastErrorMessage(buffer, ARRAYSIZE(buffer));
	return toValue(context,buffer);
}

static Value getLastErrorLocation(CDialogBuilder* pThis, Context& context, ArgList& args) {
	TCHAR buffer[512];
	pThis->GetLastErrorLocation(buffer, ARRAYSIZE(buffer));
	return toValue(context, buffer);
}

static Value setInstance(CDialogBuilder* pThis, Context& context, ArgList& args) {
	pThis->SetInstance((HINSTANCE)args[0].ToInt64());
	return undefined_value;
}

void RegisterDialogBuilder(qjs::Module* module) {
	auto ctrl = module->ExportClass<CDialogBuilder>("DialogBuilder");
	ctrl.Init<deleteDialogBuilder>(Class<CDialogBuilder>::class_id());
	ctrl.AddCtor<newDialogBuilder>();
	ctrl.AddFunc<create>("create");
	ctrl.AddFunc<getLastErrorMessage>("getLastErrorMessage");
	ctrl.AddFunc<getLastErrorLocation>("getLastErrorLocation");
	ctrl.AddFunc<setInstance>("setInstance");
}



}//namespace

