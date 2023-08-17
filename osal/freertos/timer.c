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

static void freertos_timer_callback( TimerHandle_t xTimer )
{
	al_os_timer_t *tmr = (al_os_timer_t *)pvTimerGetTimerID(xTimer);

	tmr->cb(tmr->arg);
}

al_os_timer_t *al_os_timer_create(const char *name,
								  uint_t period, bool_t auto_reload,
								  al_os_timer_cb cb, void *arg)
{
	al_os_timer_t *tmr = (al_os_timer_t *)pvPortMalloc(sizeof(al_os_timer_t));
	if (tmr == NULL) {
		return NULL;
	}

	tmr->cb = cb;
	tmr->arg = arg;

	tmr->handle = xTimerCreate(name, pdMS_TO_TICKS(period),
							   auto_reload ? pdTRUE : pdFALSE,
							   tmr, freertos_timer_callback);
	if (tmr->handle == NULL) {
		vPortFree(tmr);
		return NULL;
	}

	return tmr;
}

int_t al_os_timer_del(al_os_timer_t *tmr)
{
	if (xTimerDelete(tmr->handle, portMAX_DELAY) != pdPASS) {
		return -1;
	}

	vPortFree(tmr);

	return 0;
}

int_t al_os_timer_start(al_os_timer_t *tmr)
{
	if (xTimerStart(tmr->handle, portMAX_DELAY) != pdPASS) {
		return -1;
	}

	return 0;
}

int_t al_os_timer_stop(al_os_timer_t *tmr)
{
	if (xTimerStop(tmr->handle, portMAX_DELAY) != pdPASS) {
		return -1;
	}

	return 0;
}

int_t al_os_timer_start_isr(al_os_timer_t *tmr, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xTimerStartFromISR(tmr->handle, &__yield) != pdPASS) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

int_t al_os_timer_stop_isr(al_os_timer_t *tmr, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xTimerStopFromISR(tmr->handle, &__yield) != pdPASS) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

__END_DECLS

