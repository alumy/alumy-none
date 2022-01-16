#ifndef __AL_BASE__
#define __AL_BASE__ 1

#if AL_HAVE_SYS_CDEFS
#include <sys/cdefs.h>
#else
#include "alumy/cdefs.h"
#endif


#if  defined ( __GNUC__ ) || defined ( __clang__ )

  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */

  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */

  #ifndef __used
    #define __used    __attribute__((unused))
  #endif /* __used */

  #ifndef __aligned
    #define __aligned(x)    __attribute__((aligned(x)))
  #endif

  #ifndef __attribute_const__
    #define __attribute_const__     __attribute__((__const__))
  #endif

  #ifndef __deprecated
    #define __deprecated		__attribute__((deprecated))
  #endif

  #define __naked				__attribute__((naked)) noinline __noclone notrace
  #define __noreturn			__attribute__((noreturn))


  #ifndef __printf
    #define __printf(a,b)		__attribute__((format(printf,a,b)))
  #endif

  #ifndef __scanf
    #define __scanf(a,b)		__attribute__((format(scanf,a,b)))
  #endif

  #ifndef __maybe_unused
    #define __maybe_unused		__attribute__((unused))
  #endif

  #ifndef __always_unused
    #define __always_unused		__attribute__((unused))
  #endif

  #ifndef __always_inline
    #define __always_inline     __attribute__((always_inline))
  #endif

  #ifndef __section
    #define __section(sec)      __attribute__((used, section(sec)))
  #endif

  #ifndef __unlikely
    #define __unlikely(cond)	__glibc_unlikely(cond)
  #endif

  #ifndef __likely
    #define __likely(cond)		__glibc_likely(cond)
  #endif

#endif /* __GNUC__ */

#if defined (__CC_ARM)

  #ifndef __packed
    #define __packed __attribute__((packed))
  #endif /* __packed */

  #ifndef __used
    #define __used    __attribute__((unused))
  #endif /* __used */

  #ifndef __maybe_unused
    #define __maybe_unused		__attribute__((unused))
  #endif

  #ifndef __always_unused
    #define __always_unused		__attribute__((unused))
  #endif

  #ifndef __always_inline
    #define __always_inline     __attribute__((always_inline))
  #endif

  #ifndef __aligned
    #define __aligned(x)    __attribute__((aligned(x)))
  #endif

  #ifndef __noinit
    #define __noinit        __attribute__((zero_init))
  #endif

  #ifndef __section
    #define __section(sec)  __attribute__((used, section(sec)))
  #endif

  #ifndef __attribute_const__
    #define __attribute_const__     __attribute__((__const__))
  #endif
#endif /* __CC_ARM */

#ifndef __STRING
#define __STRING(x) #x
#endif

#ifndef __MS
#define __MS(x)		__STRING(x)
#endif

#ifndef __ES
#define __ES(v)		[v] = __STRING(v)
#endif

#endif

