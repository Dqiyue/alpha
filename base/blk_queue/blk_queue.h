/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-09 Sun 09:36:18
 * @description: 
 * 
 */
#include <stdint.h>
#include "blk.h"

//define
typedef enum {WAIT,NOWAIT} choice_t;
typedef  unsigned int   blk_queue_t;



//function
blk_queue_t blk_queue_create(size_t size);

void blk_queue_free(blk_queue_t que);


int blk_queue_push(blk_queue_t que, blk_t blk,choice_t  ch); 

blk_t blk_queue_pop(blk_queue_t que,choice_t  ch); 






