#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

uint32_t al_os_get_tick(void)
{
	return xTaskGetTickCount();
}

uint32_t al_os_get_tick_isr(void)
{
	return xTaskGetTickCountFromISR();
}

__END_DECLS
