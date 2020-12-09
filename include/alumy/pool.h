#ifndef __POOL_H
#define __POOL_H

#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/list.h"

__BEGIN_DECLS

/**
 * @brief memory pool
 */
typedef struct al_pool {
    list_head_t free;       /*!< free list */
    int32_t nr_free;        /*!< free items number */
    int32_t nr_used;        /*!< used items number */
    int32_t nr_total;       /*!< total items number */
} al_pool_t;


/**
 * @brief Create a memory pool
 *
 * @author chenyj (9/17/2019)
 *
 * @param po
 * @param buf
 * @param nr
 * @param sz
 * @param offset
 */
void al_create_pool(al_pool_t *po,
                    void *buf, size_t size, size_t nmemb, off_t offset);

/**
 * @brief Get item from memory pool
 *
 * @author chenyj (9/17/2019)
 *
 * @param po
 * @param offset
 *
 * @return void*
 */
void *al_get_from_pool(al_pool_t *po, int32_t offset);

/**
 * @brief Put the item to memory pool
 *
 * @author chenyj (9/17/2019)
 *
 * @param po
 * @param ent
 * @param offset
 */
void al_put_into_pool(al_pool_t *po, void *ent, int32_t offset);

__END_DECLS

#endif

