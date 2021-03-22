/**
  *********************************************************************************
  *
  * @file    md_trng.c
  * @brief   TRNG module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_trng.h"

/** @addtogroup Micro_Driver
  * @{
  */

#ifdef MD_TRNG

/** @addtogroup MD_TRNG
  * @{
  */

/** @addtogroup MD_TRNG_Public_Functions
  * @{
  */
/** @addtogroup MD_TRNG_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Initializes the TRNG according to the specified
  *         parameters in the md_trng_init_t.
  * @param  init: Pointer to a md_trng_init_t structure that contains
  *         the configuration information.
  * @retval None
  */
void md_trng_init(md_trng_init_t *init)
{
	SET_BIT(TRNG->CR, TRNG_CR_TRNGSEL_MSK);
	MODIFY_REG(TRNG->CR, TRNG_CR_DSEL_MSK, (init->data_width) << TRNG_CR_DSEL_POSS);
	MODIFY_REG(TRNG->CR, TRNG_CR_SDSEL_MSK, (init->seed_type) << TRNG_CR_SDSEL_POSS);
	MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (init->adjc) << TRNG_CR_ADJC_POSS);

	if (init->adjc == 0) {
		MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (0) << TRNG_CR_ADJC_POSS);
	}
	else {
		MODIFY_REG(TRNG->CR, TRNG_CR_ADJC_MSK, (1) << TRNG_CR_ADJC_POSS);
	}

	WRITE_REG(TRNG->SEED, init->seed);
	MODIFY_REG(TRNG->CFGR, TRNG_CFGR_TSTART_MSK, (init->t_start) << TRNG_CFGR_TSTART_POSS);
	MODIFY_REG(TRNG->CR, TRNG_CR_POSTEN_MSK, (init->posten) << TRNG_CR_POSTEN_MSK);
}

/**
  * @brief  Set each @ref md_trng_init_t field to default value.
  * @param  init: Pointer to a @ref md_trng_init_t structure which will be initialized.
  * @retval None
  */
void md_trng_struct_init(md_trng_init_t *init)
{
	init->data_width = MD_TRNG_DSEL_32B;
	init->seed_type  = MD_TRNG_SEED_TYPE_SEED;
	init->seed       = 12345678;
	init->t_start    = 30000;
	init->adjc       = 0;
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
