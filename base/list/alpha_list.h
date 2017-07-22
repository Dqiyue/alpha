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
typedef enum {
	EN_ALPHA_SINGLE_LIST,
	EN_ALPHA_DOUBLE_LIST,
}alpha_list_type_t;

typedef unsigned int alpha_list_t; 
//typedef unsigned int alpha_iterator_t;
typedef void (*alpha_list_free_call_t)(data_t);

//function declare
alpha_list_t alpha_list_create(alpha_list_type_t type,alpha_bool_t bround);

void alpha_list_release(alpha_list_t list);

err_t alpha_list_insert(alpha_list_t list, data_t data,alpha_bool_t bfree,alpha_list_free_call_t free_call);
err_t alpha_list_erase(alpha_list_t list ,alpha_iterator_t iter); 

alpha_iterator_t alpha_list_begin(alpha_list_t list);
alpha_iterator_t alpha_list_end(alpha_list_t list);


#endif // !__ALPHA_LIST__