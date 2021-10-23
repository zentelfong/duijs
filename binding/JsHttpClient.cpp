#include "network/HttpClient.h"
#include "Util.h"
#include "JsEngine.h"


namespace duijs {

using namespace network;

static void deleteClient(HttpClient* w) {
	HttpClient::Destroy(w);
}

static HttpClient* createClient(qjs::Context& context, qjs::ArgList& args) {
	JsEngine* engine = JsEngine::get(context);
	return HttpClient::Create(std::bind(&JsEngine::PostTask,engine,std::placeholders::_1));
}

static Value enableCookies(HttpClient* pThis, Context& context, ArgList& args) {
	pThis->enableCookies(args[0].ToStdString().c_str());
	return undefined_value;
}

static Value getCookieFilename(HttpClient* pThis, Context& context, ArgList& args) {
	return context.NewString(pThis->getCookieFilename().c_str());
}

static Value setSSLVerification(HttpClient* pThis, Context& context, ArgList& args) {
	pThis->setSSLVerification(args[0].ToStdString().c_str());
	return undefined_value;
}

static Value getSSLVerification(HttpClient* pThis, Context& context, ArgList& args) {
	return context.NewString(pThis->getSSLVerification().c_str());
}

static Value setTimeoutForConnect(HttpClient* pThis, Context& context, ArgList& args) {
	pThis->setTimeoutForConnect(args[0].ToInt32());
	return undefined_value;
}

static Value getTimeoutForConnect(HttpClient* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->getTimeoutForConnect());
}

static Value setTimeoutForRead(HttpClient* pThis, Context& context, ArgList& args) {
	pThis->setTimeoutForRead(args[0].ToInt32());
	return undefined_value;
}

static Value getTimeoutForRead(HttpClient* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->getTimeoutForRead());
}


//HttpResponse
static void deleteResponce(HttpResponse* rep) {
	rep->Release();
}

static HttpResponse* createResponce(qjs::Context& context, qjs::ArgList& args) {
	return NULL;
}

Value ToValue(Context& context,HttpResponse* response) {
	response->AddRef();
	return Class<HttpResponse>::ToJs(context, response);
}

static Value succeed(HttpResponse* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->isSucceed());
}

static Value body(HttpResponse* pThis, Context& context, ArgList& args) {
	std::vector<char>* data = pThis->getResponseData();
	return context.NewString(data->data(),data->size());
}

static Value headers(HttpResponse* pThis, Context& context, ArgList& args) {
	std::vector<char>* data = pThis->getResponseHeader();
	return context.NewString(data->data(), data->size());
}

static Value code(HttpResponse* pThis, Context& context, ArgList& args) {
	return context.NewInt32(pThis->getResponseCode());
}

static Value error(HttpResponse* pThis, Context& context, ArgList& args) {
	return context.NewString(pThis->getErrorBuffer());
}



//HttpRequest

class JsRequest :public HttpRequest {
public:
	JsRequest() {
	}

	~JsRequest() {
	}

	void OnFinish(HttpClient* client, HttpResponse* response) {
		if (callback_.IsFunction()) {
			callback_.Call(ToValue(*callback_.context(), response));
		}
	}

	void Mark(JS_MarkFunc* mark_func) {
		callback_.Mark(mark_func);
	}

	void SetCallback(Value callback) {
		callback_ = callback;
		setResponseCallback(std::bind(&JsRequest::OnFinish, 
			this, std::placeholders::_1, std::placeholders::_2));
	}
private:
	Value callback_;
};

static void deleteRequest(JsRequest* req) {
	req->Release();
}

static JsRequest* createRequest(qjs::Context& context, qjs::ArgList& args) {
	JsRequest* req = new JsRequest();
	req->AddRef();

	if (args[0].IsString()) {
		req->setUrl(args[0].ToStdString());
	}
	return req;
}

static void markRequest(JsRequest* pThis, JS_MarkFunc* mark_func) {
	pThis->Mark(mark_func);
}

static Value setType(JsRequest* pThis, Context& context, ArgList& args) {
	pThis->setRequestType((HttpRequest::Type)args[0].ToInt32());
	return undefined_value;
}

static Value setUrl(JsRequest* pThis, Context& context, ArgList& args) {
	pThis->setUrl(args[0].ToStdString());
	return undefined_value;
}

static Value setBody(JsRequest* pThis, Context& context, ArgList& args) {
	auto body = args[0].ToString();
	pThis->setRequestData(body.str(), body.len());
	return undefined_value;
}

static Value setCallback(JsRequest* pThis, Context& context, ArgList& args) {
	if (!args[0].IsFunction()) {
		return context.ThrowTypeError("args 0 needs function");
	}

	pThis->SetCallback(args[0]);
	return undefined_value;
}


static Value setHeaders(JsRequest* pThis, Context& context, ArgList& args) {
	if (!args[0].IsObject()) {
		return context.ThrowTypeError("args 0 needs object");
	}

	std::vector<std::string> headers;
	auto properties = args[0].GetProperties();
	for (auto pro : properties) {
		std::string header = pro.first;
		header.append(":");
		header.append(pro.second.ToStdString());
		headers.push_back(header);
	}
	pThis->setHeaders(headers);
	return undefined_value;
}

static Value get(HttpClient* pThis, Context& context, ArgList& args) {
	JsRequest * req = Class<JsRequest>::ToC(args[0]);
	if (!req) {
		return context.ThrowTypeError("args 0 needs HttpRequest");
	}
	req->setRequestType(HttpRequest::Type::kGET);
	pThis->send(req);
	return undefined_value;
}

static Value post(HttpClient* pThis, Context& context, ArgList& args) {
	JsRequest* req = Class<JsRequest>::ToC(args[0]);
	if (!req) {
		return context.ThrowTypeError("args 0 needs HttpRequest");
	}
	req->setRequestType(HttpRequest::Type::kPOST);
	pThis->send(req);
	return undefined_value;
}

static Value send(HttpClient* pThis, Context& context, ArgList& args) {
	JsRequest* req = Class<JsRequest>::ToC(args[0]);
	if (!req) {
		return context.ThrowTypeError("args 0 needs HttpRequest");
	}
	pThis->send(req);
	return undefined_value;
}

static Value sendImmediate(HttpClient* pThis, Context& context, ArgList& args) {
	JsRequest* req = Class<JsRequest>::ToC(args[0]);
	if (!req) {
		return context.ThrowTypeError("args 0 needs HttpRequest");
	}
	pThis->sendImmediate(req);
	return undefined_value;
}

void RegisterHttpClient(Module* module) {

	{
		auto ctrl = module->ExportClass<HttpClient>("HttpClient");
		ctrl.Init<deleteClient>();
		ctrl.AddCtor<createClient>();

		ADD_FUNCTION(enableCookies);
		ADD_FUNCTION(getCookieFilename);
		ADD_FUNCTION(setSSLVerification);
		ADD_FUNCTION(getSSLVerification);
		ADD_FUNCTION(setTimeoutForConnect);
		ADD_FUNCTION(getTimeoutForConnect);
		ADD_FUNCTION(setTimeoutForRead);
		ADD_FUNCTION(getTimeoutForRead);
		ADD_FUNCTION(send);
		ADD_FUNCTION(sendImmediate);
		ADD_FUNCTION(get);
		ADD_FUNCTION(post);
	}

	{
		auto ctrl = module->ExportClass<HttpResponse>("HttpResponse");
		ctrl.Init<deleteResponce>();

		ADD_FUNCTION(succeed);
		ADD_FUNCTION(body);
		ADD_FUNCTION(headers);
		ADD_FUNCTION(code);
		ADD_FUNCTION(error);
	}

	{
		auto ctrl = module->ExportClass<JsRequest>("HttpRequest");
		ctrl.Init2<deleteRequest, markRequest>();
		ctrl.AddCtor<createRequest>();
		ADD_FUNCTION(setType);
		ADD_FUNCTION(setUrl);
		ADD_FUNCTION(setHeaders);
		ADD_FUNCTION(setBody);
		ADD_FUNCTION(setCallback);
	}
}


}//namespace



