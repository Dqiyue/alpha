/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-21 Fri 10:06:31
 * @description: 
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "alpha_log.h"
#include <comm/commfunc.h>

typedef enum {
	ALPHA_LOG_STATE_FINE,
	ALPHA_LOG_STATE_ERR,
	ALPHA_LOG_STATE_EXCHANGE,
}alpha_log_state;

typedef struct {
	FILE* fp;
	char* filename;
	unsigned int wpos;
	unsigned int bak;
	alpha_log_level_t lv;
	alpha_log_state state;
	unsigned char buff[MAX_LOG_RECORD_SIZE];
 }i_alpha_log_t;

int alpha_log_recover(i_alpha_log_t* alog)
{
	CLOSE_FP(alog->fp);
	alog->fp = fopen(alog->filename,"w+b");

	if (alog->fp == NULL) {
		alog->state = ALPHA_LOG_STATE_ERR;
		err_print("can not open file %s\n",alog->filename);
		return -1;
	}

	 
	alog->wpos = 0;
	alog->state = ALPHA_LOG_STATE_FINE;

	return 0;
}


int alpha_log_exchange(i_alpha_log_t* alog)
{
	alog->state = ALPHA_LOG_STATE_EXCHANGE;
	CLOSE_FP(alog->fp);

	int ns = snprintf(alog->buff,MAX_LOG_RECORD_SIZE,"%s.%u",alog->filename,alog->bak);

	if (ns <= 0 || ns == MAX_LOG_RECORD_SIZE) {	
		err_print("alpha log exchange failed\n");
		return -1;
	}

	alog->buff[ns] = 0;
	
	if (0 > rename(alog->filename,alog->buff)){
		err_print("rename %s to %s failed\n",alog->filename,alog->buff);
		return -1;
	}

	++alog->bak;
	alog->bak &= (MAX_BAK_NUM - 1);

	return alpha_log_recover(alog);
}

int alpha_log_check_state(i_alpha_log_t* alog) 
{
	if (alog->state == ALPHA_LOG_STATE_FINE) {
		return 0;
	}

	if (alog->state == ALPHA_LOG_STATE_EXCHANGE) {
		return alpha_log_exchange(alog);
	}

	return alpha_log_recover(alog);
}

/******************FUNCTION**********************/






void err_print(char* format,...)
{
	printf("err:\n");
	return;
}


alpha_log_t alpha_log_create(const char* path)
{
	i_alpha_log_t* alog = (i_alpha_log_t*)malloc(sizeof(i_alpha_log_t));

	if (alog == NULL) {
		err_print("malloc space for alpha_log failed\n");
		goto err_return;
	}

	alog->fp = fopen(path,"w+b");

	if (alog->fp == NULL) {
		err_print("can not open file %s\n",path);
		goto err_return;
	}

	size_t len = strlen(path)
	alog->filename = (char*)malloc( len + 1);

	if (alog->filename == NULL) {
		err_print("malloc space for alpha_log failed\n");
		goto err_return;
	}

	memcpy(alog->filename,path,len);
	alog->filename[len] = 0;

	alog->wpos = 0;
	alog->bak = 0;
	alog->state = ALPHA_LOG_STATE_FINE;
	alog->lv = lv;

	return (alpha_log_t)alog;

err_return:
	alpha_log_release(alog);
	return NULL;
}

void alpha_log_set_level(alpha_log_t alpha_log,alpha_log_level_t lv)
{
	i_alpha_log_t* alog = (i_alpha_log_t* )log;
	assert(alog);

	alog->lv = lv;
	return;
}

void alpha_log_write(alpha_log_t log,const char* file,unsigned int line,
	alpha_log_level_t lv,const char* func,const char* format, ...)
{
	i_alpha_log_t* alog = (i_alpha_log_t* )log;
	assert(alog);

	if (alpha_log_check_state(alog) != 0) {
		return;
	}

	if (lv > alog->lv) {
		return;
	}


	int s = snprintf(alog->buff,MAX_LOG_RECORD_SIZE,"%s : %u %s ",file,line,func);

	if (s <= 0 || s == MAX_LOG_RECORD_SIZE) {
		err_print("!!!!!!!!write log error!!!!!!\n");
		return;
	}

	size_t nw = s;
	size_t nleft = MAX_LOG_RECORD_SIZE - nw;

	va_list arg = (va_list)((char*)(&format) + 4); 
　　	s = vsnprintf(alog->buff,nleft, format, arg);

	if (s <= 0 || s == nleft) {
		err_print("!!!!!!!!write log error!!!!!!\n");
		return;
	}

	nw += s;

	if (fwrite(alog->buff,nw,1,alog->fp) != 1) {
		err_print("!!!!!!!!write log error!!!!!!\n");
		return;
	}

	alog->wpos += nw;

	if (alog->wpos >= MAX_LOG_SIZE)
	{
		(void)alpha_log_exchange(alog);
	}

	return;
}



void 	alpha_log_release(alpha_log_t log)
{
	if (!log) {return;}

	i_alpha_log_t* alog = (i_alpha_log_t* )log;

	CLOSE_FP(alog->fp);
	FREE(alog->filename);
	FREE(alog);
	return;
}



//start log service
int start_alpha_log_service(char* path,alpha_log_level_t lv)
{
	alpha_log = alpha_log_create(path,lv);

	if (!alpha_log) {
		err_print("start alpha log service failed\n");
		return -1;
	}

	err_print("alpha log service start\n");

	return 0;
}

//set log level
void set_alpha_log_level(alpha_log_level_t lv)
{
	((i_alpha_log_t*)alpha_log)->lv = lv;
	return;
}

//end log service
void end_alpha_log_service()
{
	alpha_log_release(alpha_log);
	err_print("alpha log service end\n");
	return;
}