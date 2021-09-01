#include "qjs.h"
#include <stdarg.h>

namespace qjs {

const Value undefined_value(nullptr, JS_UNDEFINED);
const Value null_value(nullptr, JS_NULL);
const Value true_value(nullptr, JS_TRUE);
const Value false_value(nullptr, JS_FALSE);
const Value exception_value(nullptr, JS_EXCEPTION);
const Value uninit_value(nullptr, JS_UNINITIALIZED);



Module::Module(JSContext* ctx, const char* name)
	:context_(ctx), module_(nullptr)
{
	module_ = JS_NewCModule(ctx, name, Module::OnInit);
}

Module::~Module() {

}

bool Module::Export(const char* name, const Value& value) {
	int rslt = JS_AddModuleExport(context_, module_, name);
	exports_.insert({ name,value });
	return rslt == 0;
}

bool Module::Export(const char* name, JSValue value) {
	int rslt = JS_AddModuleExport(context_, module_, name);
	exports_.insert({ name,Value(context_,std::move(value)) });
	return rslt == 0;
}

Value Module::GetImportMeta() {
	return Value(context_, JS_GetImportMeta(context_, module_));
}

int Module::OnInit(JSContext* ctx, JSModuleDef* m) {
	Context* context = Context::get(ctx);
	if (!context) {
		return -1;
	}

	auto module = context->GetModule(m);
	if (!module) {
		return -1;
	}

	//导出value
	for (auto& itr : module->exports_) {
		JS_SetModuleExport(ctx, m, itr.first.c_str(),
			itr.second.CopyValue());
	}
	return 0;
}

void Context::Init(int argc, char** argv) {
	JS_SetContextOpaque(context_, this);
	js_init_module_std(context_, "std");
	js_init_module_os(context_, "os");
	js_std_add_helpers(context_, argc, argv);
	JS_AddIntrinsicBigFloat(context_);
	JS_AddIntrinsicBigDecimal(context_);
}


void Context::ExecuteJobs() {
	JSContext* ctx1;
	int err;

	for (;;) {
		err = JS_ExecutePendingJob(JS_GetRuntime(context_), &ctx1);
		if (err <= 0) {
			if (err < 0)
				DumpError();
			break;
		}
	}
}

Module* Context::NewModule(const char* name) {
	auto module = std::make_unique<Module>(context_, name);
	Module* m = module.get();
	modules_.insert({ m->module(),std::move(module) });
	return m;
}


std::unique_ptr<Module> Context::GetModule(JSModuleDef* m) {
	auto find = modules_.find(m);
	if (find != modules_.end()) {
		std::unique_ptr<Module> module = std::move(find->second);
		modules_.erase(find);
		return module;
	}
	return nullptr;
}


//加载字节码
bool Context::LoadByteCode(const uint8_t* buf, size_t buf_len) {

	Value obj(context_,JS_ReadObject(context_, buf, buf_len, JS_READ_OBJ_BYTECODE));

	if (obj.IsException()) {
		return false;
	}

	if (obj.tag() == JS_TAG_MODULE) {
		if (JS_ResolveModule(context_, obj) < 0) {
			return false;
		}
		js_module_set_import_meta(context_, obj, false, true);
	}

	Value val(context_,JS_EvalFunction(context_, obj));
	if (val.IsException()) {
		return false;
	}
	return true;
}

Value Context::NewUint8ArrayBuffer(const uint8_t* buf, size_t len) {
	Value abuf = NewArrayBuffer(buf, len);

	if (abuf.IsException())
		return abuf;

	Value global = Global();
	Value u8array_ctor = global.GetProperty("Uint8Array");
	return u8array_ctor.Call(abuf);
}


Value Context::ThrowSyntaxError(const char* fmt, ...) {
	JSValue val;
	va_list ap;

	va_start(ap, fmt);
	val = JS_ThrowError(context_, JS_SYNTAX_ERROR, fmt, ap);
	va_end(ap);
	return Value(context_,std::move(val));
}

Value Context::ThrowTypeError(const char* fmt, ...) {
	JSValue val;
	va_list ap;

	va_start(ap, fmt);
	val = JS_ThrowError(context_, JS_TYPE_ERROR, fmt, ap);
	va_end(ap);
	return Value(context_, std::move(val));
}

Value Context::ThrowReferenceError(const char* fmt, ...) {
	JSValue val;
	va_list ap;

	va_start(ap, fmt);
	val = JS_ThrowError(context_, JS_REFERENCE_ERROR, fmt, ap);
	va_end(ap);
	return Value(context_, std::move(val));
}

Value Context::ThrowRangeError(const char* fmt, ...) {
	JSValue val;
	va_list ap;

	va_start(ap, fmt);
	val = JS_ThrowError(context_, JS_RANGE_ERROR, fmt, ap);
	va_end(ap);
	return Value(context_, std::move(val));
}

Value Context::ThrowInternalError(const char* fmt, ...) {
	JSValue val;
	va_list ap;

	va_start(ap, fmt);
	val = JS_ThrowError(context_, JS_INTERNAL_ERROR, fmt, ap);
	va_end(ap);
	return Value(context_, std::move(val));
}

Value Context::ThrowOutOfMemory() {
	return Value(context_, JS_ThrowOutOfMemory(context_));
}

uint8_t* Value::ToBuffer(size_t* psize) const {
	size_t aoffset, asize, size;
	JSValue abuf = JS_GetTypedArrayBuffer(context_, value_, &aoffset, &asize, NULL);
	if (JS_IsException(abuf)) {
		Context::get(context_)->DumpError();
		return nullptr;
	}

	uint8_t* buf = JS_GetArrayBuffer(context_, &size, abuf);
	if (buf) {
		buf += aoffset;
		size = asize;
	} else {
		size = 0;
	}
	JS_FreeValue(context_, abuf);

	*psize = size;
	return buf;
}




}//namespace


