/*
 * Server_H.h
 *
 *  Created on: Mar 6, 2017
 *      Author: w
 */

#ifndef SERVER_H_H_
#define SERVER_H_H_


#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include "ser_h_init.h"
#include "ser_h_loop.h"
#include "ser_h_auth.h"
#include "ser_h_heart.h"
#include "ipc_shm.h"

static int sockfd=0;
static int son_pid=0;

#endif /* SERVER_H_H_ */
