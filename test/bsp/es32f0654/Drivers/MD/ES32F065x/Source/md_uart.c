/**
  *********************************************************************************
  *
  * @file    md_uart.c
  * @brief   UART module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_uart.h"
#include "md_cmu.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_UART

/** @addtogroup MD_UART
  * @{
  */

/** @addtogroup MD_UART_Public_Functions
  * @{
  */
/** @addtogroup MD_UART_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset UART peripheral
  * @param  UARTx: UART peripheral
  * @retval None
  */
void md_uart_reset(UART_TypeDef *UARTx)
{
	WRITE_REG(UARTx->BRR, 0x0);
	WRITE_REG(UARTx->LCR, 0x0);
	WRITE_REG(UARTx->MCR, 0x0);
	WRITE_REG(UARTx->CR, 0x0);
	WRITE_REG(UARTx->RTOR, 0x0);
	WRITE_REG(UARTx->FCR, 0x0);
	WRITE_REG(UARTx->IDR, 0xFFF);
}

/**
  * @brief  Initializes the UARTx according to the specified
  *         parameters in the uart_init_t.
  * @param  UARTx: UART peripheral
  * @param  init: Pointer to a md_uart_init_t structure that contains
  *         the configuration information for the specified UART module.
  * @retval None
  */
void md_uart_init(UART_TypeDef *UARTx, md_uart_init_t *init)
{
	md_uart_reset(UARTx);

	MODIFY_REG(UARTx->LCR, UART_LCR_DLS_MSK, init->word_length);
	MODIFY_REG(UARTx->LCR, UART_LCR_STOP_MSK, init->stop_bits);
	MODIFY_REG(UARTx->LCR, UART_LCR_PEN_MSK | UART_LCR_PS_MSK, init->parity);
	MODIFY_REG(UARTx->MCR, UART_MCR_AFCEN_MSK, init->fctl);
	SET_BIT(UARTx->LCR, UART_LCR_BRWEN_MSK);
	WRITE_REG(UARTx->BRR, md_cmu_get_pclk1_clock() / init->baud);
	CLEAR_BIT(UARTx->LCR, UART_LCR_BRWEN_MSK);
	SET_BIT(UARTx->FCR, UART_FCR_FIFOEN_MSK);
	SET_BIT(UARTx->LCR, UART_LCR_RXEN_MSK);
}

/**
  * @brief  Initialize the UARTx peripheral using the default parameters.
  * @param  init: Pointer to a md_uart_init_t structure
  * @retval None
  */
void md_uart_init_struct(md_uart_init_t *init)
{
	init->baud        = 115200;
	init->word_length = MD_UART_WORD_LENGTH_8B;
	init->stop_bits   = MD_UART_STOP_BITS_1;
	init->parity      = MD_UART_PARITY_NONE;
	init->fctl        = MD_UART_FLOW_CTL_DISABLE;

	return;
}
/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
#endif
/**
 * @}
 */
