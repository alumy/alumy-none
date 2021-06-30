#ifndef __CONFIG_H
#define __CONFIG_H 1

#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * debug uart, printf informations to this uart
 */
#if 0
#define DBG_UART                UART2

#define DBG_UART_TX_PORT        GPIOC
#define DBG_UART_TX_PIN         GPIO_PIN_12
#define DBG_UART_TX_FUNC        GPIO_FUNC_5

#define DBG_UART_RX_PORT        GPIOD
#define DBG_UART_RX_PIN         GPIO_PIN_2
#define DBG_UART_RX_FUNC        GPIO_FUNC_5
#endif

__END_DECLS

#endif

