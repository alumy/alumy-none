/**
 * @file crypto.h
 * @brief Cryptographic functions and utilities
 * 
 * This header provides cryptographic functionality including AES encryption
 * and decryption operations in various modes (CBC, CTR) with support for
 * different key sizes and encoding formats.
 */

#ifndef __AL_CRYPTO_H
#define __AL_CRYPTO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/byteorder.h"
#include "alumy/crypto/md5.h"

__BEGIN_DECLS

/** @brief AES-128 key type (16 bytes) */
typedef uint8_t al_aes_128_key_t[16];

/** @brief AES-128 initialization vector type (16 bytes) */
typedef uint8_t al_aes_128_iv_t[16];

/** @brief AES-192 key type (24 bytes) */
typedef uint8_t al_aes_192_key_t[24];

/** @brief AES-192 initialization vector type (24 bytes) */
typedef uint8_t al_aes_192_iv_t[24];

/** @brief AES-256 key type (32 bytes) */
typedef uint8_t al_aes_256_key_t[32];

/** @brief AES-256 initialization vector type (32 bytes) */
typedef uint8_t al_aes_256_iv_t[32];

/**
 * @brief AES CBC mode encryption
 * 
 * @param out Output buffer for encrypted data
 * @param outsz Size of output buffer
 * @param in Input data to encrypt
 * @param len Length of input data
 * @param key Encryption key
 * @param keylen Length of encryption key
 * @param __iv Initialization vector
 * @param __iv_len Length of initialization vector
 * @return Number of bytes written to output buffer, or negative on error
 */
ssize_t aes_cbc_enc(void *out, size_t outsz, const void *in, size_t len,
                    const void *key, size_t keylen,
                    const void *__iv, size_t __iv_len);

/**
 * @brief AES CBC mode encryption with Base64 encoding
 * 
 * @param in Input data to encrypt
 * @param len Length of input data
 * @param key Encryption key
 * @param keylen Length of encryption key
 * @param __iv Initialization vector
 * @param __iv_len Length of initialization vector
 * @return Base64 encoded encrypted string, or NULL on error (caller must free)
 */
char *aes_cbc_enc_base64(const void *in, size_t len,
                         const void *key, size_t keylen,
                         const void *__iv, size_t __iv_len);

/**
 * @brief AES CBC mode decryption
 * 
 * @param out Output buffer for decrypted data
 * @param outsz Size of output buffer
 * @param in Encrypted input data
 * @param len Length of encrypted data
 * @param key Decryption key
 * @param keylen Length of decryption key
 * @param __iv Initialization vector
 * @param __iv_len Length of initialization vector
 * @param check_pad Whether to check and remove PKCS#7 padding
 * @return Number of bytes written to output buffer, or negative on error
 */
ssize_t aes_cbc_dec(void *out, size_t outsz, const void *in, size_t len,
                    const void *key, size_t keylen,
                    const void *__iv, size_t __iv_len,
                    bool check_pad);

/**
 * @brief AES CBC mode decryption from Base64 encoded data
 * 
 * @param out Output buffer for decrypted data
 * @param outsz Size of output buffer
 * @param b64 Base64 encoded encrypted data
 * @param key Decryption key
 * @param keylen Length of decryption key
 * @param __iv Initialization vector
 * @param __iv_len Length of initialization vector
 * @param check_pad Whether to check and remove PKCS#7 padding
 * @return Number of bytes written to output buffer, or negative on error
 */
ssize_t aes_cbc_dec_base64(void *out, size_t outsz, const char *b64,
                           const void *key, size_t keylen,
                           const void *__iv, size_t __iv_len,
                           bool check_pad);

/**
 * @brief AES-128 CTR mode encryption
 * 
 * @param out Output buffer for encrypted data
 * @param outsz Size of output buffer
 * @param in Input data to encrypt
 * @param len Length of input data
 * @param key AES-128 encryption key
 * @param iv Initialization vector/counter
 * @return Number of bytes written to output buffer, or negative on error
 */
ssize_t aes_128_ctr_enc(void *out, size_t outsz, const void *in, size_t len,
						const al_aes_128_key_t key, const al_aes_128_iv_t iv);

/**
 * @brief AES-128 CTR mode decryption
 * 
 * @param out Output buffer for decrypted data
 * @param outsz Size of output buffer
 * @param in Encrypted input data
 * @param len Length of encrypted data
 * @param key AES-128 decryption key
 * @param iv Initialization vector/counter
 * @return Number of bytes written to output buffer, or negative on error
 */
ssize_t aes_128_ctr_dec(void *out, size_t outsz, const void *in, size_t len,
						const al_aes_128_key_t key, const al_aes_128_iv_t iv);

/**
 * @brief AES-128 CTR mode in-place encryption
 * 
 * @param data Data buffer to encrypt in-place
 * @param len Length of data
 * @param key AES-128 encryption key
 * @param iv Initialization vector/counter
 */
void al_aes128_ctr_encrypt(void *data, size_t len,
                           const al_aes_128_key_t key,
                           const al_aes_128_iv_t iv);

/**
 * @brief AES-128 CTR mode in-place decryption
 * 
 * @param data Data buffer to decrypt in-place
 * @param len Length of data
 * @param key AES-128 decryption key
 * @param iv Initialization vector/counter
 */
void al_aes128_ctr_decrypt(void *data, size_t len,
                           const al_aes_128_key_t key,
                           const al_aes_128_iv_t iv);

__END_DECLS

#endif  /* __AL_CRYPTO_H */
