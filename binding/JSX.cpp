#include "Util.h"

namespace duijs {

//全局jsx函数 tag,atts,kids
static Value jsxFunc(Context& context, ArgList& args) {
	auto tag = args[0].ToString();


	//创建control
	CDuiString tagName(tag.str(), tag.len());
	CDuiString strClass;
	strClass.Format(_T("C%sUI"), tagName.GetData());
	CControlUI *pControl = dynamic_cast<CControlUI*>(
		CControlFactory::GetInstance()->CreateControl(strClass));

	if (!pControl) {
		return undefined_value;
	}

	//保存属性值，控件init时应用
	auto attrs = args[1];
	if (attrs.IsObject()) {
		auto attrsMap = attrs.GetProperties();
		for (auto itr = attrsMap.begin(); itr != attrsMap.end(); ++itr) {
			CDuiString name(itr->first.c_str());
			CDuiString value(itr->second.ToStdString().c_str());
			pControl->SaveAttribute(name, value);
		}
	}

	//添加子控件
	auto child = toControl(args[2]);
	if (child) {
		auto pContainer = static_cast<IContainerUI*>(pControl->GetInterface(_T("IContainer")));
		if(pContainer)
			pContainer->Add(child);
	}
	return toValue(context, pControl);
}

void RegisterJSX(qjs::Context* context) {
	context->Global().SetProperty("JSX", context->NewFunction<jsxFunc>("JSX"));
}


}//namespace
