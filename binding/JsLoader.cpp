
#include "quickjs/qjs.h"
#include "duilib/UIlib.h"

namespace duijs{

using namespace DuiLib;

int has_suffix(const char* str, const char* suffix)
{
	size_t len = strlen(str);
	size_t slen = strlen(suffix);
	return (len >= slen && !memcmp(str + len - slen, suffix, slen));
}


typedef JSModuleDef* (JSInitModuleFunc)(JSContext* ctx,
	const char* module_name);

static JSModuleDef* js_module_loader_dll(JSContext* ctx,
	const char* module_name)
{
	JSModuleDef* m;
	HMODULE hd;
	JSInitModuleFunc* init;
	char* filename;

	if (!strchr(module_name, '/')) {
		/* must add a '/' so that the DLL is not searched in the
		   system library paths */
		filename = (char*)js_malloc(ctx, strlen(module_name) + 2 + 1);
		if (!filename)
			return NULL;
		strcpy(filename, "./");
		strcpy(filename + 2, module_name);
	}
	else {
		filename = (char*)module_name;
	}

	/* C module */
	hd = LoadLibraryA(filename);
	if (filename != module_name)
		js_free(ctx, filename);

	if (!hd) {
		JS_ThrowReferenceError(ctx, "could not load module filename '%s' as shared library",
			module_name);
		goto fail;
	}

	init = (JSInitModuleFunc*)GetProcAddress(hd, "js_init_module");
	if (!init) {
		JS_ThrowReferenceError(ctx, "could not load module filename '%s': js_init_module not found",
			module_name);
		goto fail;
	}

	m = init(ctx, module_name);
	if (!m) {
		JS_ThrowReferenceError(ctx, "could not load module filename '%s': initialization error",
			module_name);
	fail:
		if (hd)
			FreeLibrary(hd);
		return NULL;
	}
	return m;
}

JSModuleDef* jsModuleLoader(JSContext* ctx,
	const char* module_name, void* opaque)
{
	JSModuleDef* m;

	if (has_suffix(module_name, ".dll")) {
		m = js_module_loader_dll(ctx, module_name);
	}
	else {
		DWORD buf_len;
		JSValue func_val;
		BYTE* buf;

#if _UNICODE
		TCHAR errorMsg[64];
		TCHAR* name = a2w(module_name, CP_UTF8);
		buf = CResourceManager::LoadFile(name, &buf_len, errorMsg);
		delete[] name;
#else
		buf = CResourceManager::LoadFile(module_name, &buf_len, errorMsg);
#endif
		if (!buf) {
			JS_ThrowReferenceError(ctx, "could not load module filename '%s'",
				module_name);
			return NULL;
		}

		/* compile the module */
		func_val = JS_Eval(ctx, (char*)buf, buf_len, module_name,
			JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);

		delete[] buf;

		if (JS_IsException(func_val))
			return NULL;
		/* XXX: could propagate the exception */
		js_module_set_import_meta(ctx, func_val, TRUE, FALSE);
		/* the module is already referenced, so we must free it */
		m = (JSModuleDef*)JS_VALUE_GET_PTR(func_val);
		JS_FreeValue(ctx, func_val);
	}
	return m;
}



}//namespace

