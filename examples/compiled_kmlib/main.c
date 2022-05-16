// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 02/09/2021
// UPDATED: 16/05/2022

#include "../../compiled/kmlib.h"

int main(int argc, char** argv)
{
	//kml_init_gc();

	//int i = 12;
	//kml_printf("new test2 %p \n", &i);

	//const char c = 'a';
	//const char* str2 = "string";
	//kml_printf("final test : %d, %x, %f, %s, %% \n", 42, 434542, 12.45, str2);

	char* test = kml_malloc(4);
	test[0] = '0';
	test[1] = '1';
	test[2] = '2';
	test[3] = '3';
	kml_print(test);
	kml_free(test);

	//kml_end_gc();

	return 0;
}
