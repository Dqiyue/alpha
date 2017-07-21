/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-05-22 Mon 11:01:40
 * @description: 
 * 
 */

#ifndef SIGNAL_S_H
#define SIGNAL_S_H

#include <stdio.h>
#include <time.h>

typedef unsigned int signal_t;
typedef void* (*slot_handler)(void*);


signal_t  signal_create();

void signal_wait(signal_t sig,slot_handler handler, void* parm,void* ret);

void signal_notify(signal_t sig);

void signal_release(signal_t sig);

#endif // SIGNAL_S_H





