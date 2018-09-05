#include "stackAlloc.h"
#include "memutils.h"
#include <ctype.h>
#define STACK_HEADER_SIZE_BYTES 4


void stackAllocInit(StackAllocator* alloc, char* buffer, size_t size) 
{
	alloc->buffer = buffer;
	alloc->size = size;
	alloc->stackPointer = 0;
}

void* stackAlloc(StackAllocator* alloc, size_t size) {
	if (alloc->stackPointer + size + STACK_HEADER_SIZE_BYTES > alloc->size) 
	{
		return NULL;
	}
	size_t prevSP = alloc->stackPointer;
	alloc->stackPointer += size + STACK_HEADER_SIZE_BYTES;
	void* headerPtr = alloc->buffer + (prevSP + size);
	*(unsigned __int32*) headerPtr = (unsigned __int32)size;
	return (void*) (alloc->buffer + prevSP);
}

void* stackAllocAligned(StackAllocator* alloc, size_t size, size_t align) 
{
	if (align & (align - 1)) 
	{
		return NULL;
	}
	uintptr_t mask = align - 1;
	size_t prevSP = alloc->stackPointer;
	if (alloc->stackPointer + size + STACK_HEADER_SIZE_BYTES + mask > alloc->size) 
	{
		return NULL;
	}
	alloc->stackPointer += size + STACK_HEADER_SIZE_BYTES + mask;
	void* headerPtr = alloc->buffer + (prevSP + size);
	*(unsigned __int32*)headerPtr = (unsigned __int32)size;
	return (void*)((uintptr_t) (alloc->buffer + prevSP) & ~mask);
}

void stackFree(StackAllocator* alloc) 
{
	size_t size = (size_t)((unsigned __int32*)(alloc->buffer + alloc->stackPointer))[-1];
	alloc->stackPointer -= size;
}

void stackReset(StackAllocator* alloc) 
{
	alloc->stackPointer = 0;
}