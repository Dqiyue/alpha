/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-06-13 Tue 21:22:55
 * @description: 
 * 
 */

#ifndef TRANS_TCP_H
#define TRANS_TCP_H

#include <stdbool.h>

typedef unsigned int trans_tcp_t;

trans_tcp_t trans_tcp_create(const char* host,unsigned short port,bool asServer);

void 	trans_tcp_release(trans_tcp_t tcp);

#endif // TRANS_TCP_H
