#include <errno.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

__weak int *__al_errno(void)
{
    return (int *)&(errno);
}

void set_errno(int e)
{
    *__al_errno() = e;
}

__END_DECLS

