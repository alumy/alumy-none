#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/list.h"
#include "alumy/pool.h"
#include "alumy/errno.h"

__BEGIN_DECLS


void al_create_pool(al_pool_t * po,
                    void *buf, size_t size, size_t nmemb, off_t offset)
{
    uint8_t *p;
    list_head_t *link;

    po->nr_free = nmemb;
    po->nr_total = nmemb;
    po->nr_used = 0;
    INIT_LIST_HEAD(&po->free);

    p = (uint8_t *)buf;

    while (nmemb--) {
        link = (list_head_t *)(p + offset);
        list_add_tail(link, &po->free);
        p += size;
    }
}

void *al_get_from_pool(al_pool_t *po, int32_t offset)
{
    list_head_t *link;

    if (list_empty(&po->free)) {
        return NULL;
    }

    link = po->free.next;
    list_del(link);
    --po->nr_free;
    ++po->nr_used;

    return ((uint8_t *)link - offset);
}

void al_put_into_pool(al_pool_t *po, void *ent, int32_t offset)
{
    list_head_t *link;

    link = (list_head_t *)((uintptr_t)ent + offset);
    list_add_tail(link, &po->free);
    --po->nr_used;
    ++po->nr_free;
}

__END_DECLS

