#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *fp = fopen("/home/yamorn/temp/test", "w+");
	fprintf(fp, "Hello world\n");
	fputs("This is testing for fputs...\n", fp);
	fclose(fp);
	
	return 0;
}
