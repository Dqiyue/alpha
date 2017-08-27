/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-09 Sun 21:01:04
 * @description: 
 * 
 */
#include <comm/alpha_type.h>

//typedef
typedef unsigned int blk_t;
typedef void (*blk_data_free)(void*);



//function
blk_t blk_create(void* data,size_t size,alpha_bool_t freeable,blk_data_free free_call);

void* blk_data(blk_t blk);

size_t blk_size(blk_t blk);


void blk_free(blk_t blk);