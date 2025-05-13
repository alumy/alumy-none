#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/check.h"
#include "alumy/osal.h"

__BEGIN_DECLS

void al_os_delay(int32_t ms)
{
}

void al_os_delay_until(al_os_tick_t *prev, int32_t ms)
{
}

void al_os_yield_isr(bool_t yield)
{

}

al_os_task_t *al_os_task_create(const char *name,
                                uint32_t prio,
                                uint32_t stack,
                                void (*func)(void *arg),
                                void *arg)
{
	return 0;
}

int32_t al_os_task_delete(al_os_task_t *handle)
{
	return 0;
}

uint32_t al_os_task_get_prio(al_os_task_t handle)
{
	return 0;
}

void al_os_set_timeout_state(al_os_timeout_t *timeout)
{
}

bool_t al_os_check_timeout(al_os_timeout_t *timeout, al_os_tick_t *tick)
{
	return false;
}

__END_DECLS

