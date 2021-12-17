#include "StdAfx.h"
#include "UIImageControl.h"
#include "async/image_loader.h"

namespace DuiLib
{

CImageControlUI::CImageControlUI() 
	:m_fillType(kFitFull),m_hBmp(nullptr), m_loader(nullptr)
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

void CImageControlUI::Load(LPCTSTR file) {
	delete m_loader;
	m_loader = new ImageLoader();

	char* file_utf8 = w2a(file, CP_UTF8);

	m_loader->Load(file_utf8,[this](RefPtr<ImageData> data) {
			if (data) {

			} else {

			}
		});

	delete[] file_utf8;
}

}//namespace


