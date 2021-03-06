/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-11 Tue 17:30:51
 * @description: 
 * 
 */
#ifndef COMMFUNC_H
#define COMMFUNC_H



#include <stdio.h>


/**
change size to a number which meets 2^x
ex: 7 -> 8 , 8 -> 8 ,11 -> 16 
**/
size_t roundup_pow_of_two(size_t size,unsigned int width); 

#define MEMBER_ENTRY(ptr,type,member,mtype)  ((mtype*)((unsigned char*)(ptr) + (size_t)(&( ((type*)0)->member))))

#define SWAP(a,b) { \
 	a ^= b;		\
	b ^= a;		\
	a ^= b;		\
}


#define SAFE_FREE(ptr) { 		\
	if (ptr) { 		\
		free(ptr);  	\
		ptr = NULL; 	\
	}			\
}


#define SAFE_CLOSE_FP(fp) {   	\
	if (fp) { 		\
		fclose(fp);  	\
		fp = NULL; 	\
	}			\
}


#define COMM_MALLOC_TYPE(type) ((type*)malloc(sizeof(type)))
#define COMM_MALLOC_SIZE(type,size) ((type*)malloc(size))
#define COMM_MALLOC_ARRY(type,num) ((type*)malloc(sizeof(type) * (num))


#endif // COMMFUNC_H
