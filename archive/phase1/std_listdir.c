#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

void printdir(char *dir,int depth){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp=opendir(dir))==NULL){
	fprintf(stderr,"cann't open directory:%s\n",dir);
	return;
    }

    chdir(dir);
    while((entry=readdir(dp))!=NULL){
	lstat(entry->d_name,&statbuf);
	if(S_ISDIR(statbuf.st_mode)){
	   /* Found  a directory,buf ignore . and .. */
	   if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0){
	      continue;
	   } 
	   printf("%*s%s/\n",depth,"",entry->d_name);
	   /* Recurse at a new indent level */
	   printdir(entry->d_name,depth+4);
	}else{
	    printf("%*s%s\n",depth,"",entry->d_name);
	} 
    }
    chdir("..");
    closedir(dp);
}

int main(int argc,char *argv[]){
    if(argc==1){
	printf("Usage:%s <pathname>\n",argv[0]);
	exit(0);
    }

    printdir(argv[1],0);

    exit(0);
}
