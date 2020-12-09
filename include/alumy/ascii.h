#ifndef __ASCII_H
#define __ASCII_H 1

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

enum {
    SOH = 0x01,
    STX = 0x02,
    ETX = 0x03,
    EOT = 0x04,
    ACK = 0x06,
    NAK = 0x15,
    CAN = 0x18,
};

__END_DECLS

#endif

