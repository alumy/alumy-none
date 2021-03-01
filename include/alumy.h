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
#include "alumy/errno.h"
#include "alumy/log.h"
#include "alumy/list.h"
#include "alumy/pool.h"
#include "alumy/filter.h"
#include "alumy/driver.h"
#include "alumy/mem.h"
#include "alumy/string.h"
#include "alumy/base64.h"
#include "alumy/byteswap.h"
#include "alumy/fifo.h"
#include "alumy/crc.h"
#include "alumy/bug.h"
#include "alumy/xyzmodem.h"
#include "alumy/initialized.h"
#include "alumy/pid.h"

__BEGIN_DECLS

int32_t alumy_init(void);

int32_t alumy_cleanup(void);

__END_DECLS

#endif

