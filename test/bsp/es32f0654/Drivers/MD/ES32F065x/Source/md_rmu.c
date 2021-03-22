/**
  *********************************************************************************
  *
  * @file    md_rmu.c
  * @brief   Reset management unit driver.
  *
  * @version V1.0
  * @date    07 May 2020
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_rmu.h"
#include "md_syscfg.h"


/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_RMU

/** @addtogroup MD_RMU
  * @{
  */

/** @addtogroup MD_RMU_Public_Functions
  * @{
  */
/** @addtogroup MD_RMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the RMU register
  * @retval None
  */
void md_rmu_reset(void)
{
	SYSCFG_UNLOCK();
	WRITE_REG(RMU->CR, 0x0);
	WRITE_REG(RMU->CRSTSR, 0xFFFF);
	WRITE_REG(RMU->AHB1RSTR, 0x0);
	WRITE_REG(RMU->AHB2RSTR, 0x0);
	WRITE_REG(RMU->APB1RSTR, 0x0);
	WRITE_REG(RMU->APB2RSTR, 0x0);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Configure BOR parameters.
  * @param  flt: filter time.
  * @param  vol: The voltage.
  * @param  state: The new status: ENABLE/DISABLE.
  * @retval None
  */
void md_rmu_bor_config(md_rmu_bor_filter_t flt, md_rmu_bor_vol_t vol, type_func_t state)
{
	SYSCFG_UNLOCK();

	if (state) {
		MODIFY_REG(RMU->CR, RMU_CR_BORFLT_MSK, flt << RMU_CR_BORFLT_POSS);
		MODIFY_REG(RMU->CR, RMU_CR_BORVS_MSK, vol << RMU_CR_BORVS_POSS);
		SET_BIT(RMU->CR, RMU_CR_BOREN_MSK);
	}
	else {
		CLEAR_BIT(RMU->CR, RMU_CR_BOREN_MSK);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Get specified reset status
  * @param  state: Speicifies the type of the reset,
  * @retval The status.
  */
uint32_t md_rmu_get_reset_status(md_rmu_state_t state)
{
	if (state == MD_RMU_RST_ALL)
		return RMU->RSTSR;

	if (READ_BIT(RMU->RSTSR, state))
		return SET;

	return RESET;
}

/**
  * @brief  Clear the specified reset status
  * @param  state: Specifies the type of the reset,
  * @retval None
  */
void md_rmu_clear_reset_status(md_rmu_state_t state)
{
	SYSCFG_UNLOCK();
	WRITE_REG(RMU->CRSTSR, state);
	SYSCFG_LOCK();

	return;
}
/**
  * @brief  Reset peripheral device
  * @param  perh: The peripheral device,
  * @retval None
  */
void md_rmu_reset_periperal(md_rmu_peripheral_t perh)
{
	uint32_t idx, pos;

	idx = ((uint32_t)perh >> 27) & 0x7;
	pos = perh & ~(0x7 << 27);
	SYSCFG_UNLOCK();

	switch (idx) {
	case 0:
		WRITE_REG(RMU->AHB1RSTR, pos);
		break;
	case 1:
		WRITE_REG(RMU->AHB2RSTR, pos);
		break;
	case 2:
		WRITE_REG(RMU->APB1RSTR, pos);
		break;
	case 4:
		WRITE_REG(RMU->APB2RSTR, pos);
		break;
	default:
		break;
	}

	SYSCFG_LOCK();
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
