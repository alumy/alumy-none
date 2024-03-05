#ifndef __AL_OSAL_TASK_H
#define __AL_OSAL_TASK_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal/tick.h"

__BEGIN_DECLS

typedef void * al_os_task_t;
typedef uint64_t al_os_timeout_t;

void al_os_delay(int32_t ms);
void al_os_delay_until(al_os_tick_t *prev, int32_t ms);
void al_os_yield_isr(bool_t yield);

int32_t al_os_task_create(al_os_task_t *handle,
						  const char *name,
						  uint32_t prio,
						  uint32_t stack,
						  void (*func)(void *arg),
						  void *arg);

int32_t al_os_task_delete(al_os_task_t handle);

uint32_t al_os_task_get_prio(al_os_task_t handle);

void al_os_set_timeout_state(al_os_timeout_t *timeout);

bool_t al_os_check_timeout(al_os_timeout_t *timeout, al_os_tick_t *tick);

__END_DECLS

#endif

