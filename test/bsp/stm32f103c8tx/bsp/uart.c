#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include "stm32f1xx_hal.h"
#include "config.h"
#include "main.h"

__BEGIN_DECLS

UART_HandleTypeDef dbg_uart = { 0 };

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

  return (HAL_UART_Transmit(&dbg_uart, &c, sizeof(c), 1000) == HAL_OK) ? ch : -EOF;
}

/**
  * @brief  Initializate pin of uart module.
  * @retval None
  */
static void dbg_uart_pin_init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	return;
}

int32_t dbg_uart_init(void)
{
	dbg_uart_pin_init();

	/* Initialize uart */
	dbg_uart.Instance = USART1;
	dbg_uart.Init.BaudRate = 115200;
	dbg_uart.Init.WordLength = UART_WORDLENGTH_8B;
	dbg_uart.Init.StopBits = UART_STOPBITS_1;
	dbg_uart.Init.Parity = UART_PARITY_NONE;
	dbg_uart.Init.Mode = UART_MODE_TX_RX;
	dbg_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	dbg_uart.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&dbg_uart) != HAL_OK) {
		Error_Handler();
	}

	return 0;
}

__END_DECLS

