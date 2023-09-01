#ifndef __AL_FS_INTERFACE_LFS_FILE_H
#define __AL_FS_INTERFACE_LFS_FILE_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/fs/littlefs/lfs.h"

__BEGIN_DECLS

/**
 * @brief Write a file to lfs
 *
 * @author jack (2023/9/1)
 *
 * @param lfs The lfs context
 * @param file_name The file name
 * @param buf The buffer to write
 * @param size The size of written data
 * @param flag The open flag
 *
 * @return int32_t Return 0 on success, otherwise return
 *  	   negative
 */
int32_t al_lfs_write_file(lfs_t *lfs, const char *file_name,
						  const void *buf, size_t size, int32_t flag);

/**
 * @brief Read a file from lfs
 *
 * @author jack (2023/9/1)
 *
 * @param lfs The lfs context
 * @param file_name The file name
 * @param buf The buffer to read
 * @param size The read length
 *
 * @return ssize_t Return the read length on write, otherwise
 *  	   return negative
 */
ssize_t al_lfs_read_file(lfs_t *lfs, const char *file_name,
						 void *buf, size_t size);

/**
 * @brief Copy a file
 *
 * @author jack (2023/9/1)
 *
 * @param src_lfs
 * @param dest_lfs
 * @param src_path
 * @param dest_path
 *
 * @return int32_t
 */
int32_t al_lfs_cp(lfs_t *src_lfs, lfs_t *dest_lfs,
				  const char *src_path, const char *dest_path);

/**
 * @brief Get the file size
 *
 * @author jack (2023/9/1)
 *
 * @param lfs
 * @param path
 *
 * @return ssize_t
 */
ssize_t al_lfs_get_file_size(lfs_t *lfs, const char *path);

__END_DECLS

#endif

