#pragma once
#include <functional>


namespace network {


class Scheduler {
public:
	virtual void PostTask(std::function<void()> task) = 0;
};


}//namespace


