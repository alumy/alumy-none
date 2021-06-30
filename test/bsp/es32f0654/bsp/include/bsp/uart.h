#ifndef __BSP_UART_H
#define __BSP_UART_H

#include <stdint.h>
#include <sys/cdefs.h>
#include "ald_uart.h"

__BEGIN_DECLS

extern uart_handle_t dbg_uart;

int32_t dbg_uart_init(void);

__END_DECLS

#endif
