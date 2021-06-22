#ifndef __AL_ARCH_ARM_BITBAND_H
#define __AL_ARCH_ARM_BITBAND_H 1

#include "alumy/config.h"
#include "alumy/base.h"
#include "alumy/types.h"

__BEGIN_DECLS

#define BITBAND(addr, bit)      \
    ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bit << 2))

#define MEM_ADDR(addr)      *((volatile unsigned long *)(addr))

__END_DECLS

#endif

