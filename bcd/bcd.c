#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/mock.h"
#include "alumy/bug.h"

__BEGIN_DECLS

__attribute_const__ uint8_t bcd2bin(uint8_t bcd)
{
    return (bcd & 0x0f) + (bcd >> 4) * 10;
}

__attribute_const__ 
uint8_t al_bcd2bin(uint8_t bcd) __attribute__((alias("bcd2bin")));

__attribute_const__ uint8_t bin2bcd(uint8_t bin)
{
    return ((bin / 10) << 4) | (bin % 10);
}

__attribute_const__
uint8_t al_bin2bcd(uint8_t bin) __attribute__((alias("bin2bcd")));

__END_DECLS

