#ifndef __ALPHA_TYPE_H__
#define __ALPHA_TYPE_H__

#include <stdint.h>

#ifndef ALPHA_CONFIG_H
#include "alpha_config.h"
#endif

//types
typedef unsigned int obj_t;
typedef unsigned int addr_t;
typedef unsigned int data_t;
typedef unsigned int alpha_iterator_t;

typedef enum {
    ERR_SUCCESS = 0,
    ERR_FAILED,
}err_t;

typedef enum {
      ALPHA_FALSE = 0,
      ALPHA_TRUE = 1,
}alpha_bool_t;

#endif // !__ALPHA_TYPE_H__