#include <stdio.h>

typedef struct{
	unsigned int low_pass:vcf:1; // this means the field will only use 1 bit of storage
	unsigned int reverb:1;

}synth;

int main(void){
	int x = 0x54; // 0101 0100
	printf("x = %d\n", x);
	return 0;
}
