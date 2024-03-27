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

__static_inline__ __attribute_const__ char al_hex2asc(uint8_t value)
{
    static const char al_hex_asc_tab[16] = "0123456789ABCDEF";

    if (__likely(value < ARRAY_SIZE(al_hex_asc_tab))) {
        return al_hex_asc_tab[value];
    }

    return 0;
}

__static_inline__ __attribute_const__ uint8_t al_asc2hex(char asc)
{
    static const uint8_t al_asc_hex_tab[128] = {
        ['0'] = 0x00, ['1'] = 0x01, ['2'] = 0x02, ['3'] = 0x03,
        ['4'] = 0x04, ['5'] = 0x05, ['6'] = 0x06, ['7'] = 0x07,
        ['8'] = 0x08, ['9'] = 0x09, ['A'] = 0x0A, ['B'] = 0x0B,
        ['C'] = 0x0C, ['D'] = 0x0D, ['E'] = 0x0E, ['F'] = 0x0F,
        ['a'] = 0x0A, ['b'] = 0x0B, ['c'] = 0x0C, ['d'] = 0x0D,
        ['e'] = 0x0E, ['f'] = 0x0F,
    };

    uint_t off = asc;

    if (__likely(off < ARRAY_SIZE(al_asc_hex_tab))) {
        return al_asc_hex_tab[off];
    }

    return 0;
}

__END_DECLS

#endif

