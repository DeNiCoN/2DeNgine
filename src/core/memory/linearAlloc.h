#pragma once
#include <ctype.h>

typedef struct {
	char* buffer;
	size_t size;
	size_t offset;
} LinearAllocator;

void* linAllocAligned(LinearAllocator* alloc, size_t size, size_t align);
void* linAlloc(LinearAllocator* alloc, size_t size);
void linAllocInit(LinearAllocator* alloc, char* buffer, size_t bufSize);
void linFree(LinearAllocator* alloc, void* pointer); // Do nothing
void linReset(LinearAllocator* alloc); //Set offset to 0