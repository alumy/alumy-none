#include "alumy/net/proto.h"

__BEGIN_DECLS

int_t al_net_proto_init(al_net_proto_t *ctx)
{
    INIT_LIST_HEAD(&ctx->ls);

    ctx->curr = NULL;

    return 0;
}

al_net_proto_item_t *al_net_proto_get(al_net_proto_t *ctx, uint_t version)
{
    list_head_t *pos, *n;

    list_for_each_safe(pos, n, &ctx->ls) {
        al_net_proto_item_t *item = list_entry(pos, al_net_proto_item_t, link);

        if (item->version == version) {
            return item;
        }
    }

    return NULL;
}

int_t al_net_proto_register(al_net_proto_t *ctx, al_net_proto_item_t *_new)
{
    if (al_net_proto_get(ctx, _new->version) != NULL) {
        set_errno(EEXIST);
        return -1;
    }

    list_add_tail(&_new->link, &ctx->ls);

    set_errno(0);
    return 1;
}

int_t al_net_proto_set(al_net_proto_t *ctx, uint_t version)
{
    al_net_proto_item_t *item = al_net_proto_get(ctx, version);

    if (item == NULL) {
        set_errno(ENOENT);
        return -1;
    }

    ctx->curr = item;

    set_errno(0);
    return 0;
}

__END_DECLS

