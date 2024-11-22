#ifndef __AL_BITOPS_BITS_PER_LONG_H
#define __AL_BITOPS_BITS_PER_LONG_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#if defined(__LONG_WIDTH__) && (__LONG_WIDTH__ == 64)
#define BITS_PER_LONG 64
#elif defined(__SIZEOF_LONG__) && (__SIZEOF_LONG__ == 8)
#define BITS_PER_LONG 64
#elif defined(__LONG_WIDTH__) && (__LONG_WIDTH__ == 32)
#define BITS_PER_LONG 32
#elif defined(__SIZEOF_LONG__) && (__SIZEOF_LONG__ == 4)
#define BITS_PER_LONG 32
#else
#define BITS_PER_LONG   __BITS_PER_LONG
#endif

#ifndef BITS_PER_LONG_LONG
#define BITS_PER_LONG_LONG 64
#endif

/*
 * small_const_nbits(n) is true precisely when it is known at compile-time
 * that BITMAP_SIZE(n) is 1, i.e. 1 <= n <= BITS_PER_LONG. This allows
 * various bit/bitmap APIs to provide a fast inline implementation. Bitmaps
 * of size 0 are very rare, and a compile-time-known-size 0 is most likely
 * a sign of error. They will be handled correctly by the bit/bitmap APIs,
 * but using the out-of-line functions, so that the inline implementations
 * can unconditionally dereference the pointer(s).
 */
#define small_const_nbits(nbits) \
    (__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG && (nbits) > 0)

__END_DECLS

#endif
