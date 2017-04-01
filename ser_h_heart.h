/*
 * Ser_H_heart.h
 *
 *  Created on: Mar 14, 2017
 *      Author: w
 */




#ifndef SER_H_HEART_H_
#define SER_H_HEART_H_

static int con_h_fd=0;

static char heart_s_buff[1024]={0};
static char heart_r_buff[1024]={0};
static pid_t spid=0;

void start_heart(int *fd);

#endif /* SER_H_HEART_H_ */
