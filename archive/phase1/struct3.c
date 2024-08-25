#include <stdio.h>
#include <stdlib.h>

static struct user_st{
	int age;
	char *str;
};

void show(struct user_st *u){
	printf("age=%d str=%s\n",u->age,u->str);
}
int main(){
	struct user_st u,*upt;
	upt=&u;
	upt->age=10;
	upt->str="hello world";
	show(upt);

	++upt->age; // equals to ++(upt->age)
	show(upt);
	show(upt);
}
