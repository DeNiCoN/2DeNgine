#pragma once

typedef struct {
	size_t objCount;
	size_t objSize;
	char* buffer;
	void* nextFreeBlock;
} PoolAllocator;

void* PoolAlloc(PoolAllocator alloc);
void PoolFree(PoolAllocator alloc, void* pointer);
void PoolInit(PoolAllocator alloc);
void PoolReset(PoolAllocator alloc);