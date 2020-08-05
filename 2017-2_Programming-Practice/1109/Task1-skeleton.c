#include <stdio.h>
struct complexNum {
	int real;
	int img;
}; 
typedef void (*calcFuncPtr)(struct complexNum, struct complexNum, int*, int*);

struct complexNum createComplexNum(int real, int img)
{
	struct complexNum tmp;
	tmp.real=real;
	tmp.img=img;
	return tmp;
}

void plus (struct complexNum input1, struct complexNum input2, int* output_real, int* output_img){
    *output_real=input1.real+input2.real;
	*output_img=input1.img+input2.img;
	return;
}

void minus (struct complexNum input1, struct complexNum input2, int* output_real, int* output_img){
    *output_real=input1.real - input2.real;
	*output_img=input1.img - input2.img;
	return;
}

void mult (struct complexNum input1, struct complexNum input2, int* output_real, int* output_img){
    *output_real=(input1.real) * (input2.real) - (input1.img)*(input2.img);
	*output_img=(input1.real)*(input2.img) + (input1.img)*(input2.real);
}

void calc (struct complexNum input1, struct complexNum input2, int* r3, int* i3, calcFuncPtr func){
	func(input1,input2,r3,i3);
}
/*
int main(){
    calcFuncPtr f = NULL;
    int r1, r2, r3, i1, i2, i3;
    struct complexNum newCom1, newCom2;
    char op;

    scanf("%d %d %c %d %d", &r1, &i1, &op, &r2, &i2);
    switch(op){
    case '+': f = plus; break;
    case '-': f = minus; break;
    case '*': f = mult; break;
    }

    newCom1 = createComplexNum(r1, i1);
    newCom2 = createComplexNum(r2, i2); 
    calc(newCom1, newCom2, &r3, &i3, f);
    printf("%d %d\n", r3, i3);
    return 0;
}
*/

