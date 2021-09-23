#include "quickjs/qjs.h"
#include "utils/storage.h"
#include "sqlite3/sqlite3.h"
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
		engine->PostTask([code, promise]() {
			Context* context = Context::get(promise->context());
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
		engine->PostTask([code, promise]() {
			Context* context = Context::get(promise->context());
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
		engine->PostTask([code, promise, data]() {
			Context* context = Context::get(promise->context());
			Value rslt = context->NewObject();
			rslt.SetPropertyInt32("code", code);
			Value jdata = context->ParseJson(data.c_str(), data.length(), "<sqlite3>");
			rslt.SetProperty("data", jdata);

			promise->Resolve(rslt);
			delete promise;
		});
	});
	return promise->promise();
}


static Value escape(Storage* pThis, Context& context, ArgList& args) {
	if (!args[0].IsString()) {
		return undefined_value;
	}

	String str = args[0].ToString();

	char* escape = sqlite3_mprintf("%q", str.str());
	Value rslt = context.NewString(escape);
	sqlite3_free(escape);
	return rslt;
}

void RegisterStorage(qjs::Module* module) {
	auto cls = module->ExportClass<Storage>("Storage");
	cls.Init<deleteStorage>();
	cls.AddCtor<createStorage>();
	cls.AddFunc<open>("open");
	cls.AddFunc<close>("close");
	cls.AddFunc<exec>("exec");
	cls.AddFunc<escape>("escape");
}


}//namespace
