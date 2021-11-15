#ifndef MEMORY_REF_COUNTED_H_
#define MEMORY_REF_COUNTED_H_

#include <atomic>
#include <assert.h>
#include "ref_ptr.h"

// See ref_counted.h for comments on the public methods.
class RefCounted {
public:
	RefCounted(const RefCounted&) = delete;
	RefCounted& operator=(const RefCounted&) = delete;

	void AddRef() const {
		ref_count_.fetch_add(1u, std::memory_order_relaxed);
	}

	// Returns true if the object should self-delete.
	bool Release() const {
#ifndef NDEBUG
		assert(!adoption_required_);
		assert(!destruction_started_);
#endif
		assert(ref_count_.load(std::memory_order_acquire) != 0u);
		// TODO(vtl): We could add the following:
		//     if (ref_count_.load(std::memory_order_relaxed) == 1u) {
		// #ifndef NDEBUG
		//       destruction_started_= true;
		// #endif
		//       return true;
		//     }
		// This would be correct. On ARM (an Nexus 4), in *single-threaded* tests,
		// this seems to make the destruction case marginally faster (barely
		// measurable), and while the non-destruction case remains about the same
		// (possibly marginally slower, but my measurements aren't good enough to
		// have any confidence in that). I should try multithreaded/multicore tests.
		if (ref_count_.fetch_sub(1u, std::memory_order_release) == 1u) {
			std::atomic_thread_fence(std::memory_order_acquire);
#ifndef NDEBUG
			destruction_started_ = true;
#endif
			delete this;
			return true;
		}
		return false;
	}

	bool HasOneRef() const {
		return ref_count_.load(std::memory_order_acquire) == 1u;
	}
protected:
	RefCounted()
		: ref_count_(1u)
#ifndef NDEBUG
		,
		adoption_required_(true),
		destruction_started_(false)
#endif
	{
	}

	virtual ~RefCounted() {
#ifndef NDEBUG
		assert(!adoption_required_);
		// Should only be destroyed as a result of |Release()|.
		assert(destruction_started_);
#endif
	}

#ifndef NDEBUG
	template <typename T>
	friend RefPtr<T> AdoptRef(T* ptr);

	void Adopt() {
		assert(adoption_required_);
		adoption_required_ = false;
	}
#endif

private:
	mutable std::atomic_uint_fast32_t ref_count_;

#ifndef NDEBUG
	mutable bool adoption_required_;
	mutable bool destruction_started_;
#endif
};



#define FRIEND_REF_COUNTED(T) \
  friend class RefCounted; \
  friend class detail::MakeRefCountedHelper<T>

#endif 
