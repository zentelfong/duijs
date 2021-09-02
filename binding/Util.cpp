#include "Util.h"

namespace duijs {

std::string Wide2UTF8(const std::wstring& strWide)
{
    int nUTF8 = ::WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), strWide.size(), NULL, 0, NULL, NULL);

    std::unique_ptr<char[]> buffer(new char[nUTF8 + 1]);
    if (!buffer)
    {
        return "";
    }

    ::WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), strWide.size(), buffer.get(), nUTF8, NULL, NULL);
    buffer[nUTF8] = '\0';

    return buffer.get();
}

std::string Wide2UTF8(LPCTSTR strWide) {

    int nUTF8 = ::WideCharToMultiByte(CP_UTF8, 0, strWide, -1, NULL, 0, NULL, NULL);
    std::unique_ptr<char[]> buffer(new char[nUTF8 + 1]);
    if (!buffer)
    {
        return "";
    }

    ::WideCharToMultiByte(CP_UTF8, 0, strWide, -1, buffer.get(), nUTF8, NULL, NULL);
    buffer[nUTF8] = '\0';
    return buffer.get();
}

RECT toRect(const qjs::Value& value) {
    RECT rc = {
        value.GetProperty("left").ToInt32(),
        value.GetProperty("top").ToInt32(),
        value.GetProperty("right").ToInt32(),
        value.GetProperty("bottom").ToInt32() };
    return rc;
}

qjs::Value toValue(qjs::Context& ctx, const RECT& rc) {
    auto value = ctx.NewObject();
    value.SetPropertyInt32("left", rc.left);
    value.SetPropertyInt32("top", rc.top);
    value.SetPropertyInt32("right", rc.right);
    value.SetPropertyInt32("bottom", rc.bottom);
    return value;
}


qjs::Value toValue(qjs::Context& ctx, LPCTSTR str) {
    std::string utf8 = Wide2UTF8(str);
    return ctx.NewString(utf8.c_str(),utf8.length());
}


POINT toPoint(const qjs::Value& value) {
    POINT pt = {
        value.GetProperty("x").ToInt32(),
        value.GetProperty("y").ToInt32()
    };
    return pt;
}

qjs::Value toValue(qjs::Context& ctx, const POINT& pt) {
    auto value = ctx.NewObject();
    value.SetPropertyInt32("x", pt.x);
    value.SetPropertyInt32("y", pt.y);
    return value;
}

SIZE toSize(const qjs::Value& value) {
    SIZE pt = {
        value.GetProperty("cx").ToInt32(),
        value.GetProperty("cy").ToInt32()
    };
    return pt;
}

qjs::Value toValue(qjs::Context& ctx, const SIZE& pt) {
    auto value = ctx.NewObject();
    value.SetPropertyInt32("cx", pt.cx);
    value.SetPropertyInt32("cy", pt.cy);
    return value;
}

qjs::Value toValue(qjs::Context& ctx, const DuiLib::TPercentInfo& b) {
    auto value = ctx.NewObject();
    value.SetPropertyFloat64("left", b.left);
    value.SetPropertyFloat64("top", b.top);
    value.SetPropertyFloat64("right", b.right);
    value.SetPropertyFloat64("bottom", b.bottom);
    return value;
}

DuiLib::TPercentInfo toPercentInfo(const qjs::Value& value) {
    DuiLib::TPercentInfo rc = {
        value.GetProperty("left").ToFloat64(),
        value.GetProperty("top").ToFloat64(),
        value.GetProperty("right").ToFloat64(),
        value.GetProperty("bottom").ToFloat64() };
    return rc;
}


}//namespace
