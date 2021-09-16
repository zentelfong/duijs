#include "StdAfx.h"
#include "UIRichText.h"

namespace DuiLib {


CRichTextUI::CRichTextUI() 
	:m_dwTextColor(0), m_iFont(0)
{
	::ZeroMemory(&m_rcTextPadding, sizeof(m_rcTextPadding));
}

CRichTextUI::~CRichTextUI() {


}

void CRichTextUI::SetText(LPCTSTR text) {
	CControlUI::SetText(text);

}


void CRichTextUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) {


}

void CRichTextUI::SetTextColor(DWORD dwTextColor) {


}


DWORD CRichTextUI::GetTextColor() const {


}


void CRichTextUI::SetDisabledTextColor(DWORD dwTextColor) {


}


DWORD CRichTextUI::GetDisabledTextColor() const {


}


void CRichTextUI::SetFont(int index) {


}


int CRichTextUI::GetFont() const {


}







}//namespace

