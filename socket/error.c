#include "netcomplex.h"
#include <stdarg.h>

void err_sys(const char *fmt, ...){
	va_list ap;
	err_print(fmt,ap);
	exit(1);
}

void err_msg(const char *fmt, ...){
	va_list ap;
	err_print(fmt,ap);
	return;
}

static void err_print(const char *fmt,va_list ap){
	va_start(ap);
	vprintf(fm,ap);
	va_end(ap);
}
