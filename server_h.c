/*
 * Server_H.c
 *
 *  Created on: Mar 3, 2017
 *      Author: w
 */

#include "server_h.h"

int main()
{
	Ser_H_init(&sockfd);
	Ser_H_loop(&sockfd);
	return 0;
}


