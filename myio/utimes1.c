#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <utime.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
    if(argc==1){
	fprintf(stderr,"usage:a.out <file.. >\n");
	exit(1);
    }
    
    int i;
    struct stat statbuf;
    struct utimbuf utbuf;

    for(i=1;i<argc;i++){
	if(stat(argv[i],&statbuf)<0){
	    fprintf(stderr,"stat file %s error\n",argv[i]);
	    continue;
	}

	utbuf.actime=statbuf.st_atime;
	utbuf.modtime=statbuf.st_mtime;
	if(utime(argv[i],&utbuf)<0){
	    fprintf(stderr,"utime file %s error\n",argv[i]);    
	}	    
    }

    exit(0);
}
