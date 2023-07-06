#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/check.h"
#include "alumy/string.h"
#include "alumy/git_hash.h"
#include "alumy/version.h"

__BEGIN_DECLS

static const al_version_t al_version = {
    .av_major = ALUMY_MAJOR,
    .av_minor = ALUMY_MINOR,
    .av_rev = ALUMY_REV,
    .av_build = ALUMY_BUILD,
	.av_git_hash = GIT_HASH,
};

const char *al_get_version_s(void)
{
	return AL_VERSION;
}

const al_version_t *al_get_version(void)
{
	return &al_version;
}

int_t al_version_init(al_version_t *av, uint16_t major, uint16_t minor,
					  uint16_t rev, uint16_t build, const char *git_hash)
{
	AL_CHECK_RET(av == NULL, EINVAL, -1);

	av->av_major = major;
	av->av_minor = minor;
	av->av_rev = rev;
	av->av_build = build;
	strlcpy(av->av_git_hash, git_hash, sizeof(av->av_git_hash));

	return 0;
}

__END_DECLS

