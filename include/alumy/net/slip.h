#ifndef __AL_NET_SLIP_H
#define __AL_NET_SLIP_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS

typedef struct al_slip_opt {
	int_t (*sl_putc)(int_t c);
	int_t (*sl_getc)(void);
} al_slip_opt_t;

typedef struct al_slip {
	void *recv_buf;
	size_t recv_size;

	uintptr_t recv_wp;
	size_t recv_len;
	int_t recv_state;

	al_slip_opt_t opt;
} al_slip_t;

int_t al_slip_init(al_slip_t *slip, void *recv_buf, size_t recv_size,
				   const al_slip_opt_t *opt);

size_t al_slip_write(al_slip_t *slip, const void *data, size_t len);

size_t al_slip_recv(al_slip_t *slip);

void *al_slip_get_recv(al_slip_t *slip);

__END_DECLS

#endif

