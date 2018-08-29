#pragma once
#include <ctype.h>

#define MAX_ALIGN = 128

typedef struct {
	char* buffer;
	size_t size;
	size_t offset;
} LinearAllocator;

void* linAllocAligned(LinearAllocator* alloc, size_t size, size_t align);
void* linAlloc(LinearAllocator* alloc, size_t size);
LinearAllocator linAllocInit(char* buffer, size_t bufSize);
void linFree(LinearAllocator* alloc, void* pointer); // Do nothing
void linReset(LinearAllocator* alloc); //Set offset to 0