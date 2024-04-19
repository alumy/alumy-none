#ifndef __AL_TIME_TICK_H
#define __AL_TIME_TICK_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

void al_tick_init(void);

/**
 * @brief This should invoke in 1 msecond timer callback
 *
 * @author jack (2024/4/19)
 *
 * @param void
 */
void al_tick_inc(void);

uint32_t al_tick_get_sec(void);
uint32_t al_tick_get_msec(void);
uint32_t al_tick_get_tick(void);
uint32_t al_tick_elapsed_tick(uint32_t last);
uint32_t al_tick_elapsed_sec(uint32_t last);

__END_DECLS

#endif

