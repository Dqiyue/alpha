/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-09 Sun 10:10:39
 * @description: 
 * 
 */

#include "blk_queue.h"
#include <comm/commfunc.h>


typedef  struct {
	unsigned int 	size;
	unsigned int 	rpos;
	unsigned int 	wpos;
	blk_t* 			blks;
}inter_blk_queue_t;

#define INTER_BLK_QUEUE_ACCESS(blk_queue) ((inter_blk_queue_t*)blk_queue)
#define INTER_BLK_QUEUE_SIZE(blk_queue) (INTER_BLK_QUEUE_ACCESS(blk_queue)->size)
#define INTER_BLK_QUEUE_BLKS(blk_queue) (INTER_BLK_QUEUE_ACCESS(blk_queue)->blks)
#define INTER_BLK_QUEUE_RPOS(blk_queue) (INTER_BLK_QUEUE_ACCESS(blk_queue)->rpos)
#define INTER_BLK_QUEUE_WPOS(blk_queue) (INTER_BLK_QUEUE_ACCESS(blk_queue)->wpos)


blk_queue_t blk_queue_create(size_t size)
{
	if (size == 0) {
		return 0;
	}

	inter_blk_queue_t* blk_queue = (inter_blk_queue_t*)malloc(sizeof(inter_blk_queue_t)); 

	if (NULL == blk_queue){
		return 0;
	}

	blk_queue->size = roundup_pow_of_two(size,sizeof(unsigned int));

	blk_queue->blks = (blk_t*)malloc(sizeof(blk_t)*blk_queue->size);

	if (NULL == blk_queue->blks) {
		free(blk_queue);
		return 0;
	}

	size_t i;
	for(i = 0; i < blk_queue->size; ++i){
		blk_queue->blks[i] = 0;
	}

	blk_queue->rpos = 0;
	blk_queue->wpos = 0;

	return (blk_queue_t)blk_queue;
}

void blk_queue_free(blk_queue_t que)
{
	if (!INTER_BLK_QUEUE_ACCESS(que)) { return; }

	#ifdef STAGE_DEBUG
	assert(INTER_BLK_QUEUE_BLKS(que));
	#endif

	int i;

	for(i = 0; i != INTER_BLK_QUEUE_SIZE(que); ++i) {
		if (INTER_BLK_QUEUE_BLKS(que)[i]) {
			blk_free(INTER_BLK_QUEUE_BLKS(que)[i]);
		}
	}
		
	free(INTER_BLK_QUEUE_BLKS(que));
	INTER_BLK_QUEUE_BLKS(que) = 0;
	free(blk_queue);
	return;
}


int blk_queue_push(blk_queue_t que, blk_t blk,choice_t  ch)
{
	#ifdef STAGE_DEBUG
	assert(que);
	#endif

	if (INTER_BLK_QUEUE_WPOS(que) - INTER_BLK_QUEUE_RPOS(que) >= INTER_BLK_QUEUE_SIZE(que)){
		
		if (ch == NOWAIT) {
			return -1;
		}

		while (INTER_BLK_QUEUE_WPOS(que) - INTER_BLK_QUEUE_RPOS(que) >= INTER_BLK_QUEUE_SIZE(que)) {
			//cond wait
		}
	}

	unsigned int wp = INTER_BLK_QUEUE_WPOS(que) & (INTER_BLK_QUEUE_SIZE(que) - 1);
	INTER_BLK_QUEUE_BLKS(que)[wp] = blk;
	++INTER_BLK_QUEUE_WPOS(que);
	return 0;
}

blk_t blk_queue_pop(blk_queue_t que,choice_t  ch)
{
	#ifdef STAGE_DEBUG
	assert(que);
	#endif

	if (INTER_BLK_QUEUE_WPOS(que) == INTER_BLK_QUEUE_RPOS(que)) {

		if (NOWAIT == ch){
			return 0;
		}

		while (INTER_BLK_QUEUE_WPOS(que) == INTER_BLK_QUEUE_RPOS(que)) {
			//cond wait
		}
	}

	unsigned int rp = INTER_BLK_QUEUE_RPOS(que) & (INTER_BLK_QUEUE_SIZE(que) - 1);
	blk_t blk = INTER_BLK_QUEUE_BLKS(que)[rp];
	++INTER_BLK_QUEUE_RPOS(que);

	return blk;
}

