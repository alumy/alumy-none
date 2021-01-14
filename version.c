#include "alumy/version.h"
#include "alumy/base.h"

__BEGIN_DECLS

static const al_version_t al_version = {
    .major = ALUMY_MAJOR,
    .minor = ALUMY_MINOR,
    .rev = ALUMY_REV,
    .build = ALUMY_BUILD,
};

const char *al_get_version_s(void)
{
	return AL_VERSION;
}


const al_version_t *al_get_version(void)
{
	return &al_version;
}

__END_DECLS

