#pragma once
#include <stdlib.h>

#if _UNICODE
typedef wchar_t css_char;
#else
typedef char css_char;
#endif

typedef struct{
	const css_char* data;
	size_t len;
}css_str_t;

enum class CssSelectorMode{
	kSelectorBegin,
	kSelectorValue,
	kSelectorEnd,
};

typedef void (*parse_selector_func)(CssSelectorMode mode,const css_str_t* sel,void* ud);
typedef void (*parse_value_func)(const css_str_t* key, const css_str_t* value,void* ud);

bool css_parse(const css_char* str, parse_selector_func selector_func, parse_value_func value_func, void* ud);

bool css_parse(const css_char* str, parse_value_func value_func, void* ud);

//解析 rgb(0,0,255) 类似的函数
typedef void(*parse_func_func)(const css_str_t* func_name, const css_str_t* argv,size_t argc, void* ud);
bool css_parse_func(const css_char* str, parse_func_func value_func, void* ud);
