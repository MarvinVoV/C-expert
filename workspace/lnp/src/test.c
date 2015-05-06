#include "gen.h"
int main(void){
	struct ifconf ifc;
	char buf[2048];
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	printf("ifconf=%ld\n",sizeof(ifc));
	exit(0);
}
