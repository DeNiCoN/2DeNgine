#pragma once
#include <ctype.h>

#define ALIGN_POINTER(ptr, align) ((void*)((uintptr_t)ptr & (align - 1)))
//#define NULL (void*)0

/*
static inline void* alignPointer(void* ptr, size_t align) {

	return (align & (align - 1)) ? ptr : (void*)((uintptr_t)ptr & (align - 1));
} 
*/