#include "storage.h"
#include "sqlite3/sqlite3.h"
#include "cjsonpp/cjsonpp.h"

using namespace cjsonpp;

Storage::Storage() 
	:sqlite_(nullptr), thread_("Storage")
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
			if (sqlite_) {
				finish(0);
				return;
			}
			int rslt = sqlite3_open(name_.c_str(), &sqlite_);
			if (rslt != 0) {
				sqlite3_close(sqlite_);
				sqlite_ = nullptr;
			}
			finish(rslt);
		});
}


void Storage::Close(std::function<void(int)> finish) {
	thread_.PostTask([this, finish]() {
		if (!sqlite_) {
			finish(0);
			return;
		}
		int rslt = sqlite3_close(sqlite_);
		sqlite_ = nullptr;
		finish(rslt);
		});

}

int on_exec(void* ud, int argc, char** argv, char** name) {
	Json* array = (Json*)ud;
	Json value = Json::object();
	for (int i = 0; i < argc; ++i) {
		value.add(name[i], argv[i]);
	}
	array->add(value);
	return 0;
}

void Storage::Exec(const std::string& sql, std::function<void(int,std::string)> finish) {
	std::string sql_(sql);
	thread_.PostTask([this, sql_, finish]() {
		if (!sqlite_) {
			finish(-1, "");
			return;
		}
		Json result = Json::array();
		char* error;
		int code = sqlite3_exec(sqlite_,sql_.c_str(),on_exec,&result,&error);
		if (code != SQLITE_OK) {
			finish(code, error);
		} else {
			finish(code, result.dump());
		}
	});
}


#include <thread>

void testStorage() {

	Storage s;
	s.Open("test.db", [](int code) {
		printf("open storage %d\n", code);
	});


	s.Exec("CREATE TABLE test(key text,value text)", [](int code, const std::string& js) {
		printf("create table %d %s\n", code,js.c_str());
	});

	s.Exec("INSERT INTO test VALUES ('Gates','Bill')", [](int code, const std::string& js) {
		printf("insert table %d %s\n", code, js.c_str());
	});

	s.Exec("SELECT * FROM test", [](int code, const std::string& js) {
		printf("select table %d %s\n", code, js.c_str());
	});


	s.Close([](int code) {
		printf("code storage %d\n", code);
	});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


