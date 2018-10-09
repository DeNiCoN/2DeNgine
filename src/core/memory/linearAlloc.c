#include <ctype.h>
#include "linearAlloc.h"
#include "memutils.h"
#include <stdio.h>

void* linAllocAligned(LinearAllocator* alloc, size_t size, size_t align) 
{
	if (align & (align - 1)) 
	{
		return NULL;
	}
	size_t addBytes = align - 1;
	uintptr_t rawPtr = (uintptr_t) alloc->buffer + alloc->offset;
	if (alloc->offset + size + addBytes > alloc->size) 
	{
		return NULL;
	}
	alloc->offset += size + addBytes;
	return (void*)(rawPtr & ~addBytes);
}

void* linAlloc(LinearAllocator* alloc, size_t size) 
{
	size_t prevOffset = alloc->offset;
	if (alloc->offset + size > alloc->size) 
	{
		return NULL;
	}
	alloc->offset += size;
	return alloc->buffer + prevOffset;
}

void linAllocInit(LinearAllocator* alloc, char* buffer, size_t bufSize) 
{
	alloc->buffer = buffer;
	alloc->size = bufSize;
	alloc->offset = 0;
}

void linReset(LinearAllocator* alloc) 
{
	alloc->offset = 0;
}

void linFree(LinearAllocator* alloc, void* pointer) 
{

}