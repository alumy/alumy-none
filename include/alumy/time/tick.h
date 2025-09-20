/**
 * @file tick.h
 * @brief System tick management and timing utilities
 * 
 * This module provides system tick functionality for time tracking and timing operations.
 * It maintains a millisecond-resolution tick counter that can be used for timeouts,
 * delays, and general time measurement in embedded systems.
 * 
 * @author Alumy Development Team
 * @date 2024
 */

#ifndef __AL_TIME_TICK_H
#define __AL_TIME_TICK_H 1

#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
 * @brief Initialize the tick system
 */
void al_tick_init(void);

/**
 * @brief This should invoke in 1 msecond timer callback
 *
 * @author jack (2024/4/19)
 *
 * @param void
 */
void al_tick_inc(void);

/**
 * @brief Adjust the tick counter by the specified elapsed ticks
 *
 * @param tick_elapsed Number of ticks that have elapsed
 */
void al_tick_adj(uint32_t tick_elapsed);

/**
 * @brief Get the current time in seconds since system start
 *
 * @return Current time in seconds
 */
uint32_t al_tick_get_sec(void);

/**
 * @brief Get the current time in milliseconds since system start
 *
 * @return Current time in milliseconds
 */
uint32_t al_tick_get_msec(void);

/**
 * @brief Get the current tick count
 *
 * @return Current tick count
 */
uint32_t al_tick_get_tick(void);

/**
 * @brief Calculate elapsed ticks since the last recorded tick
 *
 * @param last The last recorded tick value
 * @return Number of ticks elapsed since the last tick
 */
uint32_t al_tick_elapsed_tick(uint32_t last);

/**
 * @brief Calculate elapsed seconds since the last recorded time
 *
 * @param last The last recorded time in seconds
 * @return Number of seconds elapsed since the last time
 */
uint32_t al_tick_elapsed_sec(uint32_t last);

__END_DECLS

#endif
