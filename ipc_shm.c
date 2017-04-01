/*
 * Ipc_shm.c
 *
 *  Created on: Mar 23, 2017
 *      Author: w
 */


#include "server_h.h"


int shm_init(int *shmbuf)
{
	key_t key;
	key=ftok(".",55);
	if(key==-1){
		perror("ftok");
		return 1;
	}
	int shmid=shmget(key,8,IPC_CREAT|0664);
	if(shmid==-1){
		printf("shmget error ...\n");
		return 2;
	}
	if((shmbuf = shmat(shmid, NULL, 0)) < 0) {
	    perror("shmat");
		return 3;
	}
	printf("shminit\n");
	return 0;
}

int shm_read(int *shmbuf)
{
	printf("pid is %d\n",*shmbuf);
	return *shmbuf;
}

void shm_write(int *shmbuf)
{
	int num=0;
	num=getpid();
	strcpy((char*)shmbuf,(char *)&num);
	//*shmbuf=getpid();
	//printf("son_pid is %d\n",*((int*)&num));
	printf("son_pid is %d\n",*shmbuf);
}

void shm_free(int *shmbuf)
{
	shmdt(shmbuf);
}



