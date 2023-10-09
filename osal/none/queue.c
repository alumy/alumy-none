#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_queue_t al_os_queue_create(uint_t num, size_t size)
{
	return NULL;
}

int_t al_os_queue_del(al_os_queue_t queue)
{
	return 0;
}

int_t al_os_queue_send(al_os_queue_t queue, const void *data, int_t timeout)
{
	return 0;
}

int_t al_os_queue_send_isr(al_os_queue_t queue, const void *data,
						   bool_t *yield)
{
	return 0;
}

int_t al_os_queue_send_back(al_os_queue_t queue,
							const void *data, int_t timeout)
{
	return 0;
}

int_t al_os_queue_send_back_isr(al_os_queue_t queue,
								const void *data, bool_t *yield)
{
	return 0;
}

int_t al_os_queue_send_front(al_os_queue_t queue,
							 const void *data, int_t timeout)
{
	return 0;
}

int_t al_os_queue_send_front_isr(al_os_queue_t queue,
								 const void *data, bool_t *yield)
{
	return 0;
}

int_t al_os_queue_recv(al_os_queue_t queue, void *data, int_t timeout)
{
	return 0;
}

int_t al_os_queue_recv_isr(al_os_queue_t queue, void *data, bool_t *yield)
{
	return 0;
}

int_t al_os_queue_count(al_os_queue_t queue)
{
	return 0;
}

int_t al_os_queue_count_isr(al_os_queue_t queue, bool_t *yield)
{
	return 0;
}

int_t al_os_queue_reset(al_os_queue_t queue)
{
	return 0;
}

int_t al_os_queue_peek(al_os_queue_t queue, void *data, int_t timeout)
{
	return 0;
}

int_t al_os_queue_peek_isr(al_os_queue_t queue, void *data)
{
	return 0;
}

__END_DECLS

