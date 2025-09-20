/**
 * @file    lrc.h
 * @author  alumy project
 * @version v0.0.1
 * @brief   Longitudinal Redundancy Check (LRC) calculation utilities
 * 
 * This header file provides LRC calculation functions for error detection
 * in data transmission and storage. LRC is a simple parity check that
 * calculates the XOR of all bytes in a data block.
 * 
 * @copyright Copyright (c) 2019 alumy project
 */

#ifndef __AL_LRC_H
#define __AL_LRC_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
 * @brief Calculate Longitudinal Redundancy Check (LRC) for data
 *
 * This function calculates the LRC value by performing an XOR operation
 * on all bytes in the provided data buffer. LRC is commonly used for
 * simple error detection in communication protocols and data storage.
 *
 * @param data Pointer to the data buffer to calculate LRC for
 * @param len Length of the data buffer in bytes
 *
 * @return uint8_t The calculated LRC value (8-bit checksum)
 */
uint8_t al_lrc(const void *data, size_t len);

__END_DECLS

#endif
