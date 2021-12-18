#include "async/image_loader.h"
#include "network/FileDownload.h"
#include "gtest/gtest.h"

using namespace network;

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


class DownloadListener:public CurlDownloadListener{
public:
	virtual void didReceiveResponse() { 
		printf("download responce\n");
	}

	virtual void didProgress(int total, int size) {
		printf("download data %d/%d\n",size, total);
	}

	virtual void didFinish() {
		printf("download finish");
	}

	virtual void didFail() { 
		printf("download faild");
	}
};

DownloadListener* listener = new DownloadListener();


TEST(FileDownload, download) {

	auto download = CurlDownload::create(listener,"https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png","dest.png");
	download->start();
}

