#include <stdlib.h>

int f1(){
	void* p = malloc(100);
	int* c = calloc(10, 100);
	free(p);
	p = realloc(p, 10);
	p = realloc(p, 50);
	free(p);
	free(p);

	return 0;
}

int main() {
	int *e;
	f1();
	e = calloc(1, 1);
	free(e);
	return 0;
}
