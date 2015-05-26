#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BSZ 4096

unsigned char buf[BSZ];

unsigned char translate(unsigned char c){
	if(isalpha(c)){
		if(c>='n')
			c-=13;
		else if(c>='a')
			c+=13;
		else if(c>='N')
			c-=13;
		else 
			c+=13;
	}

	return(c);
}

int main(int argc,char *argv[]){
	if(argc!=3){
		fprintf(stderr,"usage:a.out filein fileout\n");
		exit(1);
	}

	int ifd,ofd,i,n,nw;
	if((ifd=open(argv[1],O_RDONLY))<0){
		perror("open error");
		exit(1);
	}
	if((ofd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0644))<0){
		perror("open error");
		exit(1);
	}
	while((n=read(ifd,buf,BSZ))>0){
		for(i=0;i<n;i++)
			buf[i]=translate(buf[i]);
		if((nw=write(ofd,buf,n))!=n){
			if(nw<0){
				perror("write error");
				exit(1);
			}else{
				perror("short write");
				exit(1);
			}
		}
	}

	fsync(ofd);
	exit(0);

}
