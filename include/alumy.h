/**
 ******************************************************************************
 * @file    alumy.h
 * @author  jackchen
 * @version v0.0.3
 * @date    15-Jan-2019
 * @brief   The header of libalumy
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; </center></h2>
 * alumy/test.h or alumy/unity.h will overwrite the malloc and
 * free, so please include the two headers alone or pairing for
 * c file that called malloc and free
 *
 ******************************************************************************
 */
#ifndef __ALUMY_H
#define __ALUMY_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bit.h"
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
#include "alumy/osal.h"
#include "alumy/thread.h"
#include "alumy/watchdog.h"

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

__END_DECLS

#endif

