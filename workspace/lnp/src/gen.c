/*
 * gen.c
 *
 *  Created on: May 4, 2015
 *      Author: yamorn
 */
#include "gen.h"

ssize_t readline(int fd, void *buf, size_t maxlen) {
	ssize_t n, rc;
	char c, *ptr;

	ptr = buf;
	for (n = 1; n < maxlen; n++) {
		again: if ((rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break; /* newline is stored, like fgets() */
		} else if (rc == 0) {
			*ptr = 0; /* line terminal char '\0' */
			return (n - 1);
		} else {
			if (errno == EINTR)
				goto again;
			return (-1); /* error, errno set by read() */
		}
	}
	*ptr = 0; /* null terminate like fgets(); */
	return (n);
}

ssize_t writen(int fd, const void *buf, size_t nbytes) {
	size_t nleft;
	ssize_t nw;
	const char *ptr;

	ptr = buf;
	nleft = nbytes;
	while (nleft > 0) {
		if ((nw = write(fd, ptr, nleft)) <= 0) {
			if (nw < 0 && errno == EINTR)
				nw = 0; /* and call write() again */
			else
				return (-1); /* error */
		}
		nleft -= nw;
		ptr += nw;
	}
	return (nbytes - nleft);
}

int daemonize(const char *pname, int facility) {
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	umask(0); /* clear file creation mask */

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0) { /* get maximum number of fd */
		perror("getrlimit error");
		return (-1);
	}

	if ((pid = fork()) < 0) {
		perror("fork error");
		return (-1);
	} else if (pid) { /* terminal parent */
		exit(0);
	}

	if (setsid() < 0) /* become session leader */
		return (-1);

	/* ensure future opens won't allocate controlling TTYs. */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0) {
		perror("sigaction error");
		return (-1);
	}

	if ((pid = fork()) < 0) {
		perror("fork error");
		return (-1);
	} else if (pid) {
		exit(0);
	}

	chdir("/");

	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/* attach fd 0,1,2 to /dev/null. */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(pname, LOG_PID, facility);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected fd %d %d %d", fd0, fd1, fd2);
		return (-1);
	}
	return (0);
}

