#pragma once

class Paragraph;

namespace DuiLib {

#define DUI_CTR_RICHTEXT _T("RichText")

class UILIB_API CRichTextUI :public CControlUI
{
	DECLARE_DUICONTROL(CRichTextUI)
public:
	CRichTextUI();
	~CRichTextUI();

	void SetText(LPCTSTR text);//设置文本内容
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	LPCTSTR GetClass() const { return DUI_CTR_RICHTEXT; }

	void SetTextColor(DWORD dwTextColor);
	DWORD GetTextColor() const;
	void SetDisabledTextColor(DWORD dwTextColor);
	DWORD GetDisabledTextColor() const;
	void SetFont(int index);
	int GetFont() const;

private:
	Paragraph* m_paragraph;
	DWORD	m_dwTextColor;
	int		m_iFont;
	RECT	m_rcTextPadding;
};


}//duilib




