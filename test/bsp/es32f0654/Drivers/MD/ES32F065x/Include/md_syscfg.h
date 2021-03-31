/**
  *********************************************************************************
  *
  * @file    md_syscfg.h
  * @brief   SYSCFG module driver.
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

#ifndef __MD_SYSCFG_H__
#define __MD_SYSCFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "md_utils.h"


/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_SYSCFG SYSCFG
  * @brief SYSCFG module driver
  * @{
  */

/** @defgroup MD_SYSCFG_Public_Macros SYSCFG Public Macros
  * @{
  */
#define SYSCFG_LOCK()  		WRITE_REG(SYSCFG->PROT, 0x0U)
#define SYSCFG_UNLOCK()		WRITE_REG(SYSCFG->PROT, 0x55AA6996U)
#define GET_SYSCFG_LOCK()	READ_BIT(SYSCFG->PROT, SYSCFG_PROT_PROT_MSK)

#define MD_BOOT_FROM_BOOT_ROM()					\
do {								\
	SYSCFG_UNLOCK();					\
	SET_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BRRMPEN_MSK);	\
	CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK);	\
	SYSCFG_LOCK();						\
} while (0)

#define MD_BOOT_FROM_BOOT_FLASH()					\
do {								\
	SYSCFG_UNLOCK();					\
	CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BRRMPEN_MSK);	\
	SET_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK);	\
	SYSCFG_LOCK();						\
} while (0)

#define MD_BOOT_FROM_FLASH()					\
do {								\
	SYSCFG_UNLOCK();					\
	CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BRRMPEN_MSK);	\
	CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK);	\
	SYSCFG_LOCK();						\
} while (0)
/**
  * @}
  */


/** @defgroup MD_SYSCFG_Public_Functions SYSCFG Public Functions
  * @{
  */
__INLINE void md_vtor_config(uint32_t offset, type_func_t status)
{
	SYSCFG_UNLOCK();

	if (status) {
		MODIFY_REG(SYSCFG->VTOR, SYSCFG_VTOR_VTO_MSK, (offset & ~0x3FU));
		SET_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_VTOEN_MSK);
	}
	else {
		CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_VTOEN_MSK);
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
#ifdef __cplusplus
}
#endif

#endif
