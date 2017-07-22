/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-27 Thu 17:56:48
 * @description: 
 * 
 */

#include "alpha_list.h"

#ifdef STAGE_DEBUG
#include <assert.h>
#endif

//typedef

typedef struct {
	inter_alpha_singlelist_node_t* next;
	data_t data;
	alpha_bool_t bfree;
	alpha_list_free_call_t free_call; 
}inter_alpha_singlelist_node_t;

typedef inter_alpha_singlelist_node_t* inter_alpha_singlelist_t;

typedef struct {
	inter_alpha_doublelist_node_t* prev;
	inter_alpha_doublelist_node_t* next;
	data_t data;
	alpha_bool_t bfree;
	alpha_list_free_call_t free_call; 
}inter_alpha_doublelist_node_t;

typedef inter_alpha_doublelist_node_t* inter_alpha_doublelist_t;

typedef struct {
	void* plist_h;
	void* plist_t;
	void* pfreelist;
	err_t (*inter_alpha_list_insert_call)(void*,data_t,alpha_bool_t,alpha_list_free_call_t);
	err_t (*inter_alpha_list_erase_call)(void*,data_t);
	void (*inter_alpha_list_release_call)(void*);
	alpha_bool_t bround;
}inter_alpha_list_t;


//inter function

//single list
inline void inter_alpha_singlelist_call_free(inter_alpha_singlelist_node_t* pnode)
{
	if (pnode->bfree && pnode->data) {
		if (pnode->free_call) {
			(pnode->free_call)(pnode->data);
			pnode->data = 0;
			pnode->free_call = 0;
		}else {
			free(pnode->data);
			pnode->data = 0;
		}
	}
}

inline void inter_alpha_list_move_to_singlefreelist(inter_alpha_singlelist_t* freelist, inter_alpha_singlelist_node_t* pnode)
{
	pnode->next = *freelist;
	*freelist = pnode;
}


//double list
inline void inter_alpha_doublelist_call_free(inter_alpha_doublelist_node_t* pnode)
{
	if (pnode->bfree && pnode->data) {
		if (pnode->free_call) {
			(pnode->free_call)(pnode->data);
			pnode->data = 0;
			pnode->free_call = 0;
		}else {
			free(pnode->data);
			pnode->data = 0;
		}
	}
}

inline void inter_alpha_list_move_to_doublefreelist((inter_alpha_doublelist_t* freelist, inter_alpha_doublelist_node_t* pnode)
{
	pnode->next = *freelist;
	*freelist = pnode;
}



//single list
inter_alpha_singlelist_node_t* inter_alpha_get_free_singlelist_node(inter_alpha_singlelist_t* freelist)
{
	if (*freelist) {
		inter_alpha_singlelist_node_t* pnode = *freelist;
		*freelist = (*freelist)->next;
		return pnode
	}

	return (inter_alpha_singlelist_node_t*)malloc(sizeof(inter_alpha_singlelist_node_t));
}


err_t inter_alpha_singlelist_insert(void* list,data_t data,alpha_bool_t bfree,alpha_list_free_call_t free_call)
{
	#ifdef STAGE_DEBUG
	assert(list != 0);
	#endif

	inter_alpha_list_t* i_list = (inter_alpha_list_t*)list;

	inter_alpha_singlelist_node_t* pnode = inter_alpha_get_free_singlelist_node((inter_alpha_singlelist_t*)&(i_list->pfreelist));

	if (UNLIKELY(pnode == 0)) {
		return ERR_FAILED;
	}

	pnode->data = data;
	pnode->bfree = bfree;
	pnode->free_call = free_call;
	pnode->next = 0;

	if (LIKELY(i_list->plist_t)) {
		((inter_alpha_singlelist_node_t*)(i_list->plist_t))->next  = pnode;
		i_list->plist_t = (void*)pnode;
	}else {
		i_list->plist_t = (void*)pnode;
		i_list->plist_h = (void*)pnode;
	}

	i_list->plist = (void*)pnode;

	if (i_list->bround) {
		((inter_alpha_singlelist_node_t*)(i_list->plist_t))->next = (inter_alpha_singlelist_node_t*)(i_list->plist_h);
	}

	return ERR_SUCCESS;
}


err_t inter_alpha_singlelist_erase(void* list,alpha_iterator_t iter)
{
	#ifdef STAGE_DEBUG
	assert(list != 0);
	#endif

	inter_alpha_list_t* i_list = (inter_alpha_list_t*)list;

	inter_alpha_singlelist_node_t* pnode = (inter_alpha_singlelist_node_t*)(i_list->plist_h) ;
	

	if (UNLIKELY(pnode == 0 || iter == 0) ) {
		return ERR_FAILED;
	}


	if (i_list->plist_h == (void*)iter) {
		i_list->plist_h = (i_list->plist_h == i_list->plist_t) ? (i_list->plist_t = 0) : (void*)(((inter_alpha_singlelist_node_t*)(i_list->plist_h))->next);
		
		if (i_list->bround && i_list->plist_t != 0) {
			((inter_alpha_singlelist_node_t*)(i_list->plist_t))->next = (inter_alpha_singlelist_node_t*)(i_list->plist_h);
		}
		
		inter_alpha_singlelist_call_free((inter_alpha_singlelist_node_t*)iter);
		inter_alpha_list_move_to_singlefreelist((inter_alpha_singlelist_t*)&(i_list->pfreelist),(inter_alpha_singlelist_node_t*)iter);
		return ERR_SUCCESS;
	}

	inter_alpha_singlelist_node_t* ptemp = pnode;
	pnode = pnode->next;
	alpha_bool_t bfound = ALPHA_FALSE;
	
	while (pnode != (inter_alpha_singlelist_node_t*)(i_list->plist_t)) {
		if (pnode  == (inter_alpha_singlelist_node_t*)iter){
			bfound = ALPHA_TRUE;
			break;
		}
		ptemp = pnode;
		pnode = pnode->next;
	}

	if (bfound == ALPHA_TRUE) {
		ptemp->next = pnode->next;
		inter_alpha_singlelist_call_free((inter_alpha_singlelist_node_t*)iter);
		inter_alpha_list_move_to_singlefreelist((inter_alpha_singlelist_t*)&(i_list->pfreelist),(inter_alpha_singlelist_node_t*)iter);
		return ERR_SUCCESS;
	}

	if (pnode ==  (inter_alpha_singlelist_node_t*)iter){
		i_list->plist_t = ptemp;
		
		if (i_list->bround) {
			ptemp->next = (inter_alpha_singlelist_node_t*)(i_list->plist_h);
		}
		
		inter_alpha_singlelist_call_free((inter_alpha_singlelist_node_t*)iter);
		inter_alpha_list_move_to_singlefreelist((inter_alpha_singlelist_t*)&(i_list->pfreelist),(inter_alpha_singlelist_node_t*)iter);
		return ERR_SUCCESS;
	}

	return ERR_FAILED;
}


void inter_alpha_singlelist_release(void* list)
{
	return;
}


//double list
err_t inter_alpha_doublelist_insert(void* list,data_t data,alpha_bool_t bfree,alpha_list_free_call_t free_call)
{
	return ERR_SUCCESS;
}



err_t inter_alpha_doublelist_erase(void* list,data_t data)
{
	return ERR_SUCCESS;
}


void inter_alpha_doublelist_release(void* list)
{
	return;
}


//interface
alpha_list_t alpha_list_create(alpha_list_type_t type,alpha_bool_t bround)
{
	inter_alpha_list_t* list = (inter_alpha_list_t*)malloc(sizeof(inter_alpha_list_t));

	if (list == 0) {
		return 0;
	}

	switch(type) {
		case EN_ALPHA_SINGLE_LIST:{
			list->plist_h = 0;
			list->plist_t = 0;
			list->pfreelist = 0;
			list->inter_alpha_list_insert_call = inter_alpha_singlelist_insert;
			list->inter_alpha_list_erase_call = inter_alpha_singlelist_erase;
			list->inter_alpha_list_release_call = inter_alpha_singlelist_release;
			break;
		}
		case EN_ALPHA_DOUBLE_LIST: {
			list->plist_h = 0;
			list->plist_t = 0;
			list->pfreelist = 0;
			list->inter_alpha_list_insert_call = inter_alpha_doublelist_insert;
			list->inter_alpha_list_erase_call = inter_alpha_doublelist_erase;
			list->inter_alpha_list_release_call = 
			break;
		}
		default:{
			free(list);
			return 0;
		}
	}

	return (alpha_list_t)list;
}


void alpha_list_release(alpha_list_t list)
{
	#ifdef STAGE_DEBUG
	assert(list != 0);
	#endif
	((inter_alpha_list_t*)list)->inter_alpha_list_release_call((void*)list);
	free(list);
	return;
}


err_t alpha_list_insert(alpha_list_t list, data_t data,alpha_bool_t bfree,alpha_list_free_call_t free_call)
{	
	#ifdef STAGE_DEBUG
	assert(list != 0);
	#endif
	return ((inter_alpha_list_t*)list)->inter_alpha_list_insert_call((void*)list,data,bfree,free_call);
}

err_t alpha_list_erase(alpha_list_t list ,data_t data)
{
	#ifdef STAGE_DEBUG
	assert(list != 0);
	#endif
	return ((inter_alpha_list_t*)list)->inter_alpha_list_erase_call((void*)list,data);
} 
