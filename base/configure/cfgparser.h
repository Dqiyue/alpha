#ifndef __CFGPARSER_H__
#define __CFGPARSER_H__

typedef unsigned int alpha_cfgparser_t;


alpha_cfgparser_t cfgparser_load_cfg(const char* cfgfile);

const char* cfgparser_parse_str(alpha_cfgparser_t parser, const char* key);
unsigned int cfgparser_parse_uint(alpha_cfgparser_t parser,const char* key);

void cfgparser_release(alpha_cfgparser_t cfgparser);

#endif // !__CFGPARSER_H__