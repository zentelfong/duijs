#pragma once
#include <atomic>

namespace qjs {

template<class T> class WeakPtr;

template<class T>
struct WeakImpl {
	WeakImpl(T* p)
		:ptr(p), ref(1)
	{
	}

	bool valid() {
		return ptr != nullptr;
	}

	void Destroy() {
		ptr = nullptr;
		int r = --ref;
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

	T* ptr;
	std::atomic<int> ref;
};



template<class T>
class WeakObject {
public:
	WeakObject()
		:weak_impl_(nullptr)
	{
	}

	~WeakObject() {
		if(weak_impl_)
			weak_impl_->Destroy();
	}

	template<class U>
	WeakPtr<U> get_weak_ptr() {
		if (!weak_impl_) {
			weak_impl_ = new WeakImpl<T>(static_cast<T*>(this));
		}
		return WeakPtr<U>((WeakImpl<U>*)weak_impl_);
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


	WeakPtr(nullptr_t null)
		:ptr_(nullptr)
	{
	}


	WeakPtr(WeakImpl<T>* data)
		:ptr_(data)
	{
		if(ptr_)
			ptr_->AddRef();
	}

	WeakPtr(WeakObject<T>* data)
		:ptr_(data->weak_impl_)
	{
		if (ptr_)
			ptr_->AddRef();
	}


	WeakPtr(const WeakPtr<T>& r)
		:ptr_(r.ptr_)
	{
		if (ptr_)
			ptr_->AddRef();
	}

	~WeakPtr() {
		ptr_->Release();
	}

	WeakPtr<T>& operator=(WeakImpl<T>* p) {
		if (p) p->AddRef();
		if (ptr_) ptr_->Release();
		ptr_ = p;
		return *this;
	}

	WeakPtr<T>& operator=(const WeakPtr<T>& r) {
		return *this = r.ptr_;
	}

	WeakImpl<T>* impl() {
		return ptr_;
	}

	T* get() {
		if (ptr_ && ptr_->valid())
			return ptr_->ptr;
		else
			return nullptr;
	}

	bool valid() {
		return ptr_ && ptr_->valid();
	}

	operator bool() {
		return ptr_ && ptr_->valid();
	}

	operator T* () const { 
		if (ptr_ && ptr_->valid())
			return ptr_->ptr;
		else
			return nullptr;
	}

	T& operator*() const {
		assert(ptr_ && ptr_->valid());
		return ptr_->ptr;
	}

	T* operator->() const {
		assert(ptr_ && ptr_->valid());
		return ptr_->ptr;
	}
private:
	WeakImpl<T>* ptr_;
};

}//namespace

