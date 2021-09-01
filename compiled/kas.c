// KAS (Kbz_8 Allocation System) project is a mini project for fun.
// It's my own implementation of functions malloc,
// free, realloc, calloc...
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 01/09/2021

#include "kas.h"

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

	#ifdef KAS_USE_BLOCKS_MANAGER
		block* block_ptr = head;

		while(block_ptr != NULL)
		{
			if(block_ptr->size >= size)
			{
				if(block_ptr->size == size)
					return ptr = (void*)((unsigned long)block_ptr + sizeof(block));
			}
			block_ptr = block_ptr->next;
		}

		block_ptr = sbrk(_size);
		add_block(block_ptr);
		if(!block_ptr)
		{
			printf("\033]1;31m KAS error: unable to alloc %ld size \033]1;39m \n", size);
			return NULL;
		}
		ptr = (void*)((unsigned long)block_ptr + sizeof(block));
		return ptr;
	#else
		ptr = sbrk(size);
		if(!ptr)
		{
			printf("\033]1;31m KAS error: unable to alloc %ld size \033]1;39m \n", size);
			return NULL;
		}
		return ptr;
	#endif // KAS_USE_BLOCKS_MANAGEMENT
}

int kas_free(void* ptr)
{
	block* finder = head;
	size_t block_size = sizeof(block);
	while(finder != tail)
	{
		if(ptr == (void*)((unsigned long)finder + block_size))
		{
		#ifdef KAS_USE_BLOCK_MANAGEMENT
			remove_block(finder);
		#endif
			ptr = NULL;
			return 1;
		}

		finder = finder->next;
	}
	return 0;
}

