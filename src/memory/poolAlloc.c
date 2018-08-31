#include "poolAlloc.h"
#include <ctype.h>

void poolInit(PoolAllocator* alloc, char* buffer, size_t objSize, unsigned int objCount) 
{
	if (objSize < MIN_POOL_OBJECT_SIZE_BYTES) 
	{
		return;
	}
	alloc->buffer = buffer;
	alloc->nextFreeBlock = (void*)buffer;
	alloc->objSize = objSize;
	alloc->objCount = objCount;
	char* current = buffer;
	char* next;
	for (int i = 0; i < objCount; i++) 
	{
		next = current + objSize;
		*((uintptr_t*)current) = (uintptr_t) next;
		current = next;
	}
	*((uintptr_t*)(current - objSize)) = NULL;
}

void* poolAlloc(PoolAllocator* alloc) 
{
	void* ptr = alloc->nextFreeBlock;
	alloc->nextFreeBlock = (void*) (*(uintptr_t*)ptr);
	return ptr;
}

void poolFree(PoolAllocator* alloc, void* pointer) 
{
	*((uintptr_t*) pointer) = alloc->nextFreeBlock;
	alloc->nextFreeBlock = pointer;
}

void poolReset(PoolAllocator* alloc) 
{
	poolInit(alloc, alloc->buffer, alloc->objSize, alloc->objCount);
}