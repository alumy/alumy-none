#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/mock.h"
#include "alumy/bug.h"

__BEGIN_DECLS

__attribute_const__ uint8_t bcd2bin(uint8_t bcd)
{
    BUG_ON(((bcd & 0xF0) >> 4) > 0x09);
    BUG_ON((bcd & 0x0F) > 0x09);

    return (bcd & 0x0f) + (bcd >> 4) * 10;
}

__attribute_const__ uint8_t bin2bcd(uint8_t bin)
{
    BUG_ON(bin > 99);

    return ((bin / 10) << 4) | (bin % 10);
}

__END_DECLS

