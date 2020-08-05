#include <stdio.h>

typedef void (*calcFuncPtr)(int, int, int, int, int*, int*);

// fill below functions
void plus(int r1, int i1, int r2, int i2, int* r3, int* i3)
{
	*r3 = r1+r2;
	*i3 = i1+i2;
	return;
}

void minus(int r1, int i1, int r2, int i2, int* r3, int* i3)
{
    *r3=r1-r2;
	*i3=i1-i2;
	return;
}

void mult(int r1, int i1, int r2, int i2, int* r3, int* i3)
{
    *r3=r1*r2-i1*i2;
	*i3=r1*i2+i1*r2;
	return;
}

void calc(int r1, int i1, int r2, int i2, int* r3, int* i3, calcFuncPtr func)
{
	func(r1,i1,r2,i2,r3,i3);
	return;    
}
/*
int main()
{
    calcFuncPtr f = NULL;
    int r1, r2, r3, i1, i2, i3;
    char op;

    scanf("%d %d %c %d %d", &r1, &i1, &op, &r2, &i2);
    switch(op)
    {
        case '+': f = plus; break;
        case '-': f = minus; break;
        case '*': f = mult; break;
    }

    calc(r1, i1, r2, i2, &r3, &i3, f);
    printf("%d %d\n", r3, i3);
    return 0;
}

*/


