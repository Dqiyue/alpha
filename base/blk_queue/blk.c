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
	bool freeable;
}inter_blk_t;

blk_t blk_create(void* data,unsigned int size,bool freeable)
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

	return (blk_t)blk;
}



void blk_free(blk_t blk)
{
	inter_blk_t* inter_blk = (inter_blk_t*)blk;
	
	if (inter_blk == NULL) {
		return; 
	}

	if (inter_blk->data && inter_blk->freeable){
		free(inter_blk->data);
		inter_blk->data == NULL;
	}

	free(inter_blk);
	return;
}
