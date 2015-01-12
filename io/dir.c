#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc,char *argv[]){
	DIR *dp;
	struct dirent *dirp;
	if(argc!=2){
		perror("usage: dir directory name\n");
		exit(EXIT_FAILURE);
	}

	dp=opendir(argv[1]);
	if(dp==NULL){
		fprintf(stderr,"can't open %s\n",argv[1]);
		exit(EXIT_FAILURE);
	}

	while((dirp=readdir(dp))!=NULL){
		printf("%s\n",dirp->d_name);
	}

	closedir(dp);
	exit(0);
}
