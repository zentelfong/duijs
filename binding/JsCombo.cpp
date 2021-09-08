#include "Util.h"

namespace duijs {

static Value getTextStyle(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTextStyle());
}


static Value setTextStyle(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextStyle(args[0].ToUint32());
	return undefined_value;
}

static Value getTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetTextColor());
}


static Value setTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getDisabledTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledTextColor());
}


static Value setDisabledTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getFont(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFont());
}


static Value setFont(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetFont(args[0].ToInt32());
	return undefined_value;
}

static Value getTextPadding(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTextPadding());
}


static Value setTextPadding(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextPadding(toRect(args[0]));
	return undefined_value;
}


static Value isShowHtml(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsShowHtml());
}


static Value setShowHtml(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowHtml(args[0].ToBool());
	return undefined_value;
}


static Value isShowShadow(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsShowShadow());
}


static Value setShowShadow(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetShowShadow(args[0].ToBool());
	return undefined_value;
}


static Value getDropBoxAttributeList(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDropBoxAttributeList());
}


static Value setDropBoxAttributeList(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetDropBoxAttributeList(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value setDropBoxSize(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetDropBoxSize(toSize(args[0]));
	return undefined_value;
}


static Value getDropBoxSize(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDropBoxSize());
}


static Value getListType(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetListType());
}


static Value getCurSel(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCurSel());
}


static Value selectItem(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SelectItem(args[0].ToInt32(),args[1].ToBool());
	return undefined_value;
}

static Value selectMultiItem(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SelectMultiItem(args[0].ToInt32(), args[1].ToBool());
	return undefined_value;
}


static Value unSelectItem(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->UnSelectItem(args[0].ToInt32(), args[1].ToBool());
	return undefined_value;
}

static Value setItemIndex(CComboUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->SetItemIndex(toControl(args[0]), args[1].ToInt32()));
}


static Value getNormalImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetNormalImage());
}


static Value setNormalImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetNormalImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getHotImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotImage());
}


static Value setHotImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetHotImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getPushedImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetPushedImage());
}


static Value setPushedImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetPushedImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getFocusedImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFocusedImage());
}


static Value setFocusedImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetFocusedImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getDisabledImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledImage());
}


static Value setDisabledImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetDisabledImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value setScrollSelect(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetScrollSelect(args[0].ToBool());
	return undefined_value;
}


static Value getScrollSelect(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetScrollSelect());
}


static Value setItemFont(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemFont(args[0].ToInt32());
	return undefined_value;
}


static Value setItemTextStyle(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextStyle(args[0].ToUint32());
	return undefined_value;
}


static Value getItemTextPadding(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemTextPadding());
}
static Value setItemTextPadding(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextPadding(toRect(args[0]));
	return undefined_value;
}

static Value getItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(uint32_t) pThis->GetItemTextColor());
}
static Value setItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemBkColor());
}
static Value setItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemBkColor(args[0].ToUint32());
	return undefined_value;
}


static Value getItemBkImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetItemBkImage());
}


static Value setItemBkImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetItemBkImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value isAlternateBk(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsAlternateBk());
}

static Value setAlternateBk(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetAlternateBk(args[0].ToBool());
	return undefined_value;
}

static Value getSelectedItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(uint32_t)pThis->GetSelectedItemTextColor());
}

static Value setSelectedItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedItemTextColor(args[0].ToUint32());
	return undefined_value;
}


static Value getSelectedItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetSelectedItemBkColor());
}

static Value setSelectedItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelectedItemBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getSelectedItemImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelectedItemImage());
}


static Value setSelectedItemImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetSelectedItemImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value getHotItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetHotItemTextColor());
}

static Value setHotItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotItemTextColor(args[0].ToUint32());
	return undefined_value;
}


static Value getHotItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetHotItemBkColor());
}

static Value setHotItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotItemBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getHotItemImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotItemImage());
}


static Value setHotItemImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetHotItemImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getDisabledItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledItemTextColor());
}

static Value setDisabledItemTextColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledItemTextColor(args[0].ToUint32());
	return undefined_value;
}

static Value getDisabledItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetDisabledItemBkColor());
}

static Value setDisabledItemBkColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledItemBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getDisabledItemImage(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledItemImage());
}

static Value setDisabledItemImage(CComboUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetDisabledItemImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value getItemLineColor(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetItemLineColor());
}

static Value setItemLineColor(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemLineColor(args[0].ToUint32());
	return undefined_value;
}


static Value isItemShowHtml(CComboUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsItemShowHtml());
}

static Value setItemShowHtml(CComboUI* pThis, Context& context, ArgList& args) {
	pThis->SetItemShowHtml(args[0].ToBool());
	return undefined_value;
}

void RegisterCombo(qjs::Module* module) {
	DEFINE_CONTROL2(CComboUI, CContainerUI, "Combo");
	ADD_FUNCTION(getTextStyle);
	ADD_FUNCTION(setTextStyle);
	ADD_FUNCTION(getTextColor);
	ADD_FUNCTION(setTextColor);
	ADD_FUNCTION(getDisabledTextColor);
	ADD_FUNCTION(setDisabledTextColor);
	ADD_FUNCTION(getFont);
	ADD_FUNCTION(setFont);
	ADD_FUNCTION(getTextPadding);
	ADD_FUNCTION(setTextPadding);
	ADD_FUNCTION(isShowHtml);
	ADD_FUNCTION(setShowHtml);
	ADD_FUNCTION(isShowShadow);
	ADD_FUNCTION(setShowShadow);
	ADD_FUNCTION(getDropBoxAttributeList);
	ADD_FUNCTION(setDropBoxAttributeList);
	ADD_FUNCTION(setDropBoxSize);
	ADD_FUNCTION(getDropBoxSize);
	ADD_FUNCTION(getListType);
	ADD_FUNCTION(getCurSel);
	ADD_FUNCTION(selectItem);
	ADD_FUNCTION(selectMultiItem);
	ADD_FUNCTION(unSelectItem);
	ADD_FUNCTION(setItemIndex);
	ADD_FUNCTION(getNormalImage);
	ADD_FUNCTION(setNormalImage);
	ADD_FUNCTION(getHotImage);
	ADD_FUNCTION(setHotImage);
	ADD_FUNCTION(getPushedImage);
	ADD_FUNCTION(setPushedImage);
	ADD_FUNCTION(getFocusedImage);
	ADD_FUNCTION(setFocusedImage);
	ADD_FUNCTION(getDisabledImage);
	ADD_FUNCTION(setDisabledImage);
	ADD_FUNCTION(setScrollSelect);
	ADD_FUNCTION(getScrollSelect);
	ADD_FUNCTION(setItemFont);
	ADD_FUNCTION(setItemTextStyle);
	ADD_FUNCTION(getItemTextPadding);
	ADD_FUNCTION(setItemTextPadding);
	ADD_FUNCTION(getItemTextColor);
	ADD_FUNCTION(setItemTextColor);
	ADD_FUNCTION(getItemBkColor);
	ADD_FUNCTION(setItemBkColor);
	ADD_FUNCTION(getItemBkImage);
	ADD_FUNCTION(setItemBkImage);
	ADD_FUNCTION(isAlternateBk);
	ADD_FUNCTION(setAlternateBk);
	ADD_FUNCTION(getSelectedItemTextColor);
	ADD_FUNCTION(setSelectedItemTextColor);
	ADD_FUNCTION(getSelectedItemBkColor);
	ADD_FUNCTION(setSelectedItemBkColor);
	ADD_FUNCTION(getSelectedItemImage);
	ADD_FUNCTION(setSelectedItemImage);
	ADD_FUNCTION(getHotItemTextColor);
	ADD_FUNCTION(setHotItemTextColor);
	ADD_FUNCTION(getHotItemBkColor);
	ADD_FUNCTION(setHotItemBkColor);
	ADD_FUNCTION(getHotItemImage);
	ADD_FUNCTION(setHotItemImage);
	ADD_FUNCTION(getDisabledItemTextColor);
	ADD_FUNCTION(setDisabledItemTextColor);
	ADD_FUNCTION(getDisabledItemBkColor);
	ADD_FUNCTION(setDisabledItemBkColor);
	ADD_FUNCTION(getDisabledItemImage);
	ADD_FUNCTION(setDisabledItemImage);
	ADD_FUNCTION(getItemLineColor);
	ADD_FUNCTION(setItemLineColor);
	ADD_FUNCTION(isItemShowHtml);
	ADD_FUNCTION(setItemShowHtml);
}


}//namespace
