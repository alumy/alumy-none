#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include "ald_uart.h"
#include "config.h"

__BEGIN_DECLS

uart_handle_t dbg_uart = { 0 };

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  uint8_t c = ch;

  return (ald_uart_send(&dbg_uart, &c, sizeof(c), 1000) == OK) ? ch : -EOF;
}

/**
  * @brief  Initializate pin of uart module.
  * @retval None
  */
static void dbg_uart_pin_init(void)
{
    gpio_init_t x;

    /* Initialize tx pin */
    x.mode = GPIO_MODE_OUTPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_TTL;
    x.func = DBG_UART_TX_FUNC;
    ald_gpio_init(DBG_UART_TX_PORT, DBG_UART_TX_PIN, &x);

    /* Initialize rx pin */
    x.mode = GPIO_MODE_INPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_TTL;
    x.func = DBG_UART_RX_FUNC;
    ald_gpio_init(DBG_UART_RX_PORT, DBG_UART_RX_PIN, &x);

	return;
}

/**
  * @brief  Send message complete.
  * @param  arg: Pointer to uart_handle_t structure.
  * @retval None.
  */
static void dbg_uart_send_complete(uart_handle_t *arg)
{
	return;
}

/**
  * @brief  Receive a message complete.
  * @param  arg: Pointer to uart_handle_t structure.
  * @retval None.
  */
static void dbg_uart_recv_complete(uart_handle_t *arg)
{
	return;
}

/**
  * @brief  Occurs error.
  * @param  arg: Pointer to uart_handle_t structure.
  * @retval None.
  */
static void dbg_uart_error(uart_handle_t *arg)
{
	return;
}

int32_t dbg_uart_init(void)
{
    dbg_uart_pin_init();

    /* Initialize uart */
    dbg_uart.perh             = DBG_UART;
    dbg_uart.init.baud        = 115200;
    dbg_uart.init.word_length = UART_WORD_LENGTH_8B;
    dbg_uart.init.stop_bits   = UART_STOP_BITS_1;
    dbg_uart.init.parity      = UART_PARITY_NONE;
    dbg_uart.init.mode        = UART_MODE_UART;
    dbg_uart.init.fctl        = UART_HW_FLOW_CTL_DISABLE;
    dbg_uart.tx_cplt_cbk      = dbg_uart_send_complete;
    dbg_uart.rx_cplt_cbk      = dbg_uart_recv_complete;
    dbg_uart.error_cbk        = dbg_uart_error;
    ald_uart_init(&dbg_uart);

    return 0;
}

__END_DECLS

