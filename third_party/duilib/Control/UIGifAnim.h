#ifndef GifAnimUI_h__
#define GifAnimUI_h__

#pragma once

namespace DuiLib
{

typedef struct tagAnimFrame
{
	tagAnimFrame()
	{
		nFrameId = 0;
		hBmpFrame = NULL;
		nDelayMs = 0;
	};
	~tagAnimFrame()
	{
		if (hBmpFrame)
		{
			DeleteObject(hBmpFrame);
			hBmpFrame = NULL;
		}
	}
	tagAnimFrame& operator=(const tagAnimFrame& value)
	{
		nFrameId = value.nFrameId;
		hBmpFrame = value.hBmpFrame;
		nDelayMs = value.nDelayMs;

		return *this;
	};

	UINT32 nFrameId;
	HBITMAP hBmpFrame;
	UINT32 nDelayMs;
}AnimFrame;


class UILIB_API CGifAnimUI:public CControlUI
{
public:
	DECLARE_DUICONTROL(CGifAnimUI)


	CGifAnimUI(void);
	~CGifAnimUI(void);

	LPCTSTR	GetClass() const;
	LPVOID	GetInterface(LPCTSTR pstrName);
	virtual void	DoEvent(TEventUI& event);
	virtual void	SetVisible(bool bVisible = true);
	virtual void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual void	SetBkImage(const CDuiString& strImage);

	virtual void    PaintBkImage(HDC hDC);

	virtual void	SetAutoPlay(bool bIsAuto = true);
	virtual bool	IsAutoPlay() const;
	virtual void	SetAutoSize(bool bIsAuto = true);
	virtual bool	IsAutoSize() const;
	virtual void	Play();
	virtual void	Pause();
	virtual void	Stop();

	virtual void    OnTimer(UINT_PTR idEvent);
	virtual bool	LoadFromFile(LPCTSTR pstrGifPath);
	virtual bool	LoadFromMemory(LPVOID pBuf, size_t dwSize);
protected:
	CStdPtrArray	m_Frames;
	UINT			m_nFramePosition;			// 当前放到第几帧

	int m_nFrameWidth;
	int m_nFrameHeight;

	int m_nLoopCout;		//播放几次 0无限循环//stbimg里面，解析gif时似乎没有读取这个值
	int m_nLoopedNum;

	CDuiString		m_sBkImage;
	bool			m_bIsAutoPlay;				// 是否自动播放gif
	bool			m_bIsAutoSize;				// 是否自动根据图片设置大小
	bool			m_bIsPlaying;
};

}//namespace

#endif // GifAnimUI_h__
