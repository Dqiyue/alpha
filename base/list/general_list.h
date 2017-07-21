/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-27 Thu 17:56:23
 * @description: 
 * 
 */



typedef unsigned int vector;

typedef struct list_node {
	struct list_node* prev;
	struct list_node* next;
}list_node_t;


typedef struct general_list_node {
	list_node_t   pn;
	void* 	        data;
}general_list_node_t;


#define LIST_DATA_ENTRY(list,type) (MEMBER_ENTRY(list,))