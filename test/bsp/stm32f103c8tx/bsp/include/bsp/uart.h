#ifndef __BSP_UART_H
#define __BSP_UART_H

#include <stdint.h>
#include <sys/cdefs.h>
#include "stm32f1xx_hal.h"

__BEGIN_DECLS

int32_t dbg_uart_init(void);

__END_DECLS

#endif
