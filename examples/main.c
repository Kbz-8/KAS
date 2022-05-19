#include <kmlib.h>

int main(int argc, char** argv)
{
	char buffer[256];
	km_file f = km_fopen("/home/bilbo/Documents/Programmation/c/kmlib/examples/test.txt", KM_F_RONLY | KM_F_APPEND);
	
	km_fwrite(f, "text appened", 13);
	km_fread(f, &buffer);

	km_fclose(f);

	km_println(&buffer);

	return 0;
}
