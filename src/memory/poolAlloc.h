#pragma once
#include <ctype.h>
#define MIN_POOL_OBJECT_SIZE_BYTES 8

typedef struct {
	char* buffer;
	unsigned int objCount;
	size_t objSize;
	void* nextFreeBlock;
} PoolAllocator;

void poolInit(PoolAllocator* alloc, char* buffer, size_t objSize, unsigned int objCount); //places pointer to next free block in every block
void* poolAlloc(PoolAllocator* alloc); //remove pointer to next free block, return free block
void poolFree(PoolAllocator* alloc, void* pointer); // place pointer into block, set next free block to this pointer
void poolReset(PoolAllocator* alloc); //works like init