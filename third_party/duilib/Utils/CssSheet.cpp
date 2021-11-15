#include "CssSheet.h"

CssSheet::CssSheet() {
}

CssSheet::~CssSheet() {
}

void CssSheet::OnParseSelector(CssSelectorMode mode, const css_str_t* str, void* ud) {
	CssSheet* pThis = static_cast<CssSheet*>(ud);
	switch (mode) {
	case CssSelectorMode::kSelectorBegin:
		pThis->current_ = std::make_shared<CssStyles>();
		break;
	case CssSelectorMode::kSelectorValue:
		if (str->len && str->data[0] == '.') {
			pThis->class_styles_[css_string(str->data + 1, str->len - 1)] = pThis->current_;
		}
		else if (str->len && str->data[0] == '#') {
			pThis->id_styles_[css_string(str->data + 1, str->len - 1)] = pThis->current_;
		}
		else {
			pThis->element_styles_[css_string(str->data, str->len)] = pThis->current_;
		}
		break;
	case CssSelectorMode::kSelectorEnd:
		break;
	}
}

void CssSheet::OnParseValue(const css_str_t* key, const css_str_t* value, void* ud) {
	CssSheet* pThis = static_cast<CssSheet*>(ud);
	if (pThis->current_) {
		(*pThis->current_)[css_string(key->data, key->len)] = css_string(value->data, value->len);
	}
}

bool CssSheet::Parse(const css_char* s) {
	bool rslt = css_parse(s, OnParseSelector, OnParseValue,this);
	current_ = nullptr;
	return rslt;
}

bool CssSheet::Parse(const css_string& s) {
	bool rslt = css_parse(s.c_str(), OnParseSelector, OnParseValue, this);
	current_ = nullptr;
	return rslt;
}

std::shared_ptr<CssStyles> CssSheet::GetStylesByClass(const css_string& key) {
	auto find = class_styles_.find(key);
	if (find != class_styles_.end()) {
		return find->second;
	} else {
		return nullptr;
	}
}

std::shared_ptr<CssStyles> CssSheet::GetStylesById(const css_string& key) {
	auto find = id_styles_.find(key);
	if (find != id_styles_.end()) {
		return find->second;
	} else {
		return nullptr;
	}
}

std::shared_ptr<CssStyles> CssSheet::GetStylesByElement(const css_string& key) {
	auto find = element_styles_.find(key);
	if (find != element_styles_.end()) {
		return find->second;
	} else {
		return nullptr;
	}
}

