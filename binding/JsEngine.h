#pragma once
#include "quickjs/qjs.h"

namespace duijs {

class JsEngine {
public:
	JsEngine();
	~JsEngine();

	bool Init();
	void RunLoop();

	bool Excute(const char* input, const char* filename);
private:
	qjs::Runtime* runtime_;
	qjs::Context* context_;
};


}//namespace


