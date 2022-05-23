/**
 * This file is a part of the kmlib (kbz_8 main library)
 *
 * Copyright (C) 2022 @kbz_8
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kmlib.h>

void* __km_asm_internal_mmap(void*, size_t, int, int);
int __km_asm_internal_munmap(void*, size_t);

typedef struct block
{
	size_t size;
	struct block* next;
	struct block* prev;
} block;

static block* head = NULL;
static block* tail = NULL;
static long long gc_leaks_bytes = 0;
static bool is_gc_init = false;
static bool is_cleanup_activated = false;

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

void* km_malloc(size_t size)
{
	void* ptr = NULL;
	block* block_ptr = head;

	block_ptr = __km_asm_internal_mmap(0, size + sizeof(block), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE);

	if(block_ptr == MAP_FAILED)
	{
		km_printf("\033[0;31mkmib error: unable to alloc %d bytes\033[0m\n", size);
		return NULL;
	}

	block_ptr->size = size;
	add_block(block_ptr);
	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;

	return ptr;
}

void* km_malloc_shared(size_t size)
{
	void* ptr = NULL;
	block* block_ptr = head;

	block_ptr = __km_asm_internal_mmap(0, size + sizeof(block), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_SHARED);

	if(block_ptr == MAP_FAILED)
	{
		km_printf("\033[0;31mkmib error: unable to alloc map of size : %d\033[0m\n", size);
		return NULL;
	}

	block_ptr->size = size;
	add_block(block_ptr);

	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;

	return ptr;
}

int km_free(void* ptr)
{
	block* finder = head;
	size_t block_size = sizeof(block); // avoiding redoing sizeof(block) operation at each turn of the loop
	size_t alloc_size = 0;
	do
	{
		if(ptr == (void*)((unsigned long)finder + block_size)) // searching for pointer in blocks chain
		{
			block_size += finder->size;
			alloc_size = finder->size;

			remove_block(finder);
			if(__km_asm_internal_munmap(finder, alloc_size) != 0) // free
			{
				km_print("\033[0;31mkmib error: unable to unmap pointer\033[0m\n");
				ptr = NULL;
				return 0;
			}
			if(is_gc_init)
				gc_leaks_bytes -= alloc_size;
			ptr = NULL;
			return 1; // if pointer was correctly freed
		}

		finder = finder->next;
	} while(finder != tail);
	return 0; // if pointer was not correctly freed
}

void* km_realloc(void* ptr, size_t size)
{
	if(!ptr)
		return km_malloc(size);
	block* finder = head;
	void* newPtr = NULL;
	size_t block_size = sizeof(block);
	do
	{
		if(ptr == (void*)((unsigned long)finder + block_size))
		{
			if(size == finder->size)
				return ptr;

			newPtr = km_malloc(size);

			if(size > finder->size)
				km_memcpy(newPtr, ptr, finder->size);
			else if(size < finder->size)
				km_memcpy(newPtr, ptr, size);

			if(!newPtr)
			{
				km_printf("\033[0;31mkmib error: unable to realloc %d bytes\033[0m\n", size);
				return NULL;
			}
			return newPtr;
		}
	} while(finder != tail);
	return NULL;
}

void* km_calloc(size_t n, size_t size)
{
	void* ptr = km_malloc(n * size);
	if(!ptr)
	{
		km_printf("\033[0;31mkmib error: unable to calloc %d bytes\033[0m\n", size);
		return NULL;
	}
	km_memset(ptr, 0, n * size);
	return ptr;
}

void* km_memset(void* ptr, int c, size_t size)
{
	#ifdef km_MEMSET_AUTO_MALLOC
		if(!ptr)
			ptr = km_malloc(size);
	#endif

	unsigned char* source = (unsigned char*)ptr;
	while(size--)
	{
		*source++ = (unsigned char)c;
	}
	return ptr;
}

void* km_memcpy(void* dest, void* src, size_t size)
{	
	#ifdef km_MEMCPY_AUTO_MALLOC
		if(dest == NULL)
			dest = km_malloc(size);
	#endif

	unsigned char* p_dest = (unsigned char*)dest;
	const unsigned char* p_src = (unsigned char*)src;

	if(dest != NULL && src != NULL)
	{
		while(size--)
			*p_dest++ = *p_src++;
	}
	return dest;
}

void km_end_gc()
{
	if(is_gc_init)
	{
		if(gc_leaks_bytes != 0)
		{
			printf("\033[0;35m");
			#ifndef km_GC_DONT_FREE_LEAKS
				km_printf("kmib GC warning: leak of %lld bytes has been detected ! freeing the memory leak... [#define km_GC_DONT_FREE_LEAKS to avoid that]\n", gc_leaks_bytes);
				block* free = head;
				void* ptr = NULL;
				do
				{
					ptr = (void*)((unsigned long)free + sizeof(block));
					if(!km_free(ptr))
						km_print("\033[0;31mkmib GC error: unable to free leak\n");
					free = head;
				} while(head != tail);
			#else
				km_printf("kmib GC warning: leak of %lld bytes has been detected ! \n", gc_leaks_bytes);
			#endif
		}
		else
			km_print("\33[0;32mkmib GC: no leaks have been detected \n");
		km_print("\033[0m");
		is_gc_init = false;
	}
}

void km_init_gc()
{
	gc_leaks_bytes = 0;
	is_gc_init = true;
}
