/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-07-24 Mon 18:29:09
 * @description: 
 * 
 */
#ifndef ALPHA_CONFIG_H
#define ALPHA_CONFIG_H

#ifndef STAGE_DEBUG
#define STAGE_DEBUG
#endif

//test_builtin_expect.c 


#ifndef  LIKELY
	#ifdef __GCC__
		#define LIKELY(x) __builtin_expect(!!(x), 1)
	#else
		#define LIKELY(x) (x)
	#endif
#endif

#ifndef UNLIKELY
	#ifdef __GCC__
		#define UNLIKELY(x) __builtin_expect(!!(x), 0)
	#else
		#define UNLIKELY(x) (x)
	#endif
#endif

#endif