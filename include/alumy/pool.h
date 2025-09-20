/**
 * @file    pool.h
 * @author  alumy project
 * @version v0.0.1
 * @brief   Memory pool management utilities for the alumy library
 * 
 * This header file provides memory pool functionality for efficient allocation
 * and deallocation of fixed-size memory blocks. Memory pools are useful for
 * reducing memory fragmentation and improving allocation performance in
 * applications that frequently allocate and deallocate objects of the same size.
 * 
 * @copyright Copyright (c) 2019 alumy project
 */

#ifndef __POOL_H
#define __POOL_H

#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/list.h"

__BEGIN_DECLS

/**
 * @brief Memory pool structure
 * 
 * This structure represents a memory pool that manages a collection of
 * fixed-size memory blocks. It maintains lists of free and used blocks
 * and tracks statistics about pool usage.
 */
typedef struct al_pool {
    list_head_t free;       /*!< Linked list of free memory blocks */
    int32_t nr_free;        /*!< Number of currently free items in the pool */
    int32_t nr_used;        /*!< Number of currently used items in the pool */
    int32_t nr_total;       /*!< Total number of items in the pool (free + used) */
} al_pool_t;


/**
 * @brief Create and initialize a memory pool
 * 
 * Initializes a memory pool structure with the provided buffer. The buffer
 * is divided into fixed-size blocks that can be allocated and deallocated
 * efficiently. Each block includes space for list management overhead.
 *
 * @author jack (9/17/2019)
 *
 * @param po     Pointer to the memory pool structure to initialize
 * @param buf    Pointer to the memory buffer to use for the pool
 * @param size   Size of each individual memory block in bytes
 * @param nmemb  Number of memory blocks to create in the pool
 * @param offset Byte offset within each block where the list node is stored
 */
void al_create_pool(al_pool_t *po,
                    void *buf, size_t size, size_t nmemb, off_t offset);

/**
 * @brief Allocate an item from the memory pool
 * 
 * Retrieves a free memory block from the pool. The block is removed from
 * the free list and marked as used. Returns NULL if no free blocks are
 * available.
 *
 * @author jack (9/17/2019)
 *
 * @param po     Pointer to the memory pool
 * @param offset Byte offset within the block where the list node is stored
 *
 * @return void* Pointer to the allocated memory block, or NULL if pool is empty
 */
void *al_get_from_pool(al_pool_t *po, int32_t offset);

/**
 * @brief Return an item to the memory pool
 * 
 * Returns a previously allocated memory block back to the pool's free list.
 * The block becomes available for future allocations. The caller must ensure
 * the block was originally allocated from this pool.
 *
 * @author jack (9/17/2019)
 *
 * @param po     Pointer to the memory pool
 * @param ent    Pointer to the memory block to return to the pool
 * @param offset Byte offset within the block where the list node is stored
 */
void al_put_into_pool(al_pool_t *po, void *ent, uint_t offset);

__END_DECLS

#endif
