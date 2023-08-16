#ifndef __AL_OSAL_SEMPHR_H
#define __AL_OSAL_SEMPHR_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef void * al_os_sem_t;

al_os_sem_t al_os_sem_bin_create(void);

al_os_sem_t *al_os_sem_count_create(uint_t max_count, uint_t min_count);

int_t al_os_sem_take(al_os_sem_t sem, int_t timeout);

int_t al_os_sem_take_isr(al_os_sem_t sem, bool_t *yield);

int_t al_os_sem_give_isr(al_os_sem_t sem, bool_t *yield);

int_t al_os_sem_give(al_os_sem_t sem);

__END_DECLS

#endif

