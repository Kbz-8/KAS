#include <kmlib.h>

int main(int argc, char** argv)
{
	//km_assert(0);
	km_abort();

	km_printf("test, %i\n", 2);

	return 0;
}
