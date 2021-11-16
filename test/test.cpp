#include "async/image_loader.h"
#include "gtest/gtest.h"

TEST(ImageLoader, LoadImage) {

	ImageLoader loader;

	loader.Load("test.jpg", [](RefPtr<ImageData> img) {
		int fff = 0;
		img->Resize(100, 100);
		img->SavePng("out.png");
		int fff2 = 0;
		});

	_sleep(1000);
}






