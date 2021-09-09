#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS

static uint32_t initialized = 0;

int32_t alumy_init(void)
{
    if (initialized++) {
        return 0;
    }

    return 1;
}

int32_t alumy_cleanup(void)
{
    if (!initialized) {
        return -1;
    }

    if (--initialized) {
        return 1;
    }

    return 0;
}

__END_DECLS

