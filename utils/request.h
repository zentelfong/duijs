#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>


class Responce {
public:
	int code;
	std::vector<char> responce;
};


class Request {
public:
	enum Type {
		kGet,
		kPost,
		kPut,
		kDelete,
	};

	Request()
		:type(kGet){

	}

	Type type;
	std::string url;
	std::vector<char> post;
	std::vector<std::string> headers;
	std::function<void(std::shared_ptr<Responce>)> on_responce;
};



