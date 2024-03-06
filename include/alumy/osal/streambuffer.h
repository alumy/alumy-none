#ifndef __AL_OSAL_STREAMBUFFER_H
#define __AL_OSAL_STREAMBUFFER_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef void * al_os_stream_t;

al_os_stream_t al_os_stream_create(size_t size, size_t level);

void al_os_stream_del(al_os_stream_t stream);

size_t al_os_stream_send(al_os_stream_t stream,
						 const void *data, size_t len, int_t timeout);

int_t al_os_stream_send_isr(al_os_stream_t stream,
							const void *data, size_t len, bool_t *yield);

size_t al_os_stream_recv(al_os_stream_t stream,
						void *buf, size_t size, int_t timeout);

int_t al_os_stream_recv_isr(al_os_stream_t stream,
							void *buf, size_t size, bool_t *yield);

bool_t al_os_stream_is_full(al_os_stream_t stream);

bool_t al_os_stream_is_empty(al_os_stream_t stream);

bool_t al_os_stream_reset(al_os_stream_t stream);

size_t al_os_stream_free_len(al_os_stream_t stream);

size_t al_os_stream_used_len(al_os_stream_t stream);

__END_DECLS

#endif

