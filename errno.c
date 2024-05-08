#include <errno.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

__weak void set_errno(int e)
{
    errno = e;
}

__weak int *__al_errno(void)
{
    return (int *)&(errno);
}

__END_DECLS

