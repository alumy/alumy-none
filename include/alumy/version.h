#ifndef __AL_VERSION_H
#define __AL_VERSION_H

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/byteswap.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define AL_MAJOR		1
#define AL_MINOR		0
#define AL_REV			9
#define AL_BUILD		20

#define AL_PREREQ(ma, mi)	(AL_MAJOR << 16 | AL_MINOR >= (ma) << 16 | (mi))
#define AL_VERSION			__MS(AL_MAJOR.AL_MINOR.AL_REV.AL_BUILD)

#define AL_VERSION_INIT(major, minor, rev, build, git_hash) \
	{ (major), (minor), (rev), (build), (git_hash) }

typedef struct al_version {
	uint16_t av_major;
	uint16_t av_minor;
	uint16_t av_rev;
	uint16_t av_build;
	char av_git_hash[8];
} al_version_t;

#define al_version_get_s(f) \
	static inline uint16_t al_version_get_##f(const al_version_t *ver) \
	{ \
		return ver->av_##f; \
	}

al_version_get_s(major)
al_version_get_s(minor)
al_version_get_s(rev)
al_version_get_s(build)

__static_inline__
const char *al_version_get_git_hash(const al_version_t *ver)
{
	return (const char *)ver->av_git_hash;
}

/**
 * @brief Get alumy version string
 *
 * @author jack (2023/7/6)
 *
 * @param void
 *
 * @return const char*
 */
const char *al_get_version_s(void);

/**
 * @brief Get alumy version struct
 *
 * @author jack (2023/7/6)
 *
 * @param void
 *
 * @return const al_version_t*
 */
const al_version_t *al_get_version(void);

/**
 * @brief al_version_init
 *
 * @author jack (2023/7/6)
 *
 * @param av
 * @param major
 * @param minor
 * @param rev
 * @param build
 * @param git_hash
 *
 * @return int_t
 */
int_t al_version_init(al_version_t *av,
					  uint16_t major, uint16_t minor, uint16_t rev,
					  uint16_t build, const char *git_hash);

__END_DECLS

#endif
