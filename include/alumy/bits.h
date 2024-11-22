/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __AL_BITS_H
#define __AL_BITS_H 1

#include <string.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bitops/bitsperlong.h"

#define BIT(nr)         (1UL << (nr))
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define BIT_ULL_MASK(nr)    (1ULL << ((nr) % BITS_PER_LONG_LONG))
#define BIT_ULL_WORD(nr)    ((nr) / BITS_PER_LONG_LONG)
#define BITS_PER_BYTE       8

#define BITS_PER_TYPE(type) (sizeof(type) * BITS_PER_BYTE)
#define BITS_TO_LONGS(nr)   DIV_ROUND_UP(nr, BITS_PER_TYPE(long))
#define BITS_TO_U64(nr)     DIV_ROUND_UP(nr, BITS_PER_TYPE(u64))
#define BITS_TO_U32(nr)     DIV_ROUND_UP(nr, BITS_PER_TYPE(u32))
#define BITS_TO_BYTES(nr)   DIV_ROUND_UP(nr, BITS_PER_TYPE(char))

#define BYTES_TO_BITS(nb)   ((nb) * BITS_PER_BYTE)

#define GENMASK(h, l)   \
    (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#define GENMASK_ULL(h, l)   \
    (((~0ULL) - (1ULL << (l)) + 1) & (~0ULL >> (BITS_PER_LONG_LONG - 1 - (h))))

#endif  /* __LINUX_BITS_H */
