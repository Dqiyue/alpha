/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-09 Sun 21:12:47
 * @description: 
 * 
 */
#include "blk.h"



typedef struct {
	void* data;
	unsigned int  size;
	alpha_bool_t freeable;
	blk_data_free free_call;
}inter_blk_t;

#define INTER_BLK_ACCESS(blk) ((inter_blk_t*)blk)
#define INTER_BLK_DATA(blk) (INTER_BLK_ACCESS(blk)->data)
#define INTER_BLK_SIZE(blk) (INTER_BLK_ACCESS(blk)->size)
#define INTER_BLK_BFREEABLE(blk) (INTER_BLK_ACCESS(blk)->freeable)
#define INTER_BLK_FREE_CALL (INTER_BLK_ACCESS(blk)->free_call)

blk_t blk_create(void* data,unsigned int size,alpha_bool_t freeable,blk_data_free free_call)
{
	if (size == 0) {
		return NULL;
	}

	inter_blk_t* blk = (inter_blk_t*)malloc(sizeof(inter_blk_t));

	if (blk == NULL){
		return NULL;
	}

	if (data == NULL  && (data = malloc(size)) == NULL) {

		free(blk);
		return NULL;
	}

	blk->data = data;
	blk->size = size;
	blk->freeable = freeable;
	blk->free_call = free_call;

	return (blk_t)blk;
}


void* blk_data(blk_t blk)
{
	return LIKELY(blk) ? INTER_BLK_DATA(blk) : 0;
}

size_t blk_size(blk_t blk)
{
	return LIKELY(blk) ? INTER_BLK_SIZE(blk) : 0;
}



void blk_free(blk_t blk)
{
	if (!blk) { return; }

	if (INTER_BLK_BFREEABLE(blk) && INTER_BLK_DATA(blk)){

		if (INTER_BLK_FREE_CALL(blk)) {
			INTER_BLK_FREE_CALL(blk)(INTER_BLK_DATA(blk));
		}else {
			free(INTER_BLK_DATA(blk));
		}

		
	}

	free(blk);
	return;
}
