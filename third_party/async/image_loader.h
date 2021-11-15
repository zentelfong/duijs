#pragma once
#include "thread.h"
#include "weak_ptr.h"
#include "ref_counted.h"
#include <string>

//Í¼Æ¬Êı¾İ
class ImageData:public RefCounted {
public:
	ImageData();
	~ImageData();

	int x() { return x_; }
	int y() { return y_; }
	int comp() { return comp_; }
	uint8_t* pixel() { return pixel_; }

private:
	int x_;
	int y_;
	int comp_;
	uint8_t* pixel_;
};

//Í¼Æ¬¼ÓÔØÆ÷
class ImageLoader:public WeakObject<ImageLoader> {
public:
	ImageLoader();
	~ImageLoader();

	//Òì²½¼ÓÔØÍ¼Æ¬
	void Load(const std::string& path, 
		std::function<void(RefPtr<ImageData>)> finish);

private:

};


