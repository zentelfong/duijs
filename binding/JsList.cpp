#include "Util.h"

namespace duijs {


static Value getScrollSelect(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetScrollSelect());
}

static Value setScrollSelect(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetScrollSelect(args[0].ToBool());
	return undefined_value;
}

static Value getCurSel(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCurSel());
}



static Value getCurSelActivate(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCurSelActivate());
}


static Value selectItem(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SelectItem(args[0].ToInt32(),args[1].ToBool()));
}


static Value selectItemActivate(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SelectItemActivate(args[0].ToInt32()));
}

static Value selectMultiItem(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SelectMultiItem(args[0].ToInt32(), args[1].ToBool()));
}

static Value setMultiSelect(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetMultiSelect(args[0].ToBool());
	return undefined_value;
}

static Value isMultiSelect(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsMultiSelect());
}


static Value unSelectItem(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->UnSelectItem(args[0].ToInt32(), args[1].ToBool()));
}

static Value selectAllItems(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SelectAllItems();
	return undefined_value;
}

static Value unSelectAllItems(CListUI* pThis, Context& context, ArgList& args) {
	pThis->UnSelectAllItems();
	return undefined_value;
}

static Value getSelectItemCount(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectItemCount());
}


static Value getNextSelItem(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetNextSelItem(args[0].ToInt32()));
}


static Value isFixedScrollbar(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsFixedScrollbar());
}

static Value setFixedScrollbar(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetFixedScrollbar(args[0].ToBool());
	return undefined_value;
}


//CListHeaderUI* GetHeader() const;
//CContainerUI* GetList() const;
//UINT GetListType();
//TListInfoUI* GetListInfo();



static Value getItemAt(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemAt(args[0].ToInt32()));
}


static Value getItemIndex(CListUI* pThis, Context& context, ArgList& args) {
	auto ctrl = toControl(args[0]);
	if (ctrl)
		return toValue(context, pThis->GetItemIndex(ctrl));
	else
		return undefined_value;
}


static Value setItemIndex(CListUI* pThis, Context& context, ArgList& args) {
	auto ctrl = toControl(args[0]);
	if(ctrl)
		return toValue(context,pThis->SetItemIndex(ctrl,args[1].ToInt32()));
	return undefined_value;
}

static Value getCount(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCount());
}


static Value add(CListUI* pThis, Context& context, ArgList& args) {
	auto ctrl = toControl(args[0]);
	if (ctrl)
		return toValue(context, pThis->Add(ctrl));
	return undefined_value;
}

static Value addAt(CListUI* pThis, Context& context, ArgList& args) {
	auto ctrl = toControl(args[0]);
	if (ctrl)
		return toValue(context, pThis->AddAt(ctrl,args[1].ToInt32()));
	return undefined_value;
}

static Value remove(CListUI* pThis, Context& context, ArgList& args) {
	auto ctrl = toControl(args[0]);
	if (ctrl)
		return toValue(context, pThis->Remove(ctrl));
	return undefined_value;
}

static Value removeAt(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->RemoveAt(args[0].ToInt32()));
}

static Value removeAll(CListUI* pThis, Context& context, ArgList& args) {
	pThis->RemoveAll();
	return undefined_value;
}


static Value ensureVisible(CListUI* pThis, Context& context, ArgList& args) {
	pThis->EnsureVisible(args[0].ToInt32());
	return undefined_value;
}

static Value scroll(CListUI* pThis, Context& context, ArgList& args) {
	pThis->Scroll(args[0].ToInt32(),args[1].ToInt32());
	return undefined_value;
}

static Value setItemFont(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemFont(args[0].ToInt32());
	return undefined_value;
}


static Value setItemTextStyle(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextStyle(args[0].ToInt32());
	return undefined_value;
}


static Value setItemTextPadding(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextPadding(toRect(args[0]));
	return undefined_value;
}

static Value setItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextColor(args[0].ToInt32());
	return undefined_value;
}

static Value setItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemBkColor(args[0].ToInt32());
	return undefined_value;
}
static Value setItemBkImage(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemBkImage(JsString(args[0]));
	return undefined_value;
}
static Value setAlternateBk(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetAlternateBk(args[0].ToBool());
	return undefined_value;
}
static Value setSelectedItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedItemTextColor(args[0].ToInt32());
	return undefined_value;
}
static Value setSelectedItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedItemBkColor(args[0].ToInt32());
	return undefined_value;
}
static Value setSelectedItemImage(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedItemImage(JsString(args[0]));
	return undefined_value;
}

static Value setHotItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotItemTextColor(args[0].ToInt32());
	return undefined_value;
}

static Value setHotItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotItemBkColor(args[0].ToInt32());
	return undefined_value;
}

static Value setHotItemImage(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotItemImage(JsString(args[0]));
	return undefined_value;
}
static Value setDisabledItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledItemTextColor(args[0].ToInt32());
	return undefined_value;
}


static Value setDisabledItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledItemBkColor(args[0].ToInt32());
	return undefined_value;
}

static Value setDisabledItemImage(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledItemImage(JsString(args[0]));
	return undefined_value;
}

static Value setItemLineColor(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemLineColor(args[0].ToInt32());
	return undefined_value;
}

static Value setItemShowRowLine(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemShowRowLine(args[0].ToBool());
	return undefined_value;
}

static Value setItemShowColumnLine(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemShowColumnLine(args[0].ToBool());
	return undefined_value;
}

static Value isItemShowHtml(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->IsItemShowHtml());
}
static Value setItemShowHtml(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemShowHtml(args[0].ToBool());
	return undefined_value;
}

static Value isItemRSelected(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsItemRSelected());
}
static Value setItemRSelected(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemRSelected(args[0].ToBool());
	return undefined_value;
}


static Value getItemTextPadding(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemTextPadding());
}

static Value getItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemTextColor());
}

static Value getItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemBkColor());
}

static Value getItemBkImage(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemBkImage());
}

static Value isAlternateBk(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->IsAlternateBk());
}

static Value getSelectedItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelectedItemTextColor());
}


static Value getSelectedItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelectedItemBkColor());
}

static Value getSelectedItemImage(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedItemImage());
}

static Value getHotItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetHotItemTextColor());
}

static Value getHotItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetHotItemBkColor());
}

static Value getHotItemImage(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotItemImage());
}

static Value getDisabledItemTextColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledItemTextColor());
}

static Value getDisabledItemBkColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledItemBkColor());
}

static Value getDisabledItemImage(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledItemImage());
}

static Value getItemLineColor(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemLineColor());
}

static Value setMultiExpanding(CListUI* pThis, Context& context, ArgList& args) {
	pThis->SetMultiExpanding(args[0].ToBool());
	return undefined_value;
}


static Value getExpandedItem(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetExpandedItem());
}

static Value expandItem(CListUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->ExpandItem(args[0].ToInt32(),args[1].ToBool()));
}


//IListCallbackUI* GetTextCallback() const;
//void SetTextCallback(IListCallbackUI* pCallback);

static int CALLBACK sortListFunc(UINT_PTR ctrl1, UINT_PTR ctrl2, UINT_PTR ud) {
	CControlUI* pControl1 = (CControlUI*)ctrl1;
	CControlUI* pControl2 = (CControlUI*)ctrl2;

	Value* func = (Value*)ud;

	auto context = func->context();
	Value rslt = func->Call(toValue(*context, pControl1), toValue(*context, pControl2));
	if (rslt.IsException()) {
		context->DumpError();
		return -1;
	}
	return rslt.ToInt32();
}

static Value sortItems(CListUI* pThis, Context& context, ArgList& args) {
	Value func = args[0];
	if (!func.IsFunction())
		return false_value;
	return toValue(context, (bool)pThis->SortItems(sortListFunc,(UINT_PTR)&func));
}


void RegisterList(qjs::Module* module) {
	DEFINE_CONTROL2(CListUI, CVerticalLayoutUI, "List");
	ADD_FUNCTION(getScrollSelect);
	ADD_FUNCTION(setScrollSelect);
	ADD_FUNCTION(getCurSel);
	ADD_FUNCTION(getCurSelActivate);
	ADD_FUNCTION(selectItem);
	ADD_FUNCTION(selectItemActivate);
	ADD_FUNCTION(selectMultiItem);
	ADD_FUNCTION(setMultiSelect);
	ADD_FUNCTION(isMultiSelect);
	ADD_FUNCTION(unSelectItem);
	ADD_FUNCTION(selectAllItems);
	ADD_FUNCTION(unSelectAllItems);
	ADD_FUNCTION(getSelectItemCount);
	ADD_FUNCTION(getNextSelItem);
	ADD_FUNCTION(isFixedScrollbar);
	ADD_FUNCTION(setFixedScrollbar);
	ADD_FUNCTION(getItemAt);
	ADD_FUNCTION(getItemIndex);
	ADD_FUNCTION(setItemIndex);
	ADD_FUNCTION(getCount);
	ADD_FUNCTION(add);
	ADD_FUNCTION(addAt);
	ADD_FUNCTION(remove);
	ADD_FUNCTION(removeAt);
	ADD_FUNCTION(removeAll);
	ADD_FUNCTION(ensureVisible);
	ADD_FUNCTION(scroll);
	ADD_FUNCTION(removeAt);
	ADD_FUNCTION(setItemFont);
	ADD_FUNCTION(setItemTextStyle);
	ADD_FUNCTION(setItemTextPadding);
	ADD_FUNCTION(setItemTextColor);
	ADD_FUNCTION(setItemBkColor);
	ADD_FUNCTION(setItemBkImage);
	ADD_FUNCTION(setAlternateBk);
	ADD_FUNCTION(setSelectedItemTextColor);
	ADD_FUNCTION(setSelectedItemBkColor);
	ADD_FUNCTION(setSelectedItemImage);
	ADD_FUNCTION(setHotItemTextColor);
	ADD_FUNCTION(setHotItemBkColor);
	ADD_FUNCTION(setHotItemImage);
	ADD_FUNCTION(setDisabledItemTextColor);
	ADD_FUNCTION(setDisabledItemBkColor);
	ADD_FUNCTION(setDisabledItemImage);
	ADD_FUNCTION(setItemLineColor);
	ADD_FUNCTION(setItemShowRowLine);
	ADD_FUNCTION(setItemShowColumnLine);
	ADD_FUNCTION(isItemShowHtml);
	ADD_FUNCTION(setItemShowHtml);
	ADD_FUNCTION(isItemRSelected);
	ADD_FUNCTION(setItemRSelected);
	ADD_FUNCTION(getItemTextPadding);
	ADD_FUNCTION(getItemTextColor);
	ADD_FUNCTION(getItemBkColor);
	ADD_FUNCTION(getItemBkImage);
	ADD_FUNCTION(isAlternateBk);
	ADD_FUNCTION(getSelectedItemTextColor);
	ADD_FUNCTION(getSelectedItemBkColor);
	ADD_FUNCTION(getSelectedItemImage);
	ADD_FUNCTION(getHotItemTextColor);
	ADD_FUNCTION(getHotItemBkColor);
	ADD_FUNCTION(getHotItemImage);
	ADD_FUNCTION(getDisabledItemTextColor);
	ADD_FUNCTION(getDisabledItemBkColor);
	ADD_FUNCTION(getDisabledItemImage);
	ADD_FUNCTION(getItemLineColor);
	ADD_FUNCTION(setMultiExpanding);
	ADD_FUNCTION(getExpandedItem);
	ADD_FUNCTION(expandItem);
	ADD_FUNCTION(sortItems);
}


}//namespace
