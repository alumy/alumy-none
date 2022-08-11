#ifndef __AL_CRYPTO_H
#define __AL_CRYPTO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/byteorder.h"

__BEGIN_DECLS

/*
 * Algorithm masks and types.
 */
#define CRYPTO_ALG_TYPE_MASK        0x000000ff
#define CRYPTO_ALG_TYPE_CIPHER      0x00000001
#define CRYPTO_ALG_TYPE_DIGEST      0x00000002
#define CRYPTO_ALG_TYPE_COMPRESS    0x00000004

/*
 * Transform masks and values (for crt_flags).
 */
#define CRYPTO_TFM_MODE_MASK        0x000000ff
#define CRYPTO_TFM_REQ_MASK     0x000fff00
#define CRYPTO_TFM_RES_MASK     0xfff00000

#define CRYPTO_TFM_MODE_ECB     0x00000001
#define CRYPTO_TFM_MODE_CBC     0x00000002
#define CRYPTO_TFM_MODE_CFB     0x00000004
#define CRYPTO_TFM_MODE_CTR     0x00000008

#define CRYPTO_TFM_REQ_WEAK_KEY     0x00000100
#define CRYPTO_TFM_RES_WEAK_KEY     0x00100000
#define CRYPTO_TFM_RES_BAD_KEY_LEN      0x00200000
#define CRYPTO_TFM_RES_BAD_KEY_SCHED    0x00400000
#define CRYPTO_TFM_RES_BAD_BLOCK_LEN    0x00800000
#define CRYPTO_TFM_RES_BAD_FLAGS    0x01000000

/*
 * Miscellaneous stuff.
 */
#define CRYPTO_UNSPEC           0
#define CRYPTO_MAX_ALG_NAME     64

struct aes_ctx {
    int key_length;
    uint32_t E[60];
    uint32_t D[60];
};

int aes_set_key(void *ctx_arg, const uint8_t *in_key,
                unsigned int key_len, uint32_t *flags);
void aes_encrypt(void *ctx_arg, uint8_t *out, const uint8_t *in);
void aes_decrypt(void *ctx_arg, uint8_t *out, const uint8_t *in);

__END_DECLS

#endif  /* __AL_CRYPTO_H */

