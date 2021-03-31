/**
  *********************************************************************************
  *
  * @file    md_flash_ext.c
  * @brief   FLASH module extend driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_flash.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_FLASH

/** @addtogroup MD_FLASH
  * @{
  */
/** @addtogroup MD_FLASH_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Erase one page.
  * @param  addr: The erased page's address
  * @retval Status, see @ref md_status_t.
  */
md_status_t md_flash_page_erase(uint32_t addr)
{
	md_status_t ret;

	__disable_irq();
	ret = __md_flash_page_erase(addr);
	__enable_irq();

	return ret;
}

/**
  * @brief  Programme a word.
  * @param  addr: The word's address, it is must word align.
  * @param  data: The 8 bytes data be write.
  * @param  len: The number of data be write.
  * @retval Status, see @ref md_status_t.
  */
md_status_t md_flash_word_program(uint32_t addr, uint32_t *data, uint32_t len)
{
	md_status_t ret;

	__disable_irq();
	ret = __md_flash_word_program(addr, data, len);
	__enable_irq();

	return ret;
}

/**
  * @brief  read the specified length bytes from flash, and store to the specified area.
  * @param  ram_addr: the specified area to store the reading bytes.
  * @param  addr: the start address.
  * @param  len: the length to read.
  * @retval Status, see @ref md_status_t.
  */
md_status_t md_flash_read(uint32_t *ram_addr, uint32_t addr, uint16_t len)
{
	uint32_t temp;
	uint16_t i = 0;

	assert_param(((uint32_t)(addr) & 0x3) == 0 ? 1 : 0);

	temp = (uint32_t)ram_addr;

	if (((temp & 0x3) != 0) || (((addr) & 0x3) != 0))
		return MD_ERROR;

	for (i = 0; i < len; i++) {
		ram_addr[i] = ((uint32_t *)addr)[i];
	}

	return MD_OK;
}

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
