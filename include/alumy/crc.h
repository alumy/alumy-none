#ifndef __AL_CRC_H
#define __AL_CRC_H 1

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
uint16_t mb_get_crc16(const uint8_t *buffer, size_t len);
/* crc/mb_crc16.c */

uint16_t crc16_poly(uint16_t crc, uint16_t poly, const void *data, size_t len);

__END_DECLS

#endif
