#include <stdlib.h>

int main(void) {
	void *a;
	a = malloc(1024);
	free(a);
	free(a+1);
	return 0;
}
