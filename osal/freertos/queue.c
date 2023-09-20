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

al_os_queue_t al_os_queue_create(uint_t num, size_t size)
{
	return (al_os_queue_t)xQueueCreate(num, size);
}

int_t al_os_queue_del(al_os_queue_t queue)
{
	vQueueDelete(queue);

	return 0;
}

int_t al_os_queue_send(al_os_queue_t queue, const void *data, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	if (xQueueSend((QueueHandle_t)queue, data, t) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_queue_send_isr(al_os_queue_t queue, const void *data,
						   bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xQueueSendFromISR((QueueHandle_t)queue, data, &__yield) != pdTRUE) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

int_t al_os_queue_send_back(al_os_queue_t queue,
							const void *data, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	if (xQueueSendToBack((QueueHandle_t)queue, data, t) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_queue_send_back_isr(al_os_queue_t queue,
								const void *data, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xQueueSendToBackFromISR((QueueHandle_t)queue,
								data, &__yield) != pdTRUE) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

int_t al_os_queue_send_front(al_os_queue_t queue,
							 const void *data, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	if (xQueueSendToFront((QueueHandle_t)queue, data, t) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_queue_send_front_isr(al_os_queue_t queue,
								 const void *data, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xQueueSendToFrontFromISR((QueueHandle_t)queue,
								 data, &__yield) != pdTRUE) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

int_t al_os_queue_recv(al_os_queue_t queue, void *data, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	if (xQueueReceive((QueueHandle_t)queue, data, t) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_queue_recv_isr(al_os_queue_t queue, void *data, bool_t *yield)
{
	BaseType_t __yield = pdFALSE;

	if (xQueueReceiveFromISR((QueueHandle_t)queue, data, &__yield) != pdTRUE) {
		return -1;
	}

	*yield = __yield;

	return 0;
}

int_t al_os_queue_count(al_os_queue_t queue)
{
	return uxQueueMessagesWaiting((QueueHandle_t)queue);
}

int_t al_os_queue_count_isr(al_os_queue_t queue, bool_t *yield)
{
	return uxQueueMessagesWaitingFromISR((QueueHandle_t)queue);
}

int_t al_os_queue_reset(al_os_queue_t queue)
{
	xQueueReset((QueueHandle_t)queue);

	return 0;
}

int_t al_os_queue_peek(al_os_queue_t queue, void *data, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	if (xQueuePeek((QueueHandle_t)queue, data, t) != pdTRUE) {
		return -1;
	}

	return 0;
}

int_t al_os_queue_peek_isr(al_os_queue_t queue, void *data)
{
	if (xQueuePeekFromISR((QueueHandle_t)queue, data) != pdTRUE) {
		return -1;
	}

	return 0;
}

__END_DECLS

