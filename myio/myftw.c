#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3  /* directory that can't be read */
#define FTW_NS 4  /* file that can't stat */

/* function type that is called for each filename */
typedef int Myfunc(const char *,const struct stat *,int);

static Myfunc myfunc;

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;

int main(int argc,char *argv[]){

}




static int myfunc(const char *pathname,const struct stat *statptr,int type){
    switch(type){
	case FTW_F:
	    switch(statptr->st_mode & S_IFMT){
		case S_IFREG:	nreg++;	    break;
		case S_IFBLK:	nblk++;	    break;
		case S_IFCHR:	nchr++;	    break;
		case S_IFIFO:	nfifo++;    break;
		case S_IFLNK:	nslink++;   break;
		case S_IFSOCK:	nsock++;    break;
		case S_IFDIR: 
		    fprintf(stderr,"for S_IFDIR for %s",pathname);
	    }		
	    break;
	case FTW_D:
	    ndir++;
	    break;
	case FTW_DNR:
	    fprintf(stderr,"can't read directory %s",pathname);
	    break;
	case FTW_NS:
	    fprintf(stderr,"stat error for %s",pathname);
	    break;
	default:
	    fprintf(stderr,"unkown type %d for pathname %s",type,pathname);
    }
    return(0);
}


