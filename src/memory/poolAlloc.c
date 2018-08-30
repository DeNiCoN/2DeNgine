#include "poolAlloc.h"
#include <ctype.h>

void PoolInit(PoolAllocator* alloc, char* buffer, size_t objSize, unsigned int objCount) {
	if (objSize < MIN_POOL_OBJECT_SIZE_BYTES) {
		return;
	}
	alloc->buffer = buffer;
	alloc->nextFreeBlock = (void*)buffer;
	alloc->objSize = objSize;
	alloc->objCount = objCount;
	char* current = buffer;
	char* next;
	for (int i = 0; i < objCount; i++) {
		next = current + objSize;
		*((uintptr_t*)current) = (uintptr_t) next;
		current = next;
	}
	*((uintptr_t*)(current - objSize)) = NULL;
}

void* PoolAlloc(PoolAllocator* alloc) {
	void* ptr = alloc->nextFreeBlock;
	alloc->nextFreeBlock = (void*) ((char*)ptr + alloc->objSize);
	return ptr;
}

void PoolFree(PoolAllocator* alloc, void* pointer) {
	*((uintptr_t*) pointer) = ((char*)pointer + alloc->objSize);
	alloc->nextFreeBlock = pointer;
}

void PoolReset(PoolAllocator* alloc) {
	PoolInit(alloc, alloc->buffer, alloc->objSize, alloc->objCount);
}