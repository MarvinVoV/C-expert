#include "ptc.h"

int main(void){
	struct servent *sptr;
	char **ptr;
	sptr = getservbyname("domain", "udp"); /* DNS using UDP */
	sptr = getservbyname("ftp", "tcp"); /* FTP using TCP */
	//sptr = getservbyname("ftp", NULL); /* FTP using TCP */
	printf("serv name is %s,port is %d,proto is %s\n",sptr->s_name,sptr->s_port,sptr->s_proto);
	
	ptr = sptr->s_aliases;
	for(;*ptr != NULL; ptr++){
		printf("alias is %s\n",*ptr);
	}
	exit(0);
}
