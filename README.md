# kmlib Project
kmlib (kbz_8 main library) is a mini project made for fun. It is a little lib that contains allocators, garbage collector, memory manager, io functions, strings functions... It is rather light.

This lib works only on Unix systems for now but it may become Windows compatible one day...

## Allocator system

<p align="center">
	<img src="https://github.com/Kbz-8/kmlib/blob/main/schema.png" alt="drawing"/>
</p>

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

