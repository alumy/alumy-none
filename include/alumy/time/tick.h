#ifndef __AL_TIME_TICK_H
#define __AL_TIME_TICK_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct al_tick {
    time_t tv_sec;
    int32_t tv_msec;
} al_tick_t;

void al_tick_init(void);
void al_tick_inc(void);
const al_tick_t *al_tick_get(al_tick_t *pt);

__END_DECLS

#endif

