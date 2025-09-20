/**
 * @file proto.h
 * @brief Network protocol management framework
 * 
 * This file provides a framework for managing multiple network protocol versions
 * and implementations. It allows registration, selection, and switching between
 * different protocol handlers at runtime.
 */

#ifndef __AL_NET_PROTO_H
#define __AL_NET_PROTO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/list.h"

__BEGIN_DECLS

/**
 * Network protocol item structure
 * Represents a single protocol implementation with its version and handlers
 */
typedef struct al_net_proto_item {
    list_head_t link;               /* Linked list node for protocol chain */
    uint_t version;                 /* Protocol version identifier */

    const void * const opt;         /* Protocol operation callbacks */

    void * const arg;               /* Protocol-specific argument/context */
} al_net_proto_item_t;

/**
 * Network protocol manager structure
 * Manages a collection of protocol implementations
 */
typedef struct al_net_proto {
    list_head_t ls;                 /* Head of protocol items list */
    al_net_proto_item_t *curr;      /* Currently active protocol item */
} al_net_proto_t;

/**
 * Initialize network protocol manager
 * @param ctx Protocol manager context
 * @return 0 on success, negative error code on failure
 */
int_t al_net_proto_init(al_net_proto_t *ctx);

/**
 * Get protocol item by version
 * @param ctx Protocol manager context
 * @param version Protocol version to search for
 * @return Protocol item pointer if found, NULL otherwise
 */
al_net_proto_item_t *al_net_proto_get(al_net_proto_t *ctx, uint_t version);

/**
 * Register a new protocol implementation
 * @param ctx Protocol manager context
 * @param _new New protocol item to register
 * @return 0 on success, negative error code on failure
 */
int_t al_net_proto_register(al_net_proto_t *ctx, al_net_proto_item_t *_new);

/**
 * Set active protocol by version
 * @param ctx Protocol manager context
 * @param version Protocol version to activate
 * @return 0 on success, negative error code on failure
 */
int_t al_net_proto_set(al_net_proto_t *ctx, uint_t version);

__END_DECLS

#endif
