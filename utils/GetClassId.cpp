#include "duilib/UIlib.h"
#include "quickjs/qjs.h"

#define IMPLEMENT_GET_CLASS_ID(class_name)\
	UINT class_name::GetClassId() const \
	{ return qjs::Class<class_name>::class_id(); }

namespace DuiLib {
	IMPLEMENT_GET_CLASS_ID(CControlUI);
	IMPLEMENT_GET_CLASS_ID(CContainerUI);
	IMPLEMENT_GET_CLASS_ID(CButtonUI);
	IMPLEMENT_GET_CLASS_ID(CComboUI);
	IMPLEMENT_GET_CLASS_ID(CComboBoxUI);
	IMPLEMENT_GET_CLASS_ID(CDateTimeUI);
	IMPLEMENT_GET_CLASS_ID(CEditUI);
	IMPLEMENT_GET_CLASS_ID(CActiveXUI);
	IMPLEMENT_GET_CLASS_ID(CFlashUI);
	IMPLEMENT_GET_CLASS_ID(CGifAnimUI);
#ifdef USE_XIMAGE_EFFECT
	IMPLEMENT_GET_CLASS_ID(CGifAnimExUI);
#endif
	IMPLEMENT_GET_CLASS_ID(CGroupBoxUI);
	IMPLEMENT_GET_CLASS_ID(CIPAddressUI);
	IMPLEMENT_GET_CLASS_ID(CIPAddressExUI);
	IMPLEMENT_GET_CLASS_ID(CLabelUI);
	IMPLEMENT_GET_CLASS_ID(CListUI);
	IMPLEMENT_GET_CLASS_ID(CListHeaderUI);
	IMPLEMENT_GET_CLASS_ID(CListHeaderItemUI);
	IMPLEMENT_GET_CLASS_ID(CListLabelElementUI);
	IMPLEMENT_GET_CLASS_ID(CListTextElementUI);
	IMPLEMENT_GET_CLASS_ID(CListContainerElementUI);
	IMPLEMENT_GET_CLASS_ID(CMenuUI);
	IMPLEMENT_GET_CLASS_ID(CMenuElementUI);
	IMPLEMENT_GET_CLASS_ID(COptionUI);
	IMPLEMENT_GET_CLASS_ID(CCheckBoxUI);
	IMPLEMENT_GET_CLASS_ID(CProgressUI);
	IMPLEMENT_GET_CLASS_ID(CRichEditUI);
	IMPLEMENT_GET_CLASS_ID(CScrollBarUI);
	IMPLEMENT_GET_CLASS_ID(CSliderUI);
	IMPLEMENT_GET_CLASS_ID(CTextUI);
	IMPLEMENT_GET_CLASS_ID(CTreeNodeUI);
	IMPLEMENT_GET_CLASS_ID(CTreeViewUI);
	IMPLEMENT_GET_CLASS_ID(CWebBrowserUI);
	IMPLEMENT_GET_CLASS_ID(CAnimationTabLayoutUI);
	IMPLEMENT_GET_CLASS_ID(CChildLayoutUI);
	IMPLEMENT_GET_CLASS_ID(CHorizontalLayoutUI);
	IMPLEMENT_GET_CLASS_ID(CTabLayoutUI);
	IMPLEMENT_GET_CLASS_ID(CTileLayoutUI);
	IMPLEMENT_GET_CLASS_ID(CVerticalLayoutUI);
	IMPLEMENT_GET_CLASS_ID(CRollTextUI);
	IMPLEMENT_GET_CLASS_ID(CColorPaletteUI);
	IMPLEMENT_GET_CLASS_ID(CListExUI);
	IMPLEMENT_GET_CLASS_ID(CListContainerHeaderItemUI);
	IMPLEMENT_GET_CLASS_ID(CListTextExtElementUI);
	IMPLEMENT_GET_CLASS_ID(CHotKeyUI);
	IMPLEMENT_GET_CLASS_ID(CFadeButtonUI);
	IMPLEMENT_GET_CLASS_ID(CRingUI);
}


