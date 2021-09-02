// KAS (Kbz_8 Allocation System) project is a mini project for fun.
// It's my own implementation of functions malloc,
// free, realloc, calloc...
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 02/09/2021

#ifndef __KAS__
#define __KAS__

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define malloc(x) kas_malloc(x) // replacing all malloc by kas_malloc due to conflict between malloc and sbrk

typedef struct block block;

struct block
{
	size_t size;
	block* next;
	block* prev;
};

static block* head = NULL;
static block* tail = NULL;

void add_block(block* newBlock)
{
	newBlock->prev = NULL;
	newBlock->next = NULL;
	if(!head)
	{
		head = newBlock;
		tail = head;
	}
	else
	{
		newBlock->prev = tail;
		tail = newBlock;
	}
}

void remove_block(block* delBlock)
{
	if(delBlock == head)
	{
		head = NULL;
		tail = head;
	}
	else if(delBlock == tail)
		tail = delBlock->prev;
	else
	{
		delBlock->next->prev = delBlock->prev;
		delBlock->prev->next = delBlock->next;
	}

	delBlock = NULL;
}

void* kas_malloc(size_t size)
{
	void* ptr = NULL;
	size_t _size = size >= 3 * sysconf(_SC_PAGESIZE) ? size + sizeof(block) : 3 * sysconf(_SC_PAGESIZE);

	block* block_ptr = head;

	block_ptr = sbrk(_size); // calling system allocation function
	add_block(block_ptr);
	if(!block_ptr)
	{
		printf("\033]1;31m KAS error: unable to alloc %ld size \033]1;39m \n", size);
		return NULL;
	}
	ptr = (void*)((unsigned long)block_ptr + sizeof(block));
	return ptr;
}

int kas_free(void* ptr)
{
	block* finder = head;
	size_t block_size = sizeof(block); // avoiding redoing sizeof(block) operation at each turn of the loop
	while(finder != tail)
	{
		if(ptr == (void*)((unsigned long)finder + block_size)) // searching for pointer in blocks chain
		{
			block_size += finder->size;
			remove_block(finder);
			ptr = NULL;
			sbrk(-block_size);
			return 1; // pointer was correctly freed
		}

		finder = finder->next;
	}
	return 0; // pointer was not correctly freed
}

void* kas_realloc(void* ptr, size_t size)
{
	if(!ptr)
		return kas_malloc(size);
	block* finder = head;
	void* newPtr = NULL;
	size_t block_size = sizeof(block);
	while(finder != tail)
	{
		if(ptr == (void*)((unsigned long)finder + block_size))
		{
			if(size == finder->size)
				return ptr;

			newPtr = kas_malloc(size);

			if(size > finder->size)
				memcpy(newPtr, ptr, finder->size);
			else if(size < finder->size)
				memcpy(newPtr, ptr, size);

			if(!newPtr)
			{
				printf("\033]1;31m KAS error: unable to realloc %ld size \033]1;39m \n", size);
				return NULL;
			}
			return newPtr;
		}
	}
}

#endif // __KAS__

