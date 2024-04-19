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

static uint32_t tick_tick = 0;
static uint32_t tick_msec = 0;
static uint32_t tick_sec = 0;

void al_tick_init(void)
{
    tick_tick = 0;
    tick_msec = 0;
    tick_sec = 0;
}

void al_tick_inc(void)
{
    tick_tick++;

    tick_msec++;
    if (tick_msec >= 1000) {
        tick_msec = 0;
        tick_sec++;
    }
}

__always_inline uint32_t al_tick_get_tick(void)
{
    return tick_tick;
}

__always_inline uint32_t al_tick_get_sec(void)
{
    return tick_sec;
}

__always_inline uint32_t al_tick_get_msec(void)
{
    return tick_msec;
}

__always_inline uint32_t al_tick_elapsed_tick(uint32_t last)
{
    return al_tick_get_tick() - last;
}

__always_inline uint32_t al_tick_elapsed_sec(uint32_t last)
{
    return al_tick_get_sec() - last;
}

__END_DECLS

