#ifndef __AL_TIME_TICK_H
#define __AL_TIME_TICK_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct al_tick {
    volatile time_t tv_sec;
    volatile uint_t tv_msec;
	volatile uint_t tv_tick;
} al_tick_t;

void al_tick_init(void);
void al_tick_inc(void);
const al_tick_t *al_tick_get(al_tick_t *pt);

__END_DECLS

#endif

