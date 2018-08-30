#pragma once
#include <ctype.h>
#define MIN_POOL_OBJECT_SIZE_BYTES 8

typedef struct {
	char* buffer;
	unsigned int objCount;
	size_t objSize;
	void* nextFreeBlock;
} PoolAllocator;

void PoolInit(PoolAllocator* alloc, char* buffer, size_t objSize, unsigned int objCount); //places pointer to next free block in every block
void* PoolAlloc(PoolAllocator* alloc); //remove pointer to next free block, return free block
void PoolFree(PoolAllocator* alloc, void* pointer); // place pointer into block, set next free block to this pointer
void PoolReset(PoolAllocator* alloc); //works like init