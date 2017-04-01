/*
 * Ipc_shm.h
 *
 *  Created on: Mar 23, 2017
 *      Author: w
 */

#ifndef IPC_SHM_H_
#define IPC_SHM_H_

int shm_init(int *shmbuf);
int shm_read(int *shmbuf);
void shm_write(int *shmbuf);
void shm_free(int *shmbuf);

#endif /* IPC_SHM_H_ */
