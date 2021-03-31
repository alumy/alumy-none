/**
  *********************************************************************************
  *
  * @file    md_gpio.c
  * @brief   GPIO module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_gpio.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_GPIO

/** @addtogroup MD_GPIO
  * @{
  */

/** @addtogroup MD_GPIO_Public_Functions
  * @{
  */
/** @addtogroup MD_GPIO_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Initialize the GPIOx peripheral according to the specified
  *         parameters in the gpio_init_t.
  * @param  GPIOx: Where x can be (A--H) to select the GPIO peripheral.
  * @param  pin: The pin which need to initialize.
  * @param  init: Pointer to a md_gpio_init_t structure that can contains
  *         the configuration information for the specified parameters.
  * @retval None
  */
void md_gpio_init(GPIO_TypeDef *GPIOx, uint16_t pin, md_gpio_init_t *init)
{
	uint32_t i, pos, mask, tmp;

	for (i = 0; i < 16; ++i) {
		if (((pin >> i) & 0x1) == 0)
			continue;

		/* Get position and 2-bits mask */
		pos  = i << 1;
		mask = 0x3 << pos;

		/* Set PIN mode */
		tmp  = READ_REG(GPIOx->MODE);
		tmp &= ~mask;
		tmp |= (init->mode << pos);
		WRITE_REG(GPIOx->MODE, tmp);

		/* Set PIN open-drain or push-pull */
		tmp  = READ_REG(GPIOx->ODOS);
		tmp &= ~mask;
		tmp |= (init->odos << pos);
		WRITE_REG(GPIOx->ODOS, tmp);

		/* Set PIN push-up or/and push-down */
		tmp  = READ_REG(GPIOx->PUPD);
		tmp &= ~mask;
		tmp |= (init->pupd << pos);
		WRITE_REG(GPIOx->PUPD, tmp);

		/* Set PIN output driver */
		tmp  = READ_REG(GPIOx->ODRV);
		tmp &= ~mask;
		tmp |= (init->odrv << pos);
		WRITE_REG(GPIOx->ODRV, tmp);

		/* Get position and 1-bit mask */
		pos  = i;
		mask = 0x1 << pos;

		/* Set PIN filter enable or disable */
		tmp  = READ_REG(GPIOx->FLT);
		tmp &= ~mask;
		tmp |= (init->flt << pos);
		WRITE_REG(GPIOx->FLT, tmp);

		/* Set PIN type ttl or smit */
		tmp  = READ_REG(GPIOx->TYPE);
		tmp &= ~mask;
		tmp |= (init->type << pos);
		WRITE_REG(GPIOx->TYPE, tmp);

		/* Configure PIN function */
		pos  = i < 8 ? (i << 2) : ((i - 8) << 2);
		mask = 0xF << pos;
		tmp  = i < 8 ? READ_REG(GPIOx->FUNC0) : READ_REG(GPIOx->FUNC1);
		tmp &= ~mask;
		tmp |= (init->func << pos);
		i < 8 ? WRITE_REG(GPIOx->FUNC0, tmp) : WRITE_REG(GPIOx->FUNC1, tmp);
	}

	return;
}

/**
  * @brief  Initialize the GPIOx peripheral using the default parameters.
  * @param  init: Pointer to a md_gpio_init_t structure
  * @retval None
  */
void md_gpio_init_struct(md_gpio_init_t *init)
{
	/* Fill md_gpio_init_t structure with default parameter */
	init->mode = MD_GPIO_MODE_OUTPUT;
	init->odos = MD_GPIO_PUSH_PULL;
	init->pupd = MD_GPIO_PUSH_UP;
	init->odrv = MD_GPIO_OUT_DRIVE_NORMAL;
	init->flt  = MD_GPIO_FILTER_DISABLE;
	init->type = MD_GPIO_TYPE_CMOS;
	init->func = MD_GPIO_FUNC_1;

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
