/**
 * @file    alumy.h
 * @author  jackchen
 * @version v0.0.3
 * @date    15-Jan-2019
 * @brief   Main header file for the alumy library
 * 
 * This is the primary header file that includes all necessary alumy library
 * components. It provides a comprehensive collection of utilities, data
 * structures, and algorithms for embedded system development.
 * 
 * @warning
 * The headers alumy/test.h and alumy/unity.h will override the standard
 * malloc() and free() functions. When using these testing frameworks,
 * ensure these headers are included separately or in pairs for any C files
 * that call malloc() and free() to avoid conflicts.
 * 
 * @copyright Copyright (c) 2019 alumy project
 * 
 * @par Example Usage:
 * @code
 * #include "alumy.h"
 * 
 * int main(void) {
 *     // Use alumy library functions
 *     return 0;
 * }
 * @endcode
 */
#ifndef __ALUMY_H
#define __ALUMY_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bit.h"
#include "alumy/bits.h"
#include "alumy/bits_latency.h"
#include "alumy/bitmap.h"
#include "alumy/swab.h"
#include "alumy/version.h"
#include "alumy/errno.h"
#include "alumy/log.h"
#include "alumy/list.h"
#include "alumy/rbtree.h"
#include "alumy/pool.h"
#include "alumy/bcd.h"
#include "alumy/filter.h"
#include "alumy/driver.h"
#include "alumy/mem.h"
#include "alumy/string.h"
#include "alumy/ascii.h"
#include "alumy/base64.h"
#include "alumy/byteswap.h"
#include "alumy/fifo.h"
#include "alumy/crc.h"
#include "alumy/lrc.h"
#include "alumy/bug.h"
#include "alumy/check.h"
#include "alumy/xyzmodem.h"
#include "alumy/initialized.h"
#include "alumy/pid.h"
#include "alumy/cJSON.h"
#include "alumy/cJSON_Utils.h"
#include "alumy/fs.h"
#include "alumy/csv.h"
#include "alumy/time.h"
#include "alumy/crypto.h"
#include "alumy/net.h"
#include "alumy/math.h"
#include "alumy/log2.h"
#include "alumy/osal.h"
#include "alumy/thread.h"
#include "alumy/watchdog.h"

#if defined(__GNUC__)
#include "alumy/kfifo.h"
#endif

#include "tinyprintf.h"

__BEGIN_DECLS

/**
 * @brief alumy init
 *
 * @author jack (2021/9/9)
 *
 * @param void
 *
 * @return int32_t return 0 on first init success, return 1 on
 *         already initialized
 */
int32_t alumy_init(void);

/**
 * @brief alumy cleanup
 *
 * @author jack (2021/9/9)
 *
 * @param void
 *
 * @return int32_t return 0 on cleanup success, return 1 on need
 *         more cleanup, return -1 on not initialized
 */
int32_t alumy_cleanup(void);

/**
 * @brief alumy lite init
 *
 * @author jack (2025/6/21)
 *
 * @param void
 *
 * @return int32_t return 0 on first init success, return 1 on
 *         already initialized, return -1 on error
 */
int32_t alumy_lite_init(void);

/**
 * @brief alumy lite cleanup
 *
 * @author jack (2025/6/21)
 *
 * @param void
 *
 * @return int32_t return 0 on cleanup success, return 1 on need
 *         more cleanup, return -1 on not initialized
 */
int32_t alumy_lite_cleanup(void);

__END_DECLS

#endif

