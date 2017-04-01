/*
 * Ser_H_loop.h
 *
 *  Created on: Mar 3, 2017
 *      Author: w
 */



#ifndef SER_H_LOOP_H_
#define SER_H_LOOP_H_

static int auth_count=2;
static int heart_count=3;
static int connfd=0;
static int soc_fd=0;
int Ser_H_loop(int *fd);
void start_heart();
int do_auth();

#endif /* SER_H_LOOP_H_ */
