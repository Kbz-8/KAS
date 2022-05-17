// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 02/09/2021
// UPDATED: 16/05/2022

#include "../../compiled/kmlib.h"

int main(int argc, char** argv)
{
	kml_init_gc();

	int i = 12;
	kml_printf("new test2 %p \n", &i);

	kml_printf("final test : %d, %d\n", 42, 434542);

	kml_end_gc();

	return 0;
}
