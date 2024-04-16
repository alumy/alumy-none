#ifndef __AL_TIME_UPTIME_H
#define __AL_TIME_UPTIME_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct al_uptime {
	uint32_t days;
	uint_t hours;
	uint_t mins;
} al_uptime_t;

uint32_t al_uptime(void);

void al_uptime_get(al_uptime_t *up);
void al_uptime_get_r(uint32_t uptime, al_uptime_t *up);

__END_DECLS

#endif

