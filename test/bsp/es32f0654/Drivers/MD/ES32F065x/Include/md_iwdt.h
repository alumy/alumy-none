/**
  *********************************************************************************
  *
  * @file    md_iwdt.h
  * @brief   Header file of IWDT module driver.
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

#ifndef __MD_IWDT_H__
#define __MD_IWDT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_IWDT IWDT
  * @{
  */

/**
 * @defgroup MD_IWDT_Private_Macros IWDT Private Macros
 * @{
 */

#define IWDT_UNLOCK() {WRITE_REG(IWDT->LOCK, 0x1ACCE551U);}
#define IWDT_LOCK()   {WRITE_REG(IWDT->LOCK, 0xFFFFFFFFU);}

/**
 * @}
 */

/** @defgroup MD_IWDT_Public_Functions IWDT Public Functions
  * @{
  */
/** @defgroup MD_IWDT_Public_Functions_Group2 LOAD
  * @{
  */
/**
  * @brief  Set iwdt count overload value.
  * @param  cnt: iwdt overload value.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_set_count_overload(uint32_t cnt)
{
	MODIFY_REG(IWDT->LOAD, IWDT_LOAD_LOAD_MSK, cnt << IWDT_LOAD_LOAD_POSS);
}
/**
 * @}
 */
/** @defgroup MD_IWDT_Public_Functions_Group3 VALUE
  * @{
  */
/**
  * @brief  Get iwdt current count value.
  * @retval Value for count value
  */
__STATIC_INLINE uint32_t md_iwdt_get_count_value(void)
{
	return READ_BITS(IWDT->VALUE, IWDT_VALUE_VALUE_MSK, IWDT_VALUE_VALUE_POSS);
}
/**
 * @}
 */
/** @defgroup MD_IWDT_Public_Functions_Group4 CON
  * @{
  */
/**
  * @brief  Set iwdt count clock 1.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_set_count_clock1(void)
{
	CLEAR_BIT(IWDT->CON, IWDT_CON_CLKS_MSK);
}

/**
  * @brief  Set iwdt count clock 2.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_set_count_clock2(void)
{
	SET_BIT(IWDT->CON, IWDT_CON_CLKS_MSK);
}

/**
  * @brief  Check if iwdt count clock is clock1 source.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_enable_count_clock1(void)
{
	return (READ_BIT(IWDT->CON, IWDT_CON_CLKS_MSK) != IWDT_CON_CLKS_MSK);
}

/**
  * @brief  Check if iwdt count clock is clock2 source.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_enable_count_clock2(void)
{
	return (READ_BIT(IWDT->CON, IWDT_CON_CLKS_MSK) == IWDT_CON_CLKS_MSK);
}

/**
  * @brief  Enable iwdt reset bit.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_enable_reset(void)
{
	SET_BIT(IWDT->CON, IWDT_CON_RSTEN_MSK);
}

/**
  * @brief  Disable iwdt reset bit.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_disable_reset(void)
{
	CLEAR_BIT(IWDT->CON, IWDT_CON_RSTEN_MSK);
}

/**
  * @brief  Check if is enable reset bit.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_enable_reset(void)
{
	return (READ_BIT(IWDT->CON, IWDT_CON_RSTEN_MSK) == IWDT_CON_RSTEN_MSK);
}

/**
  * @brief  Enable iwdt interrupt.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_enable_interrupt(void)
{
	SET_BIT(IWDT->CON, IWDT_CON_IE_MSK);
}

/**
  * @brief  Disable iwdt interrupt.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_disable_interrupt(void)
{
	CLEAR_BIT(IWDT->CON, IWDT_CON_IE_MSK);
}

/**
  * @brief  Check if is enable interrupt.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_enable_interrupt(void)
{
	return (READ_BIT(IWDT->CON, IWDT_CON_IE_MSK) == IWDT_CON_IE_MSK);
}

/**
  * @brief  Enable iwdt module.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_enable(void)
{
	SET_BIT(IWDT->CON, IWDT_CON_EN_MSK);
}

/**
  * @brief  Disable iwdt interrupt.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_disable(void)
{
	CLEAR_BIT(IWDT->CON, IWDT_CON_EN_MSK);
}

/**
  * @brief  Check if is enable interrupt.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_enable(void)
{
	return (READ_BIT(IWDT->CON, IWDT_CON_EN_MSK) == IWDT_CON_EN_MSK);
}
/**
 * @}
 */
/** @defgroup MD_IWDT_Public_Functions_Group5 Interrupt
  * @{
  */
/**
  * @brief  Clear iwdt Interrupt flag.
  * @retval None
  */
__STATIC_INLINE void md_iwdt_clear_flag_interrupt(void)
{
	WRITE_REG(IWDT->INTCLR, 0x55AA);
}

/**
  * @brief  Get iwdt interrupt flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_active_flag_interrupt(void)
{
	return (READ_BIT(IWDT->RIS, IWDT_RIS_WDTIF_MSK) == IWDT_RIS_WDTIF_MSK);
}
/**
 * @}
 */
/** @defgroup MD_IWDT_Public_Functions_Group6 LOCK
  * @{
  */
/**
  * @brief  Get iwdt project register status.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_iwdt_is_active_flag_lock(void)
{
	return (READ_BIT(IWDT->LOCK, IWDT_LOCK_LOCK_MSK) == IWDT_LOCK_LOCK_MSK);
}
/**
 * @}
 */
/** @defgroup MD_IWDT_Public_Functions_Group1 Initialization 
  * @{
  */
extern void md_iwdt_init(uint32_t load, type_func_t interrupt);
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
