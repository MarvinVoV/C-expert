#include<stdio.h>
main(){
	double nc;
	for(nc=0;getchar()!=EOF;++nc)
		;
	printf("%.0f\n",nc);//Suppress the printing of the decimal point and the fraction part,which is zero;
}
