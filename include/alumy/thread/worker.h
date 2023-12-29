#ifndef __AL_THREAD_WORKER_H
#define __AL_THREAD_WORKER_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

typedef struct al_worker {
	uint32_t init;
	al_os_task_t task;
	al_os_queue_t queue;
} al_worker_t;

/**
 * #brief Initialize the worker
 *
 * @author jack (2023/12/29)
 *
 * @param ctx The worker
 * @param cnt The count of worker queue items
 * @param name The worker task name
 * @param prio The worker task priority
 * @param stack The worker task stack size
 *
 * @return int32_t Return 0 on success, otherwise return
 *  	   negative
 */
int32_t al_worker_init(al_worker_t *ctx, int_t cnt,
					   const char *name, uint32_t prio, uint32_t stack);

int_t al_worker_check(al_worker_t *ctx);

int32_t al_worker_run(al_worker_t *ctx, void (*func)(void *arg), void *arg);

__END_DECLS

#endif

