#include <kmlib.h>

#include <stdio.h>

int main(int argc, char** argv)
{
	char* buffer = km_malloc(12);

	km_free(buffer);
	/*
	char buffer[256];
	km_file f = km_fopen("test.txt", KM_F_RW | KM_F_CREATE);
	
	printf("%i\n", f);

	km_fwrite(f, "text appened", 13);
	km_fread(f, &buffer);

	km_fclose(f);

	km_println(&buffer);
*/
	return 0;
}
