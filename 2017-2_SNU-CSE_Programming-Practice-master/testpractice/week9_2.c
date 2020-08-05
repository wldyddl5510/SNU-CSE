#include <stdio.h>

typedef void (*calFuncPtr) (int, int, int, int, int*, int*);

void plus(int r1, int i1, int r2, int i2, int *r3, int *i3) {
	*r3 = r1 + r2;
	*i3 = i1 + i2;
}

void minus(int r1, int i1, int r2, int i2, int *r3, int *i3) {
	*r3 = r1 - r2;
	*i3 = i1 - i2;
}

void mult(int r1, int i1, int r2, int i2, int *r3, int *i3) {
	*r3 = r1 * r2 - i1 * i2;
	*i3 = r1 * i2 + r2 * i1;
}

void calc(int r1, int i1, int r2, int i2, int *r3, int *i3, calFuncPtr fun) {
	fun(r1, i1, r2, i2, r3, i3);
}

int main(void) {
	calFuncPtr f = NULL;
	int r1, r2, i1, i2, r3, i3;
	char op;

	scanf("%d %d %c %d %d" , &r1, &i1, &op, &r2, &i2);
	if(op == '+')
		f = plus;
	else if(op == '-')
		f = minus;
	else if(op == '*')
		f = mult;

	calc(r1, i1, r2, i2, &r3, &i3, f);
	printf("%d %d\n", r3, i3);
	return 0;
}
