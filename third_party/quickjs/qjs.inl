
namespace qjs {

inline 	Value Context::ParseJson(const char* buf, size_t buf_len,
	const char* filename) {
	return Value(context_,JS_ParseJSON(context_, buf, buf_len, filename));
}

inline Value Context::NewNull() {
	return Value(context_, JS_NULL);
}

inline Value Context::NewBool(bool v) {
	return Value(context_, JS_NewBool(context_, v));
}


inline Value Context::NewInt32(int32_t v) {
	return Value(context_, JS_NewInt32(context_, v));
}


inline Value Context::NewInt64(int64_t v) {
	return Value(context_, JS_NewInt64(context_, v));
}


inline Value Context::NewUint32(uint32_t v) {
	return Value(context_, JS_NewUint32(context_, v));
}


inline Value Context::NewBigInt64(int32_t v) {
	return Value(context_, JS_NewBigInt64(context_, v));
}


inline Value Context::NewBigUint64(int64_t v) {
	return Value(context_, JS_NewBigUint64(context_, v));
}


inline Value Context::NewFloat64(double v) {
	return Value(context_, JS_NewFloat64(context_, v));
}

inline Value Context::NewString(const char* str) {
	return Value(context_, JS_NewString(context_, str));
}

inline Value Context::NewString(const char* str, size_t len) {
	return Value(context_, JS_NewStringLen(context_, str, len));
}

inline Value Context::NewObject() {
	return Value(context_, JS_NewObject(context_));
}

inline Value Context::NewArray() {
	return Value(context_, JS_NewArray(context_));
}

inline Value Context::NewClassObject(JSClassID class_id) {
	return Value(context_, JS_NewObjectClass(context_, class_id));
}

inline Value Context::NewArrayBuffer(const uint8_t* buf, size_t len) {
	return Value(context_, JS_NewArrayBufferCopy(context_, buf, len));
}

inline Value Context::NewCFunction(JSCFunction* func, const char* name, size_t length) {
	return Value(context_, JS_NewCFunction(context_, func, name, length));
}

template<Value func(Context& context, ArgList& args)>
Value Context::NewFunction(const char* name) {
	return Value(context_, JS_NewCFunction(context_, 
		[](JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		Context* context = Context::get(ctx);
		ArgList arg_list(ctx, argc, argv);
		return func(*context, arg_list).Release();
		}, name, 0));

}

inline Value Context::Global() {
	return Value(context_, JS_GetGlobalObject(context_));
}

inline Value Context::Excute(const char* input, size_t input_len,
	const char* filename) {
	return Value(context_, JS_Eval(context_, input, input_len, filename,
		JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_STRICT));
}

inline Value Context::Excute(const char* input, size_t input_len,
	const char* filename, int flags) {
	return Value(context_, JS_Eval(context_, input, input_len, filename, flags));
}

inline Value Context::Compile(const char* input, size_t input_len,
	const char* filename) {
	return Value(context_, JS_Eval(context_, input, input_len, filename,
		JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_STRICT | JS_EVAL_FLAG_COMPILE_ONLY));
}

inline Context* Module::context() {
	return Context::get(context_);
}

inline bool Module::ExportCFunc(const char* name, JSCFunction* func) {
	return Export(name, JS_NewCFunction(context_, func, name, 0));
}

template<Value func(Context& context, ArgList& args)>
bool Module::ExportFunc(const char* name) {
	return Export(name,JS_NewCFunction(context_, 
		[](JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		Context* context = Context::get(ctx);
		ArgList arg_list(ctx, argc, argv);
		return func(*context, arg_list).Release();
		}, name, 0));
}

}//namespace

