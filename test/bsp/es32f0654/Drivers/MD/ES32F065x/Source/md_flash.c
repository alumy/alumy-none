/**
  *********************************************************************************
  *
  * @file    md_flash.c
  * @brief   FLASH module driver.
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

/** @addtogroup MD_FLASH_Private_Functions
  * @{
  */
/**
  * @brief  Unlock the flash.
  * @retval Status, see @ref md_status_t.
  */
__RAMFUNC static md_status_t pragram_flash_unlock(void)
{
	uint32_t i = 0;

	if (md_flash_is_active_flag_busy())
		return MD_ERROR;

	WRITE_REG(MSC->FLASHKEY, 0x8ACE0246);
	WRITE_REG(MSC->FLASHKEY, 0x9BDF1357);

	md_flash_enable_iap();
	md_flash_enable_operate_request();

	for (i = 0; i < 0xFFFF; i++) {
		if (md_flash_is_active_flag_flashack())
			break;
	}

	return i == 0xFFFF ? MD_ERROR : MD_OK;
}

/**
  * @brief  Lock the flash.
  * @retval Status, see @ref md_status_t.
  */
__RAMFUNC static md_status_t pragram_flash_lock(void)
{
	uint16_t i;

	WRITE_REG(MSC->FLASHKEY, 0x8ACE0246);
	WRITE_REG(MSC->FLASHKEY, 0x9BDF1357);

	WRITE_REG(MSC->FLASHCR, 0x0);

	for (i = 0; i < 0xFFFF; i++) {
		if (!md_flash_is_active_flag_flashack())
			break;
	}

	return i == 0xFFFF ? MD_ERROR : MD_OK;
}

/**
  * @brief  Erase one page.
  * @param  addr: The erased page's address
  * @retval Status, see @ref md_status_t.
  */
__RAMFUNC md_status_t __md_flash_page_erase(uint32_t addr)
{
	uint32_t i;

	if (pragram_flash_unlock() != MD_OK)
		goto end;

	md_flash_disable_info_region();
	md_flash_set_flash_addr(FLASH_PAGE_ADDR(addr));
	md_flash_set_program_cmd(MD_FLASH_CMD_PE);

	for (i = 0; i < 0xFFFF; i++) {
		if (md_flash_is_active_flag_busy())
			continue;
		if (md_flash_is_active_flag_addr_ov())
			goto end;
		if (md_flash_is_active_flag_wrp_flag())
			goto end;
		if (md_flash_is_active_flag_sera())
			break;
	}

	if (i == 0xFFFF)
		goto end;

	if (pragram_flash_lock() == MD_ERROR)
		goto end;

	return MD_OK;
end:

	pragram_flash_lock();
	return MD_ERROR;
}

/**
  * @brief  Programme a word.
  * @param  addr: The word's address, it is must word align.
  * @param  data: The 8 bytes data be write.
  * @param  len: The number of data be write.
  * @retval Status, see @ref md_status_t.
  */
__RAMFUNC md_status_t __md_flash_word_program(uint32_t addr, uint32_t *data, uint32_t len)
{
	uint16_t i = 0;
	uint16_t prog_len;
	uint32_t *p_data = data;

	if (pragram_flash_unlock() != MD_OK)
		goto end;

	md_flash_disable_info_region();
	md_flash_set_flash_addr(addr);

	for (prog_len = 0; prog_len < len; prog_len++) {
		md_flash_set_low_byte_program_data(p_data[0]);
		md_flash_set_high_byte_program_data(p_data[1]);
		md_flash_set_program_cmd(MD_FLASH_CMD_WP);

		p_data += 2;

		for (i = 0; i < 0xFFFF; i++) {
			if (md_flash_is_active_flag_busy())
				continue;
			if (md_flash_is_active_flag_prog())
				break;
		}
	}
	if (i == 0xFFFF)
		goto end;

	if (pragram_flash_lock() == MD_ERROR)
		goto end;

	return MD_OK;
end:
	pragram_flash_lock();
	return MD_ERROR;
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
