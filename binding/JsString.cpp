#include "quickjs/qjs.h"
#include "ngx_str.h"

namespace duijs {
using namespace qjs;

static Value excapeSql(Context& context, ArgList& args) {
	if (!args[0].IsString()) {
		return undefined_value;
	}

	auto src = args[0].ToString();

	std::string dest;
	ngx_uint_t len = ngx_escape_sql_str(nullptr, (u_char*)src.str(), src.len());
	dest.resize(len);
	ngx_escape_sql_str((u_char*)dest.data(), (u_char*)src.str(), src.len());

	return context.NewString(dest.c_str(), dest.length());
}

static Value excapeJson(Context& context, ArgList& args) {
	if (!args[0].IsString()) {
		return undefined_value;
	}

	auto src = args[0].ToString();

	std::string dest;
	ngx_uint_t len = ngx_escape_json(nullptr, (u_char*)src.str(), src.len());
	dest.resize(len);
	ngx_escape_json((u_char*)dest.data(), (u_char*)src.str(), src.len());

	return context.NewString(dest.c_str(), dest.length());
}

static Value base64Encode(Context& context, ArgList& args) {
	if (args[0].IsString()) {
		auto str = args[0].ToString();

		ngx_str_t src;
		src.data = (u_char*)str.str();
		src.len = str.len();

		ngx_str_t dest;
		dest.data = (u_char*)malloc(BASE64_ENCODE_OUT_SIZE(src.len));
		dest.len = BASE64_ENCODE_OUT_SIZE(src.len);

		ngx_encode_base64(&dest, &src);

		auto result = context.NewString((char*)dest.data, dest.len);
		free(dest.data);
		return result;
	} else if (args[0].IsArray()) {
		size_t len;
		uint8_t* data = args[0].GetArrayBuffer(&len);

		ngx_str_t src;
		src.data = (u_char*)data;
		src.len = len;

		ngx_str_t dest;
		dest.data = (u_char*)malloc(BASE64_ENCODE_OUT_SIZE(src.len));
		dest.len = BASE64_ENCODE_OUT_SIZE(src.len);

		ngx_encode_base64(&dest, &src);

		auto result = context.NewString((char*)dest.data, dest.len);
		free(dest.data);
		return result;
	}
	return undefined_value;
}

static Value base64Decode(Context& context, ArgList& args) {
	if (!args[0].IsString()) {
		return undefined_value;
	}

	auto str = args[0].ToString();

	ngx_str_t src;
	src.data = (u_char*)str.str();
	src.len = str.len();

	ngx_str_t dest;
	dest.data = (u_char*)malloc(BASE64_DECODE_OUT_SIZE(src.len));
	dest.len = BASE64_DECODE_OUT_SIZE(src.len);

	ngx_decode_base64(&dest, &src);

	auto result = context.NewArrayBuffer((uint8_t*)dest.data, dest.len);
	free(dest.data);
	return result;
}



#define ADD_FUNCTION2(name) str_module.SetProperty(#name,context->NewFunction<name>(#name));

void RegisterString(qjs::Module* module) {
	auto context = module->context();
	auto str_module = context->NewObject();
	ADD_FUNCTION2(excapeSql);
	ADD_FUNCTION2(excapeJson);
	ADD_FUNCTION2(base64Encode);
	ADD_FUNCTION2(base64Decode);

	module->Export("String", str_module);
}


}//namespace
