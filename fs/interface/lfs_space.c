#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/bug.h"
#include "alumy/log.h"
#include "alumy/check.h"
#include "alumy/osal.h"
#include "alumy/fs/littlefs/lfs.h"
#include "alumy/fs/interface/lfs_space.h"

__BEGIN_DECLS

ssize_t al_lfs_get_fs_size(lfs_t *lfs)
{
	lfs_ssize_t size;

	size = lfs_fs_size(lfs);

	AL_CHECK_RET(size >= 0, EIO, -1);

	return size;
}

static int traverse_df_cb(void *p, lfs_block_t block)
{
    *(lfs_size_t *)p += 1;
    return 0;
}

int32_t al_lfs_block_stats(lfs_t *lfs, lfs_block_stats_t *stats)
{
	int32_t err;
	lfs_size_t used = 0;

	memset(stats, 0, sizeof(lfs_block_stats_t));

	err = lfs_fs_traverse(lfs, traverse_df_cb, &used);
	if (err < 0) {
		return -1;
	}

	stats->block_size = lfs->cfg->block_size;
	stats->block_count = lfs->cfg->block_count;
	stats->block_used = used;
	stats->block_free = lfs->cfg->block_count - used;

	return 0;
}

__END_DECLS

