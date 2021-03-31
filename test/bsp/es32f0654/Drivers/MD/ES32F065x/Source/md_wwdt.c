/**
  *********************************************************************************
  *
  * @file    md_wwdt.c
  * @brief   WWDT module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_wwdt.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_WWDT
/** @defgroup MD_WWDT WWDT
  * @{
  */
/** @defgroup MD_WWDT_Public_Functions  WWDT Public Functions
  * @{
  */
/** @defgroup MD_WWDT_Public_Functions_Group1 Initialization
  * @{
  */

/**
  * @brief Initializes the WWDT according to the specified parameters.
  * @param load: Specifies the free-running downcounter value.
  * @param win: specifics the no dog windows,
  *        the parameter can be one of the following values:
  *        @arg @ref MD_WWDT_WIN_25 No dog window size: 25%
  *        @arg @ref MD_WWDT_WIN_50 No dog window size: 50%
  *        @arg @ref MD_WWDT_WIN_75 No dog window size: 75%
  *        @arg @ref MD_WWDT_WIN_00 No dog window size: 0%
  * @param interrupt: Enable or disable interrupt.
  * @retval None
  */
void md_wwdt_init(uint32_t load, md_wwdt_win_t win, type_func_t interrupt)
{
	WWDT_UNLOCK();
	md_wwdt_set_count_overload(load);
	md_wwdt_set_forbid_feed_time(win);
	md_wwdt_set_count_lrc();
	md_wwdt_enable_reset();

	if (interrupt == ENABLE) {
		md_wwdt_enable_interrupt();
	}
	else {
		md_wwdt_disable_interrupt();
	}

	WWDT_LOCK();

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
