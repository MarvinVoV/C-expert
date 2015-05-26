#include "netcomplex.h"
#include <stdarg.h>

void err_sys(const char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	exit(1);
}

void err_msg(const char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	return;
}

