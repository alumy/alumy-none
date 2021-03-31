/**
  *********************************************************************************
  *
  * @file    md_cmu.h
  * @brief   Header file of CMU module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */


#ifndef __MD_CMU_H__
#define __MD_CMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_CMU CMU
  * @brief CMU micro driver
  * @verbatim
      In this module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F065x series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> BS16T0
      TIMER2 ----> GP16C2T0
      TIMER3 ----> GP16C2T1
      TIMER4 ----> BS16T1
      TIMER5 ----> BS16T2
      TIMER6 ----> GP16C4T0
      TIMER7 ----> BS16T3
     
      2. For ES32F033x/ES32F093x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> BS16T0
      TIMER2 ----> GP16C2T0
      TIMER3 ----> GP16C2T1
      TIMER4 ----> BS16T1
      TIMER5 ----> BS16T2
      TIMER6 ----> GP16C4T1
      TIMER7 ----> BS16T3
    @endverbatim
  * @{
  */

/** @defgroup MD_CMU_Public_Types CMU Public Types
  * @{
  */
/**
  * @brief CMU state structure definition
  */
typedef	enum {
	MD_CMU_CLOCK_HRC  = 0x1U,	/**< HRC */
	MD_CMU_CLOCK_LRC  = 0x2U,	/**< LRC */
	MD_CMU_CLOCK_LOSC = 0x3U,	/**< LOSC */
	MD_CMU_CLOCK_PLL1 = 0x4U,	/**< PLL1 */
	MD_CMU_CLOCK_HOSC = 0x5U,	/**< HOSC */
} md_cmu_clock_t;

/**
  * @brief PLL1 referance clock
  */
typedef enum {
	MD_CMU_PLL1_INPUT_HRC_6  = 0x0U,	/**< HRC  / 6 */
	MD_CMU_PLL1_INPUT_PLL2   = 0x1U,	/**< PLL2 */
	MD_CMU_PLL1_INPUT_HOSC   = 0x2U,	/**< HOSC / 1 */
	MD_CMU_PLL1_INPUT_HOSC_2 = 0x3U,	/**< HOSC / 2 */
	MD_CMU_PLL1_INPUT_HOSC_3 = 0x4U,	/**< HOSC / 3 */
	MD_CMU_PLL1_INPUT_HOSC_4 = 0x5U,	/**< HOSC / 4 */
	MD_CMU_PLL1_INPUT_HOSC_5 = 0x6U,	/**< HOSC / 5 */
	MD_CMU_PLL1_INPUT_HOSC_6 = 0x7U,	/**< HOSC / 6 */
} md_cmu_pll1_input_t;

/**
  * @brief PLL1 output clock
  */
typedef enum {
	MD_CMU_PLL1_OUTPUT_32M = 0x0U,	/**< x8  (32MHz) */
	MD_CMU_PLL1_OUTPUT_48M = 0x1U,	/**< x12 (48MHz) */
} md_cmu_pll1_output_t;

/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions CMU Public Functions
  * @{
  */
/** @defgroup MD_CMU_Public_Functions_Group2 CSR
  * @{
  */
/**
  * @brief  Configure system clock.
  * @param  clk: Clock parameter. can be one of the following values:
  *         @arg @ref MD_CMU_CLOCK_HRC
  *         @arg @ref MD_CMU_CLOCK_LRC
  *         @arg @ref MD_CMU_CLOCK_LOSC
  *         @arg @ref MD_CMU_CLOCK_PLL1
  *         @arg @ref MD_CMU_CLOCK_HOSC  
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_config_clock(md_cmu_clock_t clk)
{
	MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, clk);
}

/**
  * @brief  Get system clock.
  * @retval Current system clock. Can be one of the following values:
  *         @arg @ref MD_CMU_CLOCK_HRC
  *         @arg @ref MD_CMU_CLOCK_LRC
  *         @arg @ref MD_CMU_CLOCK_LOSC
  *         @arg @ref MD_CMU_CLOCK_PLL1
  *         @arg @ref MD_CMU_CLOCK_HOSC  
  */
__STATIC_INLINE uint32_t md_cmu_get_current_clock(void)
{
	return READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS);
}

/**
  * @brief  Get Status of switch clock.
  * @retval Status:
  *         - 0: Ready
  *         - 1: Busy
  */
__STATIC_INLINE uint32_t md_cmu_get_sys_rdyn(void)
{
	return READ_BITS(CMU->CSR, CMU_CSR_SYS_RDYN_MSK, CMU_CSR_SYS_RDYN_POS);
}

/**
  * @brief  Configure system clock filter.
  * @param  cft: Value of the following:
  *         - 0x55: Select system clock
  *         - 0xAA: Select shadow clock
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_config_cft(uint32_t cft)
{
	MODIFY_REG(CMU->CSR, CMU_CSR_CFT_CMD_MSK, cft << CMU_CSR_CFT_CMD_POSS);
}

/**
  * @brief  Get system clock.
  * @retval Current filter clock:
  *         - 0: Select system clock
  *         - 1: Select shadow clock 
  */
__STATIC_INLINE uint32_t md_cmu_get_active_filter(void)
{
	return READ_BITS(CMU->CSR, CMU_CSR_CFT_STU_MSK, CMU_CSR_CFT_STU_POS);
}

/**
  * @brief  Get Status of switch filter clock.
  * @retval Status:
  *         - 0: Ready
  *         - 1: Busy
  */
__STATIC_INLINE uint32_t md_cmu_get_cft_rdyn(void)
{
	return READ_BITS(CMU->CSR, CMU_CSR_CFT_RDYN_MSK, CMU_CSR_CFT_RDYN_POS);
}

/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group3 CFGR
  * @{
  */
/**
  * @brief  Sets HCLK1 divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_hclk1_div(uint32_t div)
{
	MODIFY_REG(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, div << CMU_CFGR_HCLK1DIV_POSS);
}

/**
  * @brief  Gets HCLK1 divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_hclk1_div(void)
{
	return READ_BITS(CMU->CFGR, CMU_CFGR_HCLK1DIV_MSK, CMU_CFGR_HCLK1DIV_POSS);
}

/**
  * @brief  Sets SYSCLK divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_sysclk_div(uint32_t div)
{
	MODIFY_REG(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, div << CMU_CFGR_SYSDIV_POSS);
}

/**
  * @brief  Gets SYSCLK divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_sysclk_div(void)
{
	return READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
}

/**
  * @brief  Sets PCLK1 divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_pclk1_div(uint32_t div)
{
	MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, div << CMU_CFGR_PCLK1DIV_POSS);
}

/**
  * @brief  Gets PCLK1 divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_pclk1_div(void)
{
	return READ_BITS(CMU->CFGR, CMU_CFGR_PCLK1DIV_MSK, CMU_CFGR_PCLK1DIV_POSS);
}

/**
  * @brief  Sets PCLK2 divider.
  * @param  div: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_pclk2_div(uint32_t div)
{
	MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, div << CMU_CFGR_PCLK2DIV_POSS);
}

/**
  * @brief  Gets PCLK2 divider.
  * @retval  divider: Value of the following:
  *         - 0x0: Fclk / 1
  *         - 0x1: Fclk / 2
  *         - 0x2: Fclk / 4
  *         - 0x3: Fclk / 8
  *         - 0x4: Fclk / 16
  *         - 0x5: Fclk / 32
  *         - 0x6: Fclk / 64
  *         - 0x7: Fclk / 128
  *         - 0x8: Fclk / 256
  *         - 0x9: Fclk / 512
  *         - 0xA: Fclk / 1024
  *         - 0xB: Fclk / 2048
  *         - 0xC: Fclk / 4096
  */
__STATIC_INLINE uint32_t md_cmu_get_pclk2_div(void)
{
	return READ_BITS(CMU->CFGR, CMU_CFGR_PCLK2DIV_MSK, CMU_CFGR_PCLK2DIV_POSS);
}

/**
  * @brief  Sets HRC frequency
  * @param  freq: Value of the following:
  *         - 0x0: 24MHz
  *         - 0x1: 2MHz
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_set_hrc_freq(uint32_t freq)
{
	MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, freq << CMU_CFGR_HRCFSW_POS);
}

/**
  * @brief  Gets HRC frequency
  * @retval  freq: Value of the following:
  *         - 0x0: 24MHz
  *         - 0x1: 2MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_hrc_freq(void)
{
	return READ_BITS(CMU->CFGR, CMU_CFGR_HRCFST_MSK, CMU_CFGR_HRCFST_POS);
}
/**
  * @}
  */

/** @defgroup MD_CMU_Public_Functions_Group4 CLKENR
  * @{
  */
/**
  * @brief  Enable HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_hosc(void)
{
	SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
}

/**
  * @brief  Disable HOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_hosc(void)
{
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
}

/**
  * @brief  Gets HOSC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc(void)
{
	return READ_BITS(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK, CMU_CLKENR_HOSCEN_POS);
}

/**
  * @brief  Enable LOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_losc(void)
{
	SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
}

/**
  * @brief  Disable LOSC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_losc(void)
{
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
}

/**
  * @brief  Gets LOSC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc(void)
{
	return READ_BITS(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK, CMU_CLKENR_LOSCEN_POS);
}

/**
  * @brief  Enable HRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_hrc(void)
{
	SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
}

/**
  * @brief  Disable HRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_hrc(void)
{
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
}

/**
  * @brief  Gets HRC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hrc(void)
{
	return READ_BITS(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK, CMU_CLKENR_HRCEN_POS);
}

/**
  * @brief  Enable LRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_lrc(void)
{
	SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
}

/**
  * @brief  Disable LRC
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_lrc(void)
{
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
}

/**
  * @brief  Gets LRC status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lrc(void)
{
	return READ_BITS(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK, CMU_CLKENR_LRCEN_POS);
}

/**
  * @brief  Enable PLL1
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_enable_pll1(void)
{
	SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
}

/**
  * @brief  Disable PLL1
  * @retval NONE
  */
__STATIC_INLINE void md_cmu_disable_pll1(void)
{
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
}

/**
  * @brief  Gets PLL1 status
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll1(void)
{
	return READ_BITS(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK, CMU_CLKENR_PLL1EN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group5 CLKSR
  * @{
  */
/**
  * @brief  Check the HOSC is active. 
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_hosc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK, CMU_CLKSR_HOSCACT_POS);
}

/**
  * @brief  Check the LOSC is active. 
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_losc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_LOSCACT_MSK, CMU_CLKSR_LOSCACT_POS);
}

/**
  * @brief  Check the HRC is active. 
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_hrc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_HRCACT_MSK, CMU_CLKSR_HRCACT_POS);
}

/**
  * @brief  Check the LRC is active. 
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_lrc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_LRCACT_MSK, CMU_CLKSR_LRCACT_POS);
}

/**
  * @brief  Check the ULRC is active. 
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_ulrc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_ULRCACT_MSK, CMU_CLKSR_ULRCACT_POS);
}

/**
  * @brief  Check the PLL1 is active. 
  * @retval Status:
  *         - 0: Not active
  *         - 1: Active
  */
__STATIC_INLINE uint32_t md_cmu_is_active_state_pll1(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_PLL1ACT_MSK, CMU_CLKSR_PLL1ACT_POS);
}

/**
  * @brief  Check the HOSC is stable. 
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_hosc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK, CMU_CLKSR_HOSCRDY_POS);
}

/**
  * @brief  Check the LOSC is stable. 
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_losc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_LOSCRDY_MSK, CMU_CLKSR_LOSCRDY_POS);
}

/**
  * @brief  Check the HRC is stable. 
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_hrc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_HRCRDY_MSK, CMU_CLKSR_HRCRDY_POS);
}

/**
  * @brief  Check the LRC is stable. 
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_lrc(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_LRCRDY_MSK, CMU_CLKSR_LRCRDY_POS);
}

/**
  * @brief  Check the PLL1 is stable. 
  * @retval Status:
  *         - 0: Not stable
  *         - 1: Stable
  */
__STATIC_INLINE uint32_t md_cmu_is_stable_state_pll1(void)
{
	return READ_BITS(CMU->CLKSR, CMU_CLKSR_PLL1RDY_MSK, CMU_CLKSR_PLL1RDY_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group6 PLLCFG
  * @{
  */
/**
  * @brief  Sets referenc clock of PLL1. 
  * @param  clk: The value of following:
  *         - 0x0: HRC / 6
  *         - 0x2: HOSC
  *         - 0x3: HOSC / 2
  *         - 0x4: HOSC / 3
  *         - 0x5: HOSC / 4
  *         - 0x6: HOSC / 5
  *         - 0x7: HOSC / 6
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pll1_source(uint32_t clk)
{
	MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1RFS_MSK, clk << CMU_PLLCFG_PLL1RFS_POSS);
}

/**
  * @brief  Gets referenc clock of PLL1. 
  * @retval The value of following:
  *         - 0x0: HRC / 6
  *         - 0x2: HOSC
  *         - 0x3: HOSC / 2
  *         - 0x4: HOSC / 3
  *         - 0x5: HOSC / 4
  *         - 0x6: HOSC / 5
  *         - 0x7: HOSC / 6
  */
__STATIC_INLINE uint32_t md_cmu_get_pll1_source(void)
{
	return READ_BITS(CMU->PLLCFG, CMU_PLLCFG_PLL1RFS_MSK, CMU_PLLCFG_PLL1RFS_POSS);
}

/**
  * @brief  Sets output clock of PLL1. 
  * @param  clk: The value of following:
  *         - 0x0: x8(32MHz)
  *         - 0x1: x12(48MHz)
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_pll1_output(uint32_t clk)
{
	MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_PLL1OS_MSK, clk << CMU_PLLCFG_PLL1OS_POS);
}

/**
  * @brief  Gets output clock of PLL1. 
  * @retval The value of following:
  *         - 0x0: x8 (32MHz)
  *         - 0x1: x12 (48MHz)
  */
__STATIC_INLINE uint32_t md_cmu_get_pll1_output(void)
{
	return READ_BITS(CMU->PLLCFG, CMU_PLLCFG_PLL1OS_MSK, CMU_PLLCFG_PLL1OS_POS);
}

/**
  * @brief  Gets lock state of PLL1. 
  * @retval The status of following:
  *         - 0x0: Lock
  *         - 0x1: Unlock
  */
__STATIC_INLINE uint32_t md_cmu_get_pll1_lock(void)
{
	return READ_BITS(CMU->PLLCFG, CMU_PLLCFG_PLL1LCKN_MSK, CMU_PLLCFG_PLL1LCKN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group7 HOSCCFG
  * @{
  */
/**
  * @brief  Sets HOSC frequence.
  * @param  clk: The value of following:
  *         - 0x0: 1MHz
  *         - 0x1: 2MHz
  *         - 0x2: 3MHz
  *         - 0x3: 4MHz
  *         - 0x4: 5MHz
  *         - 0x5: 6MHz
  *         - 0x6: 7MHz
  *         - 0x7: 8MHz
  *         - 0x8: 9MHz
  *         - 0x9: 10MHz
  *         - 0xA: 11MHz
  *         - 0xB: 12MHz
  *         - 0xC: 13MHz
  *         - 0xD: 14MHz
  *         - 0xE: 15MHz
  *         - 0xF: 16MHz
  *         - 0x10: 17MHz
  *         - 0x11: 18MHz
  *         - 0x12: 19MHz
  *         - 0x13: 20MHz
  *         - 0x14: 21MHz
  *         - 0x15: 22MHz
  *         - 0x16: 23MHz
  *         - 0x17: 24MHz
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hosc_lock(uint32_t clk)
{
	MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, clk << CMU_HOSCCFG_FREQ_POSS);
}

/**
  * @brief  Gets HOSC frequence.
  * @retval  clk: The value of following:
  *         - 0x0: 1MHz
  *         - 0x1: 2MHz
  *         - 0x2: 3MHz
  *         - 0x3: 4MHz
  *         - 0x4: 5MHz
  *         - 0x5: 6MHz
  *         - 0x6: 7MHz
  *         - 0x7: 8MHz
  *         - 0x8: 9MHz
  *         - 0x9: 10MHz
  *         - 0xA: 11MHz
  *         - 0xB: 12MHz
  *         - 0xC: 13MHz
  *         - 0xD: 14MHz
  *         - 0xE: 15MHz
  *         - 0xF: 16MHz
  *         - 0x10: 17MHz
  *         - 0x11: 18MHz
  *         - 0x12: 19MHz
  *         - 0x13: 20MHz
  *         - 0x14: 21MHz
  *         - 0x15: 22MHz
  *         - 0x16: 23MHz
  *         - 0x17: 24MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_hosc_lock(void)
{
	return READ_BITS(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, CMU_HOSCCFG_FREQ_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group8 HOSMCR
  * @{
  */
/**
  * @brief  Enable HOSC safe. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_safe(void)
{
	SET_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
}

/**
  * @brief  Disable HOSC safe. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_safe(void)
{
	CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
}

/**
  * @brief  Check HOSC safe is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_safe(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_EN_MSK, CMU_HOSMCR_EN_POS);
}

/**
  * @brief  Gets current high-clock. 
  * @retval Status:
  *         - 0: HOSC
  *         - 1: HRC
  */
__STATIC_INLINE uint32_t md_cmu_get_high_clock_source(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_CLKS_MSK, CMU_HOSMCR_CLKS_POS);
}

/**
  * @brief  Sets HOSC frequence region
  * @param  clk: The value of following:
  *         - 0: 1-2MHz
  *         - 1: 2-4MHz
  *         - 2: 4-8MHz
  *         - 3: 8-16MHz
  *         - 4: 16-24MHz
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hosc_region(uint32_t clk)
{
	MODIFY_REG(CMU->HOSMCR, CMU_HOSMCR_FRQS_MSK, clk << CMU_HOSMCR_FRQS_POSS);
}

/**
  * @brief  Gets HOSC frequence region
  * @retval The value of following:
  *         - 0: 1-2MHz
  *         - 1: 2-4MHz
  *         - 2: 4-8MHz
  *         - 3: 8-16MHz
  *         - 4: 16-24MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_hosc_region(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_FRQS_MSK, CMU_HOSMCR_FRQS_POSS);
}

/**
  * @brief  Enable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_str_interrupt(void)
{
	SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK);
}

/**
  * @brief  Disable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_str_interrupt(void)
{
	CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK);
}

/**
  * @brief  Check STR interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_str_interrupt(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK, CMU_HOSMCR_STRIE_POS);
}

/**
  * @brief  Enable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_stp_interrupt(void)
{
	SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);
}

/**
  * @brief  Disable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_stp_interrupt(void)
{
	CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);
}

/**
  * @brief  Check STP interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_stp_interrupt(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK, CMU_HOSMCR_STPIE_POS);
}

/**
  * @brief  Gets STR flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_hosc_str(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK, CMU_HOSMCR_STRIF_POS);
}

/**
  * @brief  Clear STR flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_hosc_str(void)
{
	SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK);
}

/**
  * @brief  Gets STP flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_hosc_stp(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK, CMU_HOSMCR_STPIF_POS);
}

/**
  * @brief  Clear STP flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_hosc_stp(void)
{
	SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK);
}

/**
  * @brief  Enable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hosc_nmi_interrupt(void)
{
	SET_BIT(CMU->HOSMCR, CMU_HOSMCR_NMIE_MSK);
}

/**
  * @brief  Disable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hosc_nmi_interrupt(void)
{
	CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_NMIE_MSK);
}

/**
  * @brief  Check NMI interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hosc_nmi_interrupt(void)
{
	return READ_BITS(CMU->HOSMCR, CMU_HOSMCR_NMIE_MSK, CMU_HOSMCR_NMIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group9 LOSMCR
  * @{
  */
/**
  * @brief  Enable LOSC safe. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_safe(void)
{
	SET_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK);
}

/**
  * @brief  Disable LOSC safe. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_safe(void)
{
	CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_EN_MSK);
}

/**
  * @brief  Check LOSC safe is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_safe(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_EN_MSK, CMU_LOSMCR_EN_POS);
}

/**
  * @brief  Gets current low-clock. 
  * @retval Status:
  *         - 0: LOSC
  *         - 1: LRC
  */
__STATIC_INLINE uint32_t md_cmu_get_low_clock_source(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_CLKS_MSK, CMU_LOSMCR_CLKS_POS);
}

/**
  * @brief  Enable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_str_interrupt(void)
{
	SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK);
}

/**
  * @brief  Disable STR interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_str_interrupt(void)
{
	CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK);
}

/**
  * @brief  Check STR interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_str_interrupt(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STRIE_MSK, CMU_LOSMCR_STRIE_POS);
}

/**
  * @brief  Enable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_stp_interrupt(void)
{
	SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK);
}

/**
  * @brief  Disable STP interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_stp_interrupt(void)
{
	CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK);
}

/**
  * @brief  Check STP interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_stp_interrupt(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STPIE_MSK, CMU_LOSMCR_STPIE_POS);
}

/**
  * @brief  Gets STR flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_losc_str(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STRIF_MSK, CMU_LOSMCR_STRIF_POS);
}

/**
  * @brief  Clear STR flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_losc_str(void)
{
	SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STRIF_MSK);
}

/**
  * @brief  Gets STP flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_losc_stp(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK, CMU_LOSMCR_STPIF_POS);
}

/**
  * @brief  Clear STP flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_losc_stp(void)
{
	SET_BIT(CMU->LOSMCR, CMU_LOSMCR_STPIF_MSK);
}

/**
  * @brief  Enable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_losc_nmi_interrupt(void)
{
	SET_BIT(CMU->LOSMCR, CMU_LOSMCR_NMIE_MSK);
}

/**
  * @brief  Disable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_losc_nmi_interrupt(void)
{
	CLEAR_BIT(CMU->LOSMCR, CMU_LOSMCR_NMIE_MSK);
}

/**
  * @brief  Check NMI interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_losc_nmi_interrupt(void)
{
	return READ_BITS(CMU->LOSMCR, CMU_LOSMCR_NMIE_MSK, CMU_LOSMCR_NMIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group10 PULMCR
  * @{
  */
/**
  * @brief  Enable PLL safe. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_safe(void)
{
	SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
}

/**
  * @brief  Disable PLL safe. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_safe(void)
{
	CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
}

/**
  * @brief  Check PLL safe is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_safe(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_EN_MSK, CMU_PULMCR_EN_POS);
}

/**
  * @brief  Gets current clock. 
  * @retval Status:
  *         - 0: PLL
  *         - 1: HRC
  */
__STATIC_INLINE uint32_t md_cmu_get_current_clock_source(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_CLKS_MSK, CMU_PULMCR_CLKS_POS);
}

/**
  * @brief  Sets system clock when PLL unlock. 
  * @param  opt: Value of following:
  *         - 0: Do nothing
  *         - 1: Switch HRC
  *         - 2: Switch HRC. Switch back PLL when Pll is stable.
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_system_clock_pll_unlock(uint32_t opt)
{
	MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, CMU_PULMCR_MODE_POSS);
}

/**
  * @brief  Get system clock when PLL unlock.
  * @retval opt: Value of following:
  *         - 0: Do nothing
  *         - 1: Switch HRC
  *         - 2: Switch HRC. Switch back PLL when Pll is stable.
  */
__STATIC_INLINE uint32_t md_cmu_get_system_clock_pll_unlock(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_MODE_MSK, CMU_PULMCR_MODE_POSS);
}

/**
  * @brief  Enable LCK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_lck_interrupt(void)
{
	SET_BIT(CMU->PULMCR, CMU_PULMCR_LCKIE_MSK);
}

/**
  * @brief  Disable LCK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_lck_interrupt(void)
{
	CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_LCKIE_MSK);
}

/**
  * @brief  Check LCK interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_lck_interrupt(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_LCKIE_MSK, CMU_PULMCR_LCKIE_POS);
}

/**
  * @brief  Enable ULK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_ulk_interrupt(void)
{
	SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);
}

/**
  * @brief  Disable ULK interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_ulk_interrupt(void)
{
	CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);
}

/**
  * @brief  Check ULK interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_ulk_interrupt(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK, CMU_PULMCR_ULKIE_POS);
}

/**
  * @brief  Gets LCK flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_pll_lck(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_LCKIF_MSK, CMU_PULMCR_LCKIF_POS);
}

/**
  * @brief  Clear LCK flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_pll_lck(void)
{
	SET_BIT(CMU->PULMCR, CMU_PULMCR_LCKIF_MSK);
}

/**
  * @brief  Gets ULK flag state
  * @retval State
  */
__STATIC_INLINE uint32_t md_cmu_is_active_flag_pll_ulk(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK, CMU_PULMCR_ULKIF_POS);
}

/**
  * @brief  Clear ULK flag
  * @retval None
  */
__STATIC_INLINE void md_cmu_clear_flag_pll_ulk(void)
{
	SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK);
}

/**
  * @brief  Enable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_pll_nmi_interrupt(void)
{
	SET_BIT(CMU->PULMCR, CMU_PULMCR_NMIE_MSK);
}

/**
  * @brief  Disable NMI interrupt
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_pll_nmi_interrupt(void)
{
	CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_NMIE_MSK);
}

/**
  * @brief  Check NMI interrupt is enable.
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_pll_nmi_interrupt(void)
{
	return READ_BITS(CMU->PULMCR, CMU_PULMCR_NMIE_MSK, CMU_PULMCR_NMIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group11 CLKOCR
  * @{
  */
/**
  * @brief  Enable HSC output. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_hsco(void)
{
	SET_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
}

/**
  * @brief  Disable HSC output. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_hsco(void)
{
	CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
}

/**
  * @brief  Check HSC output is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_hsco(void)
{
	return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK, CMU_CLKOCR_HSCOEN_POS);
}

/**
  * @brief  Sets high clock output type
  * @param  sel : Value of following:
  *         - 0: HOSC
  *         - 1: LOSC
  *         - 2: HRC
  *         - 3: LRC
  *         - 4: HOSM
  *         - 5: PLL1
  *         - 7: SYSCLK
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hsco_type(uint32_t sel)
{
	MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCOS_MSK, sel << CMU_CLKOCR_HSCOS_POSS);
}

/**
  * @brief  Gets high clock output type
  * @retval Value of following:
  *         - 0: HOSC
  *         - 1: LOSC
  *         - 2: HRC
  *         - 3: LRC
  *         - 4: HOSM
  *         - 5: PLL1
  *         - 7: SYSCLK
  */
__STATIC_INLINE uint32_t md_cmu_get_hsco_type(void)
{
	return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_HSCOS_MSK, CMU_CLKOCR_HSCOS_POSS);
}

/**
  * @brief  Sets high clock output divider
  * @param  div: Value of following:
  *         - 0: HSC / 1
  *         - 1: HSC / 2
  *         - 2: HSC / 4
  *         - 3: HSC / 8
  *         - 4: HSC / 16
  *         - 5: HSC / 32
  *         - 6: HSC / 64
  *         - 7: HSC / 128
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_hsco_div(uint32_t div)
{
	MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCODIV_MSK, div << CMU_CLKOCR_HSCODIV_POSS);
}

/**
  * @brief  Gets high clock output divider
  * @retval Value of following:
  *         - 0: HSC / 1
  *         - 1: HSC / 2
  *         - 2: HSC / 4
  *         - 3: HSC / 8
  *         - 4: HSC / 16
  *         - 5: HSC / 32
  *         - 6: HSC / 64
  *         - 7: HSC / 128
  */
__STATIC_INLINE uint32_t md_cmu_get_hsco_div(void)
{
	return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_HSCODIV_MSK, CMU_CLKOCR_HSCODIV_POSS);
}

/**
  * @brief  Enable LSC output. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lsco(void)
{
	SET_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
}

/**
  * @brief  Disable LSC output. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lsco(void)
{
	CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
}

/**
  * @brief  Check LSC output is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lsco(void)
{
	return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK, CMU_CLKOCR_LSCOEN_POS);
}

/**
  * @brief  Sets low clock output type
  * @param  sel : Value of following:
  *         - 0: LOSC
  *         - 1: LRC
  *         - 2: LOSM
  *         - 3: BUZZ
  *         - 4: ULRC
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_lsco_type(uint32_t sel)
{
	MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_LSCOS_MSK, sel << CMU_CLKOCR_LSCOS_POSS);
}

/**
  * @brief  Gets low clock output type
  * @retval Value of following:
  *         - 0: LOSC
  *         - 1: LRC
  *         - 2: LOSM
  *         - 3: BUZZ
  *         - 4: ULRC
  */
__STATIC_INLINE uint32_t md_cmu_get_lsco_type(void)
{
	return READ_BITS(CMU->CLKOCR, CMU_CLKOCR_LSCOS_MSK, CMU_CLKOCR_LSCOS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group12 BUZZCR
  * @{
  */
/**
  * @brief  Enable BUZZ output. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_buzz(void)
{
	SET_BIT(CMU->BUZZCR, CMU_BUZZCR_EN_MSK);
}

/**
  * @brief  Disable BUZZ output. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_buzz(void)
{
	CLEAR_BIT(CMU->BUZZCR, CMU_BUZZCR_EN_MSK);
}

/**
  * @brief  Check BUZZ output is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_buzz(void)
{
	return READ_BITS(CMU->BUZZCR, CMU_BUZZCR_EN_MSK, CMU_BUZZCR_EN_POS);
}

/**
  * @brief  Sets BUZZ divider
  * @param  div: Value of following:
  *         - 0: Freq / 2
  *         - 1: Freq / 4
  *         - 2: Freq / 8
  *         - 3: Freq / 16
  *         - 4: Freq / 32
  *         - 5: Freq / 64
  *         - 6: Freq / 128
  *         - 7: Freq / 256
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_buzz_div(uint32_t div)
{
	MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_DIV_MSK, div << CMU_BUZZCR_DIV_POSS);
}

/**
  * @brief  Gets BUZZ divider
  * @retval Value of following:
  *         - 0: Freq / 2
  *         - 1: Freq / 4
  *         - 2: Freq / 8
  *         - 3: Freq / 16
  *         - 4: Freq / 32
  *         - 5: Freq / 64
  *         - 6: Freq / 128
  *         - 7: Freq / 256
  */
__STATIC_INLINE uint32_t md_cmu_get_buzz_div(void)
{
	return READ_BITS(CMU->BUZZCR, CMU_BUZZCR_DIV_MSK, CMU_BUZZCR_DIV_POSS);
}

/**
  * @brief  Sets BUZZ data
  * @param  data: Region is from 0x00 to 0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_buzz_data(uint32_t data)
{
	MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_DAT_MSK, data << CMU_BUZZCR_DAT_POSS);
}

/**
  * @brief  Gets BUZZ data
  * @retval BUZZ data
  */
__STATIC_INLINE uint32_t md_cmu_get_buzz_data(uint32_t data)
{
	return READ_BITS(CMU->BUZZCR, CMU_BUZZCR_DAT_MSK, CMU_BUZZCR_DAT_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group13 AHB1ENR
  * @{
  */
/**
  * @brief  Enable GPIO peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_gpio(void)
{
	SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_GPIOEN_MSK);
}

/**
  * @brief  Disable GPIO peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_gpio(void)
{
	CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_GPIOEN_MSK);
}

/**
  * @brief  Check GPIO peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_gpio(void)
{
	return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_GPIOEN_MSK, CMU_AHB1ENR_GPIOEN_POS);
}

/**
  * @brief  Enable CRC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_crc(void)
{
	SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRCEN_MSK);
}

/**
  * @brief  Disable CRC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_crc(void)
{
	CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRCEN_MSK);
}

/**
  * @brief  Check CRC peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_crc(void)
{
	return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_CRCEN_MSK, CMU_AHB1ENR_CRCEN_POS);
}

/**
  * @brief  Enable CALC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_calc(void)
{
	SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CALCEN_MSK);
}

/**
  * @brief  Disable CALC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_calc(void)
{
	CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CALCEN_MSK);
}

/**
  * @brief  Check CALC peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_calc(void)
{
	return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_CALCEN_MSK, CMU_AHB1ENR_CALCEN_POS);
}

/**
  * @brief  Enable CRYPT peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_crypt(void)
{
	SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRYPTEN_MSK);
}

/**
  * @brief  Disable CRYPT peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_crypt(void)
{
	CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_CRYPTEN_MSK);
}

/**
  * @brief  Check CRYPT peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_crypt(void)
{
	return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_CRYPTEN_MSK, CMU_AHB1ENR_CRYPTEN_POS);
}

/**
  * @brief  Enable TRNG peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_trng(void)
{
	SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_TRNGEN_MSK);
}

/**
  * @brief  Disable TRNG peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_trng(void)
{
	CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_TRNGEN_MSK);
}

/**
  * @brief  Check TRNG peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_trng(void)
{
	return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_TRNGEN_MSK, CMU_AHB1ENR_TRNGEN_POS);
}

/**
  * @brief  Enable PIS peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_pis(void)
{
	SET_BIT(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK);
}

/**
  * @brief  Disable PIS peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_pis(void)
{
	CLEAR_BIT(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK);
}

/**
  * @brief  Check PIS peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_pis(void)
{
	return READ_BITS(CMU->AHB1ENR, CMU_AHB1ENR_PISEN_MSK, CMU_AHB1ENR_PISEN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group14 APB1ENR
  * @{
  */
/**
  * @brief  Enable TIMER0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer0(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM0EN_MSK);
}

/**
  * @brief  Disable TIMER0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer0(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM0EN_MSK);
}

/**
  * @brief  Check TIMER0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer0(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM0EN_MSK, CMU_APB1ENR_TIM0EN_POS);
}

/**
  * @brief  Enable TIMER1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer1(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM1EN_MSK);
}

/**
  * @brief  Disable TIMER1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer1(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM1EN_MSK);
}

/**
  * @brief  Check TIMER1 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer1(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM1EN_MSK, CMU_APB1ENR_TIM1EN_POS);
}

/**
  * @brief  Enable TIMER2 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer2(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM2EN_MSK);
}

/**
  * @brief  Disable TIMER2 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer2(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM2EN_MSK);
}

/**
  * @brief  Check TIMER2 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer2(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM2EN_MSK, CMU_APB1ENR_TIM2EN_POS);
}

/**
  * @brief  Enable TIMER3 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer3(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM3EN_MSK);
}

/**
  * @brief  Disable TIMER3 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer3(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM3EN_MSK);
}

/**
  * @brief  Check TIMER3 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer3(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM3EN_MSK, CMU_APB1ENR_TIM3EN_POS);
}

/**
  * @brief  Enable TIMER4 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer4(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM4EN_MSK);
}

/**
  * @brief  Disable TIMER4 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer4(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM4EN_MSK);
}

/**
  * @brief  Check TIMER4 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer4(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM4EN_MSK, CMU_APB1ENR_TIM4EN_POS);
}

/**
  * @brief  Enable TIMER5 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer5(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM5EN_MSK);
}

/**
  * @brief  Disable TIMER5 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer5(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM5EN_MSK);
}

/**
  * @brief  Check TIMER5 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer5(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM5EN_MSK, CMU_APB1ENR_TIM5EN_POS);
}

/**
  * @brief  Enable TIMER6 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer6(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM6EN_MSK);
}

/**
  * @brief  Disable TIMER6 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer6(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM6EN_MSK);
}

/**
  * @brief  Check TIMER6 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer6(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM6EN_MSK, CMU_APB1ENR_TIM6EN_POS);
}

/**
  * @brief  Enable TIMER7 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_timer7(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM7EN_MSK);
}

/**
  * @brief  Disable TIMER7 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_timer7(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_TIM7EN_MSK);
}

/**
  * @brief  Check TIMER7 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_timer7(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_TIM7EN_MSK, CMU_APB1ENR_TIM7EN_POS);
}

/**
  * @brief  Enable UART0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart0(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART0EN_MSK);
}

/**
  * @brief  Disable UART0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart0(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART0EN_MSK);
}

/**
  * @brief  Check UART0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart0(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART0EN_MSK, CMU_APB1ENR_UART0EN_POS);
}

/**
  * @brief  Enable UART1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart1(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART1EN_MSK);
}

/**
  * @brief  Disable UART1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart1(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART1EN_MSK);
}

/**
  * @brief  Check UART1 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart1(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART1EN_MSK, CMU_APB1ENR_UART1EN_POS);
}

/**
  * @brief  Enable UART2 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart2(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART2EN_MSK);
}

/**
  * @brief  Disable UART2 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart2(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART2EN_MSK);
}

/**
  * @brief  Check UART2 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart2(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART2EN_MSK, CMU_APB1ENR_UART2EN_POS);
}

/**
  * @brief  Enable UART3 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_uart3(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_UART3EN_MSK);
}

/**
  * @brief  Disable UART3 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_uart3(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_UART3EN_MSK);
}

/**
  * @brief  Check UART3 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_uart3(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_UART3EN_MSK, CMU_APB1ENR_UART3EN_POS);
}

/**
  * @brief  Enable USART0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_usart0(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_USART0EN_MSK);
}

/**
  * @brief  Disable USART0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_usart0(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_USART0EN_MSK);
}

/**
  * @brief  Check USART0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_usart0(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_USART0EN_MSK, CMU_APB1ENR_USART0EN_POS);
}

/**
  * @brief  Enable USART1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_usart1(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_USART1EN_MSK);
}

/**
  * @brief  Disable USART1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_usart1(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_USART1EN_MSK);
}

/**
  * @brief  Check USART1 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_usart1(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_USART1EN_MSK, CMU_APB1ENR_USART1EN_POS);
}

/**
  * @brief  Enable SPI0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_spi0(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI0EN_MSK);
}

/**
  * @brief  Disable SPI0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_spi0(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI0EN_MSK);
}

/**
  * @brief  Check SPI0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_spi0(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_SPI0EN_MSK, CMU_APB1ENR_SPI0EN_POS);
}

/**
  * @brief  Enable SPI1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_spi1(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI1EN_MSK);
}

/**
  * @brief  Disable SPI1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_spi1(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI1EN_MSK);
}

/**
  * @brief  Check SPI1 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_spi1(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_SPI1EN_MSK, CMU_APB1ENR_SPI1EN_POS);
}

/**
  * @brief  Enable SPI2 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_spi2(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI2EN_MSK);
}

/**
  * @brief  Disable SPI2 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_spi2(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_SPI2EN_MSK);
}

/**
  * @brief  Check SPI2 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_spi2(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_SPI2EN_MSK, CMU_APB1ENR_SPI2EN_POS);
}

/**
  * @brief  Enable I2C0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_i2c0(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C0EN_MSK);
}

/**
  * @brief  Disable I2C0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_i2c0(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C0EN_MSK);
}

/**
  * @brief  Check I2C0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_i2c0(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_I2C0EN_MSK, CMU_APB1ENR_I2C0EN_POS);
}

/**
  * @brief  Enable I2C1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_i2c1(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C1EN_MSK);
}

/**
  * @brief  Disable I2C1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_i2c1(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_I2C1EN_MSK);
}

/**
  * @brief  Check I2C1 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_i2c1(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_I2C1EN_MSK, CMU_APB1ENR_I2C1EN_POS);
}

/**
  * @brief  Enable CAN0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_can0(void)
{
	SET_BIT(CMU->APB1ENR, CMU_APB1ENR_CAN0EN_MSK);
}

/**
  * @brief  Disable CAN0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_can0(void)
{
	CLEAR_BIT(CMU->APB1ENR, CMU_APB1ENR_CAN0EN_MSK);
}

/**
  * @brief  Check CAN0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_can0(void)
{
	return READ_BITS(CMU->APB1ENR, CMU_APB1ENR_CAN0EN_MSK, CMU_APB1ENR_CAN0EN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group15 APB2ENR
  * @{
  */
/**
  * @brief  Enable LPTIM0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_lptim0(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_LPTIM0EN_MSK);
}

/**
  * @brief  Disable LPTIM0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_lptim0(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_LPTIM0EN_MSK);
}

/**
  * @brief  Check LPTIM0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_lptim0(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_LPTIM0EN_MSK, CMU_APB2ENR_LPTIM0EN_POS);
}

/**
  * @brief  Enable LPUART0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_lpuart0(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_LPUART0EN_MSK);
}

/**
  * @brief  Disable LPUART0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_lpuart0(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_LPUART0EN_MSK);
}

/**
  * @brief  Check LPUART0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_lpuart0(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_LPUART0EN_MSK, CMU_APB2ENR_LPUART0EN_POS);
}

/**
  * @brief  Enable ADC0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_adc0(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_ADC0EN_MSK);
}

/**
  * @brief  Disable ADC0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_adc0(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_ADC0EN_MSK);
}

/**
  * @brief  Check ADC0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_adc0(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_ADC0EN_MSK, CMU_APB2ENR_ADC0EN_POS);
}

/**
  * @brief  Enable ACMP0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_acmp0(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_ACMP0EN_MSK);
}

/**
  * @brief  Disable ACMP0 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_acmp0(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_ACMP0EN_MSK);
}

/**
  * @brief  Check ACMP0 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_acmp0(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_ACMP0EN_MSK, CMU_APB2ENR_ACMP0EN_POS);
}

/**
  * @brief  Enable ACMP1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_acmp1(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_ACMP1EN_MSK);
}

/**
  * @brief  Disable ACMP1 peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_acmp1(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_ACMP1EN_MSK);
}

/**
  * @brief  Check ACMP1 peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_acmp1(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_ACMP1EN_MSK, CMU_APB2ENR_ACMP1EN_POS);
}

/**
  * @brief  Enable WWDT peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_wwdt(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_WWDTEN_MSK);
}

/**
  * @brief  Disable WWDT peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_wwdt(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_WWDTEN_MSK);
}

/**
  * @brief  Check WWDT peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_wwdt(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_WWDTEN_MSK, CMU_APB2ENR_WWDTEN_POS);
}

/**
  * @brief  Enable LCD peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_lcd(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_LCDEN_MSK);
}

/**
  * @brief  Disable LCD peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_lcd(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_LCDEN_MSK);
}

/**
  * @brief  Check LCD peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_lcd(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_LCDEN_MSK, CMU_APB2ENR_LCDEN_POS);
}

/**
  * @brief  Enable IWDT peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_iwdt(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_IWDTEN_MSK);
}

/**
  * @brief  Disable IWDT peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_iwdt(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_IWDTEN_MSK);
}

/**
  * @brief  Check IWDT peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_iwdt(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_IWDTEN_MSK, CMU_APB2ENR_IWDTEN_POS);
}

/**
  * @brief  Enable RTC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_rtc(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_RTCEN_MSK);
}

/**
  * @brief  Disable RTC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_rtc(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_RTCEN_MSK);
}

/**
  * @brief  Check RTC peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_rtc(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_RTCEN_MSK, CMU_APB2ENR_RTCEN_POS);
}

/**
  * @brief  Enable TSENSE peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_tsense(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_TSENSEEN_MSK);
}

/**
  * @brief  Disable TSENSE peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_tsense(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_TSENSEEN_MSK);
}

/**
  * @brief  Check TSENSE peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_tsense(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_TSENSEEN_MSK, CMU_APB2ENR_TSENSEEN_POS);
}

/**
  * @brief  Enable BKPC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_bkpc(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_BKPCEN_MSK);
}

/**
  * @brief  Disable BKPC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_bkpc(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_BKPCEN_MSK);
}

/**
  * @brief  Check BKPC peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_bkpc(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_BKPCEN_MSK, CMU_APB2ENR_BKPCEN_POS);
}

/**
  * @brief  Enable DBGC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_perh_dbgc(void)
{
	SET_BIT(CMU->APB2ENR, CMU_APB2ENR_DBGCEN_MSK);
}

/**
  * @brief  Disable DBGC peripheral. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_perh_dbgc(void)
{
	CLEAR_BIT(CMU->APB2ENR, CMU_APB2ENR_DBGCEN_MSK);
}

/**
  * @brief  Check DBGC peripheral is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_perh_dbgc(void)
{
	return READ_BITS(CMU->APB2ENR, CMU_APB2ENR_DBGCEN_MSK, CMU_APB2ENR_DBGCEN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group16 LPENR
  * @{
  */
/**
  * @brief  Enable LRC low power mode.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lp_lrc(void)
{
	SET_BIT(CMU->LPENR, CMU_LPENR_LRCEN_MSK);
}

/**
  * @brief  Disable LRC low power mode. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lp_lrc(void)
{
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_LRCEN_MSK);
}

/**
  * @brief  Check LRC low power mode is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lp_lrc(void)
{
	return READ_BITS(CMU->LPENR, CMU_LPENR_LRCEN_MSK, CMU_LPENR_LRCEN_POS);
}

/**
  * @brief  Enable LOSC low power mode.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lp_losc(void)
{
	SET_BIT(CMU->LPENR, CMU_LPENR_LOSCEN_MSK);
}

/**
  * @brief  Disable LOSC low power mode. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lp_losc(void)
{
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_LOSCEN_MSK);
}

/**
  * @brief  Check LOSC low power mode is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lp_losc(void)
{
	return READ_BITS(CMU->LPENR, CMU_LPENR_LOSCEN_MSK, CMU_LPENR_LOSCEN_POS);
}

/**
  * @brief  Enable HRC low power mode.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lp_hrc(void)
{
	SET_BIT(CMU->LPENR, CMU_LPENR_HRCEN_MSK);
}

/**
  * @brief  Disable HRC low power mode. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lp_hrc(void)
{
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_HRCEN_MSK);
}

/**
  * @brief  Check HRC low power mode is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lp_hrc(void)
{
	return READ_BITS(CMU->LPENR, CMU_LPENR_HRCEN_MSK, CMU_LPENR_HRCEN_POS);
}

/**
  * @brief  Enable HOSC low power mode.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_lp_hosc(void)
{
	SET_BIT(CMU->LPENR, CMU_LPENR_HOSCEN_MSK);
}

/**
  * @brief  Disable HOSC low power mode. 
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_lp_hosc(void)
{
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_HOSCEN_MSK);
}

/**
  * @brief  Check HOSC low power mode is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_lp_hosc(void)
{
	return READ_BITS(CMU->LPENR, CMU_LPENR_HOSCEN_MSK, CMU_LPENR_HOSCEN_POS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group17 PERICR
  * @{
  */
/**
  * @brief  Stes LPTIM0 clock source.
  * @param  clk: Value of following:
  *         - 0x0: PCLK2
  *         - 0x1: PLL1
  *         - 0x3: HRC
  *         - 0x4: HOSC
  *         - 0x5: LRC
  *         - 0x6: LOSC
  *         - 0x7: ULRC
  *         - 0x8: HRC divide to 1MHz
  *         - 0x9: HOSC divide to 1MHz
  *         - 0xA: LOSM
  *         - 0xB: HOSM
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_lptim0_clock_source(uint32_t clk)
{
	MODIFY_REG(CMU->PERICR, CMU_PERICR_LPTIM0_MSK, clk << CMU_PERICR_LPTIM0_POSS);
}

/**
  * @brief  Gets LPTIM0 clock source.
  * @retval Value of following:
  *         - 0x0: PCLK2
  *         - 0x1: PLL1
  *         - 0x3: HRC
  *         - 0x4: HOSC
  *         - 0x5: LRC
  *         - 0x6: LOSC
  *         - 0x7: ULRC
  *         - 0x8: HRC divide to 1MHz
  *         - 0x9: HOSC divide to 1MHz
  *         - 0xA: LOSM
  *         - 0xB: HOSM
  */
__STATIC_INLINE uint32_t md_cmu_get_lptim0_clock_source(void)
{
	return READ_BITS(CMU->PERICR, CMU_PERICR_LPTIM0_MSK, CMU_PERICR_LPTIM0_POSS);
}

/**
  * @brief  Stes LPUART0 clock source.
  * @param  clk: Value of following:
  *         - 0x0: PCLK2
  *         - 0x1: PLL1
  *         - 0x3: HRC
  *         - 0x4: HOSC
  *         - 0x5: LRC
  *         - 0x6: LOSC
  *         - 0x7: ULRC
  *         - 0x8: HRC divide to 1MHz
  *         - 0x9: HOSC divide to 1MHz
  *         - 0xA: LOSM
  *         - 0xB: HOSM
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_lpuart0_clock_source(uint32_t clk)
{
	MODIFY_REG(CMU->PERICR, CMU_PERICR_LPUART0_MSK, clk << CMU_PERICR_LPUART0_POSS);
}

/**
  * @brief  Gets LPUART0 clock source.
  * @retval Value of following:
  *         - 0x0: PCLK2
  *         - 0x1: PLL1
  *         - 0x3: HRC
  *         - 0x4: HOSC
  *         - 0x5: LRC
  *         - 0x6: LOSC
  *         - 0x7: ULRC
  *         - 0x8: HRC divide to 1MHz
  *         - 0x9: HOSC divide to 1MHz
  *         - 0xA: LOSM
  *         - 0xB: HOSM
  */
__STATIC_INLINE uint32_t md_cmu_get_lpuart0_clock_source(void)
{
	return READ_BITS(CMU->PERICR, CMU_PERICR_LPUART0_MSK, CMU_PERICR_LPUART0_POSS);
}

/**
  * @brief  Stes LCD clock source.
  * @param  clk: Value of following:
  *         - 0x0: LOSM
  *         - 0x1: LOSC
  *         - 0x2: LRC
  *         - 0x3: ULRC
  *         - 0x4: HRC divide to 1MHz
  *         - 0x5: HOSC divide to 1MHz
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_lcd_clock_source(uint32_t clk)
{
	MODIFY_REG(CMU->PERICR, CMU_PERICR_LCD_MSK, clk << CMU_PERICR_LCD_POSS);
}

/**
  * @brief  Gets LCD clock source.
  * @retval Value of following:
  *         - 0x0: LOSM
  *         - 0x1: LOSC
  *         - 0x2: LRC
  *         - 0x3: ULRC
  *         - 0x4: HRC divide to 1MHz
  *         - 0x5: HOSC divide to 1MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_lcd_clock_source(void)
{
	return READ_BITS(CMU->PERICR, CMU_PERICR_LCD_MSK, CMU_PERICR_LCD_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group18 HRCACR
  * @{
  */
/**
  * @brief  Enable auto-calibrate.
  * @retval None
  */
__STATIC_INLINE void md_cmu_enable_auto_calib(void)
{
	SET_BIT(CMU->HRCACR, CMU_HRCACR_EN_MSK);
}

/**
  * @brief  Disable auto-calibrate.
  * @retval None
  */
__STATIC_INLINE void md_cmu_disable_auto_calib(void)
{
	CLEAR_BIT(CMU->HRCACR, CMU_HRCACR_EN_MSK);
}

/**
  * @brief  Check auto-calibrate is enable. 
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_cmu_is_enabled_auto_calib(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_EN_MSK, CMU_HRCACR_EN_POS);
}

/**
  * @brief  Sets frequence of auto-calibrate 
  * @param  freq: Value of following:
  *         - 0: 24MHz
  *         - 1: 2MHz
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_auto_calib_freq(uint32_t freq)
{
	MODIFY_REG(CMU->HRCACR, CMU_HRCACR_FREQ_MSK, freq << CMU_HRCACR_FREQ_POS);
}

/**
  * @brief  Gets frequence of auto-calibrate 
  * @retval Value of following:
  *         - 0: 24MHz
  *         - 1: 2MHz
  */
__STATIC_INLINE uint32_t md_cmu_get_auto_calib_freq(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_FREQ_MSK, CMU_HRCACR_FREQ_POS);
}

/**
  * @brief  Sets source of auto-calibrate 
  * @param  freq: Value of following:
  *         - 0: LOSC
  *         - 1: HOSC
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_auto_calib_src(uint32_t freq)
{
	MODIFY_REG(CMU->HRCACR, CMU_HRCACR_RFSEL_MSK, freq << CMU_HRCACR_RFSEL_POS);
}

/**
  * @brief  Gets source of auto-calibrate 
  * @retval Value of following:
  *         - 0: LOSC
  *         - 1: HOSC
  */
__STATIC_INLINE uint32_t md_cmu_get_auto_calib_src(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_RFSEL_MSK, CMU_HRCACR_RFSEL_POS);
}

/**
  * @brief  Sets electricity of auto-calibrate 
  * @param  ibs: Value of following:
  *         - 0: Default value
  *         - 1: Register value
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_auto_calib_elec(uint32_t ibs)
{
	MODIFY_REG(CMU->HRCACR, CMU_HRCACR_IBS_MSK, ibs << CMU_HRCACR_IBS_POS);
}

/**
  * @brief  Gets electricity of auto-calibrate 
  * @retval Value of following:
  *         - 0: Default value
  *         - 1: Register value
  */
__STATIC_INLINE uint32_t md_cmu_get_auto_calib_elec(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_IBS_MSK, CMU_HRCACR_IBS_POS);
}

/**
  * @brief  Sets accuracy of auto-calibrate 
  * @param  acc: Value of following:
  *         - 0: 0.1%
  *         - 1: 0.2%
  *         - 2: 0.4%
  *         - 3: 0.8%
  *         - 4: 1.5%
  *         - 5: 3.1%
  *         - 6: 6.2%
  *         - 7: 12.5%
  * @retval None
  */
__STATIC_INLINE void md_cmu_set_auto_calib_acc(uint32_t acc)
{
	MODIFY_REG(CMU->HRCACR, CMU_HRCACR_AC_MSK, acc << CMU_HRCACR_AC_POSS);
}

/**
  * @brief  Gets accuracy of auto-calibrate 
  * @retval Value of following:
  *         - 0: 0.1%
  *         - 1: 0.2%
  *         - 2: 0.4%
  *         - 3: 0.8%
  *         - 4: 1.5%
  *         - 5: 3.1%
  *         - 6: 6.2%
  *         - 7: 12.5%
  */
__STATIC_INLINE uint32_t md_cmu_get_auto_calib_acc(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_AC_MSK, CMU_HRCACR_AC_POSS);
}

/**
  * @brief  Starts auto-calibrate 
  * @retval None
  */
__STATIC_INLINE void md_cmu_start_auto_calib(void)
{
	SET_BIT(CMU->HRCACR, CMU_HRCACR_WRTRG_MSK);
}

/**
  * @brief  Gets status of auto-calibrate 
  * @retval Value of following:
  *         - 0: Ready
  *         - 1: Busy
  */
__STATIC_INLINE uint32_t md_cmu_get_auto_calib_status(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_BUSY_MSK, CMU_HRCACR_BUSY_POS);
}

/**
  * @brief  Gets result of auto-calibrate 
  * @retval Value of following:
  *         - 0: Invalid
  *         - 1: Success
  *         - 2: Lower then object value
  *         - 2: Higher then object value
  */
__STATIC_INLINE uint32_t md_cmu_get_auto_calib_result(void)
{
	return READ_BITS(CMU->HRCACR, CMU_HRCACR_STA_MSK, CMU_HRCACR_STA_POSS);
}
/**
  * @}
  */
/** @defgroup MD_CMU_Public_Functions_Group1 Initialization and Get BUS Clock value
  * @{
  */
extern md_status_t md_cmu_clock_config_default(void);
extern md_status_t md_cmu_clock_config(md_cmu_clock_t clk, uint32_t clock);
extern uint32_t md_cmu_get_hclk1_clock(void);
extern uint32_t md_cmu_get_sys_clock(void);
extern uint32_t md_cmu_get_pclk1_clock(void);
extern uint32_t md_cmu_get_pclk2_clock(void);
extern uint32_t md_cmu_get_clock(void);
extern void md_cmu_pll1_config(md_cmu_pll1_input_t input, md_cmu_pll1_output_t output);
/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif
