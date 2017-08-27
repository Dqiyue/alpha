/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */

#include <stdio.h>
#include "reactor.h"


typedef struct {

}inter_reactor_t;


reactor_t reactor_create()
{
	inter_reactor_t* reactor = (inter_reactor_t*)malloc(sizeof(inter_reactor_t));

	if (reactor == NULL) {
		return NULL;
	}



	return;
}

void reactor_release(reactor_t reactor)
{
	return;
}

int reactor_register_task(handle fd,void* obj, int (*task_handler)(void* obj,unsigned char* data,size_t size))
{
	return;
}

void reactor_unregister_task(handle fd)
{
	return;
}

handle reactor_register_timer(unsigned long long ms,unsigned long long repeat_ms
	void* obj,int (*timer_call)(void* obj))
{
	return;
}

void reactor_cancel_timer(handle timer)
{
	return;
}


void reactor_exec_event_loop(struct timeval* tv)
{
	return;
}