#pragma once

namespace DuiLib {

template<class T> class CWeakPtr;

template<class T>
struct CWeakImpl {
	CWeakImpl(T* p)
		:ptr(p), ref(1)
	{
		InitializeCriticalSection(&lock);
	}

	~CWeakImpl() {
		DeleteCriticalSection(&lock);
	}

	void Destroy() {
		EnterCriticalSection(&lock);
		ptr = nullptr;
		int r = --ref;
		LeaveCriticalSection(&lock);
		if (r == 0) {
			delete this;
		}
	}

	int AddRef() {
		EnterCriticalSection(&lock);
		int r = ++ref;
		LeaveCriticalSection(&lock);
		return r;
	}

	int Release() {
		EnterCriticalSection(&lock);
		int r = --ref;
		LeaveCriticalSection(&lock);
		if (r == 0) {
			delete this;
		}
		return r;
	}

	void Lock() {
		EnterCriticalSection(&lock);
	}

	void Unlock() {
		LeaveCriticalSection(&lock);
	}

	T*  ptr;
	int ref;
	CRITICAL_SECTION lock;
};

template<class T>
class CWeakObject {
public:
	CWeakObject()
		:weak_impl_(nullptr)
	{
	}

	~CWeakObject() {
		if(weak_impl_)
			weak_impl_->Destroy();
	}

	CWeakPtr<T> WeakPtr() {
		InitWeakImpl();
		return CWeakPtr<T>(weak_impl_);
	}


	int RefWeak() {
		InitWeakImpl();
		return weak_impl_->AddRef();
	}

	int UnrefWeak() {
		InitWeakImpl();
		return weak_impl_->Release();
	}

	CWeakImpl<T>* WeakImpl() {
		InitWeakImpl();
		return weak_impl_;
	}
private:
	inline void InitWeakImpl() {
		if(!weak_impl_)
			weak_impl_(new CWeakImpl<T>(static_cast<T*>(this)))
	}

	friend class CWeakPtr<T>;
	CWeakImpl<T>* weak_impl_;
};



template<class T>
class CWeakPtr {
public:
	CWeakPtr()
		:ptr_(nullptr)
	{
	}

	CWeakPtr(CWeakImpl<T>* data)
		:ptr_(data)
	{
		if(ptr_)
			ptr_->AddRef();
	}


	CWeakPtr(const CWeakPtr<T>& r):ptr_(r.ptr_)
	{
		if (ptr_)
			ptr_->AddRef();
	}

	~CWeakPtr() {
		ptr_->Release();
	}

	CWeakPtr<T>& operator=(CWeakImpl<T>* p)
	{
		if (p) p->AddRef();
		if (ptr_) ptr_->Release();
		ptr_ = p;
		return *this;
	}

	CWeakPtr<T>& operator=(const CWeakPtr<T>& r)
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
	CWeakImpl<T>* ptr_;
};


}//namespace
