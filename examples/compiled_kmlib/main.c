// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 02/09/2021
// UPDATED: 03/09/2021

#include <stdio.h>
#include "../../compiled/kmlib.h"

int main()
{
	kml_init_gc();

	char* ptr = (char*)kml_malloc(2);
	printf("%p\n", ptr);

	kml_end_gc();

//	kml_free(ptr);

	return 0;
}

