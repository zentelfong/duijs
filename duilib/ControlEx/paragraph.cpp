#include "paragraph.h"

#define FACE_ID 0x80000000

uint32_t UTF16_To_UCS4(const wchar_t* pwUTF16, unsigned int& dwUCS4);
uint32_t UCS4_To_UTF16(unsigned int dwUCS4, wchar_t* pwUTF16);


Line::Line(Paragraph* paragraph)
	:paragraph_(paragraph),min_(0),max_(0) {
	pos_.x = pos_.y = 0;
}

Line::~Line() {

}

static bool DrawBitmap(HDC hDC, HBITMAP hBitmap, const RECT& rcDest)
{
	if (!hDC || !hBitmap)
		return false;

	BITMAP BMInf;
	GetObject(hBitmap, sizeof(BITMAP), &BMInf);

	HDC hDCBits = CreateCompatibleDC(hDC);
	HBITMAP temp = (HBITMAP)SelectObject(hDCBits, hBitmap);

	RECT rcBmpPart = { 0,0,BMInf.bmWidth,BMInf.bmHeight };

	BLENDFUNCTION bf = { AC_SRC_OVER, TRUE, 255, AC_SRC_ALPHA };
	RECT rcTemp = { 0 };

	BOOL bResult = AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right - rcDest.left, rcDest.bottom - rcDest.top,
		hDCBits, rcBmpPart.left, rcBmpPart.top, rcBmpPart.right - rcBmpPart.left, rcBmpPart.bottom - rcBmpPart.top, bf);
	SelectObject(hDCBits, temp);
	DeleteDC(hDCBits);
	return !!bResult;
}


int Line::DrawChar(HDC hdc, RECT& rc, uint32_t ch) {
	wchar_t buf[8];
	uint32_t len = UCS4_To_UTF16(ch, buf);
	return DrawText(hdc, buf, len, &rc, DT_SINGLELINE | DT_VCENTER);
}



void Line::Draw(HDC hdc, const POINT& pos, uint32_t style) {
	//绘制一行，支持文字和表情，emoji
	std::vector<uint32_t>& content = paragraph_->content_;
	size_t width = 0;
	for (size_t i = min_; i < max_; ++i) {
		HBITMAP bmp = paragraph_->LoadCharBmp(content[i]);
		if (bmp) {
			//绘制图片
			RECT rc = { pos.x + (LONG)width,pos.y,0,0 };
			rc.right = rc.left + paragraph_->bmpSize_;
			rc.bottom = rc.top + paragraph_->bmpSize_;
			DrawBitmap(hdc, bmp, rc);
			width += paragraph_->bmpSize_;
		} else {
			//绘制文本
			RECT rc = { pos.x + (LONG)width,pos.y,0,0 };
			rc.right = rc.left + paragraph_->bmpSize_;
			rc.bottom = rc.top + paragraph_->bmpSize_;
			width += DrawChar(hdc, rc, content[i]);
		}
	}
}

Paragraph::Paragraph() 
	:callback_(nullptr), bmpSize_(30), maxLine_(10), lineHeight_(32), lastMaxWidth_(0)
{

}

Paragraph::~Paragraph() {
	for (auto bmp : bmpCache_) {
		DeleteObject(bmp.second);
	}
}

void Paragraph::AddText(const wchar_t* text, size_t len) {
	unsigned int unicode = 0;
	for (size_t i = 0; i < len; ) {
		uint32_t count = UTF16_To_UCS4(text + i, unicode);
		if (count == 0) {
			//无效字符
			i += 1;
		} else {
			content_.push_back(unicode);
			i += count;
		}
	}
}

HBITMAP Paragraph::LoadCharBmp(uint32_t ch) {
	//从缓存中获取
	auto find = bmpCache_.find(ch);
	if (find != bmpCache_.end()) {
		return find->second;
	}

	//加载图片
	if (ch >= FACE_ID) {
		uint32_t face = ch - FACE_ID;
		HBITMAP bmp = callback_->LoadFace(face);
		if (bmp != nullptr) {
			bmpCache_.insert(std::make_pair(ch, bmp));
		}
		return bmp;
	}

	//加载emoji
	if (ch > 0xffff || (ch >= 0x2b1b && ch <= 0x3299)) {
		HBITMAP bmp = callback_->LoadEmoji(ch);
		if (bmp != nullptr) {
			bmpCache_.insert(std::make_pair(ch, bmp));
		}
		return bmp;
	}
	return nullptr;
}


void Paragraph::AddFace(uint32_t faceId) {
	content_.push_back(faceId | FACE_ID);
}


//获取字符的尺寸
SIZE Paragraph::GetCharSize(HDC hdc, uint32_t ch) {
	//表情
	if (ch >= FACE_ID) {
		SIZE sz = { (LONG)bmpSize_,(LONG)bmpSize_ };
		return sz;
	}

	//emoji
	if (LoadCharBmp(ch)) {
		SIZE sz = { (LONG)bmpSize_,(LONG)bmpSize_ };
		return sz;
	}
	
	//文字
	wchar_t buf[8];
	uint32_t len = UCS4_To_UTF16(ch, buf);
	SIZE sz = {0,0};
	GetTextExtentPoint(hdc, buf, len, &sz);
	return sz;
}



void Paragraph::Layout(HDC hdc, int maxWidth) {
	lines_.clear();
	charSize_.clear();

	//计算字符尺寸
	if (charSize_.size() != content_.size()) {
		HGDIOBJ oldObj = (HGDIOBJ)::SelectObject(hdc, callback_->GetFont());
		for (auto ch : content_) {
			charSize_.push_back(GetCharSize(hdc, ch));
		}
		::SelectObject(hdc, oldObj);
	}


	//计算line
	size_t start = 0;
	size_t width = 0;
	for (size_t i = 0; i < content_.size(); ++i) {
		width += charSize_[i].cx;
		if (width > maxWidth || content_[i] == '\n') {
			std::shared_ptr<Line> line = std::make_shared<Line>(this);

			line->min_ = start;
			line->max_ = i;
			line->pos_.x = 0;
			line->pos_.y = lines_.size() * lineHeight_;
			lines_.push_back(line);

			//换行符不绘制
			if (content_[i] == '\n') {
				start = i + 1;
				width = 0;
			} else {
				start = i;
				width = charSize_[i].cx;
			}
		}
	}


	//处理末尾的文字
	if (start < content_.size()) {
		std::shared_ptr<Line> line = std::make_shared<Line>(this);
		line->min_ = start;
		line->max_ = content_.size();
		line->pos_.x = 0;
		line->pos_.y = lines_.size() * lineHeight_;
		lines_.push_back(line);
	}

}

void Paragraph::Draw(HDC hdc, const RECT& rc) {
	//计算布局
	if (lastMaxWidth_ != rc.right - rc.left) {
		lastMaxWidth_ = rc.right - rc.left;
		Layout(hdc, lastMaxWidth_);
	}

	POINT pt = { rc.left,rc.top };

	size_t lines = lines_.size();
	if (lines > maxLine_) {
		lines = maxLine_;
	}

	//绘制文字
	HGDIOBJ oldObj = (HGDIOBJ)::SelectObject(hdc, callback_->GetFont());
	for (size_t i = 0; i < lines;++i) {
		lines_[i]->Draw(hdc, pt, DT_SINGLELINE);
		pt.y += lineHeight_;
	}
	::SelectObject(hdc, oldObj);
}


void Paragraph::SetMaxLine(size_t maxLine) {
	maxLine_ = maxLine;
	NeedLayout();
}


void Paragraph::SetLineHeight(size_t height) {
	lineHeight_ = height;
	NeedLayout();
}

void Paragraph::NeedLayout() {
	lastMaxWidth_ = 0;
	lines_.clear();
	charSize_.clear();
}









uint32_t UTF16_To_UCS4(const wchar_t* pwUTF16, unsigned int& dwUCS4)
{
	wchar_t    w1, w2;

	if (pwUTF16 == NULL)
	{   // 参数错误
		return 0;
	}

	w1 = pwUTF16[0];
	if (w1 >= 0xD800 && w1 <= 0xDFFF)
	{   // 编码在替代区域（Surrogate Area）
		if (w1 < 0xDC00)
		{
			w2 = pwUTF16[1];
			if (w2 >= 0xDC00 && w2 <= 0xDFFF)
			{
				dwUCS4 = (w2 & 0x03FF) + (((w1 & 0x03FF) + 0x40) << 10);
				return 2;
			}
		}
		return 0;   // 非法UTF16编码    
	}
	else
	{
		dwUCS4 = w1;
		return 1;
	}
}

uint32_t UCS4_To_UTF16(unsigned int dwUCS4, wchar_t* pwUTF16)
{
	if (dwUCS4 <= 0xFFFF)
	{
		if (pwUTF16 != NULL)
		{
			*pwUTF16 = static_cast<wchar_t>(dwUCS4);
		}

		return 1;
	}
	else if (dwUCS4 <= 0xEFFFF)
	{
		if (pwUTF16 != NULL)
		{
			pwUTF16[0] = static_cast<wchar_t>(0xD800 + (dwUCS4 >> 10) - 0x40);   // 高10位  
			pwUTF16[1] = static_cast<wchar_t>(0xDC00 + (dwUCS4 & 0x03FF));     // 低10位  
		}
		return 2;
	}
	else
	{
		return 0;
	}
}




