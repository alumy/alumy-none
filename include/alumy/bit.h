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
#define set_bit(reg, bit)       ((reg) |= (1u << (bit)))
#endif

#ifndef clear_bit
#define clear_bit(reg, bit)     ((reg) &= ~(1u << (bit)))
#endif

#ifndef get_bit
#define get_bit(reg, bit)       (!!((reg) & (1u << (bit))))
#endif

#ifndef toggle_bit
#define toggle_bit(reg, bit)	((reg) ^= (1u << (bit)))
#endif

#ifndef set_bit_64
#define set_bit_64(reg, bit)		((reg) |= (1ull << (bit)))
#endif

#ifndef clear_bit_64
#define clear_bit_64(reg, bit)		((reg) &= ~(1ull << (bit)))
#endif

#ifndef get_bit_64
#define get_bit_64(reg, bit)		(!!((reg) & (1ull << (bit))))
#endif

#ifndef toggle_bit_64
#define toggle_bit_64(reg, bit)	((reg) ^= (1ull << (bit)))
#endif

__static_inline__ uint32_t al_popcount(uint32_t x)
{
#if (defined(__GNUC__) || defined(__clang__))
	return __builtin_popcount(x);
#else
	x = x - ((x >> 1) & 0x55555555UL);
	x = (x & 0x33333333UL) + ((x >> 2) & 0x33333333UL);
	return (((x + (x >> 4)) & 0xf0f0f0fUL) * 0x1010101UL) >> 24;
#endif
}

__static_inline__ uint32_t al_popcountl(uint32_t x)
{
#if (defined(__GNUC__) || defined(__clang__))
	return __builtin_popcountl(x);
#else
	x = x - ((x >> 1) & 0x55555555UL);
	x = (x & 0x33333333UL) + ((x >> 2) & 0x33333333UL);
	return (((x + (x >> 4)) & 0xf0f0f0fUL) * 0x1010101UL) >> 24;
#endif
}

__static_inline__ uint32_t al_popcountll(uint64_t x)
{
#if (defined(__GNUC__) || defined(__clang__))
	return __builtin_popcountll(x);
#else
	x = (x & 0x5555555555555555ULL) + ((x >>  1) & 0x5555555555555555ULL);
	x = (x & 0x3333333333333333ULL) + ((x >>  2) & 0x3333333333333333ULL);
	x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x >>  4) & 0x0F0F0F0F0F0F0F0FULL);
	return (x * 0x0101010101010101ULL) >> 56;
#endif
}

__END_DECLS

#endif

