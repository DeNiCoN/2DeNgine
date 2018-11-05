#include "poolAlloc.h"
#include <ctype.h>

int poolInit(PoolAllocator* alloc, char* buffer, size_t objSize, unsigned int objCount) 
{
	if (objSize < MIN_POOL_OBJECT_SIZE_BYTES) 
	{
		return 0;
	}
	alloc->buffer = buffer;
	alloc->nextFreeBlock = (void*)buffer;
	alloc->objSize = objSize;
	alloc->objCount = objCount;
	char* current = buffer;
	char* next;
	for (unsigned int i = 0; i < objCount; i++) 
	{
		next = current + objSize;
		*((uintptr_t*)current) = (uintptr_t) next;
		current = next;
	}
	*((uintptr_t*)(current - objSize)) = (uintptr_t) NULL;
	return 1;
}

void* poolAlloc(PoolAllocator* alloc) 
{
	if (alloc->nextFreeBlock)
	{
		void* ptr = alloc->nextFreeBlock;
		alloc->nextFreeBlock = (void*)(*(uintptr_t*)ptr); // take pointer from ptr and set nextFreeBlock to it
		return ptr;
	}
	return NULL;
}

void poolFree(PoolAllocator* alloc, void* pointer) 
{
	*((uintptr_t*) pointer) = (uintptr_t) alloc->nextFreeBlock; // write nextFreeBlock in point that pointer points
	alloc->nextFreeBlock = pointer;
}

void poolReset(PoolAllocator* alloc) 
{
	poolInit(alloc, alloc->buffer, alloc->objSize, alloc->objCount);
}