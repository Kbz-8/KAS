// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 02/09/2021
// UPDATED: 04/09/2021

#include <stdio.h>
#include "../../compiled/kmlib.h"

int main(int argc, char** argv)
{
	kml_init_gc();

	char* ptr = (char*)kml_malloc(2);
	printf("%p\n", ptr);
	kml_free(ptr);

	int x = 1;
	kml_print("new test\n");
	kml_printf("new test2\n", x);

	kml_end_gc();


	return 0;
}

