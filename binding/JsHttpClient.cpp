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



void RegisterHttpClient(Module* module) {
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
}


}//namespace



