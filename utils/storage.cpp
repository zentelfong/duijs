#include "storage.h"
#include "sqlite3/sqlite3.h"
#include "cjsonpp/cjsonpp.h"

using namespace cjsonpp;

Storage::Storage() 
	:sqlite_(nullptr), thread_mgr_(ThreadManager::Instance())
{
}

Storage::~Storage() {
}

void Storage::Open(const std::string& name, std::function<void(int)> finish) {
	std::string name_(name);
	WeakPtr<Storage> ptr = weak_ptr();
	thread_mgr_->PostTask(ThreadManager::kStorage,[ptr, name_,finish]() {
		Storage* pThis = ptr.Lock();
		if (pThis) {
			if (pThis->sqlite_) {
				sqlite3_close(pThis->sqlite_);
				pThis->sqlite_ = nullptr;
			}

			int rslt = sqlite3_open(name_.c_str(), &pThis->sqlite_);
			if (rslt != 0) {
				sqlite3_close(pThis->sqlite_);
				pThis->sqlite_ = nullptr;
			}
			finish(rslt);
		}
		ptr.Unlock();
	});
}


void Storage::Close(std::function<void(int)> finish) {
	WeakPtr<Storage> ptr = weak_ptr();
	thread_mgr_->PostTask(ThreadManager::kStorage, [ptr, finish]() {
		Storage* pThis = ptr.Lock();
		if (pThis && pThis->sqlite_) {
			int rslt = sqlite3_close(pThis->sqlite_);
			pThis->sqlite_ = nullptr;
			finish(rslt);
		}
		ptr.Unlock();
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
	WeakPtr<Storage> ptr = weak_ptr();

	thread_mgr_->PostTask(ThreadManager::kStorage,[ptr, sql_, finish]() {
		Storage* pThis = ptr.Lock();
		if (pThis && pThis->sqlite_) {
			Json result = Json::array();
			char* error;
			int code = sqlite3_exec(pThis->sqlite_, sql_.c_str(), on_exec, &result, &error);
			if (code != SQLITE_OK) {
				finish(code, error);
			}
			else {
				finish(code, result.dump());
			}
		}
		ptr.Unlock();
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


