/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */

##ifndef LIST_H
#define LIST_H

#include<comm/alpha_type.h>

typedef ptr_t list_t;

list_t list_create();

alpha_uint list_size(list_t list);

void list_release(list_t list);

err_t list_push(list_t list,obj_t obj,alpha_bool_t bfree,free_callback free_call);

obj_t list_pop(list_t list);

iterator_t list_begin(list_t list);

iterator_t list_end(list_t list);

void next(iterator_t* iter);

err_t list_erase(list_t list,iterator_t iter);

obj_t list_iterator_data(iterator_t iter);

obj_t list_iterator_pop_data(list_t list,iterator_t iter);

#endif // LIST_H
