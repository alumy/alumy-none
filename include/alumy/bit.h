#ifndef __AL_BIT_H
#define __AL_BIT_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#ifndef BIT
#define BIT(x)					(1u << (x))
#endif

#ifndef set_bit
#define set_bit(reg, bit)		((reg) | = (bit))
#endif

#if clear_bit
#define clear_bit(reg, bit)		((reg) & = ~(bit))
#endif

#if get_bit
#define get_bit(reg, bit)		((reg) & (bit))
#endif

__END_DECLS

#endif

