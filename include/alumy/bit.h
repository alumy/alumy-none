#ifndef __AL_BIT_H
#define __AL_BIT_H 1

#include <string.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bitops/bitops.h"

__BEGIN_DECLS

#ifndef BIT_COUNT
#define BIT_COUNT(x)			((x) << 3)
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

__static_inline__ int al_popcount(int x)
{
#if __has_builtin(__builtin_popcount)
	return __builtin_popcount(x);
#else
	x = x - ((x >> 1) & 0x55555555UL);
	x = (x & 0x33333333UL) + ((x >> 2) & 0x33333333UL);
	return (((x + (x >> 4)) & 0xf0f0f0fUL) * 0x1010101UL) >> 24;
#endif
}

__static_inline__ int al_popcountl(long x)
{
#if __has_builtin(__builtin_popcountl)
	return __builtin_popcountl(x);
#else
	x = x - ((x >> 1) & 0x55555555UL);
	x = (x & 0x33333333UL) + ((x >> 2) & 0x33333333UL);
	return (((x + (x >> 4)) & 0xf0f0f0fUL) * 0x1010101UL) >> 24;
#endif
}

__static_inline__ int al_popcountll(long long x)
{
#if __has_builtin(__builtin_popcountll)
	return __builtin_popcountll(x);
#else
	x = (x & 0x5555555555555555ULL) + ((x >>  1) & 0x5555555555555555ULL);
	x = (x & 0x3333333333333333ULL) + ((x >>  2) & 0x3333333333333333ULL);
	x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x >>  4) & 0x0F0F0F0F0F0F0F0FULL);
	return (x * 0x0101010101010101ULL) >> 56;
#endif
}

__static_inline__ int al_ctzll(long long x)
{
#if __has_builtin(__builtin_ctzll)
    return __builtin_ctzll(x);
#else
    int r = 63;
    x &= ~x + 1;
    if (x & 0x00000000FFFFFFFF) r -= 32;
    if (x & 0x0000FFFF0000FFFF) r -= 16;
    if (x & 0x00FF00FF00FF00FF) r -= 8;
    if (x & 0x0F0F0F0F0F0F0F0F) r -= 4;
    if (x & 0x3333333333333333) r -= 2;
    if (x & 0x5555555555555555) r -= 1;
    return r;
#endif
}

__static_inline__ int al_clzll(long long x)
{
#if __has_builtin(__builtin_clzll)
    return __builtin_clzll(x);
#else
    int r = 0;
    if (!(x & 0xFFFFFFFF00000000)) r += 32, x <<= 32;
    if (!(x & 0xFFFF000000000000)) r += 16, x <<= 16;
    if (!(x & 0xFF00000000000000)) r += 8,  x <<= 8;
    if (!(x & 0xF000000000000000)) r += 4,  x <<= 4;
    if (!(x & 0xC000000000000000)) r += 2,  x <<= 2;
    if (!(x & 0x8000000000000000)) r += 1,  x <<= 1;
    return r;
#endif
}

__static_inline__ int al_parity(long long x)
{
#if __has_builtin(__builtin_parity)
    return __builtin_parity(x);
#else
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    x ^= x >> 32;
    return x & 1;
#endif
}

/*
 * Find First Set bit
 */
__static_inline__ int al_ffsll(long long mask)
{
#if __has_builtin(__builtin_ffsll)
    return __builtin_ffsll(mask);
#elif __has_builtin(__builtin_ctzll)
    if (mask == 0)
        return (0);

    return __builtin_ctzll(mask) + 1;
#else
    int bit;

    if (mask == 0)
        return (0);
    for (bit = 1; !(mask & 1); bit++)
        mask = (unsigned long long)mask >> 1;
    return (bit);
#endif
}

__static_inline__ int al_ffsl(long mask)
{
#if __has_builtin(__builtin_ffsl)
    return __builtin_ffsl(mask);
#elif __has_builtin(__builtin_ctzl)
    if (mask == 0)
        return (0);

    return __builtin_ctzl(mask) + 1;
#else
    int bit;

    if (mask == 0)
        return (0);
    for (bit = 1; !(mask & 1); bit++)
        mask = (unsigned long)mask >> 1;
    return (bit);
#endif
}

__static_inline__ int al_ffs(int mask)
{
#if __has_builtin(__builtin_ffs)
    return __builtin_ffs(mask);
#elif __has_builtin(__builtin_ctz)
    if (mask == 0)
        return (0);

    return __builtin_ctz(mask) + 1;
#else
    int bit;

    if (mask == 0)
        return (0);
    for (bit = 1; !(mask & 1); bit++)
        mask = (unsigned)mask >> 1;
    return (bit);
#endif
}


/*
 * Find Last Set bit
 */
__static_inline__ int al_flsll(long long mask)
{
#if __has_builtin(__builtin_flsll)
    return __builtin_flsll(mask);
#elif __has_builtin(__builtin_clzll)
    if (mask == 0)
        return (0);

    return (sizeof(mask) << 3) - __builtin_clzll(mask);
#else
    int bit;

    if (mask == 0)
        return (0);
    for (bit = 1; mask != 1; bit++)
        mask = (unsigned long long)mask >> 1;
    return (bit);
#endif
}

__static_inline__ int al_flsl(long mask)
{
#if __has_builtin(__builtin_flsl)
    return __builtin_flsl(mask);
#elif __has_builtin(__builtin_clzl)
    if (mask == 0)
        return (0);

    return (sizeof(mask) << 3) - __builtin_clzl(mask);
#else
    int bit;

    if (mask == 0)
        return (0);
    for (bit = 1; mask != 1; bit++)
        mask = (unsigned long)mask >> 1;
    return (bit);
#endif
}

static __always_inline int al_fls(uint32_t x)
{
#if __has_builtin(__builtin_fls)
    return __builtin_fls(mask);
#elif __has_builtin(__builtin_clz)
    if (x == 0)
        return (0);

    return (sizeof(x) << 3) - __builtin_clz(x);
#else
    return generic_fls(x);
#endif
}

static __always_inline int al_fls64(uint64_t x)
{
    uint32_t h = x >> 32;
    if (h)
        return al_fls(h) + 32;
    return al_fls(x);
}

static inline unsigned int al_fls_long(unsigned long l)
{
    if (sizeof(l) == 4)
        return al_fls(l);
    return al_fls64(l);
}

__static_inline__ void al_bzero(void *s, size_t n)
{
    memset(s, 0, n);
}

__END_DECLS

#endif

