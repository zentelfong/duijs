#include "Util.h"

namespace duijs {

static inline DuiLib::CTreeNodeUI* toTreeNode(const qjs::Value& value) {
	return qjs::Class<DuiLib::CTreeNodeUI>::ToC(value);
}

static Value add(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->Add(toTreeNode(args[0])));
}

static Value addAt(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (int32_t)pThis->AddAt(toTreeNode(args[0]),args[1].ToInt32()));
}

static Value remove(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->Remove(toTreeNode(args[0])));
}

static Value removeAt(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->RemoveAt(args[0].ToInt32()));
}

static Value removeAll(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->RemoveAll();
	return undefined_value;
}

static Value setItemCheckBox(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SetItemCheckBox(args[0].ToBool(),toTreeNode(args[1])));
}

static Value setItemExpand(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemExpand(args[0].ToBool(), toTreeNode(args[1]));
	return undefined_value;
}


static Value setVisibleFolderBtn(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetVisibleFolderBtn(args[0].ToBool());
	return undefined_value;
}

static Value getVisibleFolderBtn(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetVisibleFolderBtn());
}


static Value setVisibleCheckBtn(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetVisibleCheckBtn(args[0].ToBool());
	return undefined_value;
}

static Value getVisibleCheckBtn(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetVisibleCheckBtn());
}

static Value setItemMinWidth(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemMinWidth(args[0].ToUint32());
	return undefined_value;
}

static Value getItemMinWidth(CTreeViewUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemMinWidth());
}

static Value setItemTextColor(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value setItemHotTextColor(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemHotTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value setSelItemTextColor(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelItemTextColor(args[0].ToUint32());
	return undefined_value;
}


static Value setSelItemHotTextColor(CTreeViewUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelItemHotTextColor(args[0].ToUint32());
	return undefined_value;
}



void RegisterTreeView(qjs::Module* module) {
	DEFINE_CONTROL2(CTreeViewUI, CListUI, "TreeView");
	ADD_FUNCTION(add);
	ADD_FUNCTION(addAt);
	ADD_FUNCTION(remove);
	ADD_FUNCTION(removeAt);
	ADD_FUNCTION(removeAll);
	ADD_FUNCTION(setItemCheckBox);
	ADD_FUNCTION(setItemExpand);
	ADD_FUNCTION(setVisibleFolderBtn);
	ADD_FUNCTION(getVisibleFolderBtn);
	ADD_FUNCTION(setVisibleCheckBtn);
	ADD_FUNCTION(getVisibleCheckBtn);
	ADD_FUNCTION(setItemMinWidth);
	ADD_FUNCTION(getItemMinWidth);
	ADD_FUNCTION(setItemTextColor);
	ADD_FUNCTION(setItemHotTextColor);
	ADD_FUNCTION(setSelItemTextColor);
	ADD_FUNCTION(setSelItemHotTextColor);
}


}//namespace
