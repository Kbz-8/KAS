// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 16/05/2022

#ifndef __KMlib__
#define __KMlib__

#include <stdio.h>
#include <stdlib.h>

#define malloc(x) kml_malloc(x) // replacing all malloc by kml_malloc due to conflict between malloc and sbrk
#define realloc(x) kml_realloc(x)
#define calloc(x, y) kml_calloc(x, y)
#define free(x) kml_free(x)

#define kml_abort() (kml_println("abortion") && *((char*)0))
#define sexit(status) kml_exit(status)
#define atexit(func) kml_atexit(func)

typedef enum { false = 0, true = 1 } bool;

typedef char* kml_va_list;
#define kml_va_start(ap, parmn) (void)((ap) = (char*)(&(parmn) + 1))
#define kml_va_arg(ap, type) (((type*)((ap) = ((ap) + sizeof(type))))[-1]) // wtf
#define kml_va_end(ap) (void)((ap) = 0)

#ifndef CHAR_BIT
#	define CHAR_BIT 8
#endif

void* kml_malloc(size_t size);
void* kml_malloc_shared(size_t size);
int kml_free(void* ptr);
void* kml_realloc(void* ptr, size_t size);
void* kml_calloc(size_t n, size_t size);
void* kml_memset(void* ptr, int c, size_t size);
void* kml_memcpy(void* dest, void* src, size_t size);

void kml_exit(int status);
int kml_atexit(void (*func)(void));

void kml_assert(int cond);

void kml_init_gc(void);
void kml_end_gc(void);

void kml_print(const char* out);
void kml_println(const char* out);
void kml_printf(const char* out, ...);

size_t kml_strlen(const char* str);
void kml_strcpy(char* dest, const char* src);
void kml_stradd(char* dest, const char* src);
void kml_strrev(char* arr, int start, int end);

char* kml_vsprintf(const char* src, kml_va_list args);

char* kml_nitoa(int num, char* dest, int pos, int base);
char* kml_itoa(int num, char* dest, int base);
char* kml_nlltoa(long long num, char* dest, int pos, int base);
char* kml_lltoa(long long num, char* dest, int base);
#define MAX_PRECISION 10
char* kml_nftoa(double num, char* dest, int pos, int precision);
char* kml_ftoa(double num, char* dest, int precision);

#endif // __KMlib__

