#ifndef __AL_OSAL_QUEUE_H
#define __AL_OSAL_QUEUE_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef void * al_os_queue_t;

al_os_queue_t al_os_queue_create(uint_t num, size_t size);
int_t al_os_queue_del(al_os_queue_t queue);

int_t al_os_queue_send(al_os_queue_t queue, const void *data, int_t timeout);
int_t al_os_queue_send_isr(al_os_queue_t queue,
						   const void *data, bool_t *yield);

int_t al_os_queue_send_back(al_os_queue_t queue,
							const void *data, int_t timeout);
int_t al_os_queue_send_back_isr(al_os_queue_t queue,
								const void *data, bool_t *yield);

int_t al_os_queue_send_front(al_os_queue_t queue,
							 const void *data, int_t timeout);
int_t al_os_queue_send_front_isr(al_os_queue_t queue,
								 const void *data, bool_t *yield);

int_t al_os_queue_recv(al_os_queue_t queue, void *data, int_t timeout);
int_t al_os_queue_recv_isr(al_os_queue_t queue, void *data, bool_t *yield);

int_t al_os_queue_count(al_os_queue_t queue);
int_t al_os_queue_count_isr(al_os_queue_t queue, bool_t *yield);

int_t al_os_queue_reset(al_os_queue_t queue);

int_t al_os_queue_peek(al_os_queue_t queue, void *data, int_t timeout);
int_t al_os_queue_peek_isr(al_os_queue_t queue, void *data);

__END_DECLS

#endif

