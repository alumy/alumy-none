#include <stdlib.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

void *al_os_malloc(size_t size)
{
	return malloc(size);
}

void al_os_free(void *p)
{
	free(p);
}

size_t al_os_get_free_heap_size(void)
{
	return 0;
}

size_t al_os_get_min_free_heap_size(void)
{
	return 0;
}

__END_DECLS

