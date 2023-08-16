#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

al_os_sem_t al_os_sem_bin_create(void)
{
	return (al_os_sem_t)xSemaphoreCreateBinary();
}

al_os_sem_t *al_os_sem_count_create(uint_t max_count, uint_t min_count)
{
	return (al_os_sem_t)xSemaphoreCreateCounting(max_count, min_count);
}

int_t al_os_sem_take(al_os_sem_t sem, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	if (xSemaphoreTake(sem, t) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_sem_take_isr(al_os_sem_t sem, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xSemaphoreTakeFromISR(sem, &__yield) != pdTRUE) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

int_t al_os_sem_give(al_os_sem_t sem)
{
	if (xSemaphoreGive(sem) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_sem_give_isr(al_os_sem_t sem, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xSemaphoreGiveFromISR(sem, &__yield) != pdTRUE) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

__END_DECLS
