#ifndef __AL_OSAL_TASK_H
#define __AL_OSAL_TASK_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal/tick.h"

__BEGIN_DECLS

void al_os_delay(uint_t ms);
void al_os_delay_until(al_os_tick_t *prev, uint_t ms);
void al_os_yield_isr(bool_t yield);

__END_DECLS

#endif

