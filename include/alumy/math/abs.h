#ifndef __AL_MATH_ABS_H
#define __AL_MATH_ABS_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

__static_inline__ int al_abs(int x)
{
#if defined(__SIZEOF_INT__) && (__SIZEOF_INT__ == 2)
	return x ^ (x >> 15) - (x >> 15);
#elif defined(__SIZEOF_INT__) && (__SIZEOF_INT__ == 4)
    return x ^ (x >> 31) - (x >> 31);
#else
	#error "__SIZEOF_INT__ is not unknown"
#endif
}

__static_inline__ long al_labs(long x)
{
	return x ^ (x >> 31) - (x >> 31);
}

__static_inline__ long long al_llabs(long long x)
{
	return x ^ (x >> 63) - (x >> 63);
}

__END_DECLS

#endif

