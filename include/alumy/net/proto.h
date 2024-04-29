#ifndef __AL_NET_PROTO_H
#define __AL_NET_PROTO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/list.h"

__BEGIN_DECLS

typedef struct al_net_proto_item {
    list_head_t link;
    uint_t version;

    const void * const opt;

    void * const arg;
} al_net_proto_item_t;

typedef struct al_net_proto {
    list_head_t ls;
    al_net_proto_item_t *curr;
} al_net_proto_t;

int_t al_net_proto_init(al_net_proto_t *ctx);

al_net_proto_item_t *al_net_proto_get(al_net_proto_t *ctx, uint_t version);

int_t al_net_proto_register(al_net_proto_t *ctx, al_net_proto_item_t *_new);

int_t al_net_proto_set(al_net_proto_t *ctx, uint_t version);

__END_DECLS

#endif

