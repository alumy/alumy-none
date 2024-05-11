#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

void *al_os_malloc(size_t size)
{
	return pvPortMalloc(size);
}

void al_os_free(void *p)
{
	vPortFree(p);
}

void *al_os_calloc(size_t nmemb, size_t size)
{
    return pvPortCalloc(nmemb, size);
}

void *al_os_realloc(void *ptr, size_t size)
{
    return pvPortRealloc(ptr, size);
}

size_t al_os_get_free_heap_size(void)
{
	return xPortGetFreeHeapSize();
}

size_t al_os_get_min_free_heap_size(void)
{
	return xPortGetMinimumEverFreeHeapSize();
}

__END_DECLS

