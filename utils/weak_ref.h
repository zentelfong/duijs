#pragma once
template<class T> class WeakPtr;


template<class T>
class WeakObject {
public:
	WeakObject()
		:weak_data_(new WeakData(this))
	{
	}

	~WeakObject() {
		weak_data_->Invalied();
		weak_data_->Release();
	}

	WeakPtr weak_ptr() {
		return WeakPtr(weak_data_);
	}

private:
	struct WeakData{
		WeakObject(T* p) 
			:ptr(p),ref(1)
		{
		}

		void Invalied() {
			ptr = nullptr;
		}

		int AddRef() {
			return AtomicOps::Increment(&ref);
		}

		int Release() {
			int count = AtomicOps::Decrement(&ref);
			if (!count) {
				delete this;
			}
			return count;
		}
		T*  ptr;
		int ref;
	};

	friend class WeakPtr<T>;
	WeakData* weak_data_;
};



template<class T>
class WeakPtr {
public:
	WeakPtr(WeakObject<T>::WeakData* data) {
		data->AddRef();
	}

	~WeakPtr() {
		data->Release();
	}


private:
	WeakObject<T>::WeakData* ptr_;
};



