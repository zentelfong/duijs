#include "Util.h"
#include "async/image_loader.h"

namespace duijs {


static ImageData* createImage(qjs::Context& context, qjs::ArgList& args) {
	ImageData* img = MakeRefCounted<ImageData>();
	img->AddRef();
	return img;
}

static void deleteImage(ImageData* img) {
	img->Release();
}











}//namespace


