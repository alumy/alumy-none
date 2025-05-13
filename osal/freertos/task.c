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

void al_os_delay_until(al_os_tick_t *prev, int32_t ms)
{
	BUILD_BUG_ON(sizeof(al_os_tick_t) != sizeof(TickType_t));

	TickType_t __ms =( ms < 0) ? portMAX_DELAY : pdMS_TO_TICKS(ms);

	vTaskDelayUntil(prev, __ms);
}

void al_os_yield_isr(bool_t yield)
{
	portYIELD_FROM_ISR(yield);
}

al_os_task_t *al_os_task_create(const char *name,
                                uint32_t prio,
                                uint32_t stack,
                                void (*func)(void *arg),
                                void *arg)
{
    BaseType_t ret;
    TaskHandle_t __handle;

    ret = xTaskCreate(func, name, stack, arg, prio, &__handle);
    if (ret != pdPASS) {
        set_errno(EPERM);
        return NULL;
    }

    al_os_task_t *handle = al_os_malloc(sizeof(al_os_task_t));
    if (handle == NULL) {
        set_errno(ENOMEM);
        return NULL;
    }

    *handle = __handle;

    return handle;
}

int32_t al_os_task_delete(al_os_task_t *handle)
{
    vTaskDelete((TaskHandle_t)*handle);

    al_os_free(handle);

	return 0;
}

uint32_t al_os_task_get_prio(al_os_task_t handle)
{
    return uxTaskPriorityGet((TaskHandle_t)handle);
}

void al_os_set_timeout_state(al_os_timeout_t *timeout)
{
	BUILD_BUG_ON(sizeof(al_os_timeout_t) < sizeof(TimeOut_t));
	BUILD_BUG_ON(sizeof(al_os_tick_t) < sizeof(TickType_t));

	vTaskSetTimeOutState((TimeOut_t *)timeout);
}

bool_t al_os_check_timeout(al_os_timeout_t *timeout, al_os_tick_t *tick)
{
	BaseType_t ret;

	BUILD_BUG_ON(sizeof(al_os_timeout_t) < sizeof(TimeOut_t));
	BUILD_BUG_ON(sizeof(al_os_tick_t) < sizeof(TickType_t));

    return !!xTaskCheckForTimeOut((TimeOut_t *)timeout, (TickType_t *)tick);
}

__END_DECLS

