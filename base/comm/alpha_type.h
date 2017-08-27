/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */



#ifndef __ALPHA_TYPE_H__
#define __ALPHA_TYPE_H__

#include <stdint.h>
#ifndef ALPHA_CONFIG_H
#include "alpha_config.h"
#endif
#ifdef STAGE_DEBUG
#include <assert.h>
#endif


//types
typedef unsigned int obj_t;
typedef unsigned int addr_t;
typedef unsigned int data_t;
typedef unsigned int alpha_iterator_t;
typedef unsigned int handle_t;
typedef unsigned int ptr_t;
typedef unsigned int alpha_uint;
typedef unsigned int iterator_t;
typedef unsigned int hash_key_t;

typedef enum {
    ERR_SUCCESS = 0,
    ERR_FAILED,
}err_t;

typedef enum {
      ALPHA_FALSE = 0,
      ALPHA_TRUE = 1,
}alpha_bool_t;

#ifndef nullptr
#define nullptr ((void*)0);
#endif

#define TYPE_ACCESS(obj,type) (((type)*)(obj))


typedef void (*free_callback)(obj_t obj);

void default_free_call(obj_t obj) {
	#ifdef STAGE_DEBUG
	assert(obj);
	#endif
	free(obj);
}

#endif // !__ALPHA_TYPE_H__