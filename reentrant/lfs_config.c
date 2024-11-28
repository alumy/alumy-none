/*
 * lfs util functions
 *
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "alumy.h"
#include "lfs_util.h"

#ifdef LFS_CONFIG

// Software CRC implementation with small lookup table
uint32_t lfs_crc(uint32_t crc, const void *buffer, size_t size)
{
	return al_crc32_no_comp(crc, buffer, size);
}

#endif
