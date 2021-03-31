/**
  *********************************************************************************
  *
  * @file    md_spi.c
  * @brief   SPI module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_spi.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_SPI

/** @addtogroup MD_SPI
  * @{
  */

/** @addtogroup MD_SPI_Public_Functions
  * @{
  */
/** @addtogroup MD_SPI_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the SPI specificed.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
void md_spi_reset(SPI_TypeDef *SPIx)
{
	SPIx->CON1    = 0x0;
	SPIx->CON2    = 0x0;
	SPIx->CRCPOLY = 0x00000007;

	return;
}

/**
  * @brief  Initialize the SPI registers according to the specified parameters in init.
  * @note   As some bits in SPI configuration registers can only be written when the SPI is disabled (SPI_CON1_SPIEN bit =0),
  *         SPI IP should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @param  SPIx: SPI Instance
  * @param  init: pointer to a @ref md_spi_init_t structure
  * @retval An ErrorStatus enumeration value.
  */
md_status_t md_spi_init(SPI_TypeDef *SPIx, md_spi_init_t *init)
{
	uint32_t tmp = 0;

	md_spi_reset(SPIx);

	if ((init->mode) == MD_SPI_MODE_MASTER)
		tmp |= 1 << SPI_CON1_SSOUT_POS;

	tmp |= ((init->phase << SPI_CON1_CPHA_POS) | (init->polarity << SPI_CON1_CPOL_POS) |
	        (init->baud << SPI_CON1_BAUD_POSS) | (init->data_size << SPI_CON1_FLEN_POS) |
		(init->mode << SPI_CON1_MSTREN_POS) | (init->ss_en << SPI_CON1_SSEN_POS) |
		(init->first_bit << SPI_CON1_LSBFST_POS));

	SPIx->CON1 = tmp;

	if (init->dir == MD_SPI_DIRECTION_2LINES) {
		CLEAR_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK);
		CLEAR_BIT(SPIx->CON1, SPI_CON1_RXO_MSK);
	}
	else if (init->dir == MD_SPI_DIRECTION_2LINES_RXONLY) {
		CLEAR_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK);
		SET_BIT(SPIx->CON1, SPI_CON1_RXO_MSK);
	}
	else {
		SET_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK);
	}

	/* configure CRC */
	SPIx->CON1   |= (init->crc_calc << SPI_CON1_CRCEN_POS);
	SPIx->CRCPOLY = init->crc_poly;

	md_spi_enable(SPIx);
	return MD_OK;
}

/**
  * @brief  Set each @ref md_spi_init_t field to default value.
  * @param  init: pointer to a @ref md_spi_init_t structure
  * whose fields will be set to default values.
  * @retval None
  */
void md_spi_struct_init(md_spi_init_t *init)
{
	init->mode      = MD_SPI_MODE_MASTER;
	init->dir       = MD_SPI_DIRECTION_2LINES;
	init->data_size	= MD_SPI_DATA_SIZE_8;
	init->baud      = MD_SPI_BAUD_16;
	init->phase     = MD_SPI_CPHA_SECOND;
	init->polarity	= MD_SPI_CPOL_HIGH;
	init->first_bit	= MD_SPI_FIRSTBIT_MSB;
	init->ss_en     = DISABLE;
	init->crc_calc	= DISABLE;
	init->crc_poly	= 0;
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
