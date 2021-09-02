// KAS (Kbz_8 Allocation System) project is a mini project for fun.
// It's my own implementation of functions malloc,
// free, realloc, calloc...
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 02/09/2021

#include <stdio.h>
#include "../../header_only/kas.h"

int main()
{
	char* ptr = (char*)kas_malloc(13);
	printf("%p\n", ptr);
	kas_free(ptr);

	return 0;
}

