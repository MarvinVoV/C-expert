#include <stdlib.h>
#include <stdio.h>
typedef int INT;
typedef int *P; //P is a pointer which point to int type
typedef int (*Add)(int,int);
typedef int *(*Mul)(int,int);

int myAdd(int a,int b){
	return a+b;
}
int useAdd(Add add,int a,int b){
	return add(a,b);	
}

int *myMul(int a,int b){
	int *p;
	int r=a*b;
	p=&r;
	return p;
}
void useMul(Mul mul,int a,int b){
	int *p;
	p=mul(a,b);
	printf("mul result=%d\n",*p);
}
int main(void){
	/* scenario one */
	INT i=10;
	printf("i=%d\n",i);

	/* scenario two */
	int a=10;
	P z=&a;
	printf("%d\n",*z);
	
	/* scenario three */
	int r=useAdd(myAdd,10,20);
	printf("r=%d\n",r);

	/* scenario four */
	useMul(myMul,10,2);


	exit(0);
}

