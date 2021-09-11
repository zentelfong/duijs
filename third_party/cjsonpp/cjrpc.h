#pragma once
#include "cJSONPP.h"
#include <functional>
#include <string>
#include <unordered_map>

namespace cjsonpp {

enum {
JSONRPC2_EPARSE	= -32700, // Parse error: Invalid JSON was received by the server
JSONRPC2_EIREQ =	 -32600,   // Invalid Request: The JSON sent is not a valid Request object
JSONRPC2_ENOMET	=  -32601, // Method not found: The method doesn't exist/is not available
JSONRPC2_EIPARAM = -32602, // Invalid params: Invalid method parameter(s)
JSONRPC2_EINTERN = -32603, // Internal error: Internal JSON-RPC error
};

class Request {
public:
	Request(const std::string& method, const Json& params)
		:method_(method),params_(params)
	{
	}

	const std::string& method() const { return method_; }
	const Json& params() const { return params_; }
	Json param(const char* name) {
		return params_.at(name);
	}
private:
	std::string method_;
	Json params_;
};

class Response {
public:
	Response() 
	{
	}

	Response(Json& data)
		:data_(data)
	{
	}

	void ok(const Json& result) {
		data_ = Json::object();
		data_.add("result", result);
	}

	void error(const Json& error) {
		data_ = Json::object();
		data_.add("error", error);
	}

	void error(int code,const char* msg) {
		data_ = Json::object();
		Json error = Json::object();
		error.add("code", Json(code));
		error.add("message", Json(msg));
		data_.add("error", error);
	}

	Json data() {
		return data_;
	}

	Json result() {
		return data_["result"];
	}

	bool valied() {
		return data_.isObject();
	}
private:
	Json data_;
};

typedef std::function<void(Request& req,Response& resp)> rpc_handler_t;
typedef std::function<void(Response& resp)> rpc_call_t;

class RpcSender {
public:
	virtual ~RpcSender() {}
	virtual void send(Json& js) = 0;
};

class Rpc {
public:
	Rpc();
	Rpc(const Rpc&) = delete;
	Rpc& operator=(const Rpc&) = delete;
	~Rpc();

	void registerSender(RpcSender* sender);
	void registerHandler(const std::string& name, rpc_handler_t handler);

	bool recv(Json& js);

	void call(const Request& req, rpc_call_t oncall);
	void call(const std::string& method,Json params, rpc_call_t oncall);

private:
	//返回response json
	Json handleRequest(Json& req);
	bool handleResponse(Json& resp);

	RpcSender* sender_;
	int gen_id_;
	std::unordered_map<std::string, rpc_handler_t> handlers_;
	std::unordered_map<int, rpc_call_t> calls_;
};

}//namespace

