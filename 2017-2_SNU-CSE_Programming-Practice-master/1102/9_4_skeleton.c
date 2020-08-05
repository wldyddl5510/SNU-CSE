#include <stdio.h>
#include <string.h>

// Implement below functions
int my_union(int setA, int setB){

	return (setA|setB);

}

int my_intersection(int setA, int setB){

	return (setA&setB);

}

int my_add(int setA, int x){

	return (setA|(1<<x));
}
int my_delete(int setA, int x){

	return (setA|(1<<x))^(1<<x);

}
int my_setminus(int setA, int setB){

	return ((setA|setB)^setB);

}
void my_print(int setA){
	
	int i;
	
	for(i=0;i<32;i++){
		if((setA&(1<<i))!=0){
			printf("%d ", i);
		}
	}

	printf("\n");
}

int main(){
	int setA = 0, setB = 0;
	while(1){
		char op[30], opA[10], dummy[10];
		scanf("%s",op);

		if( strcmp(op,"quit") == 0 ) break;
		
		if( strcmp(op,"print") == 0 ){
			scanf("%s",opA);
			if( strcmp(opA,"A") == 0 ) my_print(setA);
			if( strcmp(opA,"B") == 0 ) my_print(setB);
		}
		
		if( strcmp(op,"add") == 0 ){
			int x; scanf("%d",&x);
			scanf("%s%s",dummy,opA);
			if( strcmp(opA,"A") == 0 ) setA = my_add(setA,x);
			if( strcmp(opA,"B") == 0 ) setB = my_add(setB,x);
		}
		
		if( strcmp(op,"delete") == 0 ){
			int x; scanf("%d",&x);
			scanf("%s%s",dummy,opA);
			if( strcmp(opA,"A") == 0 ) setA = my_delete(setA,x);
			if( strcmp(opA,"B") == 0 ) setB = my_delete(setB,x);
		}
		
		if( strcmp(op,"union") == 0 ) setA = my_union(setA,setB);
		
		if( strcmp(op,"intersection") == 0 ) setA = my_intersection(setA,setB);

		if( strcmp(op,"setminus") == 0 ) setA = my_setminus(setA,setB);
		
	}
}
