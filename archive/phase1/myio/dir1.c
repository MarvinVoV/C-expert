#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		fprintf(stderr,"Usage:<path>\n");
		exit(EXIT_FAILURE);
	}

	DIR *dp;
	struct dirent *dirp;
	
	if((dp=opendir(argv[1]))==NULL){
		perror("open dir failed.");
		exit(1);
	}

	while((dirp=readdir(dp))!=NULL){
		printf("filename:%s\n",dirp->d_name);
	}

	closedir(dp);
	exit(0);
}
