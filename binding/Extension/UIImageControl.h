#ifndef __UIIMAGECONTROL_H__
#define __UIIMAGECONTROL_H__

#pragma once


namespace DuiLib
{
	class ImageLoader;

	class UILIB_API CImageControlUI : public CControlUI
	{
		DECLARE_DUICONTROL(CImageControlUI)

	public:
		CImageControlUI();
		~CImageControlUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintStatusImage(HDC hDC);
	protected:
		HBITMAP m_hBmp;
		ImageLoader* m_loader;
	};
}
#endif // __UIIMAGECONTROL_H__

