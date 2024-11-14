#ifndef __AL_BITOPTS_BIT_REVERSE_H
#define __AL_BITOPTS_BIT_REVERSE_H 1

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

__static_inline__ __always_inline
uint32_t u32_bit_reverse(register uint32_t x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));

    return ((x >> 16) | (x << 16));
}

__END_DECLS

#endif


