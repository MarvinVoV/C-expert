#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
    if(argc==1){
	fprintf(stderr,"usage:a.out <file1 file2 .. >\n");
	exit(1);
    }
    
    int i;
    struct stat buf;
    char *ptr;

    for(i=1;i<argc;i++){
	printf("%s: ",argv[i]);
	if(lstat(argv[i],&buf)<0){
	    perror("lstat failed\n");
	    exit(1);
	}

	if(S_ISREG(buf.st_mode))
	    ptr="regular";
	else if(S_ISDIR(buf.st_mode))
	    ptr="directory";
	else if(S_ISCHR(buf.st_mode))
	    ptr="character special";
	else if(S_ISFIFO(buf.st_mode))
	    ptr="fifo";
	else if(S_ISLNK(buf.st_mode))
	    ptr="symbolic link";
	else if(S_ISSOCK(buf.st_mode))
	    ptr="socket";
	else if(S_ISBLK(buf.st_mode))
	    ptr="block special";
	else
	    ptr="** unkown mode **";
	printf("%s \n",ptr);
	printf("length=%ld,inode=%ld\n",buf.st_size,buf.st_ino);
    }

    exit(0);
}
