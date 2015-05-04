#include "ptc.h"

void sig_chld(int signo);

int main(int argc, char *argv[]){
	int listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in servaddr, cliaddr;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	/* child process terminal signal */
	struct sigaction act;
	act.sa_handler = sig_chld;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	socklen_t clilen = sizeof(cliaddr);
	while(1){
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if(connfd < 0){
			perror("accept error");
			exit(1);
		}
		if((childpid = fork()) == 0){ /* child process */
			close(listenfd); /* close listenning socket */
			/* process the request */
			servprocess(connfd);

			exit(0);
		}
		close(connfd); /* parent closes connected socket */
	}
}

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated \n",pid);
	return;
}
