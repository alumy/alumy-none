#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/check.h"
#include "alumy/errno.h"
#include "alumy/time/tick.h"
#include "alumy/time/uptime.h"

__BEGIN_DECLS

uint32_t al_uptime(void)
{
    return al_tick_get_sec();
}

void al_uptime_get(al_uptime_t *up)
{
	AL_CHECK(up, EINVAL);

	uint32_t uptime = al_uptime();

	up->days = uptime / 86400;
	up->hours = uptime % 86400 / 3600;
	up->mins = uptime % 86400 % 3600 / 60;
}

void al_uptime_get_r(uint32_t uptime, al_uptime_t *up)
{
    AL_CHECK(up, EINVAL);

    up->days = uptime / 86400;
    up->hours = uptime % 86400 / 3600;
    up->mins = uptime % 86400 % 3600 / 60;
}

__END_DECLS

