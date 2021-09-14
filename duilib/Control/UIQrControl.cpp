#include "StdAfx.h"
#include <atlstr.h>
#include <atlimage.h>
#include <GdiPlus.h>
#include "Utils/QR_Encode.h"


namespace DuiLib {
IMPLEMENT_DUICONTROL(CQrControlUI)

CQrControlUI::CQrControlUI()
	:m_qrImage(NULL)
{
}


CQrControlUI::~CQrControlUI()
{
	DeleteObject(m_qrImage);
	m_qrImage=NULL;
}


void CQrControlUI::SetText(LPCTSTR text)
{
	m_text=text;
	DeleteObject(m_qrImage);
	m_qrImage=NULL;
	Invalidate();//重新绘制
}


void CQrControlUI::PaintStatusImage(HDC hDC)
{
	if (!m_qrImage)
	{
		m_qrImage=GenQrImage(hDC,m_text,min(GetWidth(),GetHeight()));
	}

	BITMAP bitmap;
	GetObject(m_qrImage, sizeof(BITMAP), &bitmap);
	RECT rcBmpPart = { 0,0,bitmap.bmWidth,bitmap.bmHeight };
	CRenderEngine::DrawBitmap(hDC,m_qrImage,m_rcItem,m_rcPaint, rcBmpPart,false);
}

void CQrControlUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName,L"text")==0)
	{
		m_text=pstrValue;
	}
	else
		CControlUI::SetAttribute(pstrName,pstrValue);
}

static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;                     // number of image encoders   
	UINT size = 0;                   // size of the image encoder array in bytes   
	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;     //   Failure   

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;     //   Failure   

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;     //   Success   
		}
	}
	free(pImageCodecInfo);
	return -1;     //   Failure   
}

static BOOL SaveJpgFile(Gdiplus::Bitmap* pImage, LPCTSTR pFileName)
{
	CAtlStringW strFilePath(pFileName);
	Gdiplus::EncoderParameters encoderParameters;
	CLSID jpgClsid;
	GetEncoderClsid(L"image/jpeg", &jpgClsid);
	encoderParameters.Count = 1;
	encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
	encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues = 1;

	// Save the image as a JPEG with quality level 100.
	ULONG   quality;
	quality = 100;
	encoderParameters.Parameter[0].Value = &quality;
	Gdiplus::Status status = pImage->Save(strFilePath.GetString(), &jpgClsid, &encoderParameters);
	return status == Gdiplus::Ok;
}

static BOOL SaveHbmpToFile(HBITMAP hBitmap, LPCTSTR filename, SIZE *sz=NULL)
{
	HRESULT hr = 0;
	Gdiplus::Bitmap* bmp = Gdiplus::Bitmap::FromHBITMAP(hBitmap, NULL);
	if (bmp)
	{
		if (sz)
		{
			sz->cx = bmp->GetWidth();
			sz->cy = bmp->GetHeight();
		}
		SaveJpgFile(bmp, filename);
		delete bmp;
		return TRUE;
	}
	else
		return FALSE;
}

bool CQrControlUI::SaveImage(LPCTSTR path)
{
	if (m_qrImage)
		return SaveHbmpToFile(m_qrImage,path);
	else
		return false;
}
	
static CStringA STR_UnicodeToUtf8(CStringW strWideChar)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)strWideChar, -1, NULL, 0, NULL, NULL);
	char *multiByte = new char[len + 1];
	memset(multiByte, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)strWideChar, -1, multiByte, len, NULL, NULL);
	CStringA strMultiByte = multiByte;
	delete[] multiByte;
	return strMultiByte;
}

HBITMAP CQrControlUI::GenQrImage(HDC hdc,LPCTSTR text,int size)
{
	CQR_Encode qrEncode;
	CStringA utf8Text = STR_UnicodeToUtf8(text);
	qrEncode.EncodeData(0,0,1,-1, utf8Text.GetString());

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = size;
	bmi.bmiHeader.biHeight = size;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = size * size * sizeof(DWORD);

	RGBQUAD* pDest = NULL;
	HDC hCloneDC = ::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (LPVOID*) &pDest, NULL, 0);
	ASSERT(hCloneDC);
	ASSERT(hBitmap);
	if( hBitmap != NULL )
	{
		HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(hCloneDC, hBitmap);

		//绘制二维码
		RECT rc = { 0,0,size,size };
		CRenderEngine::DrawColor(hCloneDC, rc,0xffffffff);//绘制白色背景

		int width=size/(qrEncode.m_nSymbleSize+2);

		int xOffset=width+(size- width*(qrEncode.m_nSymbleSize+2))/2;
		int yOffset=xOffset;


		for (int i = 0; i < qrEncode.m_nSymbleSize; ++i)
		{
			for (int j = 0; j < qrEncode.m_nSymbleSize; ++j)
			{
				RECT drc = { i*width + xOffset,j*width + yOffset,(i + 1)*width + xOffset,(j + 1)*width + yOffset };
				if(qrEncode.m_byModuleData[i][j]==1)
				{
					//绘制黑色
					CRenderEngine::DrawColor(hCloneDC, drc,0xff000000);
				}
				else
				{
					//绘制白色
					CRenderEngine::DrawColor(hCloneDC, drc,0xffffffff);
				}
			}
		}

		::SelectObject(hCloneDC, hOldBitmap);

		::DeleteDC(hCloneDC);  
		::GdiFlush();
	}

	return hBitmap;
}
	
}