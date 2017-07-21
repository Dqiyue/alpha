/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-06-13 Tue 21:19:00
 * @description: 
 * 
 */
#ifndef TRANS_H
#define TRANS_H

typedef enum {

}trans_type_t;


typedef unsigned int trans_t;

trans_t trans_create();

void trans_release();


#endif // TRANS_H
