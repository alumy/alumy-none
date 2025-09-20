/**
 * @file    types.h
 * @author  jackchen
 * @version v0.0.1
 * @date    15-Jan-2019
 * @brief   Type definitions and utility macros for the alumy library
 * 
 * This header file provides essential type definitions, macros, and utility
 * functions for the alumy library. It includes standard integer types,
 * boolean types, size types, and various utility macros for min/max operations,
 * array size calculations, and container operations.
 * 
 * @copyright Copyright (c) 2019 alumy project
 * 
 */

#ifndef __AL_TYPES_H
#define __AL_TYPES_H 1

#include "alumy/config.h"
#include "alumy/typecheck.h"
#include "alumy/bits.h"

/* Include standard headers based on configuration */
#if AL_HAVE_STDINT
#include <stdint.h>
#endif

#if AL_HAVE_STDBOOL
#include <stdbool.h>
#endif

#if AL_HAVE_STDDEF
#include <stddef.h>
#endif

#if AL_HAVE_SYS_TYPES
#include <sys/types.h>
#endif

/* Inline function definitions for compatibility */
#ifndef __inline
#define __inline		inline
#endif

#ifndef __inline__
#define __inline__		__inline
#endif

#ifndef __static_inline__
#define __static_inline__		static __inline
#endif

/**
 * @brief Mark a variable as unused to suppress compiler warnings
 * @param v Variable to mark as unused
 */
#ifndef UNUSED
#define UNUSED(v)	(void)(v)
#endif

/**
 * @brief Get pointer to the container structure from a member pointer
 * @param ptr Pointer to the member
 * @param type Type of the container structure
 * @param member Name of the member within the container
 * @return Pointer to the container structure
 */
#ifndef container_of
#define container_of(ptr, type, member) ({					\
    const typeof(((type *)0)->member) *__mptr = (ptr);		\
    (type *)((void *)__mptr - offsetof(type, member)); })
#endif

/**
 * @brief Return minimum of two values (type-safe version for GCC)
 * @param x First value
 * @param y Second value
 * @return Minimum of x and y
 */
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

/**
 * @brief Return maximum of two values (type-safe version for GCC)
 * @param x First value
 * @param y Second value
 * @return Maximum of x and y
 */
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

/**
 * @brief Return minimum of three values
 * @param x First value
 * @param y Second value
 * @param z Third value
 * @return Minimum of x, y, and z
 */
#ifndef min3
#if defined(__GNUC__)
    #define min3(x, y, z) min((typeof(x))min((x), (y)), (z))
#elif defined(__CC_ARM)
    #define min3(x, y, z) min(min((x), (y)), (z))
#else
    #define min3(x, y, z) min(min((x), (y)), (z))
#endif
#endif

/**
 * @brief Return maximum of three values
 * @param x First value
 * @param y Second value
 * @param z Third value
 * @return Maximum of x, y, and z
 */
#ifndef max3
#if defined(__GNUC__)
    #define max3(x, y, z) max((typeof(x))max((x), (y)), (z))
#elif defined(__CC_ARM)
    #define max3(x, y, z) max(max((x), (y)), (z))
#else
    #define max3(x, y, z) max(max((x), (y)), (z))
#endif
#endif

/**
 * @brief Return minimum of two values with explicit type casting
 * @param type Type to cast values to
 * @param x First value
 * @param y Second value
 * @return Minimum of x and y, cast to specified type
 */
#define min_t(type, x, y) ({              \
    type __min1 = (x);                    \
    type __min2 = (y);                    \
    __min1 < __min2 ? __min1: __min2; })

/**
 * @brief Return maximum of two values with explicit type casting
 * @param type Type to cast values to
 * @param x First value
 * @param y Second value
 * @return Maximum of x and y, cast to specified type
 */
#define max_t(type, x, y) ({              \
    type __max1 = (x);                    \
    type __max2 = (y);                    \
    __max1 > __max2 ? __max1: __max2; })

/**
 * @brief Calculate number of elements in an array
 * @param a Array name
 * @return Number of elements in the array
 */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))
#endif

/**
 * @brief Round up division (kernel-style)
 * @param n Numerator
 * @param d Denominator
 * @return Result of (n + d - 1) / d
 */
#define __KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

/**
 * @brief Declare a bitmap with specified number of bits
 * @param name Name of the bitmap variable
 * @param bits Number of bits in the bitmap
 */
#define DECLARE_BITMAP(name,bits) \
    unsigned long name[BITS_TO_LONGS(bits)]

/* File offset type definition */
#if !(defined( __off_t_defined) || \
	  defined(__DEFINED_off_t))
typedef long int off_t;
#define __off_t_defined
#define __DEFINED_off_t
#endif

/* Compiler-specific type definitions for ARM Compiler */
#if defined(__CC_ARM)
	/** @brief Signed size type for ARM Compiler */
	#ifndef __ssize_t_defined
	typedef long ssize_t;
	#define __ssize_t_defined
	#endif

	/** @brief Signed integer type */
	#ifndef __int_t_defined
	typedef signed int int_t;
	#define __int_t_defined
	#endif

	/** @brief Unsigned integer type */
	#ifndef __uint_t_defined
	typedef unsigned int uint_t;
	#define __uint_t_defined
	#endif
#endif

/* Compiler-specific type definitions for IAR RL78 */
#if defined(__ICCRL78__)
	/** @brief Signed size type for IAR RL78 (16-bit) */
	#ifndef __ssize_t_defined
	typedef signed short ssize_t;
	#define __ssize_t_defined
	#endif

	/** @brief Signed integer type */
	#ifndef __int_t_defined
	typedef signed int int_t;
	#define __int_t_defined
	#endif

	/** @brief Unsigned integer type */
	#ifndef __uint_t_defined
	typedef unsigned int uint_t;
	#define __uint_t_defined
	#endif
#endif

/* Compiler-specific type definitions for GCC */
#if defined(__GNUC__)
    /** @brief Signed size type for GCC with multiple guard macros */
    #if !(defined(__ssize_t_defined) || \
          defined(_SSIZE_T_DECLARED) || \
          defined(_SSIZE_T_DEFINED) || \
          defined(__DEFINED_ssize_t))
        typedef long ssize_t;
        #define __ssize_t_defined
        #define __DEFINED_ssize_t
        #define _SSIZE_T_DECLARED
        #define _SSIZE_T_DEFINED
        
        /** @brief Maximum value for ssize_t */
        #ifndef SSIZE_MAX
            #define SSIZE_MAX INT_MAX
        #endif
    #endif

	/** @brief Signed integer type */
	#ifndef __int_t_defined
	typedef signed int int_t;
	#define __int_t_defined
	#endif

	/** @brief Unsigned integer type */
	#ifndef __uint_t_defined
	typedef unsigned int uint_t;
	#define __uint_t_defined
	#endif
#endif

/** @brief Boolean type definition */
#ifndef __bool_t_defined
typedef uint_t bool_t;
#define __bool_t_defined
#endif

/** @brief Character type definition */
#ifndef __char_t_defined
typedef char char_t;
#define __char_t_defined
#endif

/* Short unsigned integer types */
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/* Double underscore variants for kernel compatibility */
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;

/* BSD-style type definitions */
typedef unsigned char       u_char;
typedef unsigned short      u_short;
typedef unsigned int        u_int;
typedef unsigned long       u_long;

/* System V style type definitions */
typedef unsigned char       unchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;

#endif	/* end of __AL_TYPES_H */
