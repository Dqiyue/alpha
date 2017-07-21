/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-05-22 Mon 12:23:40
 * @description: 
 * 
 */


#include "thread/signal_s.h"
#include "thread/thread_s.h"

signal_t sig;

void hook_func(void* arg)
{
	printf("hello world\n");
}

int thrd_func(void* arg) {
	printf("thread start\n");
	signal_wait(sig,hook_func,NULL,NULL);

	printf("thread end\n");
	return 0;
}


int main()
{
	printf ("test program start\n");
	sig = signal_create();

	if (sig == 0) {
		printf("create signal failed\n");
		return 0;
	}

	thrd_s_t thd = thrd_s_create(thrd_func,NULL);

	if (thd == NULL) {
		printf("create thread failed\n");
		signal_release(sig);
		return 0;
	}

	printf ("notify\n");
	signal_notify(sig);

	thrd_s_exit(thd,NULL);
	signal_release(sig);
	return 0;
}