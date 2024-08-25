#include "ptc.h"

#define	INET_ADDRSTRLEN		16	/* "ddd.ddd.ddd.ddd\0" */
								   
int main(int argc, char **argv){
	char *ptr, **pptr;
	char str[INET_ADDRSTRLEN]; 

	struct hostent *hptr;

	while(--argc > 0){
		ptr = *++argv;
		if((hptr = gethostbyname(ptr)) == NULL){
			fprintf(stderr,"gethostbyname error for host %s\n",ptr);
			continue;
		}
		printf("hostname: %s\n",hptr->h_name);

		for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);
		switch(hptr->h_addrtype){
		case AF_INET:
			pptr = hptr->h_addr_list;
			for( ; *pptr != NULL; pptr++)
				printf("\taddress:%s\n",inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
			break;
		default:
			perror("unkown address type");
			break;
		}
	}
	exit(0);
}
