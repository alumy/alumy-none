#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/mem.h"
#include "alumy/log.h"
#include "alumy/bug.h"
#include "alumy/errno.h"
#include "alumy/base64.h"
#include "alumy/check.h"
#include "mbedtls/aes.h"

__BEGIN_DECLS

ssize_t aes_cbc_enc(void *out, size_t outsz, const void *in, size_t len,
                    const void *key, size_t keylen,
                    const void *__iv, size_t __iv_len)
{
    int32_t ret;
    ssize_t rv;
    size_t padlen = AL_IS_ALIGNED(len, 16) ? 16 : AL_ALIGN(len, 16) - len;
    size_t outlen = len + padlen;

    AL_CHECK_RET((keylen == 16) || (keylen == 24) || (keylen == 32),
                 EINVAL, -1);

    AL_CHECK_RET(__iv_len == 16, EINVAL, -1);

    AL_CHECK_RET(outlen <= outsz, ENOBUFS, -1);

    uint8_t *in_pad = (uint8_t *)malloc(outlen);
    if (in_pad == NULL) {
        return -ENOMEM;
    }

    memcpy(in_pad, in, len);

    for (intptr_t i = len; i < outlen; ++i) {
        in_pad[i] = padlen;
    }

    unsigned char iv[16] = { 0 };
    mbedtls_aes_context aes_ctx;

    memcpy(iv, __iv, min(sizeof(iv), __iv_len));

    mbedtls_aes_init(&aes_ctx);

    do {
        rv = -EPERM;
        ret = mbedtls_aes_setkey_enc(&aes_ctx, (unsigned char *)key,
                                     keylen * CHAR_BIT);
        if (ret != 0) {
            AL_ERROR(AL_LOG_CRYPTO,
                     "mbedtls_aes_setkey_enc failed, ret = %"PRId32, ret);
            break;
        }

        ret = mbedtls_aes_crypt_cbc(&aes_ctx, MBEDTLS_AES_ENCRYPT,
                                    outlen, iv, in_pad, out);
        if (ret != 0) {
            AL_ERROR(AL_LOG_CRYPTO,
                     "mbedtls_aes_crypt_cbc failed, mode = %d, ret = %"PRId32,
                     MBEDTLS_AES_ENCRYPT, ret);
            break;
        }

        rv = outlen;
    } while (0);

    mbedtls_aes_free(&aes_ctx);
    free(in_pad);

    return rv;
}

char *aes_cbc_enc_base64(const void *in, size_t len,
                         const void *key, size_t keylen,
                         const void *__iv, size_t __iv_len)
{
    size_t aes_bufsz = AL_ALIGN(len, 16) + 16;

    uint8_t *aesbuf = (uint8_t *)malloc(aes_bufsz);
    if (aesbuf == NULL) {
        return NULL;
    }

    char *b64 = (char *)malloc(Base64encode_len(aes_bufsz));
    if (b64 == NULL) {
        free(aesbuf);
        return NULL;
    }

    ssize_t aes_len = aes_cbc_enc(aesbuf, aes_bufsz, in, len,
                                  key, keylen, __iv, __iv_len);
    if (aes_len <= 0) {
        free(aesbuf);
        free(b64);
        return NULL;
    }

    Base64encode(b64, (const char *)aesbuf, aes_len);

    free(aesbuf);

    return b64;
}

ssize_t aes_cbc_dec(void *out, size_t outsz, const void *in, size_t len,
                    const void *key, size_t keylen,
                    const void *__iv, size_t __iv_len,
                    bool check_pad)
{
    int32_t ret;
    ssize_t rv;

    AL_CHECK_RET((keylen == 16) || (keylen == 24) || (keylen == 32),
                 EINVAL, -1);

    AL_CHECK_RET(__iv_len == 16, EINVAL, -1);

    AL_CHECK_RET(len <= outsz, ENOBUFS, -1);

    unsigned char iv[16] = { 0 };
    mbedtls_aes_context aes_ctx;

    memcpy(iv, __iv, min(sizeof(iv), __iv_len));

    mbedtls_aes_init(&aes_ctx);

    do {
        rv = -EPERM;
        ret = mbedtls_aes_setkey_dec(&aes_ctx, (unsigned char *)key,
                                     keylen * CHAR_BIT);
        if (ret != 0) {
            AL_ERROR(AL_LOG_CRYPTO,
                     "mbedtls_aes_setkey_dec failed, ret = %"PRId32, ret);
            break;
        }

        ret = mbedtls_aes_crypt_cbc(&aes_ctx, MBEDTLS_AES_DECRYPT,
                                    len, iv, in, out);
        if (ret != 0) {
            AL_ERROR(AL_LOG_CRYPTO,
                     "mbedtls_aes_crypt_cbc failed, mode = %d, ret = %"PRId32,
                     MBEDTLS_AES_ENCRYPT, ret);
            break;
        }

        if (check_pad) {
            const uint8_t *__out = (const uint8_t *)out;
            size_t pad = __out[len - 1];

            for (intptr_t i = 0, p = len - 1; i < pad; ++i, --p) {
                if (__out[p] != pad) {
                    AL_ERROR(AL_LOG_CRYPTO,
                             "%s, pad check failed, pad = %#x, __out[%d] = %#x",
                             __func__, pad, p, __out[p]);
                    break;
                }
            }

            rv = len - pad;
        } else {
            rv = len;
        }


    } while (0);

    mbedtls_aes_free(&aes_ctx);

    return rv;
}

ssize_t aes_cbc_dec_base64(void *out, size_t outsz, const char *b64,
                           const void *key, size_t keylen,
                           const void *__iv, size_t __iv_len,
                           bool check_pad)
{
    size_t aes_bufsz = Base64decode_len(b64);
    ssize_t rv;

    uint8_t *aesbuf = (uint8_t *)malloc(aes_bufsz);
    if (aesbuf == NULL) {
        return -ENOMEM;
    }

    size_t aes_len = Base64decode((char *)aesbuf, b64);

    AL_ASSERT(AL_IS_ALIGNED(aes_len, 16));

    if (!AL_IS_ALIGNED(aes_len, 16)) {
        free(aesbuf);
        return -EPERM;
    }

    rv = aes_cbc_dec(out, outsz, aesbuf, aes_len, key, keylen,
                     __iv, __iv_len, check_pad);

    free(aesbuf);

    return rv;
}

__END_DECLS

