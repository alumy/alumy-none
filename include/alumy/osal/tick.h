#ifndef __AL_OSAL_TICK_H
#define __AL_OSAL_TICK_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef uint32_t al_os_tick_t;

#ifndef DR_OS_MS_TO_TICKS
#define DR_OS_MS_TO_TICKS(ms)		((ms))
#endif

uint32_t al_os_get_tick(void);
uint32_t al_os_get_tick_isr(void);

__END_DECLS

#endif

