#ifndef __AL_OSAL_TIMER_H
#define __AL_OSAL_TIMER_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef void (*al_os_timer_cb)(void *arg);

typedef struct al_os_timer {
	void *handle;
	al_os_timer_cb cb;
	void *arg;
} al_os_timer_t;

al_os_timer_t *al_os_timer_create(const char *name,
								  uint_t period, bool_t auto_reload,
								  al_os_timer_cb cb, void *arg);

int_t al_os_timer_del(al_os_timer_t *tmr);

int_t al_os_timer_start(al_os_timer_t *tmr);

int_t al_os_timer_stop(al_os_timer_t *tmr);

int_t al_os_timer_start_isr(al_os_timer_t *tmr, bool_t *yield);

int_t al_os_timer_stop_isr(al_os_timer_t *tmr, bool_t *yield);

__END_DECLS

#endif

