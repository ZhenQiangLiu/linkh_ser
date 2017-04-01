/*
 * Ser_H_loop.c
 *
 *  Created on: Mar 3, 2017
 *      Author: w
 */
#include "server_h.h"

int do_auth()
{
	if(read_data(&connfd)>0){
		if(find_pkt()==0){
			return get_token();
		}
		else
			usleep(500000);
			return 1;
	}
	else
		usleep(500000);
		return 1;
}

int Ser_H_loop(int *fd)
{
	soc_fd=*fd;
	while(1){//等待客户端发来的请求
		char str[1024]={0};
		struct sockaddr_in cli;
		int len=sizeof(cli);
		connfd=accept(soc_fd,(struct sockaddr *)&cli,&len);
		printf("ip %s,connfd is %d\n",inet_ntop(AF_INET,&cli.sin_addr,str,1024),connfd);
		pid_t pid;
		pid=fork();
		if(pid<0){
			perror("fork");
			return 3;
		}
		else if(pid>0){
			close(connfd);
		}
		else{
			int flags=0,ret=0;
			flags = fcntl(connfd, F_GETFL, 0);
			fcntl(connfd, F_SETFL, flags | O_NONBLOCK);
			do{
				ret=do_auth();
				if(!ret)
					start_heart(&connfd);
			}while(auth_count-->0);
			close_all_sfd();
			return -1;
		}
	}
	return 0;
}
