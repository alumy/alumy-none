#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

size_t str_add_null(void *dst, size_t dstsz, const void *src, size_t len)
{
	/*lint -esym(550, len) */

	if (dstsz == 0) {
		return 0;
	}

	/* Reserve a byte for terminate */
	size_t l = min((dstsz - 1), len);
	/* Copy the data */
	memcpy(dst, src, l);
	/* Add terminal character */
	*((char *)dst + l) = '\0';

	return l;
}

__END_DECLS

