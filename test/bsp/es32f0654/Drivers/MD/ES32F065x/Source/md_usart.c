/**
  *********************************************************************************
  *
  * @file    md_usart.c
  * @brief   USART module driver.
  *
  * @version V1.0
  * @date    19 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_usart.h"
#include "md_cmu.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_USART

/** @addtogroup MD_USART
  * @{
  */

/** @addtogroup MD_USART_Public_Functions
  * @{
  */
/** @addtogroup MD_USART_Public_Functions_Group1 
  * @{
  */
/**
  * @brief  Reset the USART peripheral.
  * @param  USARTx: USART Peripheral
  * @retval None
  */
void md_usart_reset(USART_TypeDef *USARTx)
{
	md_usart_disable(USARTx);

	WRITE_REG(USARTx->CON0, 0x0);
	WRITE_REG(USARTx->CON1, 0x0);
	WRITE_REG(USARTx->CON2, 0x0);

	return;
}

/**
  * @brief  Initializes the USART mode according to the specified parameters.
  * @param  USARTx: USART Peripheral.
  * @param  init: The Initialize structure.
  * @retval None
  */
void md_usart_init(USART_TypeDef *USARTx, md_usart_init_t *init)
{
	uint32_t tmp;
	uint32_t integer;
	uint32_t fractional;

	md_usart_reset(USARTx);
	MODIFY_REG(USARTx->CON0, USART_CON0_DLEN_MSK, init->word_length);
	MODIFY_REG(USARTx->CON0, USART_CON0_PEN_MSK | USART_CON0_PSEL_MSK, init->parity);
	MODIFY_REG(USARTx->CON0, USART_CON0_RXEN_MSK | USART_CON0_TXEN_MSK, init->mode);
	MODIFY_REG(USARTx->CON1, USART_CON1_STPLEN_MSK, init->stop_bits);
	MODIFY_REG(USARTx->CON2, USART_CON2_RTSEN_MSK | USART_CON2_CTSEN_MSK, init->fctl);

	/* Determine the integer part */
	integer = ((25 * md_cmu_get_pclk1_clock()) / (4 * (init->baud)));
	tmp     = (integer / 100) << 4;

	/* Determine the fractional part */
	fractional = integer - (100 * (tmp >> 4));
	tmp       |= ((((fractional * 16) + 50) / 100) & ((uint8_t)0x0F));

	WRITE_REG(USARTx->BAUDCON, (uint16_t)tmp);
	md_usart_enable(USARTx);
	return;
}

/**
  * @brief Set each @ref md_usart_init_t field to default value.
  * @param init: pointer to a @ref md_usart_init_t structure.
  * @retval None
  */

void md_usart_init_struct(md_usart_init_t *init)
{
	init->baud        = 115200;
	init->word_length = MD_USART_WORD_LENGTH_8B;
	init->stop_bits   = MD_USART_STOP_BITS_1;
	init->parity      = MD_USART_PARITY_NONE ;
	init->mode        = MD_USART_MODE_TX_RX;
	init->fctl        = MD_USART_HW_FLOW_CTL_NONE;
}

/**
  * @brief  Initializes the synchronization mode.
  * @param  USARTx: USART Peripheral.
  * @param  init: USART Clock Init Structure.
  * @retval Status.
  */
void md_usart_clock_init(USART_TypeDef *USARTx, md_usart_clock_init_t *init)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_LBCP_MSK, init->last_bit);
	MODIFY_REG(USARTx->CON1, USART_CON1_SCKPHA_MSK, init->phase);
	MODIFY_REG(USARTx->CON1, USART_CON1_SCKPOL_MSK, init->polarity);
	MODIFY_REG(USARTx->CON1, USART_CON1_SCKEN_MSK, init->clk);
	md_usart_enable(USARTx);

	return;
}

/**
  * @brief Set each field of @ref md_usart_clock_init_t structure to default value.
  * @param init: pointer to a @ref md_usart_clock_init_t structure
  * @retval None
  */
void md_usart_clock_init_struct(md_usart_clock_init_t *init)
{
	init->clk      = MD_USART_CLOCK_DISABLE;
	init->polarity = MD_USART_CPOL_LOW;
	init->phase    = MD_USART_CPHA_1EDGE;
	init->last_bit = MD_USART_LAST_BIT_DISABLE;
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
