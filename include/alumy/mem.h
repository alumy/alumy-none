/**
 * @file    mem.h
 * @author  alumy project
 * @version v0.0.1
 * @brief   Memory utilities and alignment macros for the alumy library
 * 
 * This header file provides memory-related utilities including alignment macros,
 * pointer manipulation functions, and memory checking utilities. These utilities
 * are designed to provide efficient and portable memory operations across
 * different platforms and architectures.
 * 
 * @copyright Copyright (c) 2019 alumy project
 */

#ifndef __AL_MEM_H
#define __AL_MEM_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/** @brief Operation type for optimized memory operations */
#ifndef op_t
#define op_t	uintptr_t
#endif

/** @brief Size of operation type in bytes */
#ifndef OPSIZ
#define OPSIZ	(sizeof(op_t))
#endif

/** @brief Threshold for using optimized operations */
#ifndef OP_T_THRES
#define OP_T_THRES	16
#endif

/**
 * REPEAT_BYTE - repeat the value @x multiple times as an unsigned long value
 * @x: value to repeat
 *
 * NOTE: @x is not checked for > 0xff; larger values produce odd results.
 */
#ifndef REPEAT_BYTE
#define REPEAT_BYTE(x)	((~0ul / 0xff) * (x))
#endif

/** @brief Align a value to the specified alignment mask */
#define AL_ALIGN_MASK(x, mask)	(((x) + (mask)) & ~(mask))

/** @brief Align a pointer to the specified alignment */
#define AL_PTR_ALIGN(p, a)		((typeof(p))AL_ALIGN((uintptr_t)(p), (a)))

/** @brief Align a value up to the next alignment boundary */
#ifndef AL_ALIGN
#if defined(__GNUC__)
    #define AL_ALIGN(x, a)      AL_ALIGN_MASK((x), (typeof(x))(a) - 1)
#else
    #define AL_ALIGN(x, a)      AL_ALIGN_MASK((x), (a) - 1)
#endif
#endif

/** @brief Check if a value is aligned to the specified alignment */
#ifndef AL_IS_ALIGNED
#if defined(__GNUC__)
    #define AL_IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)
#else
    #define AL_IS_ALIGNED(x, a)     \
        (((uintptr_t)(x) & ((uintptr_t)(a) - 1)) == 0)
#endif
#endif

/** @brief Align a value down to the previous alignment boundary */
#define AL_ALIGN_DOWN(x, a)		AL_ALIGN((x) - ((a) - 1), (a))

/** @brief Check if memory access would overflow the specified bounds */
#define al_mem_is_overflow(addr, len, start, end)   \
        (!(((addr) >= (start)) && ((addr) + (len) <= (end))))

/**
 * @brief Check if the buffer is filled with the specified value
 *
 * This function examines a memory buffer to determine if all bytes
 * contain the same specified value. It's useful for verifying memory
 * initialization or pattern matching.
 *
 * @author jack (5/15/2018)
 *
 * @param buf The buffer to check
 * @param c The specified value to compare against
 * @param len The length of the buffer to check in bytes
 *
 * @return bool Return true if all bytes of the buffer are filled
 *              with the specified value, otherwise return false
 */
bool al_mem_is_filled(const void *buf, uint_fast8_t c, size_t len);

__END_DECLS

#endif
