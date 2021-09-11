#include "storage.h"
#include "third_party/sqlite3/sqlite3.h"


Storage::Storage() 
	:sqlite_(nullptr)
{
	thread_.Start();
}


Storage::~Storage() {
	thread_.Stop();
	thread_.Join();
}

void Storage::Open(const std::string& name, std::function<void(int)> finish) {
	std::string name_(name);
	thread_.PostTask([this, name_,finish]() {
			int rslt = sqlite3_open(name_.c_str(), &sqlite_);
			finish(rslt);
		});
}


void Storage::Close(std::function<void(int)> finish) {
	thread_.PostTask([this, finish]() {
		int rslt = sqlite3_close(sqlite_);
		sqlite_ = nullptr;
		finish(rslt);
		});

}


void Storage::Exec(const std::string& sql, std::function<void(int, const std::string&)> finish) {
	std::string sql_(sql);
	thread_.PostTask([this, sql_, finish]() {
		});

}



