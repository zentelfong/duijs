#include "StdAfx.h"
#include "UIImageControl.h"
#include "async/image_loader.h"

namespace DuiLib
{

	CImageControlUI::CImageControlUI() 
		:m_hBmp(nullptr), m_loader(nullptr)
	{
	}

	CImageControlUI::~CImageControlUI() {
		DeleteObject(m_hBmp);
		delete m_loader;
	}

	LPCTSTR CImageControlUI::GetClass() const {
		return _T("ImageControlUI");
	}

	LPVOID CImageControlUI::GetInterface(LPCTSTR pstrName) {
		if (_tcscmp(pstrName, _T("ImageControl")) == 0)
			return static_cast<CImageControlUI*>(this);
		return CControlUI::GetInterface(pstrName);
	}

	void CImageControlUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) {


	}

	void CImageControlUI::PaintStatusImage(HDC hDC) {


	}


}

