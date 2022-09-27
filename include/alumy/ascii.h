#ifndef __ASCII_H
#define __ASCII_H 1

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#ifndef SOH
#define SOH		0x01
#endif

#ifndef STX
#define STX		0x02
#endif

#ifndef ETX
#define ETX		0x03
#endif

#ifndef EOT
#define EOT		0x04
#endif

#ifndef ACK
#define ACK		0x06
#endif

#ifndef NAK
#define NAK		0x15
#endif

#ifndef CAN
#define CAN		0x18
#endif

#ifndef EOF
#define EOF		(-1)
#endif

extern const char al_hex_asc_tab[];

__static_inline__ __attribute_const__ uint8_t al_hex2asc(uint8_t value)
{
	return al_hex_asc_tab[value & 0x0F];
}

__END_DECLS

#endif

