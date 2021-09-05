// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 04/09/2021

#ifndef __KMlib__
#define __KMlib__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define malloc(x) kml_malloc(x) // replacing all malloc by kml_malloc due to conflict between malloc and sbrk
#define realloc(x) kml_realloc(x)
#define calloc(x, y) kml_calloc(x, y)
#define free(x) kml_free(x)

typedef struct block block;

struct block
{
	size_t size;
	block* next;
	block* prev;
};

static block* head = NULL;
static block* tail = NULL;
static unsigned long long gc_leaks_bytes = 0;
static bool is_gc_init = false;

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
		if(head->next != NULL)
			head = head->next;
		else
		{
			head = NULL;
			tail = head;
		}
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
	block* block_ptr = head;

#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
		block_ptr = sbrk(size); // calling system allocation function
#pragma GCC diagnostic pop

	block_ptr->size = size;
	add_block(block_ptr);
	if(!block_ptr)
	{
		printf("\033[0;31m");
		printf("kmlib error: unable to alloc %d size\n", size);
		printf("\033[0m");
		return NULL;
	}
	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;

	return ptr;
}

int kml_free(void* ptr)
{
	block* finder = head;
	size_t block_size = sizeof(block); // avoiding redoing sizeof(block) operation at each turn of the loop
	do
	{
		if(ptr == (void*)((unsigned long)finder + block_size)) // searching for pointer in blocks chain
		{
			block_size += finder->size;
			if(is_gc_init)
				gc_leaks_bytes -= finder->size;
			remove_block(finder);
			ptr = NULL;
			sbrk(-block_size);
			return 1; // if pointer was correctly freed
		}

		finder = finder->next;
	} while(finder != tail);
	return 0; // if pointer was not correctly freed
}

void* kml_realloc(void* ptr, size_t size)
{
	if(!ptr)
		return kml_malloc(size);
	block* finder = head;
	void* newPtr = NULL;
	size_t block_size = sizeof(block);
	do
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
				printf("\033[0;31m");
				printf("kmlib error: unable to realloc %d size\n", size);
				printf("\033[0m");
				return NULL;
			}
			return newPtr;
		}
	} while(finder != tail);
	return NULL;
}

void* kml_calloc(size_t n, size_t size)
{
	void* ptr = kml_malloc(n * size);
	if(!ptr)
	{
		printf("\033[0;31m");
		printf("kmlib error: unable to calloc %d size\n", size);
		printf("\033[0m");
		return NULL;
	}
	kml_memset(ptr, 0, n * size);
	return ptr;
}

void* kml_memset(void* ptr, int c, size_t size)
{
	#ifdef KML_MEMSET_AUTO_MALLOC
		if(!ptr)
			ptr = kml_malloc(size);
	#endif

	unsigned char* source = (unsigned char*)ptr;
	while(size--)
	{
		*source++ = (unsigned char)c;
	}
	return ptr;
}

void* kml_memcpy(void* dest, void* src, size_t size)
{	
	#ifdef KML_MEMCPY_AUTO_MALLOC
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

/* ============== Garbage collector ============== */

void kml_end_gc()
{
	if(is_gc_init)
	{
		if(gc_leaks_bytes != 0)
		{
			printf("\033[0;35m");
			#ifndef KML_GC_DONT_FREE_LEAKS
				printf("kmlib GC warning: leak of %lld bytes has been detected ! freeing the memory leak [#define KML_GC_DONT_FREE_LEAKS to avoid that]\n", gc_leaks_bytes);
				block* free = head;
				void* ptr = NULL;
				do
				{
					ptr = (void*)((unsigned long)free + sizeof(block));
					if(!kml_free(ptr))
						printf("\033[0;31mkmlib GC error: unable to free leak\n");
					free = head;
				} while(head != tail);
			#else
				printf("kmlib GC warning: leak of %lld bytes has been detected ! \n", gc_leaks_bytes);
			#endif
		}
		else
			printf("\33[0;32mkmlib GC: no leaks have been detected \n");
		printf("\033[0m");
		is_gc_init = false;
	}
}

void kml_init_gc()
{
	gc_leaks_bytes = 0;
	is_gc_init = true;
	atexit(kml_end_gc);
}

#endif // __KMlib__

