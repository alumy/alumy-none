#ifndef __AL_BITOPS_BITOPS_H
#define __AL_BITOPS_BITOPS_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bits.h"
#include "alumy/bitops/bitsperlong.h"
#include "alumy/bitops/__ffs.h"
#include "alumy/bitops/__fls.h"
#include "alumy/bitops/ffs.h"
#include "alumy/bitops/ffz.h"
#include "alumy/bitops/fls.h"
#include "alumy/bitops/fls64.h"
#include "alumy/bitops/const_hweight.h"

__BEGIN_DECLS

extern unsigned int __sw_hweight8(unsigned int w);
extern unsigned int __sw_hweight16(unsigned int w);
extern unsigned int __sw_hweight32(unsigned int w);
extern unsigned long __sw_hweight64(uint64_t w);

#include "alumy/bitops/generic-non-atomic.h"
#include "alumy/bitops/arch_hweight.h"
#include "alumy/bitops/non-atomic.h"
#include "alumy/bitops/atomic.h"

/*
 * Many architecture-specific non-atomic bitops contain inline asm code and due
 * to that the compiler can't optimize them to compile-time expressions or
 * constants. In contrary, generic_*() helpers are defined in pure C and
 * compilers optimize them just well.
 * Therefore, to make `unsigned long foo = 0; __set_bit(BAR, &foo)` effectively
 * equal to `unsigned long foo = BIT(BAR)`, pick the generic C alternative when
 * the arguments can be resolved at compile time. That expression itself is a
 * constant and doesn't bring any functional changes to the rest of cases.
 * The casts to `uintptr_t` are needed to mitigate `-Waddress` warnings when
 * passing a bitmap from .bss or .data (-> `!!addr` is always true).
 */
#define bitop(op, nr, addr)                     \
    ((__builtin_constant_p(nr) &&                   \
      __builtin_constant_p((uintptr_t)(addr) != (uintptr_t)NULL) && \
      (uintptr_t)(addr) != (uintptr_t)NULL &&           \
      __builtin_constant_p(*(const unsigned long *)(addr))) ?   \
     const##op(nr, addr) : op(nr, addr))

/*
 * The following macros are non-atomic versions of their non-underscored
 * counterparts.
 */
#define __set_bit(nr, addr)     bitop(___set_bit, nr, addr)
#define __clear_bit(nr, addr)       bitop(___clear_bit, nr, addr)
#define __change_bit(nr, addr)      bitop(___change_bit, nr, addr)
#define __test_and_set_bit(nr, addr)    bitop(___test_and_set_bit, nr, addr)
#define __test_and_clear_bit(nr, addr)  bitop(___test_and_clear_bit, nr, addr)
#define __test_and_change_bit(nr, addr) bitop(___test_and_change_bit, nr, addr)

#define test_bit(nr, addr)      bitop(_test_bit, nr, addr)
#define test_bit_acquire(nr, addr)  bitop(_test_bit_acquire, nr, addr)

static inline int get_bitmask_order(unsigned int count)
{
    int order;

    order = fls(count);
    return order;   /* We could be slightly more clever with -1 here... */
}

static __always_inline unsigned long hweight_long(unsigned long w)
{
    return sizeof(w) == 4 ? hweight32(w) : hweight64((uint64_t)w);
}

/**
 * rol64 - rotate a 64-bit value left
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint64_t rol64(uint64_t word, unsigned int shift)
{
    return (word << (shift & 63)) | (word >> ((-shift) & 63));
}

/**
 * ror64 - rotate a 64-bit value right
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint64_t ror64(uint64_t word, unsigned int shift)
{
    return (word >> (shift & 63)) | (word << ((-shift) & 63));
}

/**
 * rol32 - rotate a 32-bit value left
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint32_t rol32(uint32_t word, unsigned int shift)
{
    return (word << (shift & 31)) | (word >> ((-shift) & 31));
}

/**
 * ror32 - rotate a 32-bit value right
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint32_t ror32(uint32_t word, unsigned int shift)
{
    return (word >> (shift & 31)) | (word << ((-shift) & 31));
}

/**
 * rol16 - rotate a 16-bit value left
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint16_t rol16(uint16_t word, unsigned int shift)
{
    return (word << (shift & 15)) | (word >> ((-shift) & 15));
}

/**
 * ror16 - rotate a 16-bit value right
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint16_t ror16(uint16_t word, unsigned int shift)
{
    return (word >> (shift & 15)) | (word << ((-shift) & 15));
}

/**
 * rol8 - rotate an 8-bit value left
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint8_t rol8(uint8_t word, unsigned int shift)
{
    return (word << (shift & 7)) | (word >> ((-shift) & 7));
}

/**
 * ror8 - rotate an 8-bit value right
 * @word: value to rotate
 * @shift: bits to roll
 */
static inline uint8_t ror8(uint8_t word, unsigned int shift)
{
    return (word >> (shift & 7)) | (word << ((-shift) & 7));
}

/**
 * sign_extend32 - sign extend a 32-bit value using specified bit as sign-bit
 * @value: value to sign extend
 * @index: 0 based bit index (0<=index<32) to sign bit
 *
 * This is safe to use for 16- and 8-bit types as well.
 */
static __always_inline uint32_t sign_extend32(uint32_t value, int index)
{
    uint8_t shift = 31 - index;
    return (uint32_t)(value << shift) >> shift;
}

/**
 * sign_extend64 - sign extend a 64-bit value using specified bit as sign-bit
 * @value: value to sign extend
 * @index: 0 based bit index (0<=index<64) to sign bit
 */
static __always_inline int64_t sign_extend64(uint64_t value, int index)
{
    uint8_t shift = 63 - index;
    return (int64_t)(value << shift) >> shift;
}

static inline unsigned int fls_long(unsigned long l)
{
    if (sizeof(l) == 4)
        return fls(l);
    return fls64(l);
}

static inline int get_count_order(unsigned int count)
{
    if (count == 0)
        return -1;

    return fls(--count);
}

/**
 * get_count_order_long - get order after rounding @l up to power of 2
 * @l: parameter
 *
 * it is same as get_count_order() but with long type parameter
 */
static inline int get_count_order_long(unsigned long l)
{
    if (l == 0UL)
        return -1;
    return (int)fls_long(--l);
}

/**
 * __ffs64 - find first set bit in a 64 bit word
 * @word: The 64 bit word
 *
 * On 64 bit arches this is a synonym for __ffs
 * The result is not defined if no bits are set, so check that @word
 * is non-zero before calling this.
 */
static inline unsigned int __ffs64(uint64_t word)
{
#if BITS_PER_LONG == 32
    if (((uint32_t)word) == 0UL)
        return __ffs((uint32_t)(word >> 32)) + 32;
#elif BITS_PER_LONG != 64
#error BITS_PER_LONG not 32 or 64
#endif
    return __ffs((unsigned long)word);
}

/**
 * fns - find N'th set bit in a word
 * @word: The word to search
 * @n: Bit to find
 */
static inline unsigned int fns(unsigned long word, unsigned int n)
{
    while (word && n--)
        word &= word - 1;

    return word ? __ffs(word) : BITS_PER_LONG;
}

/**
 * assign_bit - Assign value to a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 * @value: the value to assign
 */
#define assign_bit(nr, addr, value)                 \
    ((value) ? set_bit((nr), (addr)) : clear_bit((nr), (addr)))

#define __assign_bit(nr, addr, value)                   \
    ((value) ? __set_bit((nr), (addr)) : __clear_bit((nr), (addr)))

/**
 * __ptr_set_bit - Set bit in a pointer's value
 * @nr: the bit to set
 * @addr: the address of the pointer variable
 *
 * Example:
 *  void *p = foo();
 *  __ptr_set_bit(bit, &p);
 */
#define __ptr_set_bit(nr, addr)                         \
    ({                                              \
        typecheck_pointer(*(addr));             \
        __set_bit(nr, (unsigned long *)(addr)); \
    })

/**
 * __ptr_clear_bit - Clear bit in a pointer's value
 * @nr: the bit to clear
 * @addr: the address of the pointer variable
 *
 * Example:
 *  void *p = foo();
 *  __ptr_clear_bit(bit, &p);
 */
#define __ptr_clear_bit(nr, addr)                         \
    ({                                                \
        typecheck_pointer(*(addr));               \
        __clear_bit(nr, (unsigned long *)(addr)); \
    })

/**
 * __ptr_test_bit - Test bit in a pointer's value
 * @nr: the bit to test
 * @addr: the address of the pointer variable
 *
 * Example:
 *  void *p = foo();
 *  if (__ptr_test_bit(bit, &p)) {
 *          ...
 *  } else {
 *      ...
 *  }
 */
#define __ptr_test_bit(nr, addr)                       \
    ({                                             \
        typecheck_pointer(*(addr));            \
        test_bit(nr, (unsigned long *)(addr)); \
    })

#ifndef bit_clear_unless
#define bit_clear_unless(ptr, clear, test)  \
({                              \
    const typeof(*(ptr)) clear__ = (clear), test__ = (test);\
    typeof(*(ptr)) old__, new__;                \
                                \
    old__ = READ_ONCE(*(ptr));              \
    do {                            \
        if (old__ & test__)             \
            break;                  \
        new__ = old__ & ~clear__;           \
    } while (!try_cmpxchg(ptr, &old__, new__));     \
                                \
    !(old__ & test__);                  \
})
#endif

__END_DECLS

#endif
