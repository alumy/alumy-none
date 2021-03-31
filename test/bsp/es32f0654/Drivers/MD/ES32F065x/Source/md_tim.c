/**
  *********************************************************************************
  *
  * @file    md_tim.c
  * @brief   TIM module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_tim.h"

/** @addtogroup Micro_Driver
  * @{
  */

#ifdef MD_TIM

/** @addtogroup MD_TIMER
  * @{
  */

/** @addtogroup MD_TIMER_Public_Functions
  * @{
  */
/** @addtogroup MD_TIMER_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Timer Base configuration
  * @param  TIMERx: TIMER periheral
  * @param  init: TIMER Base configuration structure
  * @retval None
  */
void md_timer_base_set_config(TIMER_TypeDef *TIMERx, md_timer_base_init_t *init)
{
	if (init->mode == MD_TIMER_CNT_MODE_UP || init->mode == MD_TIMER_CNT_MODE_DOWN) {
		CLEAR_BIT(TIMERx->CON1, TIMER_CON1_CMSEL_MSK);
		MODIFY_REG(TIMERx->CON1, TIMER_CON1_DIRSEL_MSK, init->mode << TIMER_CON1_DIRSEL_POS);
	}
	else {
		MODIFY_REG(TIMERx->CON1, TIMER_CON1_CMSEL_MSK, (init->mode - 1) << TIMER_CON1_CMSEL_POSS);
	}

	if (IS_TIMER_CLOCK_DIVISION_INSTANCE(TIMERx))
		MODIFY_REG(TIMERx->CON1, TIMER_CON1_DFCKSEL_MSK, init->clk_div << TIMER_CON1_DFCKSEL_POSS);

	WRITE_REG(TIMERx->AR, init->period);
	WRITE_REG(TIMERx->PRES, init->prescaler);

	if (IS_TIMER_REPETITION_COUNTER_INSTANCE(TIMERx))
		WRITE_REG(TIMERx->REPAR, init->re_cnt);

	return;
}

/**
  * @brief  Set the fields of the time base unit configuration data structure
  *         to their default values.
  * @param  timer_init_struct pointer to a @ref md_timer_base_init_t structure (time base unit configuration data structure)
  * @retval None
  */
void md_timer_base_struct_init(md_timer_base_init_t *timer_init_struct)
{
	/* Set the default configuration */
	timer_init_struct->prescaler   = (uint16_t)0x0000;
	timer_init_struct->mode        = MD_TIMER_CNT_MODE_UP;
	timer_init_struct->period      = 0xFFFFFFFFU;
	timer_init_struct->clk_div     = MD_TIMER_CLOCK_DIV1;
	timer_init_struct->re_cnt      = (uint8_t)0x00;
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
