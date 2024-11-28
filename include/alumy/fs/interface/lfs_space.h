#ifndef __AL_FS_INTERFACE_LFS_SPACE_H
#define __AL_FS_INTERFACE_LFS_SPACE_H 1

#include "lfs.h"
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct lfs_block_stats {
	lfs_size_t block_size;
	lfs_size_t block_count;
	lfs_size_t block_used;
	lfs_size_t block_free;
} lfs_block_stats_t;

ssize_t al_lfs_get_fs_size(lfs_t *lfs);
int32_t al_lfs_block_stats(lfs_t *lfs, lfs_block_stats_t *stats);

__END_DECLS

#endif

