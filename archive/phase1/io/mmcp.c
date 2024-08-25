#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#define COPYINCR (1024*1024*1024) /* 1GB */

int main(int argc,char *argv[]){
	int fdin,fdout;
	void *src,*dst;
	size_t copysz;
	struct stat sbuf;
	off_t fsz=0;

	if(argc!=3){
		fprintf(stderr,"usage:%s <fromfile> <tofile>",argv[0]);
		exit(1);
	}
	if((fdin=open(argv[1],O_RDONLY))<0){
		fprintf(stderr,"open error");
		exit(1);
	}
	if((fdout=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0644))<0){
		perror("open error");
		exit(1);
	}

	if(fstat(fdin,&sbuf)<0){  /* need size of input file */
		perror("fstat error");
		exit(1);
	}

	if(ftruncate(fdout,sbuf.st_size)<0){ /* set output file size */
		perror("ftruncate error");
		exit(1);
	}

	while(fsz<sbuf.st_size){
		if((sbuf.st_size-fsz)>COPYINCR)
			copysz=COPYINCR;
		else
			copysz=sbuf.st_size-fsz;
		if((src=mmap(0,copysz,PROT_READ,MAP_SHARED,fdin,fsz))==MAP_FAILED){
			perror("mmap error");
			exit(1);
		}
		if((dst==mmap(0,copysz,PROT_READ|PROT_WRITE,MAP_SHARED,fdout,fsz))==MAP_FAILED){
			perror("mmap error");
			exit(1);
		}
		memcpy(dst,src,copysz); /* does file copy */
		munmap(src,copysz);
		munmap(dst,copysz);
		fsz+=copysz;
	}
	exit(0);
}
