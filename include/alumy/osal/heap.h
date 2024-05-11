#ifndef __AL_OSAL_HEAP_H
#define __AL_OSAL_HEAP_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

void *al_os_malloc(size_t size);

void al_os_free(void *p);

void *al_os_calloc(size_t nmemb, size_t size);

void *al_os_realloc(void *ptr, size_t size);

size_t al_os_get_free_heap_size(void);

size_t al_os_get_min_free_heap_size(void);

__END_DECLS

#endif

