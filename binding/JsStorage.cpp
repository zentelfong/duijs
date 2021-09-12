#include "quickjs/qjs.h"
#include "utils/storage.h"
#include "JsEngine.h"

namespace duijs {

using namespace qjs;

static Storage* createStorage(qjs::Context& context, qjs::ArgList& args) {
	return new Storage();
}

static void deleteStorage(Storage* w) {
	delete w;
}


static Value open(Storage* pThis, Context& context, ArgList& args) {
	JsEngine* engine = JsEngine::get(context);
	Promise* promise = new Promise(context);

	pThis->Open(args[0].ToStdString(), [engine, promise](int code) {
		engine->PostTask([code, promise](Context* context) {
			promise->Resolve(context->NewInt32(code));
			delete promise;
		});
	});
	return promise->promise();
}

static Value close(Storage* pThis, Context& context, ArgList& args) {
	JsEngine* engine = JsEngine::get(context);
	Promise* promise = new Promise(context);

	pThis->Close([engine, promise](int code) {
		engine->PostTask([code, promise](Context* context) {
			promise->Resolve(context->NewInt32(code));
			delete promise;
		});
	});
	return promise->promise();
}

static Value exec(Storage* pThis, Context& context, ArgList& args) {
	JsEngine* engine = JsEngine::get(context);
	Promise* promise = new Promise(context);
	pThis->Exec(args[0].ToStdString(), [engine, promise](int code,std::string data) {
		engine->PostTask([code, promise, data](Context* context) {
			Value rslt = context->NewObject();
			rslt.SetPropertyInt32("code", code);
			rslt.SetPropertyString("data", data.data(),data.length());
			promise->Resolve(rslt);
			delete promise;
		});
	});
	return promise->promise();
}

void RegisterStorage(qjs::Module* module) {
	auto cls = module->ExportClass<Storage>("Storage");
	cls.Init<deleteStorage>();
	cls.AddCtor<createStorage>();
	cls.AddFunc<open>("open");
	cls.AddFunc<close>("close");
	cls.AddFunc<exec>("exec");
}


}//namespace
