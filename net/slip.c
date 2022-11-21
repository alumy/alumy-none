#include <stdio.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/check.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/net/slip.h"

__BEGIN_DECLS

#define SLIP_END     0xC0 /* 0300: start and end of every packet */
#define SLIP_ESC     0xDB /* 0333: escape start (one byte escaped data follows) */
#define SLIP_ESC_END 0xDC /* 0334: following escape: original byte is 0xC0 (END) */
#define SLIP_ESC_ESC 0xDD /* 0335: following escape: original byte is 0xDB (ESC) */

enum {
  SLIP_RECV_NORMAL,
  SLIP_RECV_ESCAPE
};

int_t al_slip_init(al_slip_t *slip, void *recv_buf, size_t recv_size,
				   const al_slip_opt_t *opt)
{
	AL_CHECK_RET(slip != NULL, EINVAL, -1);
	AL_CHECK_RET(recv_buf != NULL, EINVAL, -1);
	AL_CHECK_RET(recv_size > 0, EINVAL, -1);
	AL_CHECK_RET(opt != NULL, EINVAL, -1);
	AL_CHECK_RET(opt->sl_putc != NULL, EINVAL, -1);
	AL_CHECK_RET(opt->sl_getc != NULL, EINVAL, -1);

	slip->recv_len = 0;
	slip->recv_wp = 0;
	slip->recv_state = SLIP_RECV_NORMAL;

	slip->recv_buf = recv_buf;
	slip->recv_size = recv_size;

	slip->opt.sl_getc = opt->sl_getc;
	slip->opt.sl_putc = opt->sl_putc;

	return 0;
}

size_t al_slip_write(al_slip_t *slip, const void *data, size_t len)
{
	size_t i;
	int_t c;

	/* Start with packet delimiter. */
	slip->opt.sl_putc(SLIP_END);

	for (i = 0; i < len; i++) {
		c = ((const uint8_t *)data)[i];

		switch (c) {
		case SLIP_END:
			/* need to escape this byte (0xC0 -> 0xDB, 0xDC) */
			slip->opt.sl_putc(SLIP_ESC);
			slip->opt.sl_putc(SLIP_ESC_END);
			break;
		case SLIP_ESC:
			/* need to escape this byte (0xDB -> 0xDB, 0xDD) */
			slip->opt.sl_putc(SLIP_ESC);
			slip->opt.sl_putc(SLIP_ESC_ESC);
			break;
		default:
			/* normal byte - no need for escaping */
			slip->opt.sl_putc(c);
			break;
		}
	}

	/* End with packet delimiter. */
	slip->opt.sl_putc(SLIP_END);

	set_errno(0);
	return len;
}

__static_inline__ size_t al_slip_recv_byte(al_slip_t *slip, int_t c)
{
	size_t recv_len = 0;

	switch (slip->recv_state) {
	case SLIP_RECV_NORMAL:
		switch (c) {
		case SLIP_END:
			if (slip->recv_len > 0) {
				recv_len = slip->recv_len;

				slip->recv_len = 0;
				slip->recv_wp = 0;

				return recv_len;
			}

			return 0;

		case SLIP_ESC:
			slip->recv_state = SLIP_RECV_ESCAPE;
			return 0;

		default:
			break;
		}

		break;

	case SLIP_RECV_ESCAPE:
		switch (c) {
		case SLIP_ESC_END:
			c = SLIP_END;
			break;
		case SLIP_ESC_ESC:
			c = SLIP_ESC;
			break;
		default:
			break;
		}

		slip->recv_state = SLIP_RECV_NORMAL;
		break;

	default:
		break;
	}

	if (slip->recv_len <= slip->recv_size) {
		((uint8_t *)slip->recv_buf)[slip->recv_wp] = c;

		slip->recv_len++;
		slip->recv_wp++;
	}

	return 0;
}

size_t al_slip_recv(al_slip_t *slip)
{
	int_t c;
	size_t len;

	do {
		c = slip->opt.sl_getc();
		len = al_slip_recv_byte(slip, c);
	} while ((c != EOF) && (len == 0));

	return len;
}

void *al_slip_get_recv(al_slip_t *slip)
{
	return slip->recv_buf;
}

size_t al_slip_get_recv_len(al_slip_t *slip)
{
	return slip->recv_len;
}

__END_DECLS

