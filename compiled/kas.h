// KAS (Kbz_8 Allocation System) project is a mini project for fun.
// It's my own implementation of functions malloc,
// free, realloc, calloc...
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 01/09/2021

#ifndef __KAS__
#define __KAS__

#include <stdio.h>
#include <unistd.h>

typedef struct block block;

struct block
{
	size_t size;
	block* next;
	block* prev;
};

static block* head = NULL;
static block* tail = NULL;

void add_block(block* newBlock);
void remove_block(block* delBlock);
void* kas_malloc(size_t size);
int kas_free(void* ptr);

#endif // __KAS__

