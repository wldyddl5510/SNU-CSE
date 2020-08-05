#include <stdlib.h>

int main(void) {
	void *a = malloc(2);
	free(a);
	a = malloc(1);
	return 0;
}
