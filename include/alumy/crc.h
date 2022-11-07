#ifndef __AL_CRC_H
#define __AL_CRC_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/* crc/crc32.c */

/**
 * crc32 - Calculate the CRC32 for a block of data
 *
 * @crc: Input crc to chain from a previous calculution (use 0 to start a new
 *	calculation)
 * @buf: Bytes to checksum
 * @len: Number of bytes to checksum
 * @return checksum value
 */
uint32_t al_crc32(uint32_t crc, const void *buf, uint32_t len);

/**
 * crc32_wd - Calculate the CRC32 for a block of data (watchdog version)
 *
 * This checksums the data @chunk_sz bytes at a time, calling WATCHDOG_RESET()
 * after each chunk, to prevent the watchdog from firing.
 *
 * @crc: Input crc to chain from a previous calculution (use 0 to start a new
 *	calculation)
 * @buf: Bytes to checksum
 * @len: Number of bytes to checksum
 * @chunk_sz: Chunk size to use between watchdog resets
 * @return checksum
 */
uint32_t al_crc32_wd(uint32_t crc, const uint8_t *buf, uint32_t len,
                     uint32_t chunk_sz);

/**
 * crc32_no_comp - Calculate the CRC32 for a block of data (no one's compliment)
 *
 * This version uses a different algorithm which doesn't use one's compliment.
 * JFFS2 (and other things?) use this.
 *
 * @crc: Input crc to chain from a previous calculution (use 0 to start a new
 *	calculation)
 * @buf: Bytes to checksum
 * @len: Number of bytes to checksum
 * @return checksum value
 */
uint32_t al_crc32_no_comp(uint32_t crc, const void *buf, uint32_t len);

/**
 * crc32_wd_buf - Perform CRC32 on a buffer and return result in buffer
 *
 * @input:	Input buffer
 * @ilen:	Input buffer length
 * @output:	Place to put checksum result (4 bytes)
 * @chunk_sz:	Trigger watchdog after processing this many bytes
 */
void al_crc32_wd_buf(const uint8_t *input, uint32_t ilen,
					 uint8_t *output, uint32_t chunk_sz);

/* crc/crc32c.c */

/* crc/mb_crc16.c */
uint16_t mb_get_crc16(const void *data, size_t len);
/* crc/mb_crc16.c */

uint16_t crc16_poly(uint16_t crc, uint16_t poly, const void *data, size_t len);

/* see usage of this value in crc8() description */
#define CRC8_INIT_VALUE		0xFF

/*
 * Return value of crc8() indicating valid message+crc. This is true
 * if a CRC is inverted before transmission. The CRC computed over the
 * whole received bitstream is _table[x], where x is the bit pattern
 * of the modification (almost always 0xff).
 */
#define CRC8_GOOD_VALUE(_table)	(_table[0xFF])

/* required table size for crc8 algorithm */
#define CRC8_TABLE_SIZE			256

/* helper macro assuring right table size is used */
#define DECLARE_CRC8_TABLE(_table) \
	static uint8_t _table[CRC8_TABLE_SIZE]

/**
 * crc8_populate_lsb - fill crc table for given polynomial in regular bit order.
 *
 * @table:	table to be filled.
 * @polynomial:	polynomial for which table is to be filled.
 *
 * This function fills the provided table according the polynomial provided for
 * regular bit order (lsb first). Polynomials in CRC algorithms are typically
 * represented as shown below.
 *
 *	poly = x^8 + x^7 + x^6 + x^4 + x^2 + 1
 *
 * For lsb first direction x^7 maps to the lsb. So the polynomial is as below.
 *
 * - lsb first: poly = 10101011(1) = 0xAB
 */
void crc8_populate_lsb(uint8_t table[CRC8_TABLE_SIZE], uint8_t polynomial);

/**
 * crc8_populate_msb - fill crc table for given polynomial in reverse bit order.
 *
 * @table:	table to be filled.
 * @polynomial:	polynomial for which table is to be filled.
 *
 * This function fills the provided table according the polynomial provided for
 * reverse bit order (msb first). Polynomials in CRC algorithms are typically
 * represented as shown below.
 *
 *	poly = x^8 + x^7 + x^6 + x^4 + x^2 + 1
 *
 * For msb first direction x^7 maps to the msb. So the polynomial is as below.
 *
 * - msb first: poly = (1)11010101 = 0xD5
 */
void crc8_populate_msb(uint8_t table[CRC8_TABLE_SIZE], uint8_t polynomial);

/**
 * crc8() - calculate a crc8 over the given input data.
 *
 * @table:	crc table used for calculation.
 * @pdata:	pointer to data buffer.
 * @nbytes:	number of bytes in data buffer.
 * @crc:	previous returned crc8 value.
 *
 * The CRC8 is calculated using the polynomial given in crc8_populate_msb()
 * or crc8_populate_lsb().
 *
 * The caller provides the initial value (either %CRC8_INIT_VALUE
 * or the previous returned value) to allow for processing of
 * discontiguous blocks of data.  When generating the CRC the
 * caller is responsible for complementing the final return value
 * and inserting it into the byte stream.  When validating a byte
 * stream (including CRC8), a final return value of %CRC8_GOOD_VALUE
 * indicates the byte stream data can be considered valid.
 *
 * Reference:
 * "A Painless Guide to CRC Error Detection Algorithms", ver 3, Aug 1993
 * Williams, Ross N., ross<at>ross.net
 * (see URL http://www.ross.net/crc/download/crc_v3.txt).
 */
uint8_t crc8(const uint8_t table[CRC8_TABLE_SIZE],
			 uint8_t *pdata, size_t nbytes, uint8_t crc);

__END_DECLS

#endif
