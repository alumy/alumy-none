#ifndef __AL_BIT_H
#define __AL_BIT_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#ifndef BIT_COUNT
#define BIT_COUNT(x)			((x) << 3)
#endif

#ifndef BIT
#define BIT(x)					(1u << (x))
#endif

#ifndef set_bit
#define set_bit(reg, bit)       ((reg) |= (1ul << (bit)))
#endif

#ifndef clear_bit
#define clear_bit(reg, bit)     ((reg) &= ~(1ul << (bit)))
#endif

#ifndef get_bit
#define get_bit(reg, bit)       (!!((reg) & (1ul << (bit))))
#endif

#ifndef toggle_bit
#define toggle_bit(reg, bit)	((reg) ^= (1ul << (bit)))
#endif

__static_inline__ uint32_t al_popcount(uint32_t a)
{
#if (defined(__GNUC__) || defined(__CC_ARM))
    return __builtin_popcount(a);
#else
    a = a - ((a >> 1) & 0x55555555);
    a = (a & 0x33333333) + ((a >> 2) & 0x33333333);
    return (((a + (a >> 4)) & 0xf0f0f0f) * 0x1010101) >> 24;
#endif
}

__END_DECLS

#endif

