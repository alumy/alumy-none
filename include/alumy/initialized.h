#ifndef __AL_INITIALIZED_H
#define __AL_INITIALIZED_H 1

#include "alumy/byteorder.h"
#include "alumy/byteswap.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#ifndef AL_INITIALIZED
#define AL_INITIALIZED(name)        uint32_t name = 0
#endif

__static_inline__ bool al_initialized_init(uint32_t *initialized)
{
    if ((*initialized)++) {
        return false;
    }

    return true;
}

__static_inline__ bool al_initialized_final(uint32_t *initialized)
{
    if (!(*initialized)) {
        return false;
    }

    if (--(*initialized)) {
        return false;
    }

    return true;
}

__END_DECLS

#endif

