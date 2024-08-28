#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

char *strset(char *s, char c, size_t n)
{
    memset(s, c, n - 1);
    ((char *)s)[n - 1] = '\0';

    return s;
}

__END_DECLS

