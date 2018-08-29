#pragma once
#include <ctype.h>

typedef struct {
	char* buffer;
	size_t size;
	uintptr_t offset;
} LinearAllocator;

void* linAllocAligned(LinearAllocator* alloc, size_t size, size_t align);
void linFree(LinearAllocator alloc, void* pointer);
void linReset(LinearAllocator alloc);