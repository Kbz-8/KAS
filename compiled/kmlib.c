// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 17/02/2022

#include "kmlib.h"

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
static size_t __page_size = 0;

void cleanupBlocks()
{
	if(head != NULL || tail != NULL)
	{
		block* ptr = head;
		do
		{
			remove_block(ptr);
			ptr = head;
		} while(tail != NULL || head != NULL);
	}
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

	block_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);

	if(block_ptr == MAP_FAILED)
	{
		kml_print("\033[0;31m");
		printf("kmlib error: unable to alloc map of size : %d\n", size);
		kml_print("\033[0m");
		return NULL;
	}

	block_ptr->size = size;
	add_block(block_ptr);
	if(!block_ptr)
	{
		kml_print("\033[0;31m");
		printf("kmlib error: unable to alloc %d size\n", size);
		kml_print("\033[0m");
		return NULL;
	}
	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;
	
	if(!is_cleanup_activated)
	{
		atexit(cleanupBlocks);
		is_cleanup_activated = true;
	}

	return ptr;
}

void* kml_malloc_shared(size_t size)
{
	void* ptr = NULL;
	block* block_ptr = head;

	block_ptr = mmap(NULL, size + sizeof(block), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_SHARED, 0, 0);

	if(block_ptr == MAP_FAILED)
	{
		kml_print("\033[0;31m");
		printf("kmlib error: unable to alloc map of size : %d\n", size);
		kml_print("\033[0m");
		return NULL;
	}

	block_ptr->size = size;
	add_block(block_ptr);

	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;
	
	if(!is_cleanup_activated)
	{
		atexit(cleanupBlocks);
		is_cleanup_activated = true;
	}

	return ptr;
}

int kml_free(void* ptr)
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
			if(munmap(finder, alloc_size) != 0)
			{
				kml_print("\033[0;31m");
				kml_print("kmlib error: unable to unmap pointer\n");
				kml_print("\033[0m");
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
				kml_print("\033[0;31m");
				printf("kmlib error: unable to realloc %d size\n", size);
				kml_print("\033[0m");
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
		kml_print("\033[0;31m");
		printf("kmlib error: unable to calloc %d size\n", size);
		kml_print("\033[0m");
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
						kml_print("\033[0;31mkmlib GC error: unable to free leak\n");
					free = head;
				} while(head != tail);
			#else
				printf("kmlib GC warning: leak of %lld bytes has been detected ! \n", gc_leaks_bytes);
			#endif
		}
		else
			kml_print("\33[0;32mkmlib GC: no leaks have been detected \n");
		kml_print("\033[0m");
		is_gc_init = false;
	}
}

void kml_init_gc()
{
	gc_leaks_bytes = 0;
	is_gc_init = true;
	atexit(kml_end_gc);
}

size_t kml_strlen(const char* str)
{
	char c = *str;
	size_t size = 0;
	while(c != '\0')
	{
		c = *str++;
		size++;
	}
	return size;
}

void kml_print(const char* out)
{
	int fd = open("/home/bilbo/Documents/Programmation/c/kmlib/out/out", O_APPEND); // TODO : relative path
	size_t map_size = kml_strlen(out);

	char* out_buffer = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);

	if(out_buffer == MAP_FAILED)
		return;

	kml_memcpy((void*)out_buffer, (void*)out, map_size);
	fwrite(out_buffer, 1, map_size, stdout);

	close(fd);
}

void kml_printf(const char* out, ...)
{
	kml_va_list args;
	kml_va_start(args, out);

	kml_va_end(args);

	int fd = open("/home/bilbo/Documents/Programmation/c/kmlib/out/out", O_APPEND); // TODO : relative path
	size_t map_size = kml_strlen(out);

	char* out_buffer = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);

	if(out_buffer == MAP_FAILED)
		return;

	kml_memcpy((void*)out_buffer, (void*)out, map_size);
	fwrite(out_buffer, 1, map_size, stdout);

	close(fd);
}

