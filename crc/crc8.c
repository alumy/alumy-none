#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/crc.h"

__BEGIN_DECLS

/**
 * crc8_populate_msb - fill crc table for given polynomial in reverse bit order.
 *
 * @table:    table to be filled.
 * @polynomial:    polynomial for which table is to be filled.
 */
void crc8_populate_msb(uint8_t table[CRC8_TABLE_SIZE], uint8_t polynomial)
{
    int_t i, j;
    const uint8_t msbit = 0x80;
    uint8_t t = msbit;

    table[0] = 0;

    for (i = 1; i < CRC8_TABLE_SIZE; i *= 2) {
        t = (t << 1) ^ (t & msbit ? polynomial : 0);
        for (j = 0; j < i; j++)
            table[i+j] = table[j] ^ t;
    }
}

/**
 * crc8_populate_lsb - fill crc table for given polynomial in regular bit order.
 *
 * @table:    table to be filled.
 * @polynomial:    polynomial for which table is to be filled.
 */
void crc8_populate_lsb(uint8_t table[CRC8_TABLE_SIZE], uint8_t polynomial)
{
    int_t i, j;
    uint8_t t = 1;

    table[0] = 0;

    for (i = (CRC8_TABLE_SIZE >> 1); i; i >>= 1) {
        t = (t >> 1) ^ (t & 1 ? polynomial : 0);
        for (j = 0; j < CRC8_TABLE_SIZE; j += 2*i)
            table[i+j] = table[j] ^ t;
    }
}

/**
 * crc8 - calculate a crc8 over the given input data.
 *
 * @table: crc table used for calculation.
 * @pdata: pointer to data buffer.
 * @nbytes: number of bytes in data buffer.
 * @crc: previous returned crc8 value.
 */
uint8_t crc8(const uint8_t table[CRC8_TABLE_SIZE],
			 uint8_t *pdata, size_t nbytes, uint8_t crc)
{
    /* loop over the buffer data */
    while (nbytes-- > 0)
        crc = table[(crc ^ *pdata++) & 0xff];

    return crc;
}

__END_DECLS

