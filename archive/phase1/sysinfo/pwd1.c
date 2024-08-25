#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		fprintf(stderr,"usage:a.out <username>\n");
		exit(1);
	}

	struct passwd *info;
	info=getpwnam(argv[1]);
	if(info==NULL){
		perror("getpwdnam error\n");
		exit(1);
	}

	printf("username=%s\n",info->pw_name);
	printf("passwd=%s\n",info->pw_passwd);
	printf("uid=%d\n",info->pw_uid);
	printf("gid=%d\n",info->pw_gid);
	printf("info=%s\n",info->pw_gecos);
	printf("home=%s\n",info->pw_dir);
	printf("shell=%s\n",info->pw_shell);

	exit(0);
}
