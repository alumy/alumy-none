/**
 * @file worker.h
 * @brief Worker thread management for task execution
 * 
 * This module provides a worker thread implementation that can execute
 * tasks asynchronously. The worker maintains a queue of work items and
 * processes them sequentially in a dedicated thread context.
 * 
 * @author Alumy Development Team
 * @date 2023
 */

#ifndef __AL_THREAD_WORKER_H
#define __AL_THREAD_WORKER_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

/**
 * @brief Worker thread context structure
 * 
 * Contains the worker thread state, task handle, and work queue
 */
typedef struct al_worker {
	uint32_t init;          /**< Initialization flag */
	al_os_task_t task;      /**< Worker task handle */
	al_os_queue_t queue;    /**< Work item queue */
} al_worker_t;

/**
 * @brief Initialize the worker thread
 *
 * Creates and initializes a worker thread with the specified parameters.
 * The worker will create a task and queue for processing work items.
 *
 * @author jack (2023/12/29)
 *
 * @param ctx The worker context to initialize
 * @param cnt The maximum number of work items that can be queued
 * @param name The name of the worker task
 * @param prio The priority of the worker task
 * @param stack The stack size for the worker task in bytes
 *
 * @return int32_t Return 0 on success, otherwise return negative error code
 */
int32_t al_worker_init(al_worker_t *ctx, int_t cnt,
					   const char *name, uint32_t prio, uint32_t stack);

/**
 * @brief Check if the worker is properly initialized
 *
 * Verifies that the worker context has been properly initialized
 * and is ready to accept work items.
 *
 * @param ctx The worker context to check
 * @return int_t Non-zero if worker is initialized, 0 otherwise
 */
int_t al_worker_check(al_worker_t *ctx);

/**
 * @brief Submit a work item to the worker thread
 *
 * Queues a function to be executed by the worker thread. The function
 * will be called with the provided argument in the worker thread context.
 *
 * @param ctx The worker context
 * @param func The function to execute in the worker thread
 * @param arg The argument to pass to the function
 * @param timeout Timeout in milliseconds to wait for queue space
 * @return int32_t Return 0 on success, negative error code on failure
 */
int32_t al_worker_run(al_worker_t *ctx,
                      void (*func)(void *arg), void *arg, int32_t timeout);

__END_DECLS

#endif
