#pragma once
#include <vector>
#include <string>
#include <functional>
#include "ref_count.h"

class Responce:public RefCountedBase {
public:
	int code;
	std::vector<char> responce;

	REF_IMPLEMENT_COUNTING(Responce);
};


class Request:public RefCountedBase {
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

	~Request() {

	}

	Type type;
	std::string url;
	std::string cookie;
	std::vector<char> post;
	std::vector<std::string> headers;
	std::function<void(RefCountedPtr<Responce>)> onResponce;
	REF_IMPLEMENT_COUNTING(Request);
};



