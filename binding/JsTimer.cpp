#include "quickjs/qjs.h"
#include "JsEngine.h"

namespace duijs {

using namespace qjs;

struct Timer {

	Timer(JsEngine* e)
		:engine(e),id(0),func(undefined_value),promise(nullptr)
	{
	}

	~Timer() {
		if (engine && id) {
			engine->CancelDelayTask(id);
		}
		delete promise;
	}

	JsEngine* engine;
	uint32_t id;
	Value func;
	Promise* promise;
};


static Timer* createTimer(qjs::Context& context, qjs::ArgList& args) {
	return new Timer(JsEngine::get(context));
}


static void deleteTimer(Timer* w) {
	delete w;
}

static void markTimer(Timer* pThis, JS_MarkFunc* mark_func) {
	if(pThis->func.IsFunction())
		pThis->func.Mark(mark_func);
	if (pThis->promise)
		pThis->promise->Mark(mark_func);
}

static Value setTimer(Timer* pThis, Context& context, ArgList& args) {
	JsEngine* engine = JsEngine::get(context);

	if (!args[0].IsFunction()) {
		return context.ThrowTypeError("arg 0 must function");
	}

	if (!args[1].IsNumber()) {
		return context.ThrowTypeError("arg 1 must number");
	}

	auto delay = args[1].ToInt32();
	if (delay < 0) {
		return context.ThrowTypeError("arg 1 must > 0");
	}

	//保存回调函数
	delete pThis->promise;
	pThis->promise = nullptr;
	pThis->func = args[0];

	if (pThis->id > 0) {
		engine->ResetDelayTask(pThis->id,[pThis](qjs::Context* context) {
				pThis->id = 0;
				auto value = pThis->func.Call();
				if (value.IsException()) {
					context->DumpError();
				}

			}, delay);
	}
	else {
		pThis->id = engine->PostDelayTask([pThis](qjs::Context* context) {
				pThis->id = 0;
				auto value = pThis->func.Call();
				if (value.IsException()) {
					context->DumpError();
				}
			}, delay);

	}
	return undefined_value;
}

static Value killTimer(Timer* pThis, Context& context, ArgList& args) {
	JsEngine* engine = JsEngine::get(context);
	if (pThis->id) {
		engine->CancelDelayTask(pThis->id);
	}
	pThis->id = 0;
	return undefined_value;
}

//返回promise
static Value wait(Timer* pThis, Context& context, ArgList& args) {
	JsEngine* engine = JsEngine::get(context);

	if (!args[0].IsNumber()) {
		return context.ThrowTypeError("arg 1 must number");
	}

	auto delay = args[0].ToInt32();
	if (delay < 0) {
		return context.ThrowTypeError("arg 1 must > 0");
	}

	//保存回调函数
	pThis->func = undefined_value;

	delete pThis->promise;
	pThis->promise = nullptr;

	pThis->promise = new Promise(context);

	if (pThis->id > 0) {
		engine->ResetDelayTask(pThis->id, [pThis](qjs::Context* context) {
				pThis->id = 0;
				ArgList list;
				auto value = pThis->promise->Resolve(list);
				if (value.IsException()) {
					context->DumpError();
				}
			}, delay);
	}
	else {
		pThis->id = engine->PostDelayTask([pThis](qjs::Context* context) {
				ArgList list;
				auto value = pThis->promise->Resolve(list);
				if (value.IsException()) {
					context->DumpError();
				}
			}, delay);

	}
	return pThis->promise->promise();
}


void RegisterTimer(qjs::Module* module) {
	auto ctrl = module->ExportClass<Timer>("Timer");
	ctrl.Init2<deleteTimer, markTimer>();
	ctrl.AddCtor<createTimer>();
	ctrl.AddFunc<setTimer>("setTimer");
	ctrl.AddFunc<killTimer>("killTimer");
	ctrl.AddFunc<wait>("wait");
}




}//namespace



