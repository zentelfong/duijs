#include "ref_count.h"

#ifdef _WIN32

#include <Windows.h>

int AtomicOps::Increment(int* i) 
{
	return ::InterlockedIncrement(reinterpret_cast<LONG*>(i));
}


int AtomicOps::Decrement(int* i) 
{
	return ::InterlockedDecrement(reinterpret_cast<LONG*>(i));
}

#else

int AtomicOps::Increment(int* i) {
	return __sync_add_and_fetch(i, 1);
}

int AtomicOps::Decrement(int* i) {
	return __sync_sub_and_fetch(i, 1);
}

#endif

