/**
  *********************************************************************************
  *
  * @file    md_pmu.c
  * @brief   Power management unit driver.
  *
  * @version V1.0
  * @date    07 May 2020
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_pmu.h"
#include "md_syscfg.h"


/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_PMU

/** @addtogroup MD_PMU
  * @{
  */

/** @addtogroup MD_PMU_Public_Functions
  * @{
  */
/** @addtogroup MD_PMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the PMU register
  * @retval None
  */
void md_pmu_reset(void)
{
	SYSCFG_UNLOCK();
	WRITE_REG(PMU->CR, 0x0);
	WRITE_REG(PMU->LVDCR, 0x0);
	WRITE_REG(PMU->PWRCR, 0xFF);
	SYSCFG_LOCK();

	return;
}

/**
  * @brief  Enter stop1 mode
  * @retval None
  */
void md_pmu_stop1_enter(void)
{
	SYSCFG_UNLOCK();
	MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, MD_PMU_LP_STOP1 << PMU_CR_LPM_POSS);
	SYSCFG_LOCK();

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	return;
}

/**
  * @brief  Enter stop2 mode
  * @retval None
  */
void md_pmu_stop2_enter(void)
{
	SYSCFG_UNLOCK();
	SET_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);
	MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, MD_PMU_LP_STOP2 << PMU_CR_LPM_POSS);
	SYSCFG_LOCK();

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	return;
}

/**
  * @brief  Enter standby mode
  * @param  port: The port whick wake up the standby mode.
  * @param  level: Wakeup level.
  * @retval None
  */
void md_pmu_standby_enter(md_pmu_wakeup_port_t port, md_pmu_wakeup_level_t level)
{
	if (port == MD_PMU_STANDBY_PORT_SEL_NONE) {
		WRITE_REG(BKPC->PROT, 0x9669AA55);
		CLEAR_BIT(BKPC->CR, BKPC_CR_WKPEN_MSK);
		WRITE_REG(BKPC->PROT, 0);
		return;
	}

	WRITE_REG(BKPC->PROT, 0x9669AA55);
	SET_BIT(BKPC->CR, BKPC_CR_WKPEN_MSK);
	MODIFY_REG(BKPC->CR, BKPC_CR_WKPS_MSK, port << BKPC_CR_WKPS_POSS);
	MODIFY_REG(BKPC->CR, BKPC_CR_WKPOL_MSK, level << BKPC_CR_WKPOL_POS);
	WRITE_REG(BKPC->PROT, 0);

	SYSCFG_UNLOCK();
	SET_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);
	MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, MD_PMU_LP_STANDBY << PMU_CR_LPM_POSS);
	SYSCFG_LOCK();

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	return;
}

/**
  * @brief  Configure lvd using specified parameters.
  * @param  sel: LVD threshold voltage.
  * @param  mode: LVD trigger mode.
  * @param  state: New state, ENABLE/DISABLE;
  * @retval None
  */
void md_pmu_lvd_config(md_pmu_lvd_voltage_sel_t sel, md_pmu_lvd_trigger_mode_t mode, type_func_t state)
{
	SYSCFG_UNLOCK();

	if (state) {
		MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, sel << PMU_LVDCR_LVDS_POSS);
		MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, mode << PMU_LVDCR_LVIFS_POSS);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
	}
	else {
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
		CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
		CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
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
