#pragma once
#include <vector>
#include <stdint.h>
#include <memory>
#include <map>
#include <Windows.h>

class Paragraph;

//用于加载emoji或者表情
class ParagraphCallback {
public:
	virtual HBITMAP LoadEmoji(uint32_t ch) = 0;
	virtual HBITMAP LoadFace(uint32_t id) = 0;
	virtual HFONT   GetFont() = 0;
};


class Line :public std::enable_shared_from_this<Line>{
public:
	Line(Paragraph* paragraph);
	~Line();

	void Draw(HDC hdc, const POINT& pos,uint32_t style);
	int  DrawChar(HDC hdc,RECT& rc, uint32_t ch);

	Paragraph* paragraph_;
	POINT pos_; //绘制的位置
	int min_;   //开始字符位置
	int max_;   //结束字符位置
};


//支持表情，emoji文字混排
class Paragraph {
public:
	Paragraph();
	~Paragraph();

	void AddText(const wchar_t * text,size_t len);
	void AddFace(uint32_t faceId);

	void Draw(HDC hdc,const RECT& rc);

	void SetMaxLine(size_t maxLine);
	void SetLineHeight(size_t height);

	SIZE GetCharSize(HDC hdc, uint32_t ch);
private:
	friend class Line;

	//布局计算
	void Layout(HDC hdc, int maxWidth);
	void NeedLayout();
	HBITMAP LoadCharBmp(uint32_t ch);

	ParagraphCallback* callback_;
	std::vector<uint32_t> content_;
	std::vector<SIZE> charSize_;

	std::vector<std::shared_ptr<Line>> lines_;
	std::map<uint32_t,HBITMAP> bmpCache_;

	size_t bmpSize_;
	size_t maxLine_;
	size_t lineHeight_;
	size_t lastMaxWidth_;
};





