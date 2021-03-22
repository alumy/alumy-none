/**
  *********************************************************************************
  *
  * @file    md_cmu.c
  * @brief   CMU module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_cmu.h"
#include "md_syscfg.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_CMU

/** @addtogroup MD_CMU
  * @{
  */
/**
  * @defgroup MD_CMU_Private_Variables CMU Private Variables
  * @{
  */
uint32_t md_system_clock  = 24000000;
/**
  * @}
  */
/** @defgroup MD_CMU_Private_Functions CMU Private Functions
  * @{
  */

/**
  * @brief  Update the current system clock. This function
  *         will be invoked, when system clock has changed.
  * @param  clock: The new clock.
  * @retval None
  */

static void md_cmu_clock_update(uint32_t clock)
{
	md_system_clock = clock;
}
/**
  * @}
  */
/** @addtogroup MD_CMU_Public_Functions
  * @{
  */
/** @addtogroup MD_CMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Configure system clock using default.
  *         Select CMU_CLOCK_HRC(24MHz) as system clock and
  *         enable CMU_CLOCK_LRC(32768Hz).
  * @retval The status.
  */
md_status_t md_cmu_clock_config_default(void)
{
	uint32_t cnt = 4000, tmp;

	SYSCFG_UNLOCK();

	/* Select HRC */
	MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);
	while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

	if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HRC) {
		SYSCFG_LOCK();
		return MD_ERROR;
	}

	CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK);	/* Select 24Mhz */

	tmp = READ_REG(CMU->CLKENR);
	/* Enable HRC/LRC/LOSC */
	SET_BIT(tmp, CMU_CLKENR_HRCEN_MSK | CMU_CLKENR_LRCEN_MSK | CMU_CLKENR_LOSCEN_MSK);
	WRITE_REG(CMU->CLKENR, tmp);

	SYSCFG_LOCK();
	return MD_OK;
}

/**
  * @brief  Configure system clock using specified parameters
  * @param  clk: The parameter can be one of the following:
  *           @arg @ref MD_CMU_CLOCK_HRC  2MHz or 24MHz
  *           @arg @ref MD_CMU_CLOCK_LRC  32768Hz
  *           @arg @ref MD_CMU_CLOCK_LOSC 32768Hz
  *           @arg @ref MD_CMU_CLOCK_PLL1 32MHz, 48MHz or (32768*1024)Hz
  *           @arg @ref MD_CMU_CLOCK_HOSC 1MHz -- 24MHz
  * @param  clock: The clock which will be set. the value depends
  *         on the parameter of clk.
  * @retval The status.
  */
md_status_t md_cmu_clock_config(md_cmu_clock_t clk, uint32_t clock)
{
	uint32_t cnt = 4000;

	SYSCFG_UNLOCK();

	switch (clk) {
	case MD_CMU_CLOCK_HRC:
		assert_param(clock == 24000000 || clock == 2000000);

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HRC) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		if (clock == 24000000)
			CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK);
		else
			SET_BIT(CMU->CFGR, CMU_CFGR_HRCFST_MSK);

		SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);

		for (cnt = 4000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCRDY_MSK))) && (--cnt));

		md_cmu_clock_update(clock);
		break;

	case MD_CMU_CLOCK_LRC:
		/* Close SysTick interrupt in lower clock */
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_LRC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_LRC) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);

		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LRCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LRCRDY_MSK))) && (--cnt));

		md_cmu_clock_update(32768);
		break;

	case MD_CMU_CLOCK_LOSC:
		/* Close SysTick interrupt in lower clock */
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_LOSC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_LOSC) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);

		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LOSCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LOSCRDY_MSK))) && (--cnt));

		md_cmu_clock_update(32768);
		break;

	case MD_CMU_CLOCK_PLL1:
		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_PLL1 << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_PLL1) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);

		for (cnt = 4000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1ACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK))) && (--cnt));

		md_cmu_clock_update(clock);
		break;

	case MD_CMU_CLOCK_HOSC:
		assert_param(clock <= 24000000);

		MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HOSC << CMU_CSR_SYS_CMD_POSS);
		while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

		if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HOSC) {
			SYSCFG_LOCK();
			return MD_ERROR;
		}

		SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
		MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, clock / 1000000 - 1);

		for (cnt = 4000; cnt; --cnt);
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK))) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));

		md_cmu_clock_update(clock);
		break;

	default:
		break;
	}

	SYSCFG_LOCK();
	return MD_OK;
}

/**
  * @brief  Configure PLL1 using specified parameters.
  * @param  input: The input clock type.
  * @param  output: The output clock which can be 32MHz or 48MHz.
  *           When input = CMU_PLL1_INPUT_PLL2; then output must be
  *           CMU_PLL1_OUTPUT_32M, and then the real clock is (32768x1024)Hz.
  * @retval None
  */
void md_cmu_pll1_config(md_cmu_pll1_input_t input, md_cmu_pll1_output_t output)
{
	uint32_t cnt = 4000;

	SYSCFG_UNLOCK();

	if (input == MD_CMU_PLL1_INPUT_HRC_6) {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
	}
	else if (input == MD_CMU_PLL1_INPUT_PLL2) {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
		CLEAR_BIT(CMU->PLLCFG, CMU_PLLCFG_PLL2RFS_MSK);
		SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL2EN_MSK);
	}
	else {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
	}

	MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1RFS_MSK, input << CMU_PLLCFG_PLL1RFS_POSS);
	MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1OS_MSK, output << CMU_PLLCFG_PLL1OS_POS);
	SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);

	while ((READ_BIT(CMU->PLLCFG, CMU_PLLCFG_PLL1LCKN_MSK)) && (--cnt));
	cnt = 4000;
	while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK))) && (--cnt));

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Get AHB1 clock.
  * @retval The value of AHB1 clock.
  */
uint32_t md_cmu_get_hclk1_clock(void)
{
	uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
	uint32_t ahb_div = READ_BITS(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, CMU_CFGR_HCLK1DIV_POSS);

	return (md_system_clock >> sys_div) >> ahb_div;
}

/**
  * @brief  Get SYS clock
  * @retval The value of SYS clock
  */
uint32_t md_cmu_get_sys_clock(void)
{
	uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);

	return md_system_clock >> sys_div;
}

/**
  * @brief  Get APB1 clock.
  * @retval The value of APB1 clock.
  */
uint32_t md_cmu_get_pclk1_clock(void)
{
	uint32_t sys_div  = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
	uint32_t apb1_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, CMU_CFGR_PCLK1DIV_POSS);

	return (md_system_clock >> sys_div) >> apb1_div;
}

/**
  * @brief  Get APB2 clock.
  * @retval The value of APB2 clock.
  */
uint32_t md_cmu_get_pclk2_clock(void)
{
	uint32_t sys_div  = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
	uint32_t apb2_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, CMU_CFGR_PCLK2DIV_POSS);

	return (md_system_clock >> sys_div) >> apb2_div;
}

/**
  * @brief  Gets current system clock.
  * @retval The value of system clock.
  */
uint32_t md_cmu_get_clock(void)
{
	return md_system_clock;
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
