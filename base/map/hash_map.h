/**
 * 
 * @Author:		kylin
 * @Email:		dqiyue@foxmail.com
 * @Date:		2017
 * @Describe:
 * @Copyrights: 
 *
 */

#include <comm/alpha_type.h>

typedef ptr_t hash_map_t;

enum {DEFAULT_HASH = 256,MIN_HASH = 8};

hash_map_t hash_map_create(alpha_uint hash);

void hash_map_release(hash_map_t hash_map);

err_t hash_map_insert(hash_map_t hash_map, hash_key_t key,obj_t obj,alpha_bool_t bfree,free_callback free_call);

err_t hash_map_erase(hash_map_t hash_map, hash_key_t key);

obj_t hash_map_find(hash_map_t hash_map, hash_key_t key);

alpha_uint hash_map_size(hash_map_t hash_map);