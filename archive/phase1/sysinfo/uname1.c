#include <unistd.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	struct utsname unamebuf;

	if(uname(&unamebuf)<0){
		perror("uname error\n");
		exit(1);
	}
	printf("osname=%s\n",unamebuf.sysname);
	printf("nodename=%s\n",unamebuf.nodename);
	printf("release=%s\n",unamebuf.release);
	printf("machine=%s\n",unamebuf.machine);
	printf("version=%s\n",unamebuf.version);


	char buf[500];
	if(gethostname(buf,500)<0){
		perror("gethostname error\n");
		exit(1);
	}
	printf("hostname=%s\n",buf);
	exit(0);
}
