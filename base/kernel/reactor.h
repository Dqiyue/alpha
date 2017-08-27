/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */

#ifndef __REACTOR_H__
#define __REACTOR_H__




typedef unsigned int reactor_t;
typedef int 		 handle;


reactor_t reactor_create();

void reactor_release(reactor_t reactor);

int reactor_register_task(handle fd,void* obj, int (*task_handler)(void* obj,unsigned char* data,size_t size));

void reactor_unregister_task(handle fd);

handle reactor_register_timer(unsigned long long ms,unsigned long long repeat_ms
	void* obj,int (*timer_call)(void* obj));

void reactor_cancel_timer(handle timer);

void reactor_exec_event_loop(struct timeval* tv);


#endif

