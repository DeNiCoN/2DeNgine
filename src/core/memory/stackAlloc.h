#pragma once
#include <ctype.h>

typedef struct {
	char* buffer;
	size_t size;
	size_t stackPointer;
} StackAllocator;

void* stackAlloc(StackAllocator* alloc, size_t size);
void* stackAllocAligned(StackAllocator* alloc, size_t size, size_t align);
void stackFree(StackAllocator* alloc);
void stackReset(StackAllocator* alloc);
void stackAllocInit(StackAllocator* alloc, char* buffer, size_t size);