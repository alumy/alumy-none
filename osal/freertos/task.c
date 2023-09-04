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

void al_os_delay(int32_t ms)
{
	TickType_t __ms =( ms < 0) ? portMAX_DELAY : pdMS_TO_TICKS(ms);

	vTaskDelay(__ms);
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

int32_t al_os_task_create(al_os_task_t *handle,
						  const void *name,
						  uint32_t prio,
						  uint32_t stack,
						  void (*func)(void *arg),
						  void *arg)
{
	BaseType_t ret;

	ret = xTaskCreate(func, name, stack, arg, prio, (TaskHandle_t *)handle);
	if (ret != pdPASS) {
		return -1;
	}

	return 0;
}

int32_t al_os_task_delete(al_os_task_t handle)
{
	vTaskDelete(handle);

	return 0;
}

__END_DECLS

