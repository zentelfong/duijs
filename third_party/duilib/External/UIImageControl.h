#pragma once

class ImageLoader;

namespace DuiLib
{

//异步加载图片
class UILIB_API CImageControlUI : public CControlUI
{
	DECLARE_DUICONTROL(CImageControlUI)
public:
	enum FillType{
		kFill,
		kCenter,    //居中显示
		kFitWidth,  //宽度铺满
		kFitHeight, //高度铺满
		kFitFull    //铺满
	};

	CImageControlUI();
	~CImageControlUI();
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintStatusImage(HDC hDC);

	void Load(LPCTSTR file);
protected:
	FillType m_fillType;
	HBITMAP  m_hBmp;
	ImageLoader* m_loader;
};

}

