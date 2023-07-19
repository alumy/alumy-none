#ifndef __ASCII_H
#define __ASCII_H 1

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#ifndef AL_SOH
#define AL_SOH		0x01
#endif

#ifndef AL_STX
#define AL_STX		0x02
#endif

#ifndef AL_ETX
#define AL_ETX		0x03
#endif

#ifndef AL_EOT
#define AL_EOT		0x04
#endif

#ifndef AL_ACK
#define AL_ACK		0x06
#endif

#ifndef AL_NAK
#define AL_NAK		0x15
#endif

#ifndef AL_CAN
#define AL_CAN		0x18
#endif

#ifndef AL_EOF
#define AL_EOF		(-1)
#endif

extern uint8_t al_hex2asc(uint8_t value);

__END_DECLS

#endif

