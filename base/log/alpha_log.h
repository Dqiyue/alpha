/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-21 Fri 10:06:08
 * @description: 
 * 
 */

#ifndef ALPHA_LOG_H
#define ALPHA_LOG_H

#ifdef __cplusplus 
	extern "c" {
#endif

#define MAX_LOG_SIZE 0x04000000 //64MB
#define MAX_BAK_NUM 64 //it's value must be the pow of 2
#define MAX_LOG_RECORD_SIZE 4096

typedef enum {
	lv_non = 0,
	lv_error,
	lv_debug,
	lv_info,
}alpha_log_level_t;


typedef unsigned int  alpha_log_t;


void err_print(char* format,...);

alpha_log_t alpha_log_create(const char* path,alpha_log_level_t lv);

void alpha_log_set_level(alpha_log_t alpha_log,alpha_log_level_t lv);

void alpha_log_write(alpha_log_t log,alpha_log_level_t lv,const char* file,
	unsigned int line,const char* func,const char* format, ...);

void 	alpha_log_release(alpha_log_t log);




static alpha_log_t   alpha_log = 0;

//start log service
int start_alpha_log_service(char* path,alpha_log_level_t lv);

//set log level
void set_alpha_log_level(alpha_log_level_t lv);

#define ALPHA_LOG(lv,format,...) alpha_log_write(alpha_log,(lv),__FILE__,__LINE__, \
			__FUNCTION__,format, __VA_ARGS__)

#define ALPHA_INFO(format,...) alpha_log_write(alpha_log,lv_info,__FILE__,__LINE__, \
			__FUNCTION__,format, __VA_ARGS__)

#define ALPHA_DEBUG(format,...) alpha_log_write(alpha_log,lv_debug,__FILE__,__LINE__, \
			__FUNCTION__,format, __VA_ARGS__)

#define ALPHA_ERR(format,...) alpha_log_write(alpha_log,lv_error,__FILE__,__LINE__, \
			__FUNCTION__,format, __VA_ARGS__)

//end log service
void end_alpha_log_service();



#ifdef __cplusplus 
	}
#endif

#endif // SIMPLE_LOG_H
