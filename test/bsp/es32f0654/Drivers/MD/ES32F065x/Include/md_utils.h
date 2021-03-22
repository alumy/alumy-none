/**
  *********************************************************************************
  *
  * @file    md_utils.h
  * @brief   Header file of UTILS module driver.
  *
  * @version V1.0
  * @date    19 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */


#ifndef __MD_UTILS_H__
#define __MD_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "md_conf.h"
#include "type.h"
#include "es32f065x.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @addtogroup MD_UTILS
  * @{
  */

/** @defgroup MD_UTILS_Public_Types UTILS Public Types
  * @{
  */
/**
  * @brief  MD Status structures definition
  */
typedef enum {
	MD_OK      = 0x0U,	/**< Status: OK */
	MD_ERROR   = 0x1U,	/**< Status: ERROR */
	MD_BUSY    = 0x2U,	/**< Status: BUSY */
	MD_TIMEOUT = 0x3U, 	/**< Status: TIMEOUT */
} md_status_t;
/**
  * @}
  */
/** @defgroup ALD_Private_Macros Public Macros
  * @{
  */
#define MD_MCU_UID0_ADDR	0x000403E0U
#define MD_MCU_UID1_ADDR	0x000403E8U
#define MD_MCU_UID2_ADDR	0x000403F0U
#define MD_MCU_CHIPID_ADDR	0x000403F8U
/**
  * @}
  */
/** @addtogroup MD_UTILS_Public_Functions
  * @{
  */
extern void md_init_1ms_tick(void);
extern void md_inc_tick(void);
extern __weak void md_systick_irq_cbk(void);
extern uint32_t md_get_tick(void);
extern void md_delay_1ms(__IO uint32_t delay);
extern void md_mcu_irq_config(IRQn_Type irq, uint8_t prio, type_func_t status);
extern uint32_t md_mcu_get_cpu_id(void);
extern void md_mcu_get_uid(uint8_t *buf);
extern uint32_t md_mcu_get_chipid(void);
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
