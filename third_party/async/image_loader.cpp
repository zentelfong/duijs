#include "image_loader.h"
#include "stbimage/stb_image.h"
#include "stbimage/stb_image_resize.h"

ImageData::ImageData() 
	:x_(0),y_(0),comp_(0),pixel_(nullptr)
{
}

ImageData::~ImageData() {
	stbi_image_free(pixel_);
}

bool ImageData::Load(const char* file) {
	if (pixel_) {
		stbi_image_free(pixel_);
	}
	pixel_ = stbi_load(file, &x_, &y_, &comp_, 4);
	return pixel_ != nullptr;
}

void ImageData::Resize(int x, int y) {
	if (!pixel_)
		return;

	uint8_t* pixel_out = (uint8_t*)stbi_image_malloc(x * y * comp_);
	if (stbir_resize_uint8(pixel_, x_, y_, x_, pixel_out, x, y, x, comp_)) {
		stbi_image_free(pixel_);
		pixel_ = pixel_out;
	} else {
		stbi_image_free(pixel_out);
	}
}

ImageLoader::ImageLoader() 
	:thread_mgr_(ThreadManager::Instance())
{
}

ImageLoader::~ImageLoader() {
}

void ImageLoader::Load(const std::string& path,
	std::function<void(RefPtr<ImageData>)> finish) {

	WeakPtr<ImageLoader> ptr = weak_ptr();
	std::string path_(path);
	thread_mgr_->PostTask(ThreadManager::kImage, [path_,ptr,finish]() {
		auto img_data = MakeRefCounted<ImageData>();
		img_data->Load(path_.c_str());

		auto pThis = ptr.Lock();
		finish(img_data);
		ptr.Unlock();
	});
}
