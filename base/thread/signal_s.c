/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-05-22 Mon 11:09:52
 * @description: 
 * 
 */

#include <thr/threads.h>

#include "signal_s.h"



typedef struct {
	cnd_t signal;
	mtx_t mutex;
}i_signal_t;


signal_t  signal_create()
{
	i_signal_t* sig = (i_signal_t*)malloc(sizeof(i_signal_t));

	if (sig == NULL) {
		return NULL;
	}

	if (thrd_success != cnd_init(&sig->signal)) {
		free(sig);
		return NULL;
	}

	if (thrd_success != mtx_init(&sig->mutex,mtx_plain)) {
		cnd_destory(&sig->signal);
		free(sig);
		return NULL;
	}

	return (signal_t)sig;
}

void signal_wait(signal_t sig,slot_handler handler, void* parm,void* ret)
{
	assert(sig);
	i_signal_t* i_sig = (i_signal_t*)sig;

	cnd_wait(&i_sig->signal,&i_sig_mutex);
	ret = handler(parm);

	return;
}


void signal_notify(signal_t sig)
{
	cnd_signal(&((i_signal_t*)sig)->signal);
	return;
}


void signal_release(signal_t sig)
{
	if (sig == NULL) {
		return;
	}

	i_signal_t* i_sig = (i_signal_t*)sig;

	cnd_destory(&i_sig->signal);
	mtx_destory(&i_sig->mutex);

	return;
}