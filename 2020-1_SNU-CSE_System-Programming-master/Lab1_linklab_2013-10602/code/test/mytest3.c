#include <stdlib.h>

int main(void) {
	void *a = malloc(3);
	a = realloc(a, 1);

	return 0;
}
