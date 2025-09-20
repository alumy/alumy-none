/**
 * @file    watchdog.h
 * @author  jackchen
 * @version v0.0.1
 * @date    15-Jan-2019
 * @brief   Watchdog timer interface for the alumy library
 * 
 * This header file provides the watchdog timer interface for embedded systems.
 * The watchdog timer is a hardware timer that can reset the system if it is
 * not periodically reset by software, providing a way to recover from software
 * failures or infinite loops.
 * 
 * @copyright Copyright (c) 2019 alumy project
 * 
 */

#ifndef __AL_WATCHDOG_H
#define __AL_WATCHDOG_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS


/**
 * @brief Reset the watchdog timer
 * 
 * This function resets the watchdog timer to prevent the system from resetting.
 * It should be called periodically in the main loop to ensure the watchdog timer
 * is not triggered.
 * 
 * This is a weak function and should be overridden by the user.
 * 
 * @author jack (2025/9/20)
 * 
 * @param void
 * 
 * @return void
 */
void al_watchdog_reset(void);

__END_DECLS

#endif

