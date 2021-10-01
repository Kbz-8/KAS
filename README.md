# kmlib Project
kmlib (kbz_8 memory library) Project is a mini project made for fun. It is a memory lib that contains allocator, garbage collector and memory manager. It is rather light. There are a compiled version (with a .c file) and a header only version (easy to implement in your projects (include "kmlib.h") but it is slower).

This lib works only on Unix systems for now but it may become Windows compatible one day...

## Allocator system

<p align="center">
	<img src="https://github.com/Kbz-8/kmlib/blob/main/schema.png" alt="drawing"/>
</p>

## Garbage Collector

Garbage collector works with kmlib allocators. It can check your memory management on some parts of your code.
It is used like this:

```C
#include "kmlib.h"

int main(int argc, char** argv)
{
	kml_init_gc(); // initialize Garbage collector monitoring

	char* ptr = kml_malloc(256);

	// end Garbage collector monitoring
	kml_end_gc(); // warning leak of 256 bytes has been detected ! Freeing the memory [#define KML_GC_DONT_FREE_LEAKS to avoid that]

	return 0;
}
```
If ```kml_init_gc()``` was called without ending GC it will be called at program exit.

## Macros to set kmlib

This is the list of macros that can be defined to modify the behaviour oh kmlib :
* KML_MEMSET_AUTO_MALLOC : kml_memset allocate the size passed if the pointer passed is NULL
* KML_MEMCPY_AUTO_MALLOC : kml_memcpy allocate the size passed if the destination pointer passed is NULL
* KML_GC_DONT_FREE_LEAKS : kml_end_gc says what leaks you have but don't free the memory leak

### Contact
kbz_8.dev@akel-engine.com

