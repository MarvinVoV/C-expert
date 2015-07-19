/*
 * inet_convert.c
 *
 *  Created on: Jul 18, 2015
 *      Author: yamorn
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main_t2(int argc, char *argv[]) {
	unsigned char buf[sizeof(struct in6_addr)]; // unsigned char equals uint8_t, 0~255
	int domain, s;
	char str[INET6_ADDRSTRLEN];

	if (argc != 3) {
		fprintf(stderr, "Usage: %s {i4|i6|<num>} string\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	domain = (
			strcmp(argv[1], "i4") == 0 ?
					AF_INET :
					(strcmp(argv[1], "i6") == 0 ? AF_INET6 : atoi(argv[1])));

	s = inet_pton(domain, argv[2], buf);
	if (s <= 0) {
		if (s == 0) {
			fprintf(stderr, "Not in presentation format.");
		} else {
			perror("inet_pton");
		}
		exit(EXIT_FAILURE);
	}

	if (inet_ntop(domain, buf, str, INET6_ADDRSTRLEN) == NULL) {
		perror("inet_ntop");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", str);

	exit(0);

}
