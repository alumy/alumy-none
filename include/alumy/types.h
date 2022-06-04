#ifndef __AL_TYPES_H
#define __AL_TYPES_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if AL_HAVE_SYS_TYPES
#include <sys/types.h>
#endif

#ifndef __inline
#define __inline		inline
#endif

#ifndef __inline__
#define __inline__		__inline
#endif

#ifndef __static_inline__
#define __static_inline__		static __inline
#endif

#ifndef UNUSED
#define UNUSED(v)	(void)(v)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({		\
	const typeof(((type *)0)->member) * __mptr = (ptr);		\
	(type *)((uintptr_t)__mptr - offsetof(type, member)); })
#endif

#ifndef min
#if defined(__GNUC__)
    #define min(x,y) ({             \
        typeof(x) _x = (x);         \
        typeof(y) _y = (y);         \
        (void) (&_x == &_y);        \
        _x < _y ? _x : _y; })
#elif defined(__CC_ARM)
    #define min(x,y)        ((x) < (y) ? (x) : (y))
#else
    #define min(x,y)        ((x) < (y) ? (x) : (y))
#endif
#endif

#ifndef max
#if defined(__GNUC__)
    #define max(x,y) ({             \
        typeof(x) _x = (x);         \
        typeof(y) _y = (y);         \
        (void) (&_x == &_y);        \
        _x > _y ? _x : _y; })
#elif defined(__CC_ARM)
    #define max(x,y)        ((x) > (y) ? (x) : (y))
#else
    #define max(x,y)        ((x) > (y) ? (x) : (y))
#endif
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))
#endif

#ifndef is_power_of_2
#define is_power_of_2(x)        ((x) != 0 && (((x) & ((x) - 1)) == 0))
#endif

#ifndef __off_t_defined
typedef long int off_t;
#define __off_t_defined
#endif

#if defined(__CC_ARM)
	#ifndef __ssize_t_defined
	typedef long ssize_t;
	#define __ssize_t_defined
	#endif
#endif

#if defined(__GNUC__)
        #if !(defined(__ssize_t_defined) || \
              defined(_SSIZE_T_DECLARED) || \
              defined(_SSIZE_T_DEFINED))
	typedef long ssize_t;
	#define __ssize_t_defined
	#endif
#endif

#endif	/* end of _TYPES_H */

