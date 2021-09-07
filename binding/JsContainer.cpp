#include "duilib/UIlib.h"
#include "Util.h"

namespace duijs {

using namespace qjs;
using namespace DuiLib;

static CContainerUI* newControl(Context& context, ArgList& args) {
	return new CContainerUI();
}

static void deleteControl(CContainerUI* w) {
}

static Value getItemAt(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemAt(args[0].ToInt32()));
}

static Value getItemIndex(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetItemIndex(toControl(args[0])));
}

static Value setItemIndex(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->SetItemIndex(toControl(args[0]),args[1].ToInt32()));
}

static Value getCount(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->GetCount());
}

static Value add(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->Add(toControl(args[0])));
}

static Value addAt(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->AddAt(toControl(args[0]), args[1].ToInt32()));
}

static Value remove(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->Remove(toControl(args[0])));
}

static Value removeAt(CContainerUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->RemoveAt(args[0].ToInt32()));
}

static Value removeAll(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->RemoveAll();
	return undefined_value;
}


static Value getInset(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetInset());
}

static Value setInset(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetInset(toRect(args[0]));
	return undefined_value;
}

static Value getChildPadding(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetChildPadding());
}

static Value setChildPadding(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetChildPadding(args[0].ToInt32());
	return undefined_value;
}

static Value getChildAlign(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetChildAlign());
}

static Value setChildAlign(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetChildAlign(args[0].ToUint32());
	return undefined_value;
}

static Value getChildVAlign(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetChildVAlign());
}

static Value setChildVAlign(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetChildVAlign(args[0].ToUint32());
	return undefined_value;
}

static Value isAutoDestroy(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsAutoDestroy());
}

static Value setAutoDestroy(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoDestroy(args[0].ToBool());
	return undefined_value;
}

static Value isDelayedDestroy(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsDelayedDestroy());
}

static Value setDelayedDestroy(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetDelayedDestroy(args[0].ToBool());
	return undefined_value;
}


static Value isMouseChildEnabled(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsMouseChildEnabled());
}

static Value setMouseChildEnabled(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetMouseChildEnabled(args[0].ToBool());
	return undefined_value;
}

static Value findSelectable(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->FindSelectable(args[0].ToInt32(),args[1].ToBool()));
}

static Value getClientPos(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetClientPos());
}


static Value setSubControlText(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	auto text = args[1].ToString();
	return toValue(context, 
		pThis->SetSubControlText(
			CDuiString(name.str(),name.len()),CDuiString(text.str(),text.len())));
}

static Value setSubControlFixedHeight(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->SetSubControlFixedHeight(
			CDuiString(name.str(), name.len()), args[1].ToInt32()));
}

static Value setSubControlFixedWidth(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->SetSubControlFixedWdith(
			CDuiString(name.str(), name.len()), args[1].ToInt32()));
}

static Value setSubControlUserData(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	auto text = args[1].ToString();
	return toValue(context,
		pThis->SetSubControlUserData(
			CDuiString(name.str(), name.len()), CDuiString(text.str(), text.len())));
}

static Value getSubControlText(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->GetSubControlText(
			CDuiString(name.str(), name.len())));
}


static Value getSubControlFixedHeight(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->GetSubControlFixedHeight(
			CDuiString(name.str(), name.len())));
}

static Value getSubControlFixedWidth(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->GetSubControlFixedWdith(
			CDuiString(name.str(), name.len())));
}

static Value getSubControlUserData(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->GetSubControlUserData(
			CDuiString(name.str(), name.len())));
}


static Value findSubControl(CContainerUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context,
		pThis->FindSubControl(
			CDuiString(name.str(), name.len())));
}

static Value getScrollPos(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,
		pThis->GetScrollPos());
}

static Value getScrollRange(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,
		pThis->GetScrollRange());
}

static Value setScrollPos(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetScrollPos(toSize(args[0]),args[1].ToBool());
	return undefined_value;
}

static Value setScrollStepSize(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->SetScrollStepSize(args[0].ToInt32());
	return undefined_value;
}

static Value getScrollStepSize(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,
		pThis->GetScrollStepSize());
}

static Value lineUp(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->LineUp();
	return undefined_value;
}

static Value lineDown(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->LineDown();
	return undefined_value;
}

static Value pageUp(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->PageUp();
	return undefined_value;
}

static Value pageDown(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->PageDown();
	return undefined_value;
}

static Value homeUp(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->HomeUp();
	return undefined_value;
}

static Value endDown(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->EndDown();
	return undefined_value;
}

static Value lineLeft(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->LineLeft();
	return undefined_value;
}

static Value lineRight(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->LineRight();
	return undefined_value;
}

static Value pageLeft(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->PageLeft();
	return undefined_value;
}

static Value pageRight(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->PageRight();
	return undefined_value;
}

static Value homeLeft(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->HomeLeft();
	return undefined_value;
}

static Value endRight(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->EndRight();
	return undefined_value;
}

static Value enableScrollBar(CContainerUI* pThis, Context& context, ArgList& args) {
	pThis->EnableScrollBar(args[0].ToBool(),args[1].ToBool());
	return undefined_value;
}

static Value getVerticalScrollBar(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetVerticalScrollBar());
}

static Value getHorizontalScrollBar(CContainerUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHorizontalScrollBar());
}

#define ADD_FUNCTION(name) ctrl.AddFunc<name>(#name)

void RegisterContainer(qjs::Module* module) {
	auto ctrl = module->ExportClass<CContainerUI>("Container");
	ctrl.Init<deleteControl>(Class<CControlUI>::class_id());
	ctrl.AddCtor<newControl>();
	ADD_FUNCTION(getItemAt);
	ADD_FUNCTION(getItemIndex);
	ADD_FUNCTION(setItemIndex);
	ADD_FUNCTION(getCount);
	ADD_FUNCTION(add);
	ADD_FUNCTION(addAt);
	ADD_FUNCTION(remove);
	ADD_FUNCTION(removeAt);
	ADD_FUNCTION(removeAll);
	ADD_FUNCTION(getInset);
	ADD_FUNCTION(setInset);
	ADD_FUNCTION(getChildPadding);
	ADD_FUNCTION(setChildPadding);
	ADD_FUNCTION(getChildAlign);
	ADD_FUNCTION(setChildAlign);
	ADD_FUNCTION(getChildVAlign);
	ADD_FUNCTION(setChildVAlign);
	ADD_FUNCTION(isAutoDestroy);
	ADD_FUNCTION(setAutoDestroy);
	ADD_FUNCTION(isDelayedDestroy);
	ADD_FUNCTION(setDelayedDestroy);
	ADD_FUNCTION(isMouseChildEnabled);
	ADD_FUNCTION(setMouseChildEnabled);
	ADD_FUNCTION(findSelectable);
	ADD_FUNCTION(getClientPos);
	ADD_FUNCTION(setSubControlText);
	ADD_FUNCTION(setSubControlFixedHeight);
	ADD_FUNCTION(setSubControlFixedWidth);
	ADD_FUNCTION(setSubControlUserData);
	ADD_FUNCTION(getSubControlText);
	ADD_FUNCTION(getSubControlFixedHeight);
	ADD_FUNCTION(getSubControlFixedWidth);
	ADD_FUNCTION(getSubControlUserData);
	ADD_FUNCTION(findSubControl);
	ADD_FUNCTION(getScrollPos);
	ADD_FUNCTION(getScrollRange);
	ADD_FUNCTION(setScrollPos);
	ADD_FUNCTION(setScrollStepSize);
	ADD_FUNCTION(getScrollStepSize);
	ADD_FUNCTION(lineUp);
	ADD_FUNCTION(lineDown);
	ADD_FUNCTION(pageUp);
	ADD_FUNCTION(pageDown);
	ADD_FUNCTION(homeUp);
	ADD_FUNCTION(endDown);
	ADD_FUNCTION(lineLeft);
	ADD_FUNCTION(lineRight);
	ADD_FUNCTION(pageLeft);
	ADD_FUNCTION(pageRight);
	ADD_FUNCTION(homeLeft);
	ADD_FUNCTION(endRight);
	ADD_FUNCTION(enableScrollBar);
	ADD_FUNCTION(getVerticalScrollBar);
	ADD_FUNCTION(getHorizontalScrollBar);

}

}//namespace

