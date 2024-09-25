#include "durian.h"

__BEGIN_DECLS

__asm(".global __use_no_heap_region\n\t");

void *malloc(size_t size)
{
    return al_os_malloc(size);
}

void free(void *p)
{
    al_os_free(p);
}

void *realloc(void *p, size_t want)
{
    return al_os_realloc(p, want);
}

void *calloc(size_t nmemb, size_t size)
{
    return al_os_calloc(nmemb, size);
}

__END_DECLS
