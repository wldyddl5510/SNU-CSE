#include <stdlib.h>

int main(void) {
	void *a = malloc(2);
	void *b = malloc(3);
	free(b);
	a = realloc(a, 1);
	return 0;
}
