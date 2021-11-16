#pragma once
#include <mutex>
#include <atomic>

template<class T> class WeakPtr;

template<class T>
struct WeakImpl {
	WeakImpl(T* p)
		:ptr(p), ref(1)
	{
	}

	bool valied() {
		return ptr != nullptr;
	}

	void Destroy() {
		lock.lock();
		ptr = nullptr;
		int r = --ref;
		lock.unlock();
		if (r == 0) {
			delete this;
		}
	}

	int AddRef() {
		return ++ref;
	}

	int Release() {
		int r = --ref;
		if (r == 0) {
			delete this;
		}
		return r;
	}

	void Lock() {
		lock.lock();
	}

	void Unlock() {
		lock.unlock();
	}

	T* ptr;
	std::atomic<int> ref;
	std::recursive_mutex lock;
};



template<class T>
class WeakObject {
public:
	WeakObject()
		:weak_impl_(new WeakImpl<T>(static_cast<T*>(this)))
	{
	}

	~WeakObject() {
		weak_impl_->Destroy();
	}

	WeakPtr<T> weak_ptr() {
		return WeakPtr<T>(weak_impl_);
	}

private:
	friend class WeakPtr<T>;
	WeakImpl<T>* weak_impl_;
};



template<class T>
class WeakPtr {
public:
	WeakPtr()
		:ptr_(nullptr)
	{
	}

	WeakPtr(WeakImpl<T>* data)
		:ptr_(data)
	{
		if(ptr_)
			ptr_->AddRef();
	}


	WeakPtr(const WeakPtr<T>& r):ptr_(r.ptr_)
	{
		if (ptr_)
			ptr_->AddRef();
	}

	~WeakPtr() {
		ptr_->Release();
	}

	WeakPtr<T>& operator=(WeakImpl<T>* p)
	{
		if (p) p->AddRef();
		if (ptr_) ptr_->Release();
		ptr_ = p;
		return *this;
	}

	WeakPtr<T>& operator=(const WeakPtr<T>& r)
	{
		return *this = r.ptr_;
	}

	T* Lock() const {
		if (ptr_) {
			ptr_->Lock();
			return ptr_->ptr;
		}
		return nullptr;
	}


	void Unlock() const {
		if (ptr_) {
			ptr_->Unlock();
		}
	}
private:
	WeakImpl<T>* ptr_;
};

