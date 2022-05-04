#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/crc.h"

uint16_t crc16_poly(uint16_t crc, uint16_t poly, const void *data, size_t len)
{
    const uint8_t *p = (const uint8_t *)data;
    uint8_t i;

    while (len--) {
        crc = crc ^ *p++ << 8;

        for (i = 0; i < 8; i++) {
            if (crc & 0x8000) {
                crc = crc << 1 ^ poly;
            } else {
                crc = crc << 1;
            }
        }
    }

    return crc;
}
