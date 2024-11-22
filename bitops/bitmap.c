// SPDX-License-Identifier: GPL-2.0-only
/*
 * lib/bitmap.c
 * Helper functions for bitmap.h.
 */

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/mock.h"
#include "alumy/bitops/bitsperlong.h"
#include "alumy/bitops/bitmap.h"
#include "alumy/bug.h"

/**
 * DOC: bitmap introduction
 *
 * bitmaps provide an array of bits, implemented using an
 * array of unsigned longs.  The number of valid bits in a
 * given bitmap does _not_ need to be an exact multiple of
 * BITS_PER_LONG.
 *
 * The possible unused bits in the last, partially used word
 * of a bitmap are 'don't care'.  The implementation makes
 * no particular effort to keep them zero.  It ensures that
 * their value will not affect the results of any operation.
 * The bitmap operations that return Boolean (bitmap_empty,
 * for example) or scalar (bitmap_weight, for example) results
 * carefully filter out these unused bits from impacting their
 * results.
 *
 * The byte ordering of bitmaps is more natural on little
 * endian architectures.  See the big-endian headers
 * include/asm-ppc64/bitops.h and include/asm-s390/bitops.h
 * for the best explanations of this ordering.
 */

bool __bitmap_equal(const unsigned long *bitmap1,
		    const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k, lim = bits/BITS_PER_LONG;
	for (k = 0; k < lim; ++k)
		if (bitmap1[k] != bitmap2[k])
			return false;

	if (bits % BITS_PER_LONG)
		if ((bitmap1[k] ^ bitmap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			return false;

	return true;
}

bool __bitmap_or_equal(const unsigned long *bitmap1,
		       const unsigned long *bitmap2,
		       const unsigned long *bitmap3,
		       unsigned int bits)
{
	unsigned int k, lim = bits / BITS_PER_LONG;
	unsigned long tmp;

	for (k = 0; k < lim; ++k) {
		if ((bitmap1[k] | bitmap2[k]) != bitmap3[k])
			return false;
	}

	if (!(bits % BITS_PER_LONG))
		return true;

	tmp = (bitmap1[k] | bitmap2[k]) ^ bitmap3[k];
	return (tmp & BITMAP_LAST_WORD_MASK(bits)) == 0;
}

void __bitmap_complement(unsigned long *dst, const unsigned long *src, unsigned int bits)
{
	unsigned int k, lim = BITS_TO_LONGS(bits);
	for (k = 0; k < lim; ++k)
		dst[k] = ~src[k];
}

/**
 * __bitmap_shift_right - logical right shift of the bits in a bitmap
 *   @dst : destination bitmap
 *   @src : source bitmap
 *   @shift : shift by this many bits
 *   @nbits : bitmap size, in bits
 *
 * Shifting right (dividing) means moving bits in the MS -> LS bit
 * direction.  Zeros are fed into the vacated MS positions and the
 * LS bits shifted off the bottom are lost.
 */
void __bitmap_shift_right(unsigned long *dst, const unsigned long *src,
			unsigned shift, unsigned nbits)
{
	unsigned k, lim = BITS_TO_LONGS(nbits);
	unsigned off = shift/BITS_PER_LONG, rem = shift % BITS_PER_LONG;
	unsigned long mask = BITMAP_LAST_WORD_MASK(nbits);
	for (k = 0; off + k < lim; ++k) {
		unsigned long upper, lower;

		/*
		 * If shift is not word aligned, take lower rem bits of
		 * word above and make them the top rem bits of result.
		 */
		if (!rem || off + k + 1 >= lim)
			upper = 0;
		else {
			upper = src[off + k + 1];
			if (off + k + 1 == lim - 1)
				upper &= mask;
			upper <<= (BITS_PER_LONG - rem);
		}
		lower = src[off + k];
		if (off + k == lim - 1)
			lower &= mask;
		lower >>= rem;
		dst[k] = lower | upper;
	}
	if (off)
		memset(&dst[lim - off], 0, off*sizeof(unsigned long));
}

/**
 * __bitmap_shift_left - logical left shift of the bits in a bitmap
 *   @dst : destination bitmap
 *   @src : source bitmap
 *   @shift : shift by this many bits
 *   @nbits : bitmap size, in bits
 *
 * Shifting left (multiplying) means moving bits in the LS -> MS
 * direction.  Zeros are fed into the vacated LS bit positions
 * and those MS bits shifted off the top are lost.
 */

void __bitmap_shift_left(unsigned long *dst, const unsigned long *src,
			unsigned int shift, unsigned int nbits)
{
	int k;
	unsigned int lim = BITS_TO_LONGS(nbits);
	unsigned int off = shift/BITS_PER_LONG, rem = shift % BITS_PER_LONG;
	for (k = lim - off - 1; k >= 0; --k) {
		unsigned long upper, lower;

		/*
		 * If shift is not word aligned, take upper rem bits of
		 * word below and make them the bottom rem bits of result.
		 */
		if (rem && k > 0)
			lower = src[k - 1] >> (BITS_PER_LONG - rem);
		else
			lower = 0;
		upper = src[k] << rem;
		dst[k + off] = lower | upper;
	}
	if (off)
		memset(dst, 0, off*sizeof(unsigned long));
}

/**
 * bitmap_cut() - remove bit region from bitmap and right shift remaining bits
 * @dst: destination bitmap, might overlap with src
 * @src: source bitmap
 * @first: start bit of region to be removed
 * @cut: number of bits to remove
 * @nbits: bitmap size, in bits
 *
 * Set the n-th bit of @dst iff the n-th bit of @src is set and
 * n is less than @first, or the m-th bit of @src is set for any
 * m such that @first <= n < nbits, and m = n + @cut.
 *
 * In pictures, example for a big-endian 32-bit architecture:
 *
 * The @src bitmap is::
 *
 *   31                                   63
 *   |                                    |
 *   10000000 11000001 11110010 00010101  10000000 11000001 01110010 00010101
 *                   |  |              |                                    |
 *                  16  14             0                                   32
 *
 * if @cut is 3, and @first is 14, bits 14-16 in @src are cut and @dst is::
 *
 *   31                                   63
 *   |                                    |
 *   10110000 00011000 00110010 00010101  00010000 00011000 00101110 01000010
 *                      |              |                                    |
 *                      14 (bit 17     0                                   32
 *                          from @src)
 *
 * Note that @dst and @src might overlap partially or entirely.
 *
 * This is implemented in the obvious way, with a shift and carry
 * step for each moved bit. Optimisation is left as an exercise
 * for the compiler.
 */
void bitmap_cut(unsigned long *dst, const unsigned long *src,
		unsigned int first, unsigned int cut, unsigned int nbits)
{
	unsigned int len = BITS_TO_LONGS(nbits);
	unsigned long keep = 0, carry;
	int i;

	if (first % BITS_PER_LONG) {
		keep = src[first / BITS_PER_LONG] &
		       (~0UL >> (BITS_PER_LONG - first % BITS_PER_LONG));
	}

	memmove(dst, src, len * sizeof(*dst));

	while (cut--) {
		for (i = first / BITS_PER_LONG; i < len; i++) {
			if (i < len - 1)
				carry = dst[i + 1] & 1UL;
			else
				carry = 0;

			dst[i] = (dst[i] >> 1) | (carry << (BITS_PER_LONG - 1));
		}
	}

	dst[first / BITS_PER_LONG] &= ~0UL << (first % BITS_PER_LONG);
	dst[first / BITS_PER_LONG] |= keep;
}

bool __bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
				const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int lim = bits/BITS_PER_LONG;
	unsigned long result = 0;

	for (k = 0; k < lim; k++)
		result |= (dst[k] = bitmap1[k] & bitmap2[k]);
	if (bits % BITS_PER_LONG)
		result |= (dst[k] = bitmap1[k] & bitmap2[k] &
			   BITMAP_LAST_WORD_MASK(bits));
	return result != 0;
}

void __bitmap_or(unsigned long *dst, const unsigned long *bitmap1,
				const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int nr = BITS_TO_LONGS(bits);

	for (k = 0; k < nr; k++)
		dst[k] = bitmap1[k] | bitmap2[k];
}

void __bitmap_xor(unsigned long *dst, const unsigned long *bitmap1,
				const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int nr = BITS_TO_LONGS(bits);

	for (k = 0; k < nr; k++)
		dst[k] = bitmap1[k] ^ bitmap2[k];
}

bool __bitmap_andnot(unsigned long *dst, const unsigned long *bitmap1,
				const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int lim = bits/BITS_PER_LONG;
	unsigned long result = 0;

	for (k = 0; k < lim; k++)
		result |= (dst[k] = bitmap1[k] & ~bitmap2[k]);
	if (bits % BITS_PER_LONG)
		result |= (dst[k] = bitmap1[k] & ~bitmap2[k] &
			   BITMAP_LAST_WORD_MASK(bits));
	return result != 0;
}

void __bitmap_replace(unsigned long *dst,
		      const unsigned long *old, const unsigned long *new,
		      const unsigned long *mask, unsigned int nbits)
{
	unsigned int k;
	unsigned int nr = BITS_TO_LONGS(nbits);

	for (k = 0; k < nr; k++)
		dst[k] = (old[k] & ~mask[k]) | (new[k] & mask[k]);
}

bool __bitmap_intersects(const unsigned long *bitmap1,
			 const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k, lim = bits/BITS_PER_LONG;
	for (k = 0; k < lim; ++k)
		if (bitmap1[k] & bitmap2[k])
			return true;

	if (bits % BITS_PER_LONG)
		if ((bitmap1[k] & bitmap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			return true;
	return false;
}

bool __bitmap_subset(const unsigned long *bitmap1,
		     const unsigned long *bitmap2, unsigned int bits)
{
	unsigned int k, lim = bits/BITS_PER_LONG;
	for (k = 0; k < lim; ++k)
		if (bitmap1[k] & ~bitmap2[k])
			return false;

	if (bits % BITS_PER_LONG)
		if ((bitmap1[k] & ~bitmap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			return false;
	return true;
}

#define BITMAP_WEIGHT(FETCH, bits)	\
({										\
	unsigned int __bits = (bits), idx, w = 0;				\
										\
	for (idx = 0; idx < __bits / BITS_PER_LONG; idx++)			\
		w += hweight_long(FETCH);					\
										\
	if (__bits % BITS_PER_LONG)						\
		w += hweight_long((FETCH) & BITMAP_LAST_WORD_MASK(__bits));	\
										\
	w;									\
})

unsigned int __bitmap_weight(const unsigned long *bitmap, unsigned int bits)
{
	return BITMAP_WEIGHT(bitmap[idx], bits);
}

unsigned int __bitmap_weight_and(const unsigned long *bitmap1,
				const unsigned long *bitmap2, unsigned int bits)
{
	return BITMAP_WEIGHT(bitmap1[idx] & bitmap2[idx], bits);
}

unsigned int __bitmap_weight_andnot(const unsigned long *bitmap1,
				const unsigned long *bitmap2, unsigned int bits)
{
	return BITMAP_WEIGHT(bitmap1[idx] & ~bitmap2[idx], bits);
}

void __bitmap_set(unsigned long *map, unsigned int start, int len)
{
	unsigned long *p = map + BIT_WORD(start);
	const unsigned int size = start + len;
	int bits_to_set = BITS_PER_LONG - (start % BITS_PER_LONG);
	unsigned long mask_to_set = BITMAP_FIRST_WORD_MASK(start);

	while (len - bits_to_set >= 0) {
		*p |= mask_to_set;
		len -= bits_to_set;
		bits_to_set = BITS_PER_LONG;
		mask_to_set = ~0UL;
		p++;
	}
	if (len) {
		mask_to_set &= BITMAP_LAST_WORD_MASK(size);
		*p |= mask_to_set;
	}
}

void __bitmap_clear(unsigned long *map, unsigned int start, int len)
{
	unsigned long *p = map + BIT_WORD(start);
	const unsigned int size = start + len;
	int bits_to_clear = BITS_PER_LONG - (start % BITS_PER_LONG);
	unsigned long mask_to_clear = BITMAP_FIRST_WORD_MASK(start);

	while (len - bits_to_clear >= 0) {
		*p &= ~mask_to_clear;
		len -= bits_to_clear;
		bits_to_clear = BITS_PER_LONG;
		mask_to_clear = ~0UL;
		p++;
	}
	if (len) {
		mask_to_clear &= BITMAP_LAST_WORD_MASK(size);
		*p &= ~mask_to_clear;
	}
}

/**
 * bitmap_find_next_zero_area_off - find a contiguous aligned zero area
 * @map: The address to base the search on
 * @size: The bitmap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking for
 * @align_mask: Alignment mask for zero area
 * @align_offset: Alignment offset for zero area.
 *
 * The @align_mask should be one less than a power of 2; the effect is that
 * the bit offset of all zero areas this function finds plus @align_offset
 * is multiple of that power of 2.
 */
unsigned long bitmap_find_next_zero_area_off(unsigned long *map,
					     unsigned long size,
					     unsigned long start,
					     unsigned int nr,
					     unsigned long align_mask,
					     unsigned long align_offset)
{
	unsigned long index, end, i;
again:
	index = find_next_zero_bit(map, size, start);

	/* Align allocation */
    index = AL_ALIGN_MASK(index + align_offset, align_mask) - align_offset;

	end = index + nr;
	if (end > size)
		return end;
	i = find_next_bit(map, end, index);
	if (i < end) {
		start = i + 1;
		goto again;
	}
	return index;
}

/**
 * bitmap_pos_to_ord - find ordinal of set bit at given position in bitmap
 *	@buf: pointer to a bitmap
 *	@pos: a bit position in @buf (0 <= @pos < @nbits)
 *	@nbits: number of valid bit positions in @buf
 *
 * Map the bit at position @pos in @buf (of length @nbits) to the
 * ordinal of which set bit it is.  If it is not set or if @pos
 * is not a valid bit position, map to -1.
 *
 * If for example, just bits 4 through 7 are set in @buf, then @pos
 * values 4 through 7 will get mapped to 0 through 3, respectively,
 * and other @pos values will get mapped to -1.  When @pos value 7
 * gets mapped to (returns) @ord value 3 in this example, that means
 * that bit 7 is the 3rd (starting with 0th) set bit in @buf.
 *
 * The bit positions 0 through @bits are valid positions in @buf.
 */
static int bitmap_pos_to_ord(const unsigned long *buf, unsigned int pos, unsigned int nbits)
{
	if (pos >= nbits || !test_bit(pos, buf))
		return -1;

	return bitmap_weight(buf, pos);
}

/**
 * bitmap_remap - Apply map defined by a pair of bitmaps to another bitmap
 *	@dst: remapped result
 *	@src: subset to be remapped
 *	@old: defines domain of map
 *	@new: defines range of map
 *	@nbits: number of bits in each of these bitmaps
 *
 * Let @old and @new define a mapping of bit positions, such that
 * whatever position is held by the n-th set bit in @old is mapped
 * to the n-th set bit in @new.  In the more general case, allowing
 * for the possibility that the weight 'w' of @new is less than the
 * weight of @old, map the position of the n-th set bit in @old to
 * the position of the m-th set bit in @new, where m == n % w.
 *
 * If either of the @old and @new bitmaps are empty, or if @src and
 * @dst point to the same location, then this routine copies @src
 * to @dst.
 *
 * The positions of unset bits in @old are mapped to themselves
 * (the identity map).
 *
 * Apply the above specified mapping to @src, placing the result in
 * @dst, clearing any bits previously set in @dst.
 *
 * For example, lets say that @old has bits 4 through 7 set, and
 * @new has bits 12 through 15 set.  This defines the mapping of bit
 * position 4 to 12, 5 to 13, 6 to 14 and 7 to 15, and of all other
 * bit positions unchanged.  So if say @src comes into this routine
 * with bits 1, 5 and 7 set, then @dst should leave with bits 1,
 * 13 and 15 set.
 */
void bitmap_remap(unsigned long *dst, const unsigned long *src,
		const unsigned long *old, const unsigned long *new,
		unsigned int nbits)
{
	unsigned int oldbit, w;

	if (dst == src)		/* following doesn't handle inplace remaps */
		return;
	bitmap_zero(dst, nbits);

	w = bitmap_weight(new, nbits);
	for_each_set_bit(oldbit, src, nbits) {
		int n = bitmap_pos_to_ord(old, oldbit, nbits);

		if (n < 0 || w == 0)
			set_bit(oldbit, dst);	/* identity map */
		else
			set_bit(find_nth_bit(new, nbits, n % w), dst);
	}
}

/**
 * bitmap_bitremap - Apply map defined by a pair of bitmaps to a single bit
 *	@oldbit: bit position to be mapped
 *	@old: defines domain of map
 *	@new: defines range of map
 *	@bits: number of bits in each of these bitmaps
 *
 * Let @old and @new define a mapping of bit positions, such that
 * whatever position is held by the n-th set bit in @old is mapped
 * to the n-th set bit in @new.  In the more general case, allowing
 * for the possibility that the weight 'w' of @new is less than the
 * weight of @old, map the position of the n-th set bit in @old to
 * the position of the m-th set bit in @new, where m == n % w.
 *
 * The positions of unset bits in @old are mapped to themselves
 * (the identity map).
 *
 * Apply the above specified mapping to bit position @oldbit, returning
 * the new bit position.
 *
 * For example, lets say that @old has bits 4 through 7 set, and
 * @new has bits 12 through 15 set.  This defines the mapping of bit
 * position 4 to 12, 5 to 13, 6 to 14 and 7 to 15, and of all other
 * bit positions unchanged.  So if say @oldbit is 5, then this routine
 * returns 13.
 */
int bitmap_bitremap(int oldbit, const unsigned long *old,
				const unsigned long *new, int bits)
{
	int w = bitmap_weight(new, bits);
	int n = bitmap_pos_to_ord(old, oldbit, bits);
	if (n < 0 || w == 0)
		return oldbit;
	else
		return find_nth_bit(new, bits, n % w);
}

#if BITS_PER_LONG == 64
/**
 * bitmap_from_arr32 - copy the contents of u32 array of bits to bitmap
 *	@bitmap: array of unsigned longs, the destination bitmap
 *	@buf: array of u32 (in host byte order), the source bitmap
 *	@nbits: number of bits in @bitmap
 */
void bitmap_from_arr32(unsigned long *bitmap, const u32 *buf, unsigned int nbits)
{
	unsigned int i, halfwords;

	halfwords = DIV_ROUND_UP(nbits, 32);
	for (i = 0; i < halfwords; i++) {
		bitmap[i/2] = (unsigned long) buf[i];
		if (++i < halfwords)
			bitmap[i/2] |= ((unsigned long) buf[i]) << 32;
	}

	/* Clear tail bits in last word beyond nbits. */
	if (nbits % BITS_PER_LONG)
		bitmap[(halfwords - 1) / 2] &= BITMAP_LAST_WORD_MASK(nbits);
}

/**
 * bitmap_to_arr32 - copy the contents of bitmap to a u32 array of bits
 *	@buf: array of u32 (in host byte order), the dest bitmap
 *	@bitmap: array of unsigned longs, the source bitmap
 *	@nbits: number of bits in @bitmap
 */
void bitmap_to_arr32(u32 *buf, const unsigned long *bitmap, unsigned int nbits)
{
	unsigned int i, halfwords;

	halfwords = DIV_ROUND_UP(nbits, 32);
	for (i = 0; i < halfwords; i++) {
		buf[i] = (u32) (bitmap[i/2] & UINT_MAX);
		if (++i < halfwords)
			buf[i] = (u32) (bitmap[i/2] >> 32);
	}

	/* Clear tail bits in last element of array beyond nbits. */
	if (nbits % BITS_PER_LONG)
		buf[halfwords - 1] &= (u32) (UINT_MAX >> ((-nbits) & 31));
}
#endif

#if BITS_PER_LONG == 32
/**
 * bitmap_from_arr64 - copy the contents of u64 array of bits to bitmap
 *	@bitmap: array of unsigned longs, the destination bitmap
 *	@buf: array of u64 (in host byte order), the source bitmap
 *	@nbits: number of bits in @bitmap
 */
void bitmap_from_arr64(unsigned long *bitmap, const u64 *buf, unsigned int nbits)
{
	int n;

	for (n = nbits; n > 0; n -= 64) {
		u64 val = *buf++;

		*bitmap++ = val;
		if (n > 32)
			*bitmap++ = val >> 32;
	}

	/*
	 * Clear tail bits in the last word beyond nbits.
	 *
	 * Negative index is OK because here we point to the word next
	 * to the last word of the bitmap, except for nbits == 0, which
	 * is tested implicitly.
	 */
	if (nbits % BITS_PER_LONG)
		bitmap[-1] &= BITMAP_LAST_WORD_MASK(nbits);
}

/**
 * bitmap_to_arr64 - copy the contents of bitmap to a u64 array of bits
 *	@buf: array of u64 (in host byte order), the dest bitmap
 *	@bitmap: array of unsigned longs, the source bitmap
 *	@nbits: number of bits in @bitmap
 */
void bitmap_to_arr64(u64 *buf, const unsigned long *bitmap, unsigned int nbits)
{
	const unsigned long *end = bitmap + BITS_TO_LONGS(nbits);

	while (bitmap < end) {
		*buf = *bitmap++;
		if (bitmap < end)
			*buf |= (u64)(*bitmap++) << 32;
		buf++;
	}

	/* Clear tail bits in the last element of array beyond nbits. */
	if (nbits % 64)
		buf[-1] &= GENMASK_ULL((nbits - 1) % 64, 0);
}
#endif