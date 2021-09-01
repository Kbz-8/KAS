// KAS (Kbz_8 Allocation System) project is a mini project for fun.
// It's my own implementation of functions malloc,
// free, realloc, calloc...
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 01/09/2021

#include <stdio.h>
#define KAS_USE_BLOCK_MANAGEMENT
#include "../header_only/kas.h"

int main()
{
	char* ptr = kas_malloc(13); // 13 bytes allocation
	ptr = "hello world !";
	printf("%s\n", ptr);
	kas_free(ptr);

	return 0;
}

