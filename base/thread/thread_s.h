/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-05-22 Mon 12:27:56
 * @description: 
 * 
 */

#ifndef THREAD_S_H
#define THREAD_S_H

#include <stdio.h>

typedef unsigned int thrd_s_t;
typedef void* (*thrd_handler)(void*);

thrd_s_t thrd_s_create(thrd_handler handler,void* arg);

void thrd_s_enter_critical_section(thrd_s_t thrd);

void thrd_s_leave_critical_section(thrd_s_t thrd);

void thrd_s_exit(thrd_s_t thrd,void* ret);

#endif // THREAD_S_H
