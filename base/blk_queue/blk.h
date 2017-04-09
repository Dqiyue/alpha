/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-09 Sun 21:01:04
 * @description: 
 * 
 */
#include <stdbool.h>

typedef unsigned int blk_t;





blk_t blk_create(void* data,size_t size,bool freeable);


void blk_free(blk_t blk);