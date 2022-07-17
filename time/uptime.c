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

uint32_t al_uptime(void)
{
    al_tick_t *tick = al_tick_get(NULL);

    return tick->tv_sec;
}

__END_DECLS

