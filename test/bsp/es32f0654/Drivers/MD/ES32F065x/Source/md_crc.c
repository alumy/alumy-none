/**
  *********************************************************************************
  *
  * @file    md_crc.c
  * @brief   CRC module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_crc.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_CRC

/** @addtogroup MD_CRC
  * @{
  */

/** @addtogroup MD_CRC_Public_Functions
  * @{
  */
/** @addtogroup MD_CRC_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the CRC peripheral.
  * @retval None
  */
void md_crc_reset_reg(void)
{
	CRC->DATA = 0x0;
	CRC->CR   = 0x2;
	CRC->SEED = 0xFFFFFFFF;
}

/**
  * @brief  Initializes the CRC mode according to the specified parameters in
  *         the md_crc_init_t.
  * @param  init: Pointer to a md_crc_init_t structure that contains
  *         the configuration information for the specified CRC module.
  * @retval None
  */
void md_crc_init(md_crc_init_t *init)
{
	uint32_t tmp = 0;

	md_crc_reset_reg();
	tmp |= ((init->chs_rev << CRC_CR_CHSREV_POS) | (init->data_inv << CRC_CR_DATREV_POS) |
		(init->chs_inv << CRC_CR_CHSINV_POS) | (init->mode << CRC_CR_MODE_POSS) |
		(init->len << CRC_CR_DATLEN_POSS) | (init->data_rev << CRC_CR_DATREV_POS) |
		(init->order << CRC_CR_BYTORD_POS));
	WRITE_REG(CRC->CR, tmp);
	WRITE_REG(CRC->SEED, init->seed);
	MD_CRC_RESET();
	MD_CRC_ENABLE();

	return;
}

/**
  * @brief  Initialize the CRC peripheral using the default parameters.
  * @param  init: Pointer to a md_crc_init_t structure
  * @retval None
  */
void md_crc_init_struct(md_crc_init_t *init)
{
	init->mode     = MD_CRC_MODE_CCITT;
	init->len      = MD_CRC_DATASIZE_8;
	init->order    = MD_CRC_BYTORD_LOW;
	init->data_rev = DISABLE;
	init->data_inv = DISABLE;
	init->chs_rev  = DISABLE;
	init->chs_inv  = DISABLE;
	init->seed     = 0x0;

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
