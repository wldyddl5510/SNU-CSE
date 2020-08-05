#include <stdlib.h>

void fnc2() {
	void *a = malloc(1);
	free(a);
}
void fnc(){
	int *p = calloc(10, 1000);
	fnc2();
	p = realloc(p, 100);
}
int main() {
	void *p = malloc(100);
	fnc();
	fnc2();
	return 0;
}
