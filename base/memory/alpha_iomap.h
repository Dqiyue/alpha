#ifndef __ALPHA_IOMAP_H__
#define __ALPHA_IOMAP_H__

#include <stdint.h>

typedef unsigned int alpha_addr_t;
typedef unsigned int alpha_data_t;

typedef enum {
    ALPHA_READONLY,
    ALPHA_WRITEONLY,
    ALPHA_READWRITE,
}alpha_access_t;

typedef enum {
    ALPHA_SUCCESS,
}alpha_ret_t;

typedef alpha_data_t (*alpha_io_read)(alpha_addr_t addr);
typedef alpha_ret_t (*alpha_io_write)(alpha_addr_t addr,alpha_data_t val);

typedef unsigned int alpha_iomap_t;

static alpha_iomap_t alpha_iomap_instance_s = 0;

inline alpha_iomap_t alpha_iomap_instance() { return alpha_iomap_instance_s;}

#endif // !__ALPHA_IOMAP_H__