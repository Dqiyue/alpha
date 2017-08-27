/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */
#include <string.h>
#include <comm/commfunc.h>
#include <list/list.h>
#include "hash_map.h"

typedef struct {
	hash_key_t key;
	obj_t obj;
	alpha_bool_t bfree;
	free_callback free_call;
}hash_map_obj_t;


typedef struct {
	list_t* hash_list_arry;
	list_t free_obj_list;
	alpha_uint hash;
	alpha_uint size;
}i_hash_map_t;

void hash_map_obj_free(obj_t obj) 
{
	#ifdef STAGE_DEBUG
	assert(obj);
	#endif
	if (TYPE_ACCESS(obj,hash_map_obj_t)->bfree) {
		TYPE_ACCESS(obj,hash_map_obj_t)->free_call(TYPE_ACCESS(obj,hash_map_obj_t)->obj);
	}

	free(obj);
	return;
}

err_t hash_map_free_obj(i_hash_map_t* hash_map,hash_map_obj_t* obj,alpha_bool_t needfree)
{
	obj->bfree= needfree;
	#ifdef SAFE_CODE
	err_t ret = list_push(hash_map->free_obj_list,obj,true,hash_map_obj_free);
	if (ret != ERR_SUCCESS) {
		hash_map_obj_free(obj);
	}

	return ERR_SUCCESS;
	#endif
	list_push(hash_map->free_obj_list,obj,true,hash_map_obj_free);
	return ERR_SUCCESS;
}


hash_map_obj_t* get_free_obj(i_hash_map_t* hash_map)
{
	if (list_size(hash_map->free_obj_list)) {
		hash_map_obj_t* obj = (hash_map_obj_t*)list_pop(hash_map->free_obj_list);
		if (obj->bfree) {
			obj->free_call(obj->obj);
		}
		return obj;
	}

	return COMM_MALLOC_TYPE(hash_map_obj_t);
}

/////////////////////

hash_map_t hash_map_create(alpha_uint hash)
{
	i_hash_map_t* hash_map = COMM_MALLOC_TYPE(i_hash_map_t);
	#ifdef SAFE_CODE
	if (!hash_map) { return nullptr; }
	#endif

	hash_map->hash = roundup_pow_of_two(hash, sizeof(hash_map->hash));

	hash_map->hash_list_arry = COMM_MALLOC_ARRY(list_t,hash_map->hash);

	memset(hash_map->hash_list_arry,0,sizeof(list_t) * hash_map->hash);

	#ifdef SAFE_CODE
	if (!hash_map->hash_list_arry) { free(hash_map); return nullptr; }
	#endif

	hash_map->free_obj_list = list_create();

	#ifdef SAFE_CODE
	if (!hash_map->free_obj_list) { free(hash_map->hash_list_arry);free(hash_map); return nullptr;}
	#endif


	for(alpha_uint i = 0; i != hash_map->hash; ++i) {
		hash_map->hash_list_arry[i] = list_create();
		#ifdef SAFE_CODE
		if (!hash_map->hash_list_arry[i]) { hash_map_release(hash_map); return nullptr; }
		#endif
	}

	hash_map->size = 0;
	return (hash_map_t)hash_map;
}

void hash_map_release(hash_map_t hash_map)
{
	for(alpha_uint i = 0; i != TYPE_ACCESS(hash_map,i_hash_map_t)->hash; ++i) {
		#ifdef SAFE_CODE
		if (TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry[i] == 0) {
			return;
		}
		#endif

		list_release(TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry[i]);
	}
	list_release(TYPE_ACCESS(hash_map,i_hash_map_t)->free_obj_list);
	free(TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry);
	free(hash_map);
	return;
}

err_t hash_map_insert(hash_map_t hash_map, hash_key_t key,obj_t obj,alpha_bool_t bfree,free_callback free_call)
{
	hash_map_obj_t* obj = get_free_obj(TYPE_ACCESS(hash_map,i_hash_map_t));
	#ifdef SAFE_CODE
	if (!obj) {return ERR_FAILED;}
	#endif

	obj->key = key;
	obj->obj = obj;
	obj->bfree = bfree;
	obj->free_call = free_call ? free_call : default_free_call;

	#ifdef SAFE_CODE
	err_t ret = list_push(TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry[key & (TYPE_ACCESS(hash_map,i_hash_map_t)->hash - 1)],obj,true,hash_map_obj_free);
	if (ret == ERR_FAILED && hash_map_free_obj(TYPE_ACCESS(hash_map,i_hash_map_t),obj,ALPHA_FALSE) == ERR_FAILED) { free(obj);}
	return ret;
	#endif
	
	return list_push(TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry[key & (TYPE_ACCESS(hash_map,i_hash_map_t)->hash - 1)],obj,true,hash_map_obj_free);
}

err_t hash_map_erase(hash_map_t hash_map, hash_key_t key)
{
	#ifdef STAGE_DEBUG
	assert(hash_map && TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry);
	#endif
	list_t list = TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry[key & (TYPE_ACCESS(hash_map,i_hash_map_t)->hash - 1)];
	for(iterator_t it = list_begin(list); it != list_end(list);next(it)) {
		if (TYPE_ACCESS(list_iterator_data(it),hash_map_obj_t)->key == key) {
			hash_map_obj_t* obj = (hash_map_obj_t*)list_iterator_pop_data(list,it);
			--(TYPE_ACCESS(hash_map,i_hash_map_t)->size);
			return hash_map_free_obj(TYPE_ACCESS(hash_map,i_hash_map_t),obj,ALPHA_TRUE);
		}
	}

	return ERR_FAILED;
}

obj_t hash_map_find(hash_map_t hash_map, hash_key_t key)
{
	#ifdef STAGE_DEBUG
	assert(hash_map && TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry);
	#endif
	list_t list = TYPE_ACCESS(hash_map,i_hash_map_t)->hash_list_arry[key & (TYPE_ACCESS(hash_map,i_hash_map_t)->hash - 1)];
	for(iterator_t it = list_begin(list); it != list_end(list);next(it)) {
		if (TYPE_ACCESS(list_iterator_data(it),hash_map_obj_t)->key == key) {
			return TYPE_ACCESS(list_iterator_data(it),hash_map_obj_t)->obj;
		}
	}

	return nullptr;
}


alpha_uint hash_map_size(hash_map_t hash_map)
{
	#ifdef STAGE_DEBUG
	assert(hash_map);
	#endif
	return TYPE_ACCESS(hash_map,i_hash_map_t)->size;
}