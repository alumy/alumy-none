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

__BEGIN_DECLS

int32_t al_lfs_write_file(lfs_t *lfs, const char *file_name,
						  const void *buf, size_t size, int32_t flag)
{
	int32_t ret;
	lfs_file_t file;

	ret = lfs_file_open(lfs, &file, file_name, flag);
	if (ret != 0) {
		set_errno(EIO);
		return -1;
	}

	ret = lfs_file_write(lfs, &file, buf, size);
	if (ret != size) {
		goto err;
	}

	ret = lfs_file_close(lfs, &file);
	if (ret != 0) {
		set_errno(EIO);
		return -1;
	}

	return 0;

err:
	lfs_file_close(lfs, &file);

	set_errno(EIO);
	return -1;
}

ssize_t al_lfs_read_file(lfs_t *lfs, const char *file_name,
						 void *buf, size_t size)
{
	int32_t ret;
	ssize_t n;
	lfs_file_t file;

	ret = lfs_file_open(lfs, &file, file_name, LFS_O_RDONLY);
	if (ret != 0) {
		set_errno(EIO);
		return -1;
	}

	n = lfs_file_read(lfs, &file, buf, size);
	if (n < 0) {
		goto err;
	}

	ret = lfs_file_close(lfs, &file);
	if (ret != 0) {
		set_errno(EIO);
		return -1;
	}

	set_errno(0);
	return n;

err:
	lfs_file_close(lfs, &file);

	set_errno(EIO);
	return -1;
}

int32_t al_lfs_cp(lfs_t *src_lfs, lfs_t *dest_lfs,
				  const char *src_path, const char *dest_path)
{
	ssize_t len;
	int32_t ret;
	uint8_t *buf = NULL;
	bool src_open = false;
	bool dest_open = false;
	size_t size = 4096;
	lfs_file_t src_file, dest_file;

	ret = lfs_file_open(src_lfs, &src_file, src_path, LFS_O_RDONLY);
	if (ret != 0) {
		AL_ERROR(1, "lfs open %s failed, errno = %d", src_path, ret);
		goto err;
	}

	src_open = true;

	ret = lfs_file_open(dest_lfs, &dest_file, dest_path, LFS_O_RDONLY);
	if (ret != 0) {
		AL_ERROR(1, "lfs open %s failed, errno = %d", dest_path, ret);
		goto err;
	}

	dest_open = true;

	buf = (uint8_t *)al_os_malloc(size);
	if (buf == NULL) {
		goto err;
	}

    while ((len = lfs_file_read(src_lfs, &src_file, buf, size)) > 0) {
        lfs_file_write(dest_lfs, &dest_file, buf, len);
	}

	lfs_file_close(src_lfs, &src_file);
	lfs_file_close(dest_lfs, &dest_file);
	al_os_free(buf);

	return 0;

err:
	if (src_open) {
		lfs_file_close(src_lfs, &src_file);
	}

	if (dest_open) {
		lfs_file_close(dest_lfs, &dest_file);
	}

	if (buf != NULL) {
		al_os_free(buf);
	}

	return -1;
}

ssize_t al_lfs_get_file_size(lfs_t *lfs, const char *path)
{
	int32_t ret;
	lfs_file_t file;
	ssize_t size;

	ret = lfs_file_open(lfs, &file, path, LFS_O_RDONLY);
	if (ret != 0) {
		set_errno(EIO);
		return -1;
	}

	lfs_file_seek(lfs, &file, 0, LFS_SEEK_END);
	size = lfs_file_tell(lfs, &file);
	lfs_file_close(lfs, &file);

	return size;
}

__END_DECLS

