/*
 * Ser_H_init.c
 *
 *  Created on: Mar 3, 2017
 *      Author: w
 */

#include "server_h.h"


void Ser_sighandler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(connfd);
	close(sockfd);
	kill(0,SIGQUIT);
}

int Ser_H_init(int *fd)
{
	int port;
	signal(SIGINT,(__sighandler_t) Ser_sighandler);
	signal(SIGQUIT,(__sighandler_t) Ser_sighandler);
	signal(SIGCHLD, SIG_IGN);
	//read user input
	printf("please input port\n");
	scanf("%d",&port);
	*fd=socket(AF_INET,SOCK_STREAM,0);
	if(*fd==-1){
		perror("socket");
		return 1;
	}
	struct sockaddr_in serv;
	serv.sin_family=AF_INET;
	serv.sin_port=htons(port);
	serv.sin_addr.s_addr=htonl(INADDR_ANY);
	int ret=bind(*fd,(struct sockaddr *)&serv,sizeof(struct sockaddr_in));
	if(ret==-1){
		perror("bind");
		return 2;
	}
	listen(*fd,5);
	sockfd=*fd;
	printf("listening...\n");
	return 0;
}

