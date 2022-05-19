# kmlib Project
kmlib (kbz_8 main library) is a mini project made for fun. It is a little lib that contains allocators, garbage collector, memory manager, io functions, strings functions... It is rather light.

This lib works only on Unix systems for now but it may become Windows compatible one day...

## List of kmlib's functions
In `km_memory.h`:
* `void* km_malloc(size_t size);`
* `void* km_malloc_shared(size_t size);`
* `int km_free(void* ptr);`
* `void* km_realloc(void* ptr, size_t size);`
* `void* km_calloc(size_t n, size_t size);`
* `void* km_memmove(void* destination, const void* source, size_t num);`
* `void* km_memset(void* ptr, int c, size_t size);`
* `void* km_memcpy(void* dest, void* src, size_t size);`
* `void km_init_gc(void);`
* `void km_end_gc(void);`

In `km_strings.h`:
* `size_t km_strlen(const char* str);`
* `void km_strcpy(char* dest, const char* src);`
* `void km_stradd(char* dest, const char* src);`
* `void km_strrev(char* arr, int start, int end);`
* `char* km_vsprintf(const char* src, km_va_list args);`
* `char* km_nitoa(int num, char* dest, int pos, int base);`
* `char* km_itoa(int num, char* dest, int base);`
* `char* km_nlltoa(long long num, char* dest, int pos, int base);`
* `char* km_lltoa(long long num, char* dest, int base);`
* `char* km_nftoa(double num, char* dest, int pos, int precision);`
* `char* km_ftoa(double num, char* dest, int precision);`

In `km_io.h`:
* `void km_print(const char* out);`
* `void km_println(const char* out);`
* `void km_printf(const char* out, ...);`

In `kmlib.h`:
* `void km_exit(int status);`
* `int km_atexit(void (*func)(void));`
* `void km_assert(int cond);`
* `void km_abort()`

## Garbage Collector

Garbage collector works with kmlib allocators. It can check your memory management on some parts of your code.
It is used like this:

```C
#include <kmlib.h>

int main(int argc, char** argv)
{
	km_init_gc(); // initialize Garbage collector monitoring

	char* ptr = km_malloc(256);

	// end Garbage collector monitoring
	km_end_gc(); // warning leak of 256 bytes has been detected ! Freeing the memory... [#define KM_GC_DONT_FREE_LEAKS to avoid that]

	return 0;
}
```

## Macros to set kmlib

This is the list of macros that can be defined to modify the behaviour oh kmlib :
* KM_MEMSET_AUTO_MALLOC : km_memset allocate the size passed if the pointer passed is NULL
* KM_MEMCPY_AUTO_MALLOC : km_memcpy allocate the size passed if the destination pointer passed is NULL
* KM_GC_DONT_FREE_LEAKS : km_end_gc says what leaks you have but don't free the memory leak

### Contact
kbz_8.dev@akel-engine.com

