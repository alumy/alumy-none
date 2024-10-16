#ifndef __AL_CRYPTO_MD5
#define __AL_CRYPTO_MD5 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

typedef struct al_md5_ctx {
    uint32_t count[2];
    uint32_t state[4];
    uint8_t buffer[64];
} al_md5_ctx_t;

void al_md5_sign(al_md5_ctx_t *ctx,
                 void *output, const void *input, size_t len);

#endif
