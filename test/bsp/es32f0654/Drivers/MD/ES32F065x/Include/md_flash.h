/**
  *********************************************************************************
  *
  * @file    md_flash.h
  * @brief   Header file of FLASH module driver.
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

#ifndef __MD_FLASH_H__
#define __MD_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

#if defined ( __ICCARM__ )
#define __RAMFUNC       __ramfunc
#else
#define __RAMFUNC
#endif

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_FLASH FLASH
  * @brief FLASH micro driver
  * @{
  */

/** 
  * @defgroup MD_FLASH_Private_Macros FLASH Private Macros
  * @{
  */
#define FLASH_BASE_ADDR			0x00000000U
#define	FLASH_PAGE_SIZE			1024UL
#define FLASH_WORD_SIZE			8UL
#define FLASH_TOTAL_SIZE		256UL
#define FLASH_PAGE_MASK			(FLASH_PAGE_SIZE - 1)
#define FLASH_WORD_MASK			(FLASH_WORD_SIZE - 1)
#define IS_FLASH_ADDRESS(ADDR)		((ADDR) < (FLASH_BASE_ADDR + FLASH_PAGE_SIZE * FLASH_TOTAL_SIZE))
#define IS_4BYTES_ALIGN(ADDR)		(((uint32_t)(ADDR) & 0x3) == 0 ? 1 : 0)
#define FLASH_PAGE_ADDR(ADDR)		((ADDR) & (~FLASH_PAGE_MASK))
#define FLASH_PAGEEND_ADDR(ADDR)	((ADDR) | FLASH_PAGE_MASK)
#define FLASH_WORD_ADDR(ADDR)		((ADDR) & (~FLASH_WORD_MASK))
#define FLASH_WORDEND_ADDR(ADDR)	((ADDR) | FLASH_WORD_MASK)
/**
  * @}
  */

/**
  * @defgroup MD_FLASH_Public_Macros FLASH Public Macros
  * @{
  */
/**
  * @brief flash cmd
  */
typedef enum {
	MD_FLASH_CMD_AE     = 0x000051AEU,	/**< Program area erase all */
	MD_FLASH_CMD_PE     = 0x00005EA1U,	/**< Page erase  */
	MD_FLASH_CMD_WP     = 0x00005DA2U,	/**< Word program */
	MD_FLASH_CMD_DATAPE = 0x00005BA4U,	/**< Data flash page page erase */
	MD_FLASH_CMD_DATAWP = 0x00005AA5U,	/**< Data flash word program */
} md_flash_cmd_type;

/**
  * @}
  */

/** @defgroup MD_FLASH_Private_Functions FLASH Private Functions
  * @{
  */
md_status_t __md_flash_page_erase(uint32_t addr);
md_status_t __md_flash_word_program(uint32_t addr, uint32_t *data, uint32_t len);
/**
  * @}
  */

/** @defgroup MD_FLASH_Public_Functions FLASH Public Functions
  * @{
  */
/** @defgroup MD__Public_Functions_Group2 FLASHKEY
  * @{
  */
/**
  * @brief  Get flash code region status.
  * @retval Status for flash code region
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_code_region_status(void)
{
	return READ_BITS(MSC->FLASHKEY, MSC_FLASHKEY_STATUS_MSK, MSC_FLASHKEY_STATUS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group3 INFOKEY
  * @{
  */
/**
  * @brief  Get flash info region status.
  * @retval Status for flash code region
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_info_region_status(void)
{
	return READ_BITS(MSC->INFOKEY, MSC_INFOKEY_STATUS_MSK, MSC_INFOKEY_STATUS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group4 FLASHADDR
  * @{
  */
/**
  * @brief  Enable flash info region.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_enable_info_region(void)
{
	SET_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
}

/**
  * @brief  Disable flash info region.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_disable_info_region(void)
{
	CLEAR_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
}

/**
  * @brief  Check if flash info region is enable or disable.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_enable_info_region(void)
{
	return (READ_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK) == MSC_FLASHADDR_IFREN_MSK);
}

/**
  * @brief  Set flash address.
  * @param  addr: program address.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_flash_addr(uint32_t addr)
{
	MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, (addr << MSC_FLASHADDR_ADDR_POSS));
}

/**
  * @brief  Get flash address.
  * @retval Address of flash which want program.
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_flash_addr(void)
{
	return READ_BITS(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, MSC_FLASHADDR_ADDR_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group5 FLASHFIFO
  * @{
  */
/**
  * @brief  Set flash program fifo.
  * @param  data: write to info.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_fifo(uint32_t data)
{
	MODIFY_REG(MSC->FLASHFIFO, MSC_FLASHFIFO_FIFO_MSK, (data << MSC_FLASHFIFO_FIFO_POSS));
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group6 FLASHDL
  * @{
  */
/**
  * @brief  Set flash program data by low byte.
  * @param  data: program low byte data.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_low_byte_program_data(uint32_t data)
{
	MODIFY_REG(MSC->FLASHDL, MSC_FLASHDL_DATAL_MSK, (data << MSC_FLASHDL_DATAL_POSS));
}
/**
  * @brief  Get flash program data by low byte.
  * @retval DATA program in low byte.
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_low_byte_program_data(void)
{
	return READ_BITS(MSC->FLASHDL, MSC_FLASHDL_DATAL_MSK, MSC_FLASHDL_DATAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group7 FLASHDH
  * @{
  */
/**
  * @brief  Set flash program data by high byte.
  * @param  data: program low byte data.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_high_byte_program_data(uint32_t data)
{
	MODIFY_REG(MSC->FLASHDH, MSC_FLASHDH_DATAH_MSK, (data << MSC_FLASHDH_DATAH_POSS));
}

/**
  * @brief  Get flash program data by high byte.
  * @retval DATA program in high byte.
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_high_byte_program_data(void)
{
	return READ_BITS(MSC->FLASHDH, MSC_FLASHDH_DATAH_MSK, MSC_FLASHDH_DATAH_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group8 FLASHCMD
  * @{
  */
/**
  * @brief  Set flash program command.
  * @param  cmd: flash program command.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_program_cmd(uint32_t cmd)
{
	WRITE_REG(MSC->FLASHCMD, cmd);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group9 FLASHCR
  * @{
  */
/**
  * @brief  Enable flash fifo.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_enable_fifo(void)
{
	SET_BIT(MSC->FLASHCR, MSC_FLASHCR_FIFOEN_MSK);
}

/**
  * @brief  Disable flash fifo.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_disable_fifo(void)
{
	CLEAR_BIT(MSC->FLASHCR, MSC_FLASHCR_FIFOEN_MSK);
}

/**
  * @brief  Check if is enable fifo.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint8_t md_flash_is_enable_fifo(void)
{
	return (READ_BIT(MSC->FLASHCR, MSC_FLASHCR_FIFOEN_MSK) == MSC_FLASHCR_FIFOEN_MSK);
}

/**
  * @brief  Enable flash operate request.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_enable_operate_request(void)
{
	SET_BIT(MSC->FLASHCR, MSC_FLASHCR_FLASHREQ_MSK);
}

/**
  * @brief  Disable flash operate request.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_disable_operate_request(void)
{
	CLEAR_BIT(MSC->FLASHCR, MSC_FLASHCR_FLASHREQ_MSK);
}

/**
  * @brief  Check if is enable flash operate request.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint8_t md_flash_is_enable_operate_request(void)
{
	return (READ_BIT(MSC->FLASHCR, MSC_FLASHCR_FLASHREQ_MSK) == MSC_FLASHCR_FLASHREQ_MSK);
}

/**
  * @brief  Enable flash IAP reset.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_enable_iap_reset(void)
{
	SET_BIT(MSC->FLASHCR, MSC_FLASHCR_IAPRST_MSK);
}

/**
  * @brief  Enable flash IAP.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_enable_iap(void)
{
	SET_BIT(MSC->FLASHCR, MSC_FLASHCR_IAPEN_MSK);
}

/**
  * @brief  Disable flash IAP.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_disable_iap(void)
{
	CLEAR_BIT(MSC->FLASHCR, MSC_FLASHCR_IAPEN_MSK);
}

/**
  * @brief  Check if is enable interrupt.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_enable_iap(void)
{
	return (READ_BIT(MSC->FLASHCR, MSC_FLASHCR_IAPEN_MSK) == MSC_FLASHCR_IAPEN_MSK);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group10 FLASHSR
  * @{
  */
/**
  * @brief  Get flash timeout flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_timeout(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_TIMEOUT_MSK) == MSC_FLASHSR_TIMEOUT_MSK);
}

/**
  * @brief  Get flash word program complete flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_prog(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_PROG_MSK) == MSC_FLASHSR_PROG_MSK);
}

/**
  * @brief  Get flash erase page complete flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_sera(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_SERA_MSK) == MSC_FLASHSR_SERA_MSK);
}

/**
  * @brief  Get flash erase code region complete flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_mase(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_MASE_MSK) == MSC_FLASHSR_MASE_MSK);
}

/**
  * @brief  Get flash erase addr overflow flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_addr_ov(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_ADDR_OV_MSK) == MSC_FLASHSR_ADDR_OV_MSK);
}

/**
  * @brief  Get flash write project flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_wrp_flag(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_WRP_FLAG_MSK) == MSC_FLASHSR_WRP_FLAG_MSK);
}

/**
  * @brief  Get flash iap busy flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_busy(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK) == MSC_FLASHSR_BUSY_MSK);
}

/**
  * @brief  Get flash opreate enable flag.
  * @retval State of bit (1 or 0).
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_is_active_flag_flashack(void)
{
	return (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_FLASHACK_MSK) == MSC_FLASHSR_FLASHACK_MSK);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group11 FLASHPL
  * @{
  */
/**
  * @brief  Set flash program length.
  * @param  len: program data length.
  * @retval None.
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_program_len(uint32_t len)
{
	MODIFY_REG(MSC->FLASHPL, MSC_FLASHPL_PROG_LEN_MSK, (len << MSC_FLASHPL_PROG_LEN_POSS));
}

/**
  * @brief  Get flash program length.
  * @retval Length of program data.
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_program_len(void)
{
	return READ_BITS(MSC->FLASHPL, MSC_FLASHPL_PROG_LEN_MSK, MSC_FLASHPL_PROG_LEN_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group12 MEMWAIT
  * @{
  */
/**
  * @brief  Set flash sram read wait time.
  * @param tim: Time for sram read.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_sram_read_time(uint32_t tim)
{
	MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_SRAM_W_MSK, (tim << MSC_MEMWAIT_SRAM_W_POSS));
}

/**
  * @brief  Get flash sram read wait time.
  * @retval Time for sram read.
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_sram_read_time(void)
{
	return READ_BITS(MSC->MEMWAIT, MSC_MEMWAIT_SRAM_W_MSK, MSC_MEMWAIT_SRAM_W_POSS);
}

/**
  * @brief  Set flash read wait time.
  * @param tim: Time for flash read.
  * @retval None
  */
__RAMFUNC __STATIC_INLINE void md_flash_set_flash_read_time(uint32_t tim)
{
	MODIFY_REG(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, (tim << MSC_MEMWAIT_FLASH_W_POSS));
}

/**
  * @brief  Get flash read wait time.
  * @retval Time for flash read.
  */
__RAMFUNC __STATIC_INLINE uint32_t md_flash_get_read_time(void)
{
	return READ_BITS(MSC->MEMWAIT, MSC_MEMWAIT_FLASH_W_MSK, MSC_MEMWAIT_FLASH_W_POSS);
}
/**
  * @}
  */
/** @defgroup MD_FLASH_Public_Functions_Group1 Initialization
  * @{
  */
extern md_status_t md_flash_page_erase(uint32_t addr);
extern md_status_t md_flash_word_program(uint32_t addr, uint32_t *data, uint32_t len);
extern md_status_t md_flash_read(uint32_t *ram_addr, uint32_t addr, uint16_t len);
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
