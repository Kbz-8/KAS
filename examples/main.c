#include <kmlib.h>

int main(int argc, char** argv)
{
	char* buffer = (char*)km_malloc(12);
    
    km_println(km_strerror(km_errno));

	km_free(buffer);

	return 0;
}
