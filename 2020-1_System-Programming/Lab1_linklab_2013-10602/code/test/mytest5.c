#include <stdlib.h>

int main(void) {
	void *a;
	a = realloc((void*)0x10101010, 1024);
	return 0;
}
