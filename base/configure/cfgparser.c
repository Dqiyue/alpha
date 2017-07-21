#include "cfgparser.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
    
}alpha_cfg_record_t;

typedef struct {

}inter_alpha_cfgparser_t;

alpha_cfgparser_t cfgparser_load_cfg(const char* cfgfile)
{
    inter_alpha_cfgparser_t* 
}

const char* cfgparser_parse_str(alpha_cfgparser_t parser, const char* key)
{

}


unsigned int cfgparser_parse_uint(alpha_cfgparser_t parser,const char* key)
{

}

void cfgparser_release(alpha_cfgparser_t cfgparser)
{

}