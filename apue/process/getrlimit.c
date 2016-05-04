#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void){
	struct rlimit rl;
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0){
		perror("getrlimit error");
		exit(-1);
	}
	printf("cur %ld, max %ld\n", rl.rlim_cur, rl.rlim_max);
	exit(0);
}
