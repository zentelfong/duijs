#pragma once
#include "thread.h"
#include "weak_ptr.h"
#include "ref_counted.h"
#include <string>

//图片数据
class ImageData:public RefCounted {
public:
	ImageData();
	~ImageData();

	bool Load(const char* file);

	int x() { return x_; }
	int y() { return y_; }
	int comp() { return comp_; }
	uint8_t* pixel() { return pixel_; }

	void Resize(int x, int y);

	bool SaveJpg(const char* file);
	bool SavePng(const char* file);
private:
	int x_;
	int y_;
	int comp_;
	uint8_t* pixel_;
};

//图片加载器，如果ImageLoader被释放,则finish不会被调用
class ImageLoader:public WeakObject<ImageLoader> {
public:
	ImageLoader();
	~ImageLoader();

	//异步加载图片
	void Load(const std::string& path, 
		std::function<void(RefPtr<ImageData>)> finish);

private:
	ThreadManager* thread_mgr_;
};


