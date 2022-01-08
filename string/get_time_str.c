#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

const char *gen_time_str(time_t t, char *tmstr, size_t size)
{
    struct tm tm;

    localtime_r(& t, &tm);

    strftime(tmstr, size, "%F %T", &tm);

    return tmstr;
}


__END_DECLS

