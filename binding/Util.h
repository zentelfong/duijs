#pragma once
#include "quickjs/qjs.h"
#include "duilib/UIlib.h"

namespace duijs {

using namespace qjs;
using namespace DuiLib;


template<class T>
static T* createControl(qjs::Context& context, qjs::ArgList& args) {
	return new T();
}

template<class T>
static void deleteControl(T* w) {
}

#define DEFINE_CONTROL(class_,name_) \
	auto ctrl = module->ExportClass<class_>(name_); \
	ctrl.Init<deleteControl>(); \
	ctrl.AddCtor<createControl>()

#define DEFINE_CONTROL2(class_,parent_,name_) \
	auto ctrl = module->ExportClass<class_>(name_); \
	ctrl.Init<deleteControl>(Class<parent_>::class_id()); \
	ctrl.AddCtor<createControl>()

#define ADD_FUNCTION(name) ctrl.AddFunc<name>(#name)

#define EXPORT_CONST_VALUE(name) module->ExportUint32(#name,(uint32_t)name)


std::string Wide2UTF8(const std::wstring& strWide);
std::string Wide2UTF8(LPCTSTR strWide);

qjs::Value toValue(qjs::Context& ctx, LPCTSTR str);
DuiLib::CDuiString toString(const qjs::Value& value);


inline qjs::Value toValue(qjs::Context& ctx, bool b) {
	return ctx.NewBool(b);
}

inline qjs::Value toValue(qjs::Context& ctx, int32_t b) {
	return ctx.NewInt32(b);
}

inline qjs::Value toValue(qjs::Context& ctx, uint32_t b) {
	return ctx.NewUint32(b);
}

RECT toRect(const qjs::Value& value);
qjs::Value toValue(qjs::Context& ctx,const RECT& rc);


POINT toPoint(const qjs::Value& value);
qjs::Value toValue(qjs::Context& ctx, const POINT& pt);

SIZE toSize(const qjs::Value& value);
qjs::Value toValue(qjs::Context& ctx, const SIZE& pt);


qjs::Value toValue(qjs::Context& ctx, const DuiLib::TPercentInfo& b);
DuiLib::TPercentInfo toPercentInfo(const qjs::Value& value);


DuiLib::CControlUI* toControl(const qjs::Value& value);
qjs::Value toValue(qjs::Context& ctx, DuiLib::CControlUI* control);


SYSTEMTIME toSysTime(const qjs::Value& value);
qjs::Value toValue(qjs::Context& ctx, const SYSTEMTIME& time);



}//namespace
