#ifndef __AL_VERSION_H
#define __AL_VERSION_H

#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#define ALUMY_MAJOR			1
#define ALUMY_MINOR			0
#define ALUMY_REV			1
#define ALUMY_BUILD			1
#define ALUMY_SUFFIX		"beta"

#define AL_PREREQ(ma, mi)	\
	(ALUMY_MAJOR << 16 | ALUMY_MINOR >= (ma) << 16 | (mi))

#define AL_VERSION1		__MS(ALUMY_MAJOR.ALUMY_MINOR.ALUMY_REV.ALUMY_BUILD)

#ifndef ALUMY_SUFFIX
#define AL_VERSION		AL_VERSION1
#else
#define AL_VERSION		AL_VERSION1"-"ALUMY_SUFFIX
#endif

typedef struct al_version {
    uint16_t major;
    uint16_t minor;
    uint16_t rev;
    uint16_t build;
    const char *suffix;
} al_version_t;

extern const char *al_get_version_s(void);
extern const al_version_t *al_get_version(void);

__END_DECLS

#endif
