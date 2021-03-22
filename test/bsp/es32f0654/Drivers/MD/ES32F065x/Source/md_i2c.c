/**
  *********************************************************************************
  *
  * @file    md_i2c.c
  * @brief   I2C module driver.
  *
  * @version V1.0
  * @date    15 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *********************************************************************************
 */

#include "md_i2c.h"
#include "md_cmu.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_I2C
/** @defgroup MD_I2C I2C
  * @{
  */

/** @addtogroup MD_I2C_Public_Functions
  * @{
  */

/** @addtogroup MD_I2C_Public_Functions_Group1
  * @{
  */

/**
  * @brief  I2C Configuration Speed function
  * @param  hperh: Pointer to a i2c_init_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  i2c_clk: PCLK frequency from RCC.
  * @retval CCR Speed: Speed to set in I2C CCR Register
  */
uint32_t i2c_configure_speed(md_i2c_init_t *hperh, uint32_t i2c_clk)
{
	uint32_t tmp1 = 0;

	if (hperh->clk_speed <= MD_I2C_STANDARD_MODE_MAX_CLK) {
		tmp1 = (i2c_clk / (hperh->clk_speed << 1));
		if ((tmp1 & MD_I2C_CKCFG_CLKSET) < 4 )
			return 4;
		else
			return tmp1;
	}
	else {
		tmp1 = MD_I2C_CKCFG_CLKMOD;

		if (hperh->duty == MD_I2C_DUTYCYCLE_2)
			tmp1 |= (i2c_clk / (hperh->clk_speed * 3)) | MD_I2C_DUTYCYCLE_2;
		else
			tmp1 |= (i2c_clk / (hperh->clk_speed * 25)) | MD_I2C_DUTYCYCLE_16_9;

		if ((tmp1 & MD_I2C_CKCFG_CLKSET) < 1 )
			return 1;
		else
			return tmp1;
	}
}

/**
  * @brief  Initializes the I2C according to the specified parameters
  *         in the i2c_init_t and initialize the associated handle.
  * @param  I2Cx: I2C Instance.
  * @param  hperh: Pointer to a i2c_init_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval Status, see @ref md_status_t.
  */
md_status_t md_i2c_init(I2C_TypeDef *I2Cx, md_i2c_init_t *hperh)
{
	uint32_t freqrange = 0;
	uint32_t pclk1 = 0;

	if (hperh == NULL)
		return MD_ERROR;

	pclk1 = md_cmu_get_pclk1_clock();

	MD_I2C_DISABLE(I2Cx);

	freqrange = ((pclk1) / 1000000);
	WRITE_REG(I2Cx->CON2, freqrange);
	WRITE_REG(I2Cx->RT, MD_I2C_RISE_TIME(freqrange, hperh->clk_speed));
	WRITE_REG(I2Cx->CKCFG, i2c_configure_speed(hperh, pclk1));
	WRITE_REG(I2Cx->CON1, hperh->general_call);
	SET_BIT(I2Cx->CON1, hperh->no_stretch);
	WRITE_REG(I2Cx->ADDR1, (hperh->addr_mode | hperh->own_addr1));
	WRITE_REG(I2Cx->ADDR2, (hperh->dual_addr | hperh->own_addr2));

	MD_I2C_ENABLE(I2Cx);

	return MD_OK;
}

/**
  * @brief  Set each @ref md_i2c_init_t field to default value.
  * @param  init Pointer to a @ref md_i2c_init_t structure.
  * @retval None
  */
void md_i2c_struct_init(md_i2c_init_t *init)
{
	init->clk_speed    = MD_I2C_STANDARD_MODE_MAX_CLK;
	init->duty         = MD_I2C_DUTYCYCLE_2;
	init->own_addr1    = 0x0A;
	init->addr_mode    = MD_I2C_ADDR_7BIT;
	init->general_call = MD_I2C_GENERALCALL_DISABLE;
	init->no_stretch   = MD_I2C_NOSTRETCH_DISABLE;
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
