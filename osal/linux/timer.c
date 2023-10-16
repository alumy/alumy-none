#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_timer_t *al_os_timer_create(const char *name,
								  uint_t period, bool_t auto_reload,
								  al_os_timer_cb cb, void *arg)
{
	return NULL;
}

int_t al_os_timer_del(al_os_timer_t *tmr)
{
	return 0;
}

int_t al_os_timer_start(al_os_timer_t *tmr)
{
	return 0;
}

int_t al_os_timer_stop(al_os_timer_t *tmr)
{
	return 0;
}

int_t al_os_timer_start_isr(al_os_timer_t *tmr, bool_t *yield)
{
	return 0;
}

int_t al_os_timer_stop_isr(al_os_timer_t *tmr, bool_t *yield)
{
	return 0;
}

int_t al_os_timer_set_period(al_os_timer_t *tmr, uint_t period)
{
	return 0;
}

int_t al_os_timer_set_period_isr(al_os_timer_t *tmr,
								 uint_t period, bool_t *yield)
{
	return 0;
}

int_t al_os_timer_reset(al_os_timer_t *tmr)
{
	return 0;
}

int_t al_os_timer_reset_isr(al_os_timer_t *tmr, bool_t *yield)
{
	return 0;
}

__END_DECLS

