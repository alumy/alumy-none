/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __AL_BITOPS_FFZ_H
#define __AL_BITOPS_FFZ_H 1

/*
 * ffz - find first zero in word.
 * @word: The word to search
 *
 * Undefined if no zero exists, so code should check against ~0UL first.
 */
#define ffz(x)  __ffs(~(x))

#endif /* _ASM_GENERIC_BITOPS_FFZ_H_ */
