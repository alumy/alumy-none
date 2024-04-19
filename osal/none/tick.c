#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_tick_t al_os_get_tick(void)
{
    return al_tick_get_tick();
}

al_os_tick_t al_os_get_tick_isr(void)
{
    return al_tick_get_tick();
}

al_os_tick_t al_os_ms2tick(uint32_t ms)
{
	return ms;
}

uint32_t al_os_tick2ms(al_os_tick_t tick)
{
	return tick;
}

__END_DECLS
