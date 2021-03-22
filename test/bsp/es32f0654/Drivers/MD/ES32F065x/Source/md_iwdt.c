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

#include "md_iwdt.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_IWDT
/** @defgroup MD_IWDT IWDT
  * @{
  */

/** @addtogroup MD_IWDT_Public_Functions
  * @{
  */

/** @addtogroup MD_IWDT_Public_Functions_Group1
  * @{
  */

/**
 * @brief Initializes the IWDG according to the specified parameters.
 * @param load: Specifies the free-running downcounter value.
 * @param interrupt: Enable or disable interrupt.
 * @retval None
 */
void md_iwdt_init(uint32_t load, type_func_t interrupt)
{
	IWDT_UNLOCK();
	md_iwdt_set_count_overload(load);
	md_iwdt_set_count_clock2();
	md_iwdt_enable_reset();

	if (interrupt == ENABLE) {
		md_iwdt_enable_interrupt();
	}
	else {
		md_iwdt_disable_interrupt();
	}

	IWDT_LOCK();

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
#endif
/**
  * @}
  */
