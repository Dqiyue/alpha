/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */
#include <comm/commfunc.h>

typedef struct stru_list_node_t{
	struct stru_node_t* pre;
	struct stru_node_t* next;
#ifdef STAGE_DEBUG
	ptr_t   magic;
#endif
	obj_t 	obj;
	alpha_bool_t bfree;
	free_callback free_call;
}list_node_t;

typedef list_node_t* node_list_t;

typedef struct {
	list_node_t* head;
	list_node_t* tail;
	list_node_t* head_for_free;
	alpha_uint   node_num; 
}i_list_t;

void free_node(list_node_t* pnode)
{
	#ifdef STAGE_DEBUG
	assert(pnode);
	#endif

	if (pnode->bfree) {
		pnode->free_call(pnode->obj);
	}

	free(pnode);
}

void list_free_node(i_list_t* list,list_node_t* pnode)
{
	#ifdef STAGE_DEBUG
	assert(pnode->magic == (ptr_t)list);
	#endif
	pnode->next = list->head_for_free;
	list->head_for_free = pnode;
	return;
}

list_node_t* get_free_node(i_list_t* list,obj_t obj,alpha_bool_t bfree,free_callback free_call)
{
	list_node_t* pnode;

	if(list->head_for_free) {
		pnode = list->head_for_free;
		list->head_for_free = pnode->next;
		if (pnode->bfree) {
			pnode->free_call(pnode->obj);
		}
	}else {
		pnode = COMM_MALLOC_TYPE(list_node_t);
	}

	#ifdef SAFE_CODE
	if (!pnode) {return nullptr;}
	#endif
	pnode->obj = obj;
	pnode->bfree = bfree;
	pnode->free_call = free_call ? free_call : default_free_call;
	return pnode;
}

////////////////////

list_t list_create()
{
	i_list_t* list = COMM_MALLOC_TYPE(i_list_t);

	#ifdef SAFE_CODE
	if (!list) {return nullptr;}
	#endif

	#ifdef STAGE_DEBUG
	assert(list);
	#endif
	list->head = get_free_node(0,ALPHA_FALSE,nullptr);
	list->tail = get_free_node(0,ALPHA_FALSE,nullptr);

	list->head->pre = nullptr;
	list->head->next = list->tail;
	list->head->magic = 0;
	
	list->tail->pre = list->head;
	list->tail->next = nullptr;
	list->tail->magic = 0;
	list->head_for_free = nullptr;
	list->node_num = 0;
	return (list_t)list;
}

alpha_uint list_size(list_t list)
{
	return TYPE_ACCESS(list,i_list_t)->node_num;
}

err_t list_push(list_t list,obj_t obj,alpha_bool_t bfree,free_callback free_call)
{
	#ifdef STAGE_DEBUG
	assert(list);
	#endif
	list_node_t* pnode = get_free_node(TYPE_ACCESS(list,i_list_t),obj,bfree,free_call);

	#ifdef SAFE_CODE
	if (!pnode) {return ERR_FAILED;}
	#endif

	#ifdef STAGE_DEBUG
	pnode->magic = list;
	#endif

	pnode->next = TYPE_ACCESS(list,i_list_t)->head->next;
	pnode->next->pre = pnode;
	TYPE_ACCESS(list,i_list_t)->head->next = pnode;
	pnode->pre = TYPE_ACCESS(list,i_list_t)->head;

	++(TYPE_ACCESS(list,i_list_t)->node_num);
	return ERR_SUCCESS;
}


obj_t list_pop(list_t list)
{
	#ifdef STAGE_DEBUG
	assert(list && TYPE_ACCESS(list,i_list_t)->node_num);
	#endif

	list_node_t** plst = (list_node_t**)list_begin(list);
	obj_t obj = (*plst)->obj;
	(*plst)->bfree = ALPHA_FALSE;
	list_erase((iterator_t)plst);

	return obj;
}



iterator_t list_begin(list_t list)
{
	#ifdef STAGE_DEBUG
	assert(list);
	#endif

	return (iterator_t)(&(TYPE_ACCESS(list,i_list_t)->head->next));
}

iterator_t list_end(list_t list)
{
	return (iterator_t)(&(TYPE_ACCESS(list,i_list_t)->tail));
}

err_t list_erase(list_t list,iterator_t iter)
{
	#ifdef STAGE_DEBUG
	assert(list && TYPE_ACCESS(list,i_list_t)->node_num && iter && (*(TYPE_ACCESS(iter,list_node_t*))) && ((*(TYPE_ACCESS(iter,list_node_t*)))->magic == list));
	#endif
	list_node_t* pre = (*(TYPE_ACCESS(iter,list_node_t*)))->pre;
	pre->next = (*(TYPE_ACCESS(iter,list_node_t*)))->next;
	pre->next->pre = pre;

	--(TYPE_ACCESS(list,i_list_t)->node_num);

	list_free_node(TYPE_ACCESS(list,i_list_t),(*(TYPE_ACCESS(iter,list_node_t*))));
	(*(TYPE_ACCESS(iter,list_node_t*))) = pre;
	return ERR_SUCCESS;
}

void next(iterator_t iter)
{
	#ifdef STAGE_DEBUG
	assert(iter);
	#endif

	(*(TYPE_ACCESS(iter,list_node_t*))) = (*(TYPE_ACCESS(iter,list_node_t*)))->next;
	return;
}


obj_t list_iterator_data(iterator_t iter)
{
	return (*(TYPE_ACCESS(iter,list_node_t*)))->obj;
}

obj_t list_iterator_pop_data(list_t list,iterator_t iter)
{
	list_node_t** plst = iter;
	#ifdef STAGE_DEBUG
	assert(list && iter && *plst);
	#endif
	
	obj_t obj = (*plst)->obj;
	(*plst)->bfree = ALPHA_FALSE;
	list_erase(iter);

	return obj;
}


void list_release(list_t list)
{	
	#ifdef STAGE_DEBUG
	assert(list);
	#endif
	list_node_t* pfree = TYPE_ACCESS(list,i_list_t)->head;

	while (pfree) {
		TYPE_ACCESS(list,i_list_t)->head = TYPE_ACCESS(list,i_list_t)->head->next;
		free_node(pfree);
		pfree = TYPE_ACCESS(list,i_list_t)->head;
	}

	list_node_t* pfree = TYPE_ACCESS(list,i_list_t)->head_for_free;

	while (pfree) {
		TYPE_ACCESS(list,i_list_t)->head_for_free = TYPE_ACCESS(list,i_list_t)->head_for_free->next;
		free_node(pfree);
		pfree = TYPE_ACCESS(list,i_list_t)->head_for_free;
	}

	free(list);
}


