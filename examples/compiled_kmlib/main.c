// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 02/09/2021
// UPDATED: 22/02/2022

#include "../../compiled/kmlib.h"

int main(int argc, char** argv)
{
	kml_init_gc();

	char* ptr = (char*)kml_malloc(2);
	printf("%p\n", ptr);
	kml_free(ptr);

	float x = 123.23345564;
	kml_printf("new test2 %f \n", x);

	const char c = 'a';
	const char* str2 = "string";
	kml_printf("final test : %d, %x, %f, %c, %s, %% \n", 42, 434542, 12.45, c, str2);

	kml_end_gc();

	return 0;
}

