#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_stream_t al_os_stream_create(size_t size, size_t level)
{
	return (al_os_stream_t)xStreamBufferCreate(size, level);
}

void al_os_stream_del(al_os_stream_t stream)
{
	vStreamBufferDelete(stream);
}

size_t al_os_stream_send(al_os_stream_t stream,
						 const void *data, size_t len, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	return xStreamBufferSend((StreamBufferHandle_t)stream, data, len, t);
}

int_t al_os_stream_send_isr(al_os_stream_t stream,
							const void *data, size_t len, bool_t *yield)
{
	size_t n;
	BaseType_t __yield = pdFALSE;

	n = xStreamBufferSendFromISR(
				(StreamBufferHandle_t)stream, data, len, &__yield);

    if (yield) {
        *yield = __yield;
    }

	return n;
}

size_t al_os_stream_recv(al_os_stream_t stream,
						void *buf, size_t size, int_t timeout)
{
	TickType_t t = (timeout < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout);

	return xStreamBufferReceive((StreamBufferHandle_t)stream, buf, size, t);
}

int_t al_os_stream_recv_isr(al_os_stream_t stream,
							void *buf, size_t size, bool_t *yield)
{
	size_t n;
	BaseType_t __yield = pdFALSE;

	n = xStreamBufferReceiveFromISR(
				(StreamBufferHandle_t)stream, buf, size, &__yield);

    if (yield) {
        *yield = __yield;
    }

	return n;
}

bool_t al_os_stream_is_full(al_os_stream_t stream)
{
	return xStreamBufferIsFull((StreamBufferHandle_t)stream);
}

bool_t al_os_stream_is_empty(al_os_stream_t stream)
{
	return xStreamBufferIsEmpty((StreamBufferHandle_t)stream);
}

bool_t al_os_stream_reset(al_os_stream_t stream)
{
	return xStreamBufferReset((StreamBufferHandle_t)stream);
}

size_t al_os_stream_free_len(al_os_stream_t stream)
{
	return xStreamBufferSpacesAvailable((StreamBufferHandle_t)stream);
}

size_t al_os_stream_used_len(al_os_stream_t stream)
{
	return xStreamBufferBytesAvailable((StreamBufferHandle_t)stream);
}

__END_DECLS


