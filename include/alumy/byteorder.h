#ifndef __AL_BYTE_ORDER_H
#define __AL_BYTE_ORDER_H 1

#undef __LITTLE_ENDIAN
#undef __BIG_ENDIAN

#ifdef __GNUC__
	#define __LITTLE_ENDIAN		__ORDER_LITTLE_ENDIAN__
	#define __BIG_ENDIAN		__ORDER_BIG_ENDIAN__
#endif /* __GNUC__ */

#ifndef __LITTLE_ENDIAN
    #define __LITTLE_ENDIAN 1234
#endif

#ifndef __BIG_ENDIAN
    #define __BIG_ENDIAN 4321
#endif

#if !defined(__BYTE_ORDER) || \
    ((__BYTE_ORDER != __LITTLE_ENDIAN) && (__BYTE_ORDER != __BIG_ENDIAN))
    #error "__BYTE_ORDER is undefined"
#endif

#endif
