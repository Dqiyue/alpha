/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-09 Sun 10:10:39
 * @description: 
 * 
 */

#include "blk_queue.h"
#include "../commfunc.h"


typedef  struct {
	unsigned int 	que_size;
	unsigned int 	rpos;
	unsigned int 	wpos;
	blk_t* 		blk_arry;
}inter_blk_queue_t;




blk_queue_t blk_queue_create(size_t size)
{
	if (size == 0) {
		return 0;
	}

	inter_blk_queue_t* blk_queue = (inter_blk_queue_t*)malloc(sizeof(inter_blk_queue_t)); 

	if (NULL == blk_queue){
		return 0;
	}

	blk_queue->que_size = roundup_pow_of_two(size,sizeof(unsigned int));

	blk_queue->blk_arry = (blk_t*)malloc(sizeof(blk_t)*blk_queue->que_size);

	if (NULL == blk_queue->blk_arry) {
		free(blk_queue);
		return 0;
	}

	size_t i;
	for(i = 0; i < blk_queue->que_size; ++i){
		blk_queue->blk_arry[i] = 0;
	}

	blk_queue->rpos = 0;
	blk_queue->wpos = 0;

	return (blk_queue_t)blk_queue;
}

void blk_queue_free(blk_queue_t que)
{
	inter_blk_queue_t* blk_queue = (inter_blk_queue_t*)que;

	if (blk_queue) {
		if (blk_queue->blk_arry){
			free(blk_queue->blk_arry);
			blk_queue->blk_arry = NULL;
		}

		free(blk_queue);
	}

	return;
}


int blk_queue_push(blk_queue_t que, blk_t blk,choice_t  ch)
{
	inter_blk_queue_t* blk_queue = (inter_blk_queue_t*)que;

	assert(blk_queue);

	if (blk_queue->wpos - blk_queue->rpos >= blk_queue->que_size){
		
		if (ch == NOWAIT) {
			return -1;
		}

		while (blk_queue->wpos - blk_queue->rpos >= blk_queue->que_size) {
			//cond wait
		}
	}

	unsigned int wp = blk_queue->wpos & (blk_queue->que_size - 1);
	blk_queue->blk_arry[wp] = blk;
	++blk_queue->wpos;
	return 0;
}

blk_t blk_queue_pop(blk_queue_t que,choice_t  ch)
{
	inter_blk_queue_t* blk_queue = (inter_blk_queue_t*)que;
	assert(blk_queue);

	if (blk_queue->wpos == blk_queue->rpos) {

		if (NOWAIT == ch){
			return 0;
		}

		while (blk_queue->wpos == blk_queue->rpos) {
			//cond wait
		}
	}

	unsigned int rp = blk_queue->rpos & (blk_queue->que_size - 1);
	blk_t blk = blk_queue->blk_arry[rp];
	++blk_queue->rpos;

	return blk;
}

