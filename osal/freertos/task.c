#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/check.h"
#include "alumy/osal.h"

__BEGIN_DECLS

void al_os_delay(uint_t ms)
{
	vTaskDelay(ms);
}

void al_os_delay_until(al_os_tick_t *prev, uint_t ms)
{
	BUILD_BUG_ON(sizeof(al_os_tick_t) != sizeof(TickType_t));

	vTaskDelayUntil(prev, pdMS_TO_TICKS(ms));
}

void al_os_yield_isr(bool_t yield)
{
	portYIELD_FROM_ISR(yield);
}

__END_DECLS

