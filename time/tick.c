#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/time/tick.h"

__BEGIN_DECLS

static al_tick_t tick = { 0 };

void al_tick_init(void)
{
    tick.tv_sec = 0;
    tick.tv_msec = 0;
}

void al_tick_inc(void)
{
    tick.tv_msec++;
    if (tick.tv_msec >= 1000) {
        tick.tv_msec = 0;
        tick.tv_sec++;
    }
}

const al_tick_t *al_tick_get(al_tick_t *pt)
{
    if (pt != NULL) {
        pt->tv_sec = tick.tv_sec;
        pt->tv_msec = tick.tv_msec;

        return pt;
    }

    return &tick;
}

__END_DECLS

