#pragma once
#include "quickjs/qjs.h"

namespace duijs {

class JsEngine {
public:
	JsEngine();
	~JsEngine();

	bool Init();
	void RunLoop();

	qjs::Value Excute(const char* input, const char* filename);
	void DumpError() { context_->DumpError(); }
private:
	qjs::Runtime* runtime_;
	qjs::Context* context_;
};


}//namespace


