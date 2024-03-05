#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_tick_t al_os_get_tick(void)
{
	return xTaskGetTickCount();
}

al_os_tick_t al_os_get_tick_isr(void)
{
	return xTaskGetTickCountFromISR();
}

al_os_tick_t al_os_ms2tick(uint32_t ms)
{
	return pdMS_TO_TICKS(ms);
}

uint32_t al_os_tick2ms(al_os_tick_t tick)
{
	return tick * portTICK_PERIOD_MS;
}

__END_DECLS
