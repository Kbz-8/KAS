// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 03/09/2021

#include <stdio.h>
#include "../../header_only/kmlib.h"

int main()
{
	char* ptr = (char*)kml_malloc(13);
	printf("%p\n", ptr);
	kml_free(ptr);

	return 0;
}

