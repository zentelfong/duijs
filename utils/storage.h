#pragma once
#include "thread.h"
#include <string>

typedef struct sqlite3 sqlite3;

class Storage {
public:
	Storage();
	~Storage();

	void Open(const std::string& name, std::function<void(int)> finish);
	void Close(std::function<void(int)> finish);
	void Exec(const std::string& sql, std::function<void(int,std::string)> finish);
private:
	sqlite3* sqlite_;
	Thread thread_;
};

void testStorage();

