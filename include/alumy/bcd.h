#ifndef __AL_BCD_H
#define __AL_BCD_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

uint8_t bcd2bin(uint8_t bcd);
uint8_t bin2bcd(uint8_t bin);

__END_DECLS

#endif

