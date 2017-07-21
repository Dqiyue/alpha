/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-27 Thu 17:56:23
 * @description: 
 * 
 */

#ifndef __ALPHA_LIST__
#define __ALPHA_LIST__



#include "comm/alpha_type.h"

//typedef
typedef unsigned int alpha_list_t; 

typedef enum {
	SINGLE_LIST,
	DOUBLE_LIST,
	ROUND_LIST,
}alpha_list_type_t;

//function declare
alpha_list_t alpha_list_create(alpha_list_type_t type);

void alpha_list_release(alpha_list_t list);

err_t alpha_list_insert(data_t data);
err_t alpha_list_erase(data_t data); 

#endif // !__ALPHA_LIST__