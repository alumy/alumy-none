#ifndef __AL_OSAL_SEMPHR_H
#define __AL_OSAL_SEMPHR_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef void * al_os_sem_t;
typedef void * al_os_mutex_t;

al_os_sem_t al_os_sem_bin_create(void);
void al_os_sem_bin_del(al_os_sem_t sem);

al_os_sem_t al_os_sem_count_create(uint_t max_count, uint_t init_count);
void al_os_sem_count_del(al_os_sem_t sem);

al_os_mutex_t al_os_mutex_create(void);
void al_os_mutex_del(al_os_mutex_t mutex);

int_t al_os_sem_take(al_os_sem_t sem, int_t timeout);

int_t al_os_sem_take_isr(al_os_sem_t sem, bool_t *yield);

int_t al_os_sem_give_isr(al_os_sem_t sem, bool_t *yield);

int_t al_os_sem_give(al_os_sem_t sem);

int_t al_os_mutex_take(al_os_mutex_t mutex, int_t timeout);

int_t al_os_mutex_take_isr(al_os_mutex_t mutex, bool_t *yield);

int_t al_os_mutex_give(al_os_mutex_t mutex);

int_t al_os_mutex_give_isr(al_os_mutex_t mutex, bool_t *yield);

__END_DECLS

#endif

