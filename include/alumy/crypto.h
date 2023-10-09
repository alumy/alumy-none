#ifndef __AL_CRYPTO_H
#define __AL_CRYPTO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/byteorder.h"

__BEGIN_DECLS

typedef uint8_t al_aes_128_key_t[16];
typedef uint8_t al_aes_128_iv_t[16];
typedef uint8_t al_aes_192_key_t[24];
typedef uint8_t al_aes_192_iv_t[24];
typedef uint8_t al_aes_256_key_t[32];
typedef uint8_t al_aes_256_iv_t[32];

ssize_t aes_cbc_enc(void *out, size_t outsz, const void *in, size_t len,
                    const void *key, size_t keylen,
                    const void *__iv, size_t __iv_len);

char *aes_cbc_enc_base64(const void *in, size_t len,
                         const void *key, size_t keylen,
                         const void *__iv, size_t __iv_len);

ssize_t aes_cbc_dec(void *out, size_t outsz, const void *in, size_t len,
                    const void *key, size_t keylen,
                    const void *__iv, size_t __iv_len,
                    bool check_pad);

ssize_t aes_cbc_dec_base64(void *out, size_t outsz, const char *b64,
                           const void *key, size_t keylen,
                           const void *__iv, size_t __iv_len,
                           bool check_pad);

ssize_t aes_128_ctr_enc(void *out, size_t outsz, const void *in, size_t len,
						const al_aes_128_key_t key, const al_aes_128_iv_t iv);

ssize_t aes_128_ctr_dec(void *out, size_t outsz, const void *in, size_t len,
						const al_aes_128_key_t key, const al_aes_128_iv_t iv);

#endif  /* __AL_CRYPTO_H */

