/**
 * @file    version.h.in
 * @author  jackchen
 * @version v1.0.10
 * @date    15-Jan-2019
 * @brief   Version management interface for the alumy library (template file)
 * 
 * This header file provides version information and utilities for the alumy
 * library, including version checking macros, version structure definitions,
 * and functions to retrieve version information. This is a template file that
 * gets processed by CMake to generate the actual version.h header.
 * 
 * @copyright Copyright (c) 2019 alumy project
 * 
 */

#ifndef __AL_VERSION_H
#define __AL_VERSION_H

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/byteswap.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/** @brief Major version number (replaced by CMake) */
#define AL_MAJOR		1

/** @brief Minor version number (replaced by CMake) */
#define AL_MINOR		0

/** @brief Revision/patch number (replaced by CMake) */
#define AL_REV			10

/** @brief Build number (replaced by CMake) */
#define AL_BUILD		21

/**
 * @brief Check if current version meets minimum requirements
 * @param ma Required major version
 * @param mi Required minor version
 * @return Non-zero if requirements are met
 */
#define AL_PREREQ(ma, mi)	(AL_MAJOR << 16 | AL_MINOR >= (ma) << 16 | (mi))

/** @brief String representation of the current version */
#define AL_VERSION			__MS(AL_MAJOR.AL_MINOR.AL_REV.AL_BUILD)

/**
 * @brief Initialize version structure with given parameters
 * @param major Major version number
 * @param minor Minor version number
 * @param rev Revision number
 * @param build Build number
 * @param git_hash Git commit hash
 */
#define AL_VERSION_INIT(major, minor, rev, build, git_hash) \
	{ (major), (minor), (rev), (build), (git_hash) }

/**
 * @brief Version information structure
 * 
 * This structure contains all version-related information including
 * major, minor, revision, build numbers and git hash.
 */
typedef struct al_version {
	uint16_t av_major;		/**< Major version number */
	uint16_t av_minor;		/**< Minor version number */
	uint16_t av_rev;		/**< Revision number */
	uint16_t av_build;		/**< Build number */
	char av_git_hash[8];	/**< Git commit hash (first 7 chars + null terminator) */
} al_version_t;

/**
 * @brief Macro to generate getter functions for version fields
 * @param f Field name suffix (major, minor, rev, build)
 */
#define al_version_get_s(f) \
	static inline uint16_t al_version_get_##f(const al_version_t *ver) \
	{ \
		return ver->av_##f; \
	}

/** @brief Generate getter function for major version */
al_version_get_s(major)

/** @brief Generate getter function for minor version */
al_version_get_s(minor)

/** @brief Generate getter function for revision number */
al_version_get_s(rev)

/** @brief Generate getter function for build number */
al_version_get_s(build)

/**
 * @brief Get git hash from version structure
 * @param ver Pointer to version structure
 * @return Pointer to git hash string
 */
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
 * @return const char* Version string in format "major.minor.rev.build"
 */
const char *al_get_version_s(void);

/**
 * @brief Get alumy version struct
 *
 * @author jack (2023/7/6)
 *
 * @param void
 *
 * @return const al_version_t* Pointer to version structure
 */
const al_version_t *al_get_version(void);

/**
 * @brief Initialize version structure
 *
 * @author jack (2023/7/6)
 *
 * @param av Pointer to version structure to initialize
 * @param major Major version number
 * @param minor Minor version number
 * @param rev Revision number
 * @param build Build number
 * @param git_hash Git commit hash string
 *
 * @return int_t 0 on success, negative on error
 */
int_t al_version_init(al_version_t *av,
					  uint16_t major, uint16_t minor, uint16_t rev,
					  uint16_t build, const char *git_hash);

__END_DECLS

#endif
