#ifndef __AL_OSAL_TICK_H
#define __AL_OSAL_TICK_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef uint32_t al_os_tick_t;

al_os_tick_t al_os_get_tick(void);
al_os_tick_t al_os_get_tick_isr(void);
al_os_tick_t al_os_ms2tick(uint32_t ms);
uint32_t al_os_tick2ms(al_os_tick_t tick);

__END_DECLS

#endif

