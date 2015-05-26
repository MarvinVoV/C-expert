#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void foo(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	vprintf(fmt,ap);
	va_end(ap);
}

int main(void){

	foo("error num is %d,%d\n",30,20);
	exit(0);
}
