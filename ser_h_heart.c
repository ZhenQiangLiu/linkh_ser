/*
 * Ser_H_heart.c
 *
 *  Created on: Mar 14, 2017
 *      Author: w
 */

#include "server_h.h"

void heart_init()
{
	heart_s_buff[0]=0xAA;
	heart_s_buff[1]=0x55;
	heart_s_buff[2]=0;
	heart_s_buff[3]=0;
	heart_s_buff[4]=0xFF;
	heart_s_buff[5]=0;
	heart_s_buff[6]=0;
	heart_s_buff[7]=0;
	heart_s_buff[8]=0;
	heart_s_buff[9]=0;
	heart_s_buff[10]=0xEE;
}

void send_heart()
{
	int i=0;
	printf("son %d\n",getpid());
	while(1){
		usleep(500000);
		i=send(con_h_fd,heart_s_buff,12,0);
		printf("%d,sockfd=%d,len %d,msg %s\n",i,sockfd,12,heart_s_buff);
	}
}

void find_heart()
{
	char look[2]={0};
	look[0]=0xFF;
	look[1]=0x00;
	char *tmp=NULL;
	tmp=strstr(heart_r_buff+4,look);
	if((tmp-heart_r_buff)==4){
		printf("heart ok! heart_count=3;\n");
		heart_count=3;
	}
	else{
		printf("heart error!\n");
		if(heart_count>1){
			heart_count--;
			read_heart();
		}
		else {
			printf("heart over!\n");
			close_all_sfd();
		}
	}
}

int read_heart()
{
	int ret=0;
	while(1){
		usleep(500000);
		bzero(heart_r_buff,1024);
		ret=recv(con_h_fd,heart_r_buff,1023,MSG_WAITALL);
		if(ret==-1 || ret==0){
			printf("recvtimeout!%d\n",con_h_fd);
			if(heart_count>1){
				heart_count--;
				read_heart(son_pid);
			}
			else {
				printf("close all sfd!\n");
				close_all_sfd();
				int ret=kill(spid,SIGQUIT);
				printf("kill %u ret %d\n",spid,ret);
				if(ret==-1)
					perror( "kill" );
				printf("close \n");
				exit(0);
			}
		}
		else{
			printf("ret=%d\n",ret);
			find_heart();
		}
	}
}

void start_heart(int *fd)
{
	con_h_fd=*fd;
	heart_init();
	spid=fork();
	if(spid<0)
		perror("fork");
	else if(spid==0){
		printf(",,\n");
		send_heart();
	}
	else {
		printf("fork %d\n",spid);
		read_heart();
	}
}

