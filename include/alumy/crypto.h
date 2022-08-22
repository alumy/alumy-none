#ifndef __AL_CRYPTO_H
#define __AL_CRYPTO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/byteorder.h"

__BEGIN_DECLS

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

#endif  /* __AL_CRYPTO_H */

