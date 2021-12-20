#include "StdAfx.h"
#include "UIGifAnim.h"
#include "Utils/stb_image.h"

namespace DuiLib
{
enum {
	EVENT_TIME_ID = 100,
};

IMPLEMENT_DUICONTROL(CGifAnimUI)

CGifAnimUI::CGifAnimUI(void)
{
	m_nFramePosition = 0;
	m_bIsAutoPlay = true;
	m_bIsAutoSize = false;
	m_bIsPlaying = false;

	m_nLoopCout = 0;
	m_nLoopedNum = 0;
}


CGifAnimUI::~CGifAnimUI(void)
{
	for (int i = 0; i < m_Frames.GetSize(); i++)
	{
		AnimFrame* pFrame = (AnimFrame*)m_Frames[i];
		delete pFrame;
	}
	if (m_pManager)
		m_pManager->KillTimer(this, EVENT_TIME_ID);
}

LPCTSTR CGifAnimUI::GetClass() const
{
	return DUI_CTR_GIFANIM;
}

LPVOID CGifAnimUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, DUI_CTR_GIFANIM) == 0) return static_cast<CGifAnimUI*>(this);
	return CControlUI::GetInterface(pstrName);
}

void CGifAnimUI::DoEvent(TEventUI& event)
{
	if (event.Type == UIEVENT_TIMER)
		OnTimer((UINT_PTR)event.wParam);
	else
		CControlUI::DoEvent(event);
}

void CGifAnimUI::SetVisible(bool bVisible /* = true */)
{
	CControlUI::SetVisible(bVisible);
	if (bVisible && m_bIsAutoPlay)
		Play();
	else
		Stop();
}

void CGifAnimUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("bkimage")) == 0) SetBkImage(pstrValue);
	else if (_tcscmp(pstrName, _T("autoplay")) == 0) {
		SetAutoPlay(_tcscmp(pstrValue, _T("true")) == 0);
	}
	else if (_tcscmp(pstrName, _T("autosize")) == 0) {
		SetAutoSize(_tcscmp(pstrValue, _T("true")) == 0);
	}
	else
		CControlUI::SetAttribute(pstrName, pstrValue);
}

void CGifAnimUI::SetBkImage(const CDuiString& strImage)
{
	if (m_sBkImage == strImage) return;
	m_sBkImage = strImage;
	Stop();

	for (int i = 0; i < m_Frames.GetSize(); i++)
	{
		AnimFrame* pFrame = (AnimFrame*)m_Frames[i];
		delete pFrame;
	}
	m_Frames.Empty();
	m_nFramePosition = 0;

	//重新载入
	if (LoadFromFile(strImage.GetData()))
	{
		if (m_bIsAutoSize)
		{
			SetFixedWidth(m_nFrameWidth);
			SetFixedHeight(m_nFrameHeight);
		}

		if (m_bIsAutoPlay && m_Frames.GetSize() > 0)
		{
			Play();
		}
	}
	else
	{
		CControlUI::SetBkImage(strImage);
	}
}

void CGifAnimUI::SetAutoPlay(bool bIsAuto)
{
	if (m_bIsAutoPlay != bIsAuto)
	{
		m_bIsAutoPlay = bIsAuto;
		if (m_bIsAutoPlay)
			Play();
		else
			Stop();
	}
}

bool CGifAnimUI::IsAutoPlay() const
{
	return m_bIsAutoPlay;
}

void CGifAnimUI::SetAutoSize(bool bIsAuto)
{
	m_bIsAutoSize = bIsAuto;
	if (m_Frames.IsEmpty() == false)
	{
		if (m_bIsAutoSize)
		{
			SetFixedWidth(m_nFrameWidth);
			SetFixedHeight(m_nFrameHeight);
		}
	}
}

bool CGifAnimUI::IsAutoSize() const
{
	return m_bIsAutoSize;
}

void CGifAnimUI::Play()
{
	if (m_bIsPlaying || m_Frames.IsEmpty())
		return;

	m_nLoopedNum = 0;

	long lPause = ((AnimFrame*)m_Frames[m_nFramePosition])->nDelayMs;
	if (lPause == 0) lPause = 100;
	m_pManager->SetTimer(this, EVENT_TIME_ID, lPause);

	m_bIsPlaying = true;
	Invalidate();
}

void CGifAnimUI::Pause()
{
	if (!m_bIsPlaying || m_Frames.IsEmpty())
		return;

	m_pManager->KillTimer(this, EVENT_TIME_ID);
	this->Invalidate();
	m_bIsPlaying = false;
}

void CGifAnimUI::Stop()
{
	if (!m_bIsPlaying)
		return;

	m_pManager->KillTimer(this, EVENT_TIME_ID);
	m_nFramePosition = 0;
	this->Invalidate();
	m_bIsPlaying = false;
	m_nLoopedNum = 0;
}

void CGifAnimUI::OnTimer(UINT_PTR idEvent)
{
	if (idEvent != EVENT_TIME_ID)
		return;
	m_pManager->KillTimer(this, EVENT_TIME_ID);
	this->Invalidate();

	if (m_nLoopCout > 0)
	{
		if (m_nFramePosition == 0)
			m_nLoopedNum++;

		if (m_nLoopedNum <= m_nLoopCout)
		{
			if (m_Frames.GetSize() > 0)
				m_nFramePosition = (++m_nFramePosition) % m_Frames.GetSize();

			long lPause = ((AnimFrame*)m_Frames[m_nFramePosition])->nDelayMs;
			if (lPause == 0) lPause = 100;
			m_pManager->SetTimer(this, EVENT_TIME_ID, lPause);
		}
	}
	else
	{
		if (m_Frames.GetSize() > 0)
			m_nFramePosition = (++m_nFramePosition) % m_Frames.GetSize();

		long lPause = ((AnimFrame*)m_Frames[m_nFramePosition])->nDelayMs;
		if (lPause == 0) lPause = 100;
		m_pManager->SetTimer(this, EVENT_TIME_ID, lPause);
	}
}

void CGifAnimUI::PaintBkImage(HDC hDC)
{
	//绘制当前帧
	if (m_Frames.IsEmpty())
	{
		CControlUI::PaintBkImage(hDC);
	}
	else
	{
		AnimFrame* pFrame = (AnimFrame*)m_Frames[m_nFramePosition];

		RECT rcDest = m_rcItem;
		RECT bmpSrc = { 0,0,m_nFrameWidth ,m_nFrameHeight };
		CRenderEngine::DrawBitmap(hDC, pFrame->hBmpFrame, rcDest, m_rcPaint, bmpSrc,TRUE);
	}
}

bool CGifAnimUI::LoadFromFile(LPCTSTR pstrGifPath)
{
	if ((pstrGifPath == NULL) || (_tcslen(pstrGifPath) == 0))
		return false;

	bool bRet = false;
	TCHAR errMsg[128];
	DWORD size = 0;
	BYTE* data = CResourceManager::GetInstance()->LoadFile(pstrGifPath, &size, errMsg);
	if (data) {
		bRet = LoadFromMemory(data, size);
		delete[] data;
	}
	return bRet;
}

bool CGifAnimUI::LoadFromMemory(LPVOID pBuf, size_t dwSize)
{
	int* delays = NULL;
	int nFrameCount = 0;
	m_nLoopCout = 0;
	int comp = 0;
	unsigned char* pData = 
		stbi_load_gif_from_memory((unsigned char*)pBuf, dwSize, &delays, &m_nFrameWidth, &m_nFrameHeight, &nFrameCount, &comp,4);
	if (pData)
	{
		BITMAPINFO bmi;
		::ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = m_nFrameWidth;
		bmi.bmiHeader.biHeight = -m_nFrameHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = (m_nFrameWidth * 32 + 31) / 32 * 4 * m_nFrameHeight;

		for (int nFram = 0; nFram < nFrameCount; nFram++)
		{
			LPBYTE pDest = NULL;
			HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pDest, NULL, 0);
			if (!hBitmap) {
				stbi_image_free(delays);
				stbi_image_free(pData);
				return false;
			}

			AnimFrame* pframe = new AnimFrame;
			pframe->nFrameId = nFram;
			pframe->nDelayMs = delays[nFram];

			LPBYTE pFramBit = pData + m_nFrameWidth * m_nFrameHeight * nFram * 4;
			for (int i = 0; i < m_nFrameWidth * m_nFrameHeight; i++)
			{
				pDest[i * 4 + 3] = pFramBit[i * 4 + 3];
				pDest[i * 4] = pFramBit[i * 4 + 2];
				pDest[i * 4 + 1] = pFramBit[i * 4 + 1];
				pDest[i * 4 + 2] = pFramBit[i * 4];
			}

			pframe->hBmpFrame = hBitmap;
			m_Frames.Add(pframe);
		}

		stbi_image_free(delays);
		stbi_image_free(pData);
		return true;
	}

	return false;
}

}//namespace
