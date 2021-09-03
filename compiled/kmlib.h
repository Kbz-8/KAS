// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 03/09/2021

#ifndef __KMlib__
#define __KMlib__

#include <stdio.h>
#include <stdlib.h>
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

void add_block(block* newBlock);
void remove_block(block* delBlock);
void* kml_malloc(size_t size);
int kml_free(void* ptr);
void* kml_realloc(void* ptr, size_t size);
void* kml_calloc(size_t n, size_t size);
void* kml_memset(void* ptr, int c, size_t size);
void* kml_memcpy(void* dest, void* src, size_t size);

void kml_init_gc();
void kml_end_gc();

#endif // __KMlib__

