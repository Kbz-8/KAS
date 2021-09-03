// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 03/09/2021

#ifndef __KMlib__
#define __KMlib__

#include <stdio.h>
#include <unistd.h>

#define malloc(x) kml_malloc(x) // replacing all malloc by kml_malloc due to conflict between malloc and sbrk
#define realloc(x) kml_realloc(x)
#define calloc(x, y) kml_calloc(x, y)
#define free(x), kml_free(x)

typedef struct block block;

struct block
{
	size_t size;
	block* next;
	block* prev;
};

static block* head = NULL;
static block* tail = NULL;

void* kml_memset(void* ptr, int c, size_t size)
{
	#ifdef KAS_MEMSET_AUTO_MALLOC
		if(!ptr)
			ptr = kml_malloc(size);
	#endif

	unsigned char* source = (unsigned char*)ptr;
	while(size--)
	{
		*source++ = (unsigned char*)c;
	}
	return ptr;
}

void* kml_memcpy(void* dest, void* src, size_t size)
{	
	#ifdef KAS_MEMCPY_AUTO_MALLOC
		if(!dest)
			dest = kml_malloc(size);
	#endif

	unsigned char* p_dest = (unsigned char*)dest;
	const unsigned char* p_src = (unsigned char*)src;

	if(dest != NULL && src != NULL)
	{
		while(size--)
		{
			*p_dest++ = *p_src++;
		}
	}
	return dest;
}

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

void* kml_malloc(size_t size)
{
	void* ptr = NULL;
	size_t _size = size >= 3 * sysconf(_SC_PAGESIZE) ? size + sizeof(block) : 3 * sysconf(_SC_PAGESIZE);

	block* block_ptr = head;

#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
		block_ptr = sbrk(_size); // calling system allocation function sbrk
#pragma GCC diagnostic pop

	add_block(block_ptr);
	if(!block_ptr)
	{
		printf("\033]1;31m kmlib error: unable to alloc %ld size \033]1;39m \n", size);
		return NULL;
	}
	ptr = (void*)((unsigned long)block_ptr + sizeof(block));
	return ptr;
}

int kml_free(void* ptr)
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

void* kml_realloc(void* ptr, size_t size)
{
	if(!ptr)
		return kml_malloc(size);
	block* finder = head;
	void* newPtr = NULL;
	size_t block_size = sizeof(block);
	while(finder != tail)
	{
		if(ptr == (void*)((unsigned long)finder + block_size))
		{
			if(size == finder->size)
				return ptr;

			newPtr = kml_malloc(size);

			if(size > finder->size)
				kml_memcpy(newPtr, ptr, finder->size);
			else if(size < finder->size)
				kml_memcpy(newPtr, ptr, size);

			if(!newPtr)
			{
				printf("\033]1;31m kmlib error: unable to realloc %ld size \033]1;39m \n", size);
				return NULL;
			}
			return newPtr;
		}
	}
}

void* kml_calloc(size_t n, size_t size)
{
	void* ptr = kml_malloc(n * size);
	if(!ptr)
	{
		printf("\033]1;31m kmlib error: unable to calloc %ld size \033]1;39m \n", size);
		return NULL;
	}
	kml_memset(ptr, 0, n * size);
	return ptr;
}

#endif // __KMlib__

