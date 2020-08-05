#include <stdlib.h>

int main(void) {
	void *p = malloc(1);
	void *q = realloc(p, 50000);
	free(p);
	return 0;
}
