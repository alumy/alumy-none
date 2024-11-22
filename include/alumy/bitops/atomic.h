/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __AL_BITOPS_ATOMIC_H
#define __AL_BITOPS_ATOMIC_H 1

#include "alumy/bitops/bitsperlong.h"

static inline int test_and_set_bit(long nr, unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    long old;

    addr += BIT_WORD(nr);

    old = *addr;
    *addr = old | mask;

    return !!(old & mask);
}

static inline int test_and_clear_bit(long nr, unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    long old;

    addr += BIT_WORD(nr);

    old = *addr;
    *addr = old & ~mask;

    return !!(old & mask);
}

/*
 * Just alias the test versions, all of the compiler built-in atomics "fetch",
 * and optimizing compile-time constants on x86 isn't worth the complexity.
 */
#define set_bit test_and_set_bit
#define clear_bit test_and_clear_bit

#endif /* __AL_BITOPS_ATOMIC_H */
