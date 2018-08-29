#pragma once
#include <ctype.h>

typedef struct {
	size_t size;
	size_t stackPointer;
	size_t lastAllocatedSize;
	char* buffer;
} StackAllocator;

void* stackAlloc(StackAllocator* alloc, size_t size);
void* stackAllocAligned(StackAllocator* alloc, size_t size, size_t align);
void* stackFree(StackAllocator* alloc);
void* stackReset(StackAllocator* alloc);