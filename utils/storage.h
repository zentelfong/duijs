#pragma once
#include "thread.h"
#include "weak_ptr.h"
#include <string>

typedef struct sqlite3 sqlite3;

class Storage:public WeakObject<Storage> {
public:
	Storage();
	~Storage();

	void Open(const std::string& name, std::function<void(int)> finish);
	void Close(std::function<void(int)> finish);
	void Exec(const std::string& sql, std::function<void(int,std::string)> finish);
private:
	sqlite3* sqlite_;
	ThreadManager* thread_mgr_;
};

void testStorage();

