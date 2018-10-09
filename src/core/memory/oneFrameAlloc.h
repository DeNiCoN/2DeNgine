#pragma once
#include <ctype.h>

typedef struct {
	char* buffer;
	size_t size;
	size_t offset;
} OneFrameAllocator;



void* frameAllocAligned(OneFrameAllocator* alloc, size_t size, size_t align);
void* frameAlloc(OneFrameAllocator* alloc, size_t size);
void frameAllocInit(OneFrameAllocator* alloc, char* buffer, size_t bufSize);
void frameReset(OneFrameAllocator* alloc); //Set offset to 0