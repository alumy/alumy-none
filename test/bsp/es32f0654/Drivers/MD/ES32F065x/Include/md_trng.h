/**
  *********************************************************************************
  *
  * @file    md_trng.h
  * @brief   Header file of TRNG module driver.
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

#ifndef __MD_TRNG_H
#define __MD_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_TRNG TRNG
  * @brief TRNG micro driver
  * @{
  */

/** @defgroup MD_TRNG_Pubulic_Types TRNG Pubulic Types
  * @{
  */
/**
  * @brief Data width
  */
typedef enum {
	MD_TRNG_DSEL_1B  = 0x0U,	/**< 1-bit */
	MD_TRNG_DSEL_8B  = 0x1U,	/**< 8-bit */
	MD_TRNG_DSEL_16B = 0x2U,	/**< 16-bit */
	MD_TRNG_DSEL_32B = 0x3U,	/**< 32-bit */
} md_trng_data_width_t;

/**
  * @brief seed type
  */
typedef enum {
	MD_TRNG_SEED_TYPE_0    = 0x0U,	/**< Using 0 as seed */
	MD_TRNG_SEED_TYPE_1    = 0x1U,	/**< Using 1 as seed */
	MD_TRNG_SEED_TYPE_LAST = 0x2U,	/**< Using last seed */
	MD_TRNG_SEED_TYPE_SEED = 0x3U,	/**< Using value of register */
} md_trng_seed_type_t;

/**
  * @brief TRNG init structure definition
  */
typedef struct {
	md_trng_data_width_t data_width;	/**< The width of data */
	md_trng_seed_type_t seed_type;		/**< The seed type */
	uint32_t seed;		/**< The value of seed */
	uint16_t t_start;	/**< T(start) = T(hclk) * (t_start + 1), T(start) > 1ms */
	uint8_t adjc;		/**< Adjust parameter */
	uint8_t posten;		/**< Data back handle function  */
} md_trng_init_t;
/**
  * @}
  */

/** @defgroup MD_TRNG_Public_Functions TRNG Public Functions
  * @{
  */
/** @defgroup MD_TRNG_Public_Functions_Group2 CR
  * @{
  */
/**
  * @brief  Enable TRNG
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_enable_trngen(TRNG_TypeDef *trng)
{
	SET_BIT(trng->CR, TRNG_CR_TRNGEN_MSK);
}

/**
  * @brief  Disable TRNG
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_disable_trngen(TRNG_TypeDef *trng)
{
	CLEAR_BIT(trng->CR, TRNG_CR_TRNGEN_MSK);
}

/**
  * @brief  Check if TRNG enable
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_trng_is_enable(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->CR, TRNG_CR_TRNGEN_MSK, TRNG_CR_TRNGEN_POS);
}

/**
  * @brief  Enable TRNG adjust mode
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_adjust_enable(TRNG_TypeDef *trng)
{
	SET_BIT(trng->CR, TRNG_CR_ADJM_MSK);
}

/**
  * @brief  Disable TRNG adjust mode
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_adjust_disable(TRNG_TypeDef *trng)
{
	CLEAR_BIT(trng->CR, TRNG_CR_ADJM_MSK);
}

/**
  * @brief  Check if TRNG adjust enable
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_trng_is_adjust_enable(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->CR, TRNG_CR_ADJM_MSK, TRNG_CR_ADJM_POS);
}

/**
  * @brief  Set TRNG source select
  * @param  trng TRNG Instance
  * @param  src The value of following:
  *         - 0x0: TRNG0
  *         - 0x1: TRNG1
  * @retval None
  */
__STATIC_INLINE void md_trng_set_source(TRNG_TypeDef * trng, uint32_t src)
{
	MODIFY_REG(trng->CR, TRNG_CR_TRNGSEL_MSK, src << TRNG_CR_TRNGSEL_POS);
}

/**
  * @brief  Get TRNG source select.
  * @retval src The value of following:
  *         - 0x0: TRNG0
  *         - 0x1: TRNG1
  */
__STATIC_INLINE uint32_t md_trng_get_source(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->CR, TRNG_CR_TRNGSEL_MSK, TRNG_CR_TRNGSEL_POS);
}

/**
  * @brief  Enable TRNG posten
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_enable_posten(TRNG_TypeDef *trng)
{
	SET_BIT(trng->CR, TRNG_CR_POSTEN_MSK);
}

/**
  * @brief  Disable TRNG posten
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_disable_posten(TRNG_TypeDef *trng)
{
	CLEAR_BIT(trng->CR, TRNG_CR_POSTEN_MSK);
}

/**
  * @brief  Check if TRNG posten enable
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_trng_is_posten_enable(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->CR, TRNG_CR_POSTEN_MSK, TRNG_CR_POSTEN_POS);
}

/**
  * @brief  Set TRNG data width select
  * @param  trng TRNG Instance
  * @param  width The value of following:
  *         - 0x0: 1-bit
  *         - 0x1: 8-bit
  *         - 0x2: 16-bit
  *         - 0x3: 32-bit
  * @retval None
  */
__STATIC_INLINE void md_trng_set_data_width_dsel(TRNG_TypeDef * trng, uint32_t width)
{
	MODIFY_REG(trng->CR, TRNG_CR_DSEL_MSK, width << TRNG_CR_DSEL_POSS);
}

/**
  * @brief  Get TRNG data width select
  * @param  trng TRNG Instance
  * @retval The value of following:
  *         - 0x0: 1-bit
  *         - 0x1: 8-bit
  *         - 0x2: 16-bit
  *         - 0x3: 32-bit
  */
__STATIC_INLINE uint32_t md_trng_get_data_width_dsel(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->CR, TRNG_CR_DSEL_MSK, TRNG_CR_DSEL_POSS);
}

/**
  * @brief  Set TRNG seed type
  * @param  trng TRNG Instance
  * @param  type The value of following:
  *         - 0x0: 0
  *         - 0x1: 1
  *         - 0x2: last random number
  *         - 0x3: seed register value
  * @retval None
  */
__STATIC_INLINE void md_trng_set_seed_sdsel(TRNG_TypeDef * trng, uint32_t type)
{
	MODIFY_REG(trng->CR, TRNG_CR_SDSEL_MSK, type << TRNG_CR_SDSEL_POSS);
}

/**
  * @brief  Get TRNG seed type
  * @param  trng TRNG Instance
  * @retval The value of following:
  *         - 0x0: 1-bit
  *         - 0x1: 8-bit
  *         - 0x2: 16-bit
  *         - 0x3: 32-bit
  */
__STATIC_INLINE uint32_t md_trng_get_seed_sdsel(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->CR, TRNG_CR_SDSEL_MSK, TRNG_CR_SDSEL_POSS);
}

/**
  * @brief  Set TRNG adjust factor
  * @param  trng TRNG Instance
  * @param  factor Adjust factor
  * @retval None
  */
__STATIC_INLINE void md_trng_set_adjust_factor_adjc(TRNG_TypeDef * trng, uint32_t factor)
{
	MODIFY_REG(trng->CR, TRNG_CR_ADJC_MSK, factor << TRNG_CR_ADJC_POSS);
}

/**
  * @brief  Get TRNG adjust factor
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_trng_get_adjust_factor_adjc(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->CR, TRNG_CR_ADJC_MSK, TRNG_CR_ADJC_POSS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group3 SR
  * @{
  */
/**
  * @brief  Get TRNG start state
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_trng_get_start_state(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->SR, TRNG_SR_START_MSK, TRNG_SR_START_POS);
}

/**
  * @brief  Get TRNG davld state
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_trng_get_davld_state(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->SR, TRNG_SR_DAVLD_MSK, TRNG_SR_DAVLD_POS);
}

/**
  * @brief  Get TRNG serr state
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_trng_get_serr_state(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->SR, TRNG_SR_SERR_MSK, TRNG_SR_SERR_POS);
}

/**
  * @brief  Get TRNG over state
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_trng_get_over_state(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->SR, TRNG_SR_OVER_MSK, TRNG_SR_OVER_POS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group4 DR
  * @{
  */
/**
  * @brief  Get TRNG data
  * @param  trng TRNG Instance
  * @retval Data of trng
  */
__STATIC_INLINE uint32_t md_trng_get_data(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->DR, TRNG_DR_DATA_MSK, TRNG_DR_DATA_POSS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group5 SEED
  * @{
  */
/**
  * @brief  Set TRNG seed
  * @param  trng TRNG Instance
  * @param  sed Seed value 0x00000000 ~ 0xFFFFFFFF 
  * @retval None
  */
__STATIC_INLINE void md_trng_set_seed(TRNG_TypeDef * trng, uint32_t sed)
{
	 MODIFY_REG(trng->SEED, TRNG_SEED_SEED_MSK, sed << TRNG_SEED_SEED_POSS);
}

/**
  * @brief  Get TRNG seed
  * @param  trng TRNG Instance
  * @retval Seed value 0x00000000 ~ 0xFFFFFFFF 
  */
__STATIC_INLINE uint32_t md_trng_get_seed(TRNG_TypeDef * trng)
{
	return READ_BITS(trng->SEED, TRNG_SEED_SEED_MSK, TRNG_SEED_SEED_POSS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group6 CFGR
  * @{
  */
/**
  * @brief  Set TRNG init time 
  * @param  trng TRNG Instance
  * @param  time init time parameter
  * @retval None
  */
__STATIC_INLINE void md_trng_set_init_time_tstart(TRNG_TypeDef * trng, uint32_t time)
{
	 MODIFY_REG(trng->CFGR, TRNG_CFGR_TSTART_MSK, time << TRNG_CFGR_TSTART_POSS);
}

/**
  * @brief  Get TRNG init time 
  * @param  trng TRNG Instance
  * @retval Time configuration
  */
__STATIC_INLINE uint32_t md_trng_get_init_time_tstart(TRNG_TypeDef * trng)
{
	 return READ_BITS(trng->CFGR, TRNG_CFGR_TSTART_MSK, TRNG_CFGR_TSTART_POSS);
}

/**
  * @brief  Set TRNG TRNG0 clock divider 
  * @param  trng TRNG Instance
  * @param  divide TRNG0 clock divide parameter
  * @retval None
  */
__STATIC_INLINE void md_trng_set_trng0_clock_divide_ckdiv(TRNG_TypeDef * trng, uint32_t divide)
{
	 MODIFY_REG(trng->CFGR, TRNG_CFGR_CKDIV_MSK, divide << TRNG_CFGR_CKDIV_POSS);
}

/**
  * @brief  Get TRNG TRNG0 clock divide parameter
  * @param  trng TRNG Instance
  * @retval divide parameter
  */
__STATIC_INLINE uint32_t md_trng_get_trng0_clock_divide_ckdiv(TRNG_TypeDef * trng)
{
	 return READ_BITS(trng->CFGR, TRNG_CFGR_CKDIV_MSK, TRNG_CFGR_CKDIV_POSS);
}

/**
  * @brief  Set TRNG top limit 
  * @param  trng TRNG Instance
  * @param  lim Top limit value
  * @retval None
  */
__STATIC_INLINE void md_trng_set_top_limit_toplmt(TRNG_TypeDef * trng, uint32_t lim)
{
	 MODIFY_REG(trng->CFGR, TRNG_CFGR_TOPLMT_MSK, lim << TRNG_CFGR_TOPLMT_POSS);
}

/**
  * @brief  Get TRNG top limit 
  * @param  trng TRNG Instance
  * @retval Top limit value
  */
__STATIC_INLINE uint32_t md_trng_get_top_limit_toplmt(TRNG_TypeDef * trng)
{
	 return READ_BITS(trng->CFGR, TRNG_CFGR_TOPLMT_MSK, TRNG_CFGR_TOPLMT_POSS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group7 IER
  * @{
  */
/**
  * @brief  Enable TRNG START interrupt. 
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_enable_start_intrrupt(TRNG_TypeDef *trng)
{
	SET_BIT(trng->IER, TRNG_IER_START_MSK);
}

/**
  * @brief  Disable TRNG START interrupt.
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_disable_start_intrrupt(TRNG_TypeDef *trng)
{
	CLEAR_BIT(trng->IER, TRNG_IER_START_MSK);
}

/**
  * @brief  Check TRNG START interrupt is enabled
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_trng_start_interrupt_is_enable(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->IER, TRNG_IER_START_MSK, TRNG_IER_START_POS);
}

/**
  * @brief  Enable TRNG DAVLD interrupt 
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_enable_davld_intrrupt(TRNG_TypeDef *trng)
{
	SET_BIT(trng->IER, TRNG_IER_DAVLD_MSK);
}

/**
  * @brief  Disable TRNG DAVLD interrupt 
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_disable_dvald_intrrupt(TRNG_TypeDef *trng)
{
	CLEAR_BIT(trng->IER, TRNG_IER_DAVLD_MSK);
}

/**
  * @brief  Check TRNG DAVLD interrupt is enabled
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_trng_dvald_interrupt_is_enable(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->IER, TRNG_IER_DAVLD_MSK, TRNG_IER_DAVLD_POS);
}

/**
  * @brief  Enable TRNG SERR interrupt 
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_enable_serr_intrrupt(TRNG_TypeDef *trng)
{
	SET_BIT(trng->IER, TRNG_IER_SERR_MSK);
}

/**
  * @brief  Disable TRNG SERR interrupt
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_disable_serr_intrrupt(TRNG_TypeDef *trng)
{
	CLEAR_BIT(trng->IER, TRNG_IER_SERR_MSK);
}

/**
  * @brief  Check TRNG SERR interrupt is enabled
  * @param  trng TRNG Instance
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_trng_serr_interrupt_is_enable(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->IER, TRNG_IER_SERR_MSK, TRNG_IER_SERR_POS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group8 IFR
  * @{
  */
/**
  * @brief  Get TRNG START flag
  * @param  trng TRNG Instance
  * @retval State:
  *         - 0: init not finished or flag was cleared
  *         - 1: init finished 
  */
__STATIC_INLINE uint32_t md_trng_is_active_flag_start(RTC_TypeDef *trng)
{
	return READ_BITS(trng->IFR, TRNG_IFR_START_MSK, TRNG_IFR_START_POS);
}

/**
  * @brief  Get TRNG DAVLD flag
  * @param  trng TRNG Instance
  * @retval State:
  *         - 0: data not valid or flag was cleared
  *         - 1: data valid
  */
__STATIC_INLINE uint32_t md_trng_is_active_flag_davld(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->IFR, TRNG_IFR_DAVLD_MSK, TRNG_IFR_DAVLD_POS);
}

/**
  * @brief  Get TRNG SERR flag
  * @param  trng TRNG Instance
  * @retval State:
  *         - 0: not detect sequence error or flag was cleared 
  *         - 1: detected sequence error
  */
__STATIC_INLINE uint32_t md_trng_is_active_flag_serr(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->IFR, TRNG_IFR_SERR_MSK, TRNG_IFR_SERR_POS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group9 IFCR
  * @{
  */
/**
  * @brief  Clear TRNG START intterrupt flag
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_clear_flag_start_startc(TRNG_TypeDef *trng)
{
	SET_BIT(trng->IFCR, TRNG_IFCR_STARTC_MSK);
}

/**
  * @brief  Clear TRNG DAVLDC intterrupt flag
  * @param  trng TRNG Instance
  * @retval None
  */
__STATIC_INLINE void md_trng_clear_flag_davld_davldc(TRNG_TypeDef *trng)
{
	SET_BIT(trng->IFCR, TRNG_IFCR_DAVLDC_MSK);
}

/**
  * @brief  Clear TRNG SERR intterrupt flag
  * @retval None
  */
__STATIC_INLINE void md_trng_clear_flag_serr_serrc(TRNG_TypeDef *trng)
{
	SET_BIT(trng->IFCR, TRNG_IFCR_SERRC_MSK);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group10 ISR
  * @{
  */
/**
  * @brief  Get TRNG START interrupt state 
  * @retval State:
  *         - 0: no transmit interrupt 
  *         - 1: transmit interrupt
  */
__STATIC_INLINE uint32_t md_trng_get_start_interrupt_state(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->ISR, TRNG_ISR_START_MSK, TRNG_ISR_START_POS);
}

/**
  * @brief  Get TRNG DAVLD interrupt state 
  * @retval State:
  *         - 0: no transmit interrupt 
  *         - 1: transmit interrupt
  */
__STATIC_INLINE uint32_t md_trng_get_davld_interrupt_state(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->ISR, TRNG_ISR_DAVLD_MSK, TRNG_ISR_DAVLD_POS);
}

/**
  * @brief  Get TRNG SERR interrupt state 
  * @retval State:
  *         - 0: no transmit interrupt 
  *         - 1: transmit interrupt
  */
__STATIC_INLINE uint32_t md_trng_get_serr_interrupt_state(TRNG_TypeDef *trng)
{
	return READ_BITS(trng->ISR, TRNG_ISR_SERR_MSK, TRNG_ISR_SERR_POS);
}
/**
  * @}
  */
/** @defgroup MD_TRNG_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_trng_init(md_trng_init_t *init);
extern void md_trng_struct_init(md_trng_init_t *init);
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
