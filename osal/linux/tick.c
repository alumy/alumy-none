#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_tick_t al_os_get_tick(void)
{
	return 0;
}

al_os_tick_t al_os_get_tick_isr(void)
{
	return 0;
}

al_os_tick_t al_os_ms2tick(uint32_t ms)
{
	return ms;
}

__END_DECLS
