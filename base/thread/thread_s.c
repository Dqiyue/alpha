/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-05-22 Mon 12:28:21
 * @description: 
 * 
 */

#include <thr/threads.h>
#include <assert.h>

#include "thread_s.h"


typedef struct {
	thrd_t thr;
	mtx_t mutex;
} i_thrd_s_t;

thrd_s_t thrd_s_create(thrd_handler handler,void* arg)
{
	i_thrd_s_t* thd = (i_thrd_s_t*)malloc(sizeof(i_thrd_s_t));

	if (thd == NULL) {
		return NULL;
	}

	if (mtx_init(&thd->mutex,mtx_plain) != thrd_success)
	{
		free(thd);
		return NULL;
	}

	if (thrd_create(&thd->thr,handler,arg) != thrd_success) {
		mtx_destory(&thd->mutex);
		free(thd);
		return NULL;
	}

	return (thrd_s_t)thd;
}



void thrd_s_enter_critical_section(thrd_s_t thrd)
{
	mtx_lock(&((i_thrd_s_t*)thrd)->mutex);
}

void thrd_s_leave_critical_section(thrd_s_t thrd)
{
	mtx_unlock(&((i_thrd_s_t*)thrd)->mutex);
}





void thrd_s_exit(thrd_s_t thrd,void* ret)
{
	assert(thrd);

	i_thrd_s_t* thd = (i_thrd_s_t*)thrd;

	if (thrd_join(thd->thrd,ret) != thrd_success) {
		assert(0);
	}

	mtx_destory(&thd->mutex);
	free(thd);
	return;
}