#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS

void set_errno(int e)
{
    errno = e;
}

__END_DECLS

