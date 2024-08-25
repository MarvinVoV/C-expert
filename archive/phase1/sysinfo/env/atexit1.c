#include <stdio.h>
#include <stdlib.h>

void bye(){
	printf("bye...\n");
}
int main(void){
	printf("hello\n");
	int i;
	i=atexit(bye);
	if(i!=0){
		fprintf(stderr,"atexit can't regist function\n");
		exit(EXIT_FAILURE);
	}
//	printf("sleep 5 secends...\n");
//	sleep(5);

//	exit(EXIT_SUCCESS);
	return(0);// alse call exit handler
}
