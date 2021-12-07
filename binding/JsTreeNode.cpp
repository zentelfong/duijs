#include "Util.h"

namespace duijs {

static inline DuiLib::CTreeNodeUI* toTreeNode(const qjs::Value& value) {
	return qjs::WeakClass<DuiLib::CTreeNodeUI>::ToC(value);
}


static Value select(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->Select(args[0].ToBool()));
}

static Value selectMulti(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SelectMulti(args[0].ToBool()));
}

static Value add(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->Add(toControl(args[0])));
}

static Value addAt(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->AddAt(toControl(args[0]),args[1].ToInt32()));
}

static Value remove(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->Remove(toControl(args[0])));
}

static Value setVisibleTag(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetVisibleTag(args[0].ToBool());
	return undefined_value;
}

static Value getVisibleTag(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetVisibleTag());
}


static Value setItemText(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemText(JsString(args[0]));
	return undefined_value;
}

static Value getItemText(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemText());
}

static Value checkBoxSelected(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->CheckBoxSelected(args[0].ToBool());
	return undefined_value;
}

static Value isCheckBoxSelected(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsCheckBoxSelected());
}

static Value isHasChild(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsHasChild());
}

static Value addChildNode(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->AddChildNode(toTreeNode(args[0])));
}

static Value removeAt(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->RemoveAt(toTreeNode(args[0])));
}

static Value setParentNode(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetParentNode(toTreeNode(args[0]));
	return undefined_value;
}

static Value getParentNode(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetParentNode());
}


static Value getCountChild(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (int32_t)pThis->GetCountChild());
}


static Value getChildNode(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return WeakClass<CTreeNodeUI>::ToJs(context, pThis->GetChildNode(args[0].ToInt32())->get_weak_ptr<CTreeNodeUI>());
}

static Value setVisibleFolderBtn(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetVisibleFolderBtn(args[0].ToBool());
	return undefined_value;
}

static Value getVisibleFolderBtn(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetVisibleFolderBtn());
}

static Value setVisibleCheckBtn(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetVisibleCheckBtn(args[0].ToBool());
	return undefined_value;
}

static Value getVisibleCheckBtn(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetVisibleCheckBtn());
}

static Value setItemTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getItemTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemTextColor());
}


static Value setItemHotTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemHotTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getItemHotTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemHotTextColor());
}

static Value setSelItemTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelItemTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getSelItemTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelItemTextColor());
}

static Value setSelItemHotTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelItemHotTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getSelItemHotTextColor(CTreeNodeUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelItemHotTextColor());
}


void RegisterTreeNode(qjs::Module* module) {
	DEFINE_CONTROL2(CTreeNodeUI, CListContainerElementUI, "TreeNode");
	ADD_FUNCTION(select);
	ADD_FUNCTION(selectMulti);
	ADD_FUNCTION(add);
	ADD_FUNCTION(addAt);
	ADD_FUNCTION(remove);
	ADD_FUNCTION(setVisibleTag);
	ADD_FUNCTION(getVisibleTag);
	ADD_FUNCTION(setItemText);
	ADD_FUNCTION(getItemText);
	ADD_FUNCTION(checkBoxSelected);
	ADD_FUNCTION(isCheckBoxSelected);
	ADD_FUNCTION(isHasChild);
	ADD_FUNCTION(addChildNode);
	ADD_FUNCTION(removeAt);
	ADD_FUNCTION(setParentNode);
	ADD_FUNCTION(getParentNode);
	ADD_FUNCTION(getCountChild);
	ADD_FUNCTION(getChildNode);
	ADD_FUNCTION(setVisibleFolderBtn);
	ADD_FUNCTION(getVisibleFolderBtn);
	ADD_FUNCTION(setVisibleCheckBtn);
	ADD_FUNCTION(getVisibleCheckBtn);
	ADD_FUNCTION(setItemTextColor);
	ADD_FUNCTION(getItemTextColor);
	ADD_FUNCTION(setItemHotTextColor);
	ADD_FUNCTION(getItemHotTextColor);
	ADD_FUNCTION(setSelItemTextColor);
	ADD_FUNCTION(getSelItemTextColor);
	ADD_FUNCTION(setSelItemHotTextColor);
	ADD_FUNCTION(getSelItemHotTextColor);
}


}//namespace
