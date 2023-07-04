#ifndef __AL_NET_INET_ADDR_H
#define __AL_NET_INET_ADDR_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS

typedef uint32_t al_in_addr_t;

__static_inline__ __attribute_const__
al_in_addr_t al_in_addr_combine(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	al_in_addr_t in_addr = ((((uint32_t)a << 24) & 0xFF000000ul) |
						    (((uint32_t)b << 16) & 0x00FF0000ul) |
						    (((uint32_t)c << 8) & 0x0000FF00ul) |
						    ((uint32_t)d & 0x000000FFul));
	return in_addr;
}

__static_inline__
void al_in_addr_split(uint8_t *a, uint8_t *b,uint8_t *c,uint8_t *d,
					  al_in_addr_t in_addr)
{
	*a = (in_addr & 0xFF000000ul) >> 24;
	*b = (in_addr & 0x00FF0000ul) >> 16;
	*c = (in_addr & 0x0000FF00ul) >> 8;
	*d = (in_addr & 0x000000FFul);
}

__END_DECLS

#endif

