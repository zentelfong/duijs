#include "cjrpc.h"

#define JRPC_VERSION "2.0"

namespace cjsonpp {

Rpc::Rpc()
	:sender_(nullptr),gen_id_(0)
{
}

Rpc::~Rpc() {

}

void Rpc::registerSender(RpcSender* sender) {
	sender_ = sender;
}

void Rpc::registerHandler(const std::string& name, rpc_handler_t handler) {
	handlers_[name] = handler;
}

Json Rpc::handleRequest(Json& req) {
	Response response;

	Json jid = req.detach("id");

	do {
		Json jrpc = req.detach("jsonrpc");
		Json jmethod = req.detach("method");
		Json jparams = req.detach("params");

		if (jrpc.to<std::string>() != JRPC_VERSION || !jmethod.isString()) {
			response.error(JSONRPC2_EIREQ, "invalid request");
			break;
		}

		Request request(jmethod.to<std::string>(), jparams);
		auto find = handlers_.find(request.method());
		if (find == handlers_.end()) {
			response.error(JSONRPC2_ENOMET, "invalid method");
			break;
		}

		find->second(request, response);
	} while (0);

	if (!response.valied()) {
		response.ok(Json::null());
	}

	Json jres = response.data();
	jres.add("id", jid);
	jres.add("jsonrpc", JRPC_VERSION);
	return jres;
}

bool Rpc::handleResponse(Json& j) {
	Json jrpc = j.detach("jsonrpc");
	if (jrpc.to<std::string>() != JRPC_VERSION) {
		return false;
	}

	Response resp(j);
	Json jid = j.detach("id");
	auto find = calls_.find(jid.to<int>());
	if (find != calls_.end()) {
		find->second(resp);
		calls_.erase(find);
		return true;
	}
	return false;
}

void Rpc::call(const Request& req, rpc_call_t oncall) {
	Json jreq = Json::object();
	int id = ++gen_id_;
	jreq.add("id",Json(id));
	jreq.add("jsonrpc", JRPC_VERSION);
	jreq.add("method", Json(req.method()));
	jreq.add("params", req.params());
	calls_[id] = oncall;
	sender_->send(jreq);
}

void Rpc::call(const std::string& method, Json params, rpc_call_t oncall) {
	Request req(method, params);
	call(req, oncall);
}

bool Rpc::recv(Json& js) {
	if (js["method"].isString()) {
		Json jsend = handleRequest(js);
		sender_->send(jsend);
		return true;
	} else {
		return handleResponse(js);
	}
}

}//namespace
