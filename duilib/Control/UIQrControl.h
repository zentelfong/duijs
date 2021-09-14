#pragma once

namespace DuiLib {


class UILIB_API CQrControl:public CControlUI
{
public:
	CQrControl();
	~CQrControl();

	void SetText(LPCTSTR text);//设置文本内容
	virtual void PaintStatusImage(HDC hDC);//绘制二维码
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	LPCTSTR GetClass() const { return _T("QrControl"); }

	//生成二维码图片
	static HBITMAP GenQrImage(HDC hdc,LPCTSTR text,int size);

	//保存到文件
	bool SaveImage(LPCTSTR path); 
private:
	HBITMAP m_qrImage;//生成的二维码图片
	CDuiString m_text;
};


}//duilib