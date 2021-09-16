#include "StdAfx.h"
#include "UIRing.h"

namespace DuiLib
{
	IMPLEMENT_DUICONTROL(CRingUI)

	CRingUI::CRingUI() : m_fCurAngle(0.0f), m_fStep(36.0f), m_delay(100), m_pBkimage(NULL)
	{
	}

	CRingUI::~CRingUI()
	{
		if(m_pManager) m_pManager->KillTimer(this, RING_TIMERID);

		DeleteImage();
	}

	LPCTSTR CRingUI::GetClass() const
	{
		return _T("RingUI");
	}

	LPVOID CRingUI::GetInterface( LPCTSTR pstrName )
	{
		if( _tcscmp(pstrName, _T("Ring")) == 0 ) return static_cast<CRingUI*>(this);
		return CLabelUI::GetInterface(pstrName);
	}

	void CRingUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if (_tcscmp(pstrName, _T("bkimage")) == 0)
			SetBkImage(pstrValue);
		else if (_tcscmp(pstrName, _T("step")) == 0)
			m_fStep = _ttof(pstrValue);
		else if (_tcscmp(pstrName, _T("delay")) == 0)
			m_delay = _ttoi(pstrValue);
		else 
			CLabelUI::SetAttribute(pstrName, pstrValue);
	}

	void CRingUI::SetBkImage( LPCTSTR pStrImage )
	{
		if (m_sBkImage == pStrImage) return;
		m_sBkImage = pStrImage;
		DeleteImage();
		Invalidate();
	}

	void CRingUI::PaintBkImage( HDC hDC )
	{
		if(m_pBkimage == NULL) {
			InitImage();
		}

		if(m_pBkimage != NULL) {
			RECT rcItem = m_rcItem;
			int iWidth = rcItem.right - rcItem.left;
			int iHeight = rcItem.bottom - rcItem.top;
			Gdiplus::PointF centerPos(rcItem.left + iWidth/2, rcItem.top + iHeight/2);

			Gdiplus::Graphics graphics(hDC);
			graphics.TranslateTransform(centerPos.X,centerPos.Y);
			graphics.RotateTransform(m_fCurAngle);
			graphics.TranslateTransform(-centerPos.X, -centerPos.Y);//还原源点
			graphics.DrawImage(m_pBkimage,rcItem.left,rcItem.top,iWidth,iHeight);
		}
	}

	void CRingUI::DoEvent( TEventUI& event )
	{
		if( event.Type == UIEVENT_TIMER && event.wParam == RING_TIMERID ) {
			m_fCurAngle += m_fStep;
			if (m_fCurAngle > 360) {
				m_fCurAngle -= 360;
			}
			Invalidate();
		}
		else {
			CLabelUI::DoEvent(event);
		}
	}

	void CRingUI::InitImage()
	{
		m_pBkimage = CRenderEngine::GdiplusLoadImage(GetBkImage());
		if ( NULL == m_pBkimage ) return;
		if(m_pManager) m_pManager->SetTimer(this, RING_TIMERID, m_delay);
	}

	void CRingUI::DeleteImage()
	{
		if ( m_pBkimage != NULL )
		{
			delete m_pBkimage;
			m_pBkimage = NULL;
		}
	}
}
