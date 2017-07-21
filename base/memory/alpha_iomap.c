#include "alpha_iomap.h"

#if defined(WIN32) || defined(WIN64)
#define WINDOWS_PLATFORM
#include <windows.h>
#endif

#include <assert.h>


//typedef
typedef struct {
    alpha_io_read rd;
    alpha_io_write wr;
}inter_alpha_iomap_io_t;

typedef struct {
    alpha_addr_t addr;
    alpha_data_t data;
    alpha_access_t access;
    inter_alpha_iomap_io_t io;
}alpha_register_t;

typedef struct{
    alpha_addr_t addr;
    alpha_access_t access;
    size_t blk_size;
    uint8_t* blk_mem;
}inter_alpha_iomap_blk_t;


typedef struct {

}inter_alpha_iomap_segment_t;

typedef struct {
    alpha_addr_t segment_mask;
    inter_alpha_iomap_segment_t* segments; 
}inter_alpha_iomap_t;



//functions

//inter functions
#ifdef WINDOWS_PLATFORM
int exception_access_iomap(LPEXCEPTION_POINTERS e)
{
    err_print("exception code %d\n",e->ExceptionRecord->ExceptionCode);
    return 0;
}
#endif
//interface functions
alpha_data_t alpha_iomap_read(alpha_addr_t addr)
{
#ifdef WINDOWS_PLATFORM
    __try{
        ((inter_alpha_iomap_t*)(alpha_iomap_instance()))->
    }__except(exception_access_iomap(GetExceptionInformation())){
        err_print("alpha iomap has not been inited\n")
        return 
    }
    return -1;
#endif
}