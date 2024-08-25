/*
 * byteorder.c
 *
 *  Created on: Jul 17, 2015
 *      Author: yamorn
 */

#include <stdio.h>

int main_t(void) {

	union {
		short s;
		char c[sizeof(short)];
	} un;

	un.s = 0x0102;
	if (sizeof(short) == 2) {
		if (un.c[0] == 1 && un.c[1] == 2)
			printf("big-endian\n");
		else if (un.c[0] == 2 && un.c[1] == 1)
			printf("little-endian\n");
		else
			printf("unkown");

	} else {
		printf("sizeof(short) = %d\n", sizeof(short));
	}

	return (0);

}
