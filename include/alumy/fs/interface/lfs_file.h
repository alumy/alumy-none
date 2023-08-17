#ifndef __AL_FS_INTERFACE_LFS_FILE_H
#define __AL_FS_INTERFACE_LFS_FILE_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/fs/littlefs/lfs.h"

__BEGIN_DECLS

int32_t al_lfs_write_file(lfs_t *lfs, const char *file_name,
						  const void *buf, size_t size);

int32_t al_lfs_read_file(lfs_t *lfs, const char *file_name,
						 void *buf, size_t size);

int32_t al_lfs_cp(lfs_t *src_lfs, lfs_t *dest_lfs,
				  const char *src_path, const char *dest_path);

ssize_t al_lfs_get_file_size(lfs_t *lfs, const char *path);

__END_DECLS

#endif

