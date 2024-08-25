#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc,char *argv[]){
    struct stat sb;

    if(argc !=2){
	fprintf(stderr,"Usage:%s <pathname>\n",argv[0]);
	exit(EXIT_FAILURE);
    }

    if(stat(argv[1],&sb)==-1){
	perror("stat");
	exit(EXIT_FAILURE);
    }

    printf("File type:\t\t");
    
    switch(sb.st_mode & S_IFMT){
	case S_IFBLK: printf("block device\n");	    break;
	case S_IFCHR: printf("character device\n"); break;
	case S_IFDIR: printf("directory\n");        break;
	case S_IFIFO: printf("FIFO/pipe\n");        break;
	case S_IFREG: printf("regular file\n");     break;
	case S_IFLNK: printf("symlink\n");          break;
	case S_IFSOCK: printf("socket\n");          break;
	default: printf("unknown?\n");
    }
    printf("I-node number: \t\t %ld\n",(long)sb.st_ino);
    printf("Mode:\t\t %lo(octal)\n",(unsigned long)sb.st_mode);
    printf("File size:\t\t %lld bytes\n",(long long)sb.st_size);

    exit(EXIT_SUCCESS); 
}
    
