#ifndef __AL_DRV_UART_H
#define __AL_DRV_UART_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define AL_UART_WIDTH_MS(baud, bits, bytes)		\
	(1000 * (bits) * (bytes) / (baud))

typedef enum al_rs485_dir {
    AL_RS485_IN = 0,
    AL_RS485_OUT
} al_rs485_dir_t;

__END_DECLS

#endif
