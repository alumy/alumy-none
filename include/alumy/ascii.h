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

extern uint8_t al_hex2asc(uint8_t value);

__END_DECLS

#endif

