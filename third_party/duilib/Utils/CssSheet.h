#pragma once
#include <memory>
#include <map>
#include <string>
#include "CssParser.h"

#if _UNICODE
typedef std::wstring css_string;
#else
typedef std::string css_string;
#endif

typedef std::map<css_string, css_string> CssStyles;

class CssSheet {
public:
	CssSheet();
	~CssSheet();

	bool Parse(const css_char* s);
	bool Parse(const css_string& s);

	std::shared_ptr<CssStyles> GetStylesByClass(const css_string& key);
	std::shared_ptr<CssStyles> GetStylesById(const css_string& key);
	std::shared_ptr<CssStyles> GetStylesByElement(const css_string& key);
private:
	static void OnParseSelector(CssSelectorMode mode,const css_str_t* str, void* ud);
	static void OnParseValue(const css_str_t* key, const css_str_t* value, void* ud);

	std::shared_ptr<CssStyles> current_;
	std::map<css_string,std::shared_ptr<CssStyles>> class_styles_;//.a{}
	std::map<css_string,std::shared_ptr<CssStyles>> id_styles_;//#a{}
	std::map<css_string,std::shared_ptr<CssStyles>> element_styles_;//a {}
};

