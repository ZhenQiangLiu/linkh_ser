/*
 * Ser_H_auth.h
 *
 *  Created on: Mar 6, 2017
 *      Author: w
 */



#ifndef SER_H_AUTH_H_
#define SER_H_AUTH_H_

static char token_buff[1024]={0};
static char token2save_buff[1024]={0};
static int con_a_fd=0;

int get_token();
int find_pkt();
int read_data(int *);

#endif /* SER_H_AUTH_H_ */
