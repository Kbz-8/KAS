// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 02/09/2021
// UPDATED: 21/02/2022

#include <stdio.h>
#include "../../compiled/kmlib.h"

int main(int argc, char** argv)
{
	kml_init_gc();

	char* ptr = (char*)kml_malloc(2);
	printf("%p\n", ptr);
	kml_free(ptr);

	char str[16] = "this is a string";
	kml_strrev(str, 0, 16);
	kml_println(str);

	kml_println("new test");
	int x = 1;
	kml_printf("new test2 %d\n", x);

	kml_end_gc();

	return 0;
}

