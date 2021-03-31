/**
  *********************************************************************************
  *
  * @file    md_msc.h
  * @brief   Header file of MSC module driver.
  *
  * @version V1.0
  * @date    08 Mar 2020
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __MD_MSC_H__
#define __MD_MSC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"


/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_MSC MSC
  * @brief MSC module driver
  * @{
  */

/**
  * @defgroup MD_MSC_Private_Macros MSC Private Macros
  * @{
  */
#define MD_MSC_WSP_ADDR	0x10000000U
#define MD_MSC_PE_ADDR	0x10000004U
#define MD_MSC_WP_ADDR	0x10000008U
#define MD_MSC_DWP_ADDR	0x1000000cU
/**
  * @}
  */

/** @defgroup MD_MSC_Private_Types MSC Private Types
  * @{
  */
typedef uint32_t (*MD_MSC_PE)(uint32_t addr);
typedef uint32_t (*MD_MSC_WP)(uint32_t addr, uint32_t data);
typedef uint32_t (*MD_MSC_DWP)(uint32_t addr, uint32_t data_l, uint32_t data_h);
typedef uint32_t (*MD_MSC_WSP)(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase);
/**
  * @}
  */

/** @defgroup IAP_Public_Functions MSC Public Functions
  * @{
  */
/** @defgroup IAP_Public_Functions_Group1 FLASH Operation Functions
  * @{
  */
/**
  * @brief  Erases a specified page.
  * @param  addr: The beginning address of the page to be erased.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
__STATIC_INLINE__ uint32_t md_msc_erase_page(uint32_t addr)
{
	uint32_t status;
	MD_MSC_PE pe = (MD_MSC_PE)(*(uint32_t *)MD_MSC_PE_ADDR);

	__disable_irq();
	status = (*pe)(addr);
	__enable_irq();

	return !status;
}

/**
  * @brief  Programs a word at a specified address.
  * @param  addr: Specifies the address to be programmed.
  *         Bit0-1 must be zero.
  * @param  data: Specifies the data to be programmed.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
__STATIC_INLINE__ uint32_t md_msc_program_word(uint32_t addr, uint32_t data)
{
	uint32_t status;
	MD_MSC_WP wp = (MD_MSC_WP)(*(uint32_t *)MD_MSC_WP_ADDR);

	if (addr & 0x3)
		return 1;

	__disable_irq();
	status = (*wp)(addr, data);
	__enable_irq();

	return !status;
}

/**
  * @brief  Programs double words at a specified address.
  * @param  addr: Specifies the address to be programmed.
  *         Bit0-1 must be zero.
  * @param  data_l: Specifies the LSB data to be programmed.
  * @param  data_h: Specifies the MSB data to be programmed.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
__STATIC_INLINE__ uint32_t md_msc_program_dword(uint32_t addr, uint32_t data_l, uint32_t data_h)
{
	uint32_t status;
	MD_MSC_DWP dwp = (MD_MSC_DWP)(*(uint32_t *)MD_MSC_DWP_ADDR);

	if (addr & 0x3)
		return 1;

	__disable_irq();
	status = (*dwp)(addr, data_l, data_h);
	__enable_irq();

	return !status;
}

/**
  * @brief  Programs datas at a specified address.
  * @param  addr: Specifies the address to be programmed.
  *         Bit0-1 must be zero.
  * @param  data: Specifies the data to be programmed.
  * @param  len: Specifies the data length to be programmed.
  *         Bit0-1 must be zero.
  * @param  erase: Erase page flag before programming.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
__STATIC_INLINE__ uint32_t md_msc_program_words(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase)
{
	uint32_t status;
	MD_MSC_WSP wsp = (MD_MSC_WSP)(*(uint32_t *)MD_MSC_WSP_ADDR);

	if ((addr & 0x3) || (len & 0x3))
		return 1;

	__disable_irq();
	status = (*wsp)(addr, data, len, erase);
	__enable_irq();

	return !status;
}
/**
  * @}
  */
/** @defgroup IAP_Public_Functions_Group2 MSC Control Functions
  * @{
  */
/**
  * @brief  Set flash read wait cycle
  * @param  cycle: Wait cycle, [0-15] sysclock
  * @retval None
  */
__STATIC_INLINE__ void md_msc_flash_read_wait_cycle_set(uint8_t cycle)
{
	MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, cycle << MSC_MEMWAIT_FLASH_W_POSS);
}

/**
  * @brief  Get flash read wait cycle
  * @retval Wait cycle, [0-15] sysclock
  */
__STATIC_INLINE__ uint32_t md_msc_flash_read_wait_cycle_get(void)
{
	return READ_BITS(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, MSC_MEMWAIT_FLASH_W_POSS);
}

/**
  * @brief  Set sram read wait cycle
  * @param  cycle: Wait cycle, [0-3] sysclock
  * @retval None
  */
__STATIC_INLINE__ void md_msc_flash_sram_wait_cycle_set(uint8_t cycle)
{
	MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_SRAM_W_MSK, cycle << MSC_MEMWAIT_SRAM_W_POSS);
}

/**
  * @brief  Get sram read wait cycle
  * @retval Wait cycle, [0-3] sysclock
  */
__STATIC_INLINE__ uint32_t md_msc_sram_read_wait_cycle_get(void)
{
	return READ_BITS(MSC->MEMWAIT, MSC_MEMWAIT_SRAM_W_MSK, MSC_MEMWAIT_SRAM_W_POSS);
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
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __MD_MSC_H__ */
