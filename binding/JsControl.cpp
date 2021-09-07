#include "JsControl.h"
#include "duilib/UIlib.h"
#include "Util.h"


namespace duijs {

using namespace qjs;
using namespace DuiLib;



static CControlUI* newControl(Context& context,ArgList& args) {
	return new CControlUI();
}

static void deleteControl(CControlUI* w) {
}

static Value getName(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetName());
}

static Value setName(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetName(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getClass(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetClass());
}

static Value getControlFlags(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetControlFlags());
}

static Value activate(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->Activate();
	return undefined_value;
}


static Value getParent(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetParent());
}


static Value setTimer(CControlUI* pThis, Context& context, ArgList& args) {
	return context.NewBool(pThis->SetTimer(args[0].ToUint32(),args[1].ToUint32()));
}

static Value killTimer(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->KillTimer(args[0].ToUint32());
	return undefined_value;
}


static Value getText(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->GetText());
}

static Value setText(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetText(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value isResourceText(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsResourceText());
}

static Value setResourceText(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetResourceText(args[0].ToBool());
	return undefined_value;
}

static Value isDragEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsDragEnabled());
}

static Value setDragEnable(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetDragEnable(args[0].ToBool());
	return undefined_value;
}

static Value isDropEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsDropEnabled());
}

static Value setDropEnable(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetDropEnable(args[0].ToBool());
	return undefined_value;
}

static Value getGradient(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetGradient());
}

static Value setGradient(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetGradient(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getBkColor(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (unsigned int)pThis->GetBkColor());
}

static Value setBkColor(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkColor(args[0].ToUint32());
	return undefined_value;
}

static Value getBkColor2(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (unsigned int)pThis->GetBkColor2());
}

static Value setBkColor2(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkColor2(args[0].ToUint32());
	return undefined_value;
}

static Value getBkColor3(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (unsigned int)pThis->GetBkColor3());
}

static Value setBkColor3(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBkColor3(args[0].ToUint32());
	return undefined_value;
}

static Value getForeColor(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (unsigned int)pThis->GetForeColor());
}

static Value setForeColor(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetForeColor(args[0].ToUint32());
	return undefined_value;
}


static Value getBkImage(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBkImage());
}

static Value setBkImage(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetBkImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value getForeImage(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetForeImage());
}

static Value setForeImage(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetForeImage(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value getFocusBorderColor(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (unsigned int)pThis->GetFocusBorderColor());
}

static Value setFocusBorderColor(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFocusBorderColor(args[0].ToUint32());
	return undefined_value;
}


static Value isColorHSL(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->IsColorHSL());
}

static Value setColorHSL(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetColorHSL(args[0].ToBool());
	return undefined_value;
}

static Value getBorderRound(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBorderRound());
}

static Value setBorderRound(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBorderRound(toSize(args[0]));
	return undefined_value;
}

static Value getBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBorderSize());
}

static Value setBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	if(args[0].IsObject())
		pThis->SetBorderSize(toRect(args[0]));
	else
		pThis->SetBorderSize(args[0].ToInt32());
	return undefined_value;
}

static Value getBorderColor(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (unsigned int)pThis->GetBorderColor());
}

static Value setBorderColor(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBorderColor(args[0].ToUint32());
	return undefined_value;
}

static Value getLeftBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLeftBorderSize());
}

static Value SetLeftBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetLeftBorderSize(args[0].ToInt32());
	return undefined_value;
}

static Value getTopBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTopBorderSize());
}

static Value setTopBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetTopBorderSize(args[0].ToInt32());
	return undefined_value;
}

static Value getRightBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRightBorderSize());
}

static Value setRightBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetRightBorderSize(args[0].ToInt32());
	return undefined_value;
}

static Value getBottomBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBottomBorderSize());
}

static Value setBottomBorderSize(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBottomBorderSize(args[0].ToInt32());
	return undefined_value;
}

static Value getBorderStyle(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetBorderStyle());
}

static Value setBorderStyle(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetBorderStyle(args[0].ToInt32());
	return undefined_value;
}

static Value getRelativePos(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetRelativePos());
}

static Value getClientPos(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetClientPos());
}

static Value getPos(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetPos());
}

static Value setPos(CControlUI* pThis, Context& context, ArgList& args) {
	if(args.size() == 2)
		pThis->SetPos(toRect(args[0]),args[1].ToBool());
	else
		pThis->SetPos(toRect(args[0]));
	return undefined_value;
}

static Value move(CControlUI* pThis, Context& context, ArgList& args) {
	if (args.size() == 2)
		pThis->Move(toSize(args[0]), args[1].ToBool());
	else
		pThis->Move(toSize(args[0]));
	return undefined_value;
}

static Value getWidth(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetWidth());
}

static Value getHeight(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHeight());
}

static Value getX(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetX());
}

static Value getY(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetY());
}

static Value getPadding(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetPadding());
}

static Value setPadding(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetPadding(toRect(args[0]));
	return undefined_value;
}

static Value getFixedXY(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFixedXY());
}

static Value setFixedXY(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFixedXY(toSize(args[0]));
	return undefined_value;
}

static Value getFixedWidth(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFixedWidth());
}

static Value setFixedWidth(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFixedWidth(args[0].ToInt32());
	return undefined_value;
}

static Value getFixedHeight(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFixedHeight());
}

static Value setFixedHeight(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFixedHeight(args[0].ToInt32());
	return undefined_value;
}

static Value getMinWidth(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMinWidth());
}

static Value setMinWidth(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetMinWidth(args[0].ToInt32());
	return undefined_value;
}

static Value getMaxWidth(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMaxWidth());
}

static Value setMaxWidth(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetMaxWidth(args[0].ToInt32());
	return undefined_value;
}

static Value getMinHeight(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMinHeight());
}

static Value setMinHeight(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetMinHeight(args[0].ToInt32());
	return undefined_value;
}

static Value getMaxHeight(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetMaxHeight());
}

static Value setMaxHeight(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetMaxHeight(args[0].ToInt32());
	return undefined_value;
}

static Value getFloatPercent(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFloatPercent());
}

static Value setFloatPercent(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFloatPercent(toPercentInfo(args[0]));
	return undefined_value;
}

static Value getFloatAlign(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFloatAlign());
}

static Value setFloatAlign(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFloatAlign(args[0].ToUint32());
	return undefined_value;
}

static Value getToolTip(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetToolTip());
}

static Value setToolTip(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetToolTip(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value setToolTipWidth(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetToolTipWidth(args[0].ToInt32());
	return undefined_value;
}

static Value getToolTipWidth(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetToolTipWidth());
}

static Value setCursor(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetCursor(args[0].ToInt32());
	return undefined_value;
}

static Value getCursor(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCursor());
}


static Value setShortcut(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetShortcut(args[0].ToInt32());
	return undefined_value;
}

static Value getShortcut(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetShortcut());
}

static Value setContextMenuUsed(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetContextMenuUsed(args[0].ToBool());
	return undefined_value;
}

static Value isContextMenuUsed(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsContextMenuUsed());
}


static Value getUserData(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetUserData());
}

static Value setUserData(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetUserData(CDuiString(str.str(), str.len()));
	return undefined_value;
}


static Value setTag(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetTag(args[0].ToInt32());
	return undefined_value;
}

static Value getTag(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTag());
}

static Value setVisible(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetVisible(args[0].ToBool());
	return undefined_value;
}

static Value isVisible(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsVisible());
}

static Value setInternVisible(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetInternVisible(args[0].ToBool());
	return undefined_value;
}

static Value isEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsEnabled());
}

static Value setEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetEnabled(args[0].ToBool());
	return undefined_value;
}

static Value isMouseEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsMouseEnabled());
}

static Value setMouseEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetMouseEnabled(args[0].ToBool());
	return undefined_value;
}


static Value isKeyboardEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsKeyboardEnabled());
}

static Value setKeyboardEnabled(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetKeyboardEnabled(args[0].ToBool());
	return undefined_value;
}


static Value isFocused(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsFocused());
}

static Value setFocus(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFocus();
	return undefined_value;
}

static Value isFloat(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsFloat());
}

static Value setFloat(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->SetFloat(args[0].ToBool());
	return undefined_value;
}

static Value invalidate(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->Invalidate();
	return undefined_value;
}

static Value isUpdateNeeded(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsUpdateNeeded());
}


static Value needUpdate(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->NeedUpdate();
	return undefined_value;
}


static Value needParentUpdate(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->NeedParentUpdate();
	return undefined_value;
}

static Value getAdjustColor(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetAdjustColor(args[0].ToUint32()));
}


static Value getVirtualWnd(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetVirtualWnd());
}

static Value setVirtualWnd(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->SetVirtualWnd(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value addCustomAttribute(CControlUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	auto attr = args[1].ToString();

	pThis->AddCustomAttribute(CDuiString(name.str(), name.len()),
		CDuiString(attr.str(),attr.len()));
	return undefined_value;
}

static Value getCustomAttribute(CControlUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	return toValue(context, pThis->GetCustomAttribute(CDuiString(name.str(), name.len())));
}

static Value removeCustomAttribute(CControlUI* pThis, Context& context, ArgList& args) {
	auto str = args[0].ToString();
	pThis->RemoveCustomAttribute(CDuiString(str.str(), str.len()));
	return undefined_value;
}

static Value removeAllCustomAttribute(CControlUI* pThis, Context& context, ArgList& args) {
	pThis->RemoveAllCustomAttribute();
	return undefined_value;
}

static Value setAttribute(CControlUI* pThis, Context& context, ArgList& args) {
	auto name = args[0].ToString();
	auto attr = args[1].ToString();

	pThis->SetAttribute(CDuiString(name.str(), name.len()),
		CDuiString(attr.str(), attr.len()));
	return undefined_value;
}


static Value estimateSize(CControlUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->EstimateSize(toSize(args[0])));
}


static Value deleteControl2(CControlUI* pThis, Context& context, ArgList& args) {
	delete pThis;
	return undefined_value;
}


#define ADD_FUNCTION(name) ctrl.AddFunc<name>(#name)

void RegisterControl(qjs::Module* module) {
	auto ctrl = module->ExportClass<CControlUI>("Control");
	ctrl.Init<deleteControl>();
	ctrl.AddCtor<newControl>();

	ADD_FUNCTION(getName);
	ADD_FUNCTION(setName);
	ADD_FUNCTION(getClass);
	ADD_FUNCTION(getControlFlags);
	ADD_FUNCTION(activate);
	ADD_FUNCTION(getParent);
	ADD_FUNCTION(setTimer);
	ADD_FUNCTION(killTimer);
	ADD_FUNCTION(getText);
	ADD_FUNCTION(setText);
	ADD_FUNCTION(isResourceText);
	ADD_FUNCTION(setResourceText);
	ADD_FUNCTION(isDragEnabled);
	ADD_FUNCTION(setDragEnable);
	ADD_FUNCTION(isDropEnabled);
	ADD_FUNCTION(setDropEnable);
	ADD_FUNCTION(getGradient);
	ADD_FUNCTION(setGradient);
	ADD_FUNCTION(getBkColor);
	ADD_FUNCTION(setBkColor);
	ADD_FUNCTION(getBkColor2);
	ADD_FUNCTION(setBkColor2);
	ADD_FUNCTION(getBkColor3);
	ADD_FUNCTION(setBkColor3);
	ADD_FUNCTION(getForeColor);
	ADD_FUNCTION(setForeColor);
	ADD_FUNCTION(getBkImage);
	ADD_FUNCTION(setBkImage);
	ADD_FUNCTION(getForeImage);
	ADD_FUNCTION(setForeImage);
	ADD_FUNCTION(getFocusBorderColor);
	ADD_FUNCTION(setFocusBorderColor);
	ADD_FUNCTION(isColorHSL);
	ADD_FUNCTION(setColorHSL);
	ADD_FUNCTION(getBorderRound);
	ADD_FUNCTION(setBorderRound);
	ADD_FUNCTION(getBorderSize);
	ADD_FUNCTION(setBorderSize);
	ADD_FUNCTION(getBorderColor);
	ADD_FUNCTION(setBorderColor);
	ADD_FUNCTION(getLeftBorderSize);
	ADD_FUNCTION(SetLeftBorderSize);
	ADD_FUNCTION(getTopBorderSize);
	ADD_FUNCTION(setTopBorderSize);
	ADD_FUNCTION(getRightBorderSize);
	ADD_FUNCTION(setRightBorderSize);
	ADD_FUNCTION(getBottomBorderSize);
	ADD_FUNCTION(setBottomBorderSize);
	ADD_FUNCTION(getBorderStyle);
	ADD_FUNCTION(setBorderStyle);
	ADD_FUNCTION(getRelativePos);
	ADD_FUNCTION(getClientPos);
	ADD_FUNCTION(getPos);
	ADD_FUNCTION(setPos);
	ADD_FUNCTION(move);
	ADD_FUNCTION(getWidth);
	ADD_FUNCTION(getHeight);
	ADD_FUNCTION(getX);
	ADD_FUNCTION(getY);
	ADD_FUNCTION(getPadding);
	ADD_FUNCTION(setPadding);
	ADD_FUNCTION(getFixedXY);
	ADD_FUNCTION(setFixedXY);
	ADD_FUNCTION(getFixedWidth);
	ADD_FUNCTION(setFixedWidth);
	ADD_FUNCTION(getFixedHeight);
	ADD_FUNCTION(setFixedHeight);
	ADD_FUNCTION(getMinWidth);
	ADD_FUNCTION(setMinWidth);
	ADD_FUNCTION(getMaxWidth);
	ADD_FUNCTION(setMaxWidth);
	ADD_FUNCTION(getMinHeight);
	ADD_FUNCTION(setMinHeight);
	ADD_FUNCTION(getMaxHeight);
	ADD_FUNCTION(setMaxHeight);
	ADD_FUNCTION(getFloatPercent);
	ADD_FUNCTION(setFloatPercent);
	ADD_FUNCTION(getFloatAlign);
	ADD_FUNCTION(setFloatAlign);
	ADD_FUNCTION(getToolTip);
	ADD_FUNCTION(setToolTip);
	ADD_FUNCTION(setToolTipWidth);
	ADD_FUNCTION(getToolTipWidth);
	ADD_FUNCTION(setCursor);
	ADD_FUNCTION(getCursor);
	ADD_FUNCTION(setShortcut);
	ADD_FUNCTION(getShortcut);
	ADD_FUNCTION(setContextMenuUsed);
	ADD_FUNCTION(isContextMenuUsed);
	ADD_FUNCTION(getUserData);
	ADD_FUNCTION(setUserData);
	ADD_FUNCTION(getTag);
	ADD_FUNCTION(setTag);
	ADD_FUNCTION(setVisible);
	ADD_FUNCTION(isVisible);
	ADD_FUNCTION(setInternVisible);
	ADD_FUNCTION(setEnabled);
	ADD_FUNCTION(isEnabled);
	ADD_FUNCTION(setMouseEnabled);
	ADD_FUNCTION(isMouseEnabled);
	ADD_FUNCTION(setKeyboardEnabled);
	ADD_FUNCTION(isKeyboardEnabled);
	ADD_FUNCTION(setFocus);
	ADD_FUNCTION(isFocused);
	ADD_FUNCTION(setFloat);
	ADD_FUNCTION(isFloat);
	ADD_FUNCTION(invalidate);
	ADD_FUNCTION(isUpdateNeeded);
	ADD_FUNCTION(needUpdate);
	ADD_FUNCTION(needParentUpdate);
	ADD_FUNCTION(getAdjustColor);
	ADD_FUNCTION(getVirtualWnd);
	ADD_FUNCTION(setVirtualWnd);
	ADD_FUNCTION(addCustomAttribute);
	ADD_FUNCTION(getCustomAttribute);
	ADD_FUNCTION(removeCustomAttribute);
	ADD_FUNCTION(removeAllCustomAttribute);
	ADD_FUNCTION(setAttribute);
	ADD_FUNCTION(estimateSize);
	ctrl.AddFunc<deleteControl2>("delete");
}


}//namespace
