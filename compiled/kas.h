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
#define realloc(x) kas_realloc(x)
#define calloc(x, y) kas_calloc(x, y)
#define free(x) kas_free(x)

typedef struct block block;

struct block
{
	size_t size;
	block* next;
	block* prev;
};

void add_block(block* newBlock);
void remove_block(block* delBlock);
void* kas_malloc(size_t size);
int kas_free(void* ptr);
void* kas_realloc(void* ptr, size_t size);
void* kas_calloc(size_t n, size_t size);

#endif // __KAS__

