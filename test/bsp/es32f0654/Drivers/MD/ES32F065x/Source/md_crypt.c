/**
  *********************************************************************************
  *
  * @file    md_crypt.c
  * @brief   CRYPT module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_crypt.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_CRYPT
/** @addtogroup MD_CRYPT
  * @{
  */

/** @addtogroup MD_CRYPT_Public_Functions
  * @{
  */
/** @addtogroup MD_CRYPT_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Reset the CRYPT peripheral.
  * @retval None
  */
void md_crypt_reset(void)
{
	WRITE_REG(CRYPT->DATA[0], 0);
	WRITE_REG(CRYPT->DATA[1], 0);
	WRITE_REG(CRYPT->DATA[2], 0);
	WRITE_REG(CRYPT->DATA[3], 0);
	WRITE_REG(CRYPT->KEY[0], 0);
	WRITE_REG(CRYPT->KEY[1], 0);
	WRITE_REG(CRYPT->KEY[2], 0);
	WRITE_REG(CRYPT->KEY[3], 0);
	WRITE_REG(CRYPT->IV[0], 0);
	WRITE_REG(CRYPT->IV[1], 0);
	WRITE_REG(CRYPT->IV[2], 0);
	WRITE_REG(CRYPT->IV[3], 0);
	WRITE_REG(CRYPT->CON, 0x8000);
	WRITE_REG(CRYPT->IFC, 0xFFFF);
}

/**
  * @brief  Initializes the CRYPT mode according to the specified parameters in
  *         the @ref md_crypt_init_t
  * @param  init: Pointer to a md_crypt_init_t structure that contains
  *         the configuration information for the specified CRYPT module.
  * @retval None
  */
void md_crypt_init(md_crypt_init_t *init)
{
	md_crypt_reset();
	MODIFY_REG(CRYPT->CON, CRYPT_CON_ENCS_MSK | CRYPT_CON_MODE_MSK
			 | CRYPT_CON_TYPE_MSK | CRYPT_CON_FIFOODR_MSK,
			init->mode | init->type | init->order | init->encs);
}

/**
  * @brief  Initialize the CRYPT peripheral using the default parameters.
  * @param  init: Pointer to a md_crypt_init_t structure
  * @retval None
  */
void md_crypt_init_struct(md_crypt_init_t *init)
{
	init->mode  = MD_CRYPT_MODE_ECB;
	init->type  = MD_CRYPT_TYPE_32;
	init->order = MD_CRYPT_FIFO_ORDER_0;
	init->encs  = MD_CRYPT_SEL_ENCRYPT;
}

/**
  * @brief  Encrypt an amount of data in blocking mode.
  * @param  hperh: Pointer to a crypt_handle_t structure that contains
  *         the configuration information for the specified CRYPT module.
  * @param  plain_text: Pointer to plain data buffer
  * @param  cipher_text: Pointer to cipher data buffer
  * @param  size: Amount of plain data
  * @retval Status, see @ref md_status_t.
  * @note   the size is multiple of 16(ase)
  */
md_status_t md_crypt_encrypt(md_crypt_init_t *hperh, uint8_t *plain_text, uint8_t *cipher_text, uint32_t size)
{
	uint32_t count = 0;
	uint32_t i;
	uint32_t *plain_buf  = (uint32_t *)plain_text;
	uint32_t *cipher_buf = (uint32_t *)cipher_text;

	if ((plain_buf == NULL) || (cipher_buf == NULL) || (size == 0))
		return MD_ERROR;

	md_crypt_set_encs(CRYPT, MD_CRYPT_SEL_ENCRYPT);
	count = size / 16;

	while (count--) {
		for (i = 0; i < 4; i++) {
			md_crypt_set_fifo_data(CRYPT, *plain_buf);
			plain_buf++;
		}

		while (md_crypt_get_flag_done(CRYPT) == SET);

		for (i = 0; i < 4; i++) {
			*cipher_buf = md_crypt_get_fifo_data(CRYPT);
			cipher_buf++;
		}
	}

	return MD_OK;
}

/**
  * @brief  Decrypt an amount of data in blocking mode.
  * @param  hperh: Pointer to a crypt_handle_t structure that contains
  *         the configuration information for the specified CRYPT module.
  * @param  cipher_text: Pointer to cipher data buffer
  * @param  plain_text: Pointer to plain data buffer
  * @param  size: Amount of cipher data
  * @retval Status, see @ref md_status_t.
  * @note   the size is multiple of 16(ase)
  */
md_status_t md_crypt_decrypt(md_crypt_init_t *hperh, uint8_t *cipher_text, uint8_t *plain_text, uint32_t size)
{
	uint32_t count = 0;
	uint32_t i;
	uint32_t *plain_buf  = (uint32_t*)plain_text;
	uint32_t *cipher_buf = (uint32_t*)cipher_text;

	if (hperh->mode == MD_CRYPT_MODE_CTR) {
		return md_crypt_encrypt(hperh, cipher_text, plain_text, size);
	}

	if ((plain_buf == NULL) || (cipher_buf == NULL) || (size == 0))
		return MD_ERROR;

	md_crypt_set_encs(CRYPT, MD_CRYPT_SEL_DECRYPT);
	count = size / 16;

	while (count--) {
		for (i = 0; i < 4; i++) {
			md_crypt_set_fifo_data(CRYPT, *cipher_buf);
			cipher_buf++;
		}

		while (md_crypt_get_flag_done(CRYPT) == SET);

		for (i = 0; i < 4; i++) {
			*plain_buf = md_crypt_get_fifo_data(CRYPT);
			plain_buf++;
		}
	}

	return MD_OK;
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
