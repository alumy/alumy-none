#ifndef __AL_BITS_LATENCY_H
#define __AL_BITS_LATENCY_H 1

#include <string.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bitops/bitops.h"

__BEGIN_DECLS

#ifndef BIT_COUNT
#define BIT_COUNT(x)            BYTES_TO_BITS((x))
#endif

#ifndef al_set_bit
#define al_set_bit(reg, bit)       ((reg) |= (1u << (bit)))
#endif

#ifndef al_clear_bit
#define al_clear_bit(reg, bit)     ((reg) &= ~(1u << (bit)))
#endif

#ifndef al_get_bit
#define al_get_bit(reg, bit)       (!!((reg) & (1u << (bit))))
#endif

#ifndef al_toggle_bit
#define al_toggle_bit(reg, bit)    ((reg) ^= (1u << (bit)))
#endif

#ifndef al_set_bit_64
#define al_set_bit_64(reg, bit)        ((reg) |= (1ull << (bit)))
#endif

#ifndef al_clear_bit_64
#define al_clear_bit_64(reg, bit)      ((reg) &= ~(1ull << (bit)))
#endif

#ifndef al_get_bit_64
#define al_get_bit_64(reg, bit)        (!!((reg) & (1ull << (bit))))
#endif

#ifndef al_toggle_bit_64
#define al_toggle_bit_64(reg, bit) ((reg) ^= (1ull << (bit)))
#endif

__END_DECLS

#endif

