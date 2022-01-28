#ifndef __AL_MEM_H
#define __AL_MEM_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#ifndef op_t
#define op_t	uintptr_t
#endif

#ifndef OPSIZ
#define OPSIZ	(sizeof(op_t))
#endif

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

#define AL_ALIGN_MASK(x, mask)	(((x) + (mask)) & ~(mask))

#define AL_PTR_ALIGN(p, a)		((typeof(p))AL_ALIGN((uintptr_t)(p), (a)))

#ifndef AL_ALIGN
#if defined(__GNUC__)
    #define AL_ALIGN(x, a)      AL_ALIGN_MASK((x), (typeof(x))(a) - 1)
#else
    #define AL_ALIGN(x, a)      AL_ALIGN_MASK((x), (a) - 1)
#endif
#endif

#ifndef AL_IS_ALIGNED
#if defined(__GNUC__)
    #define AL_IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)
#else
    #define AL_IS_ALIGNED(x, a)     \
        (((uintptr_t)(x) & ((uintptr_t)(a) - 1)) == 0)
#endif
#endif

#define AL_ALIGN_DOWN(x, a)		AL_ALIGN((x) - ((a) - 1), (a))


__static_inline__ bool al_mem_is_overflow(
    uintptr_t addr, size_t len, uintptr_t start, uintptr_t end)
{
    return !((addr >= start) && (addr + len <= end));
}

/**
 * @brief Check if the buffer is filled with the specified value
 *
 * @author jack (5/15/2018)
 *
 * @param buf The buffer to check
 * @param c The specified value
 * @param len The length to check
 *
 * @return bool Return true if all bytes of the buffer is filled
 *  	   with the specified value, otherwise return false
 */
bool al_mem_is_filled(const void *buf, uint_fast8_t c, size_t len);

__END_DECLS

#endif
