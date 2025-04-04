#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include "config.h"
#include "SEGGER_RTT.h"

__BEGIN_DECLS

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
  
  return (SEGGER_RTT_Write(0, &c, sizeof(c)) == 1) ? ch : -EOF;
}

/**
  * @brief  Initializate pin of uart module.
  * @retval None
  */
__used static void dbg_uart_pin_init(void)
{
	return;
}

int32_t dbg_uart_init(void)
{
    SEGGER_RTT_Init();

	return 0;
}

__END_DECLS

