/**
 * \file config-no-entropy.h
 *
 * \brief Minimal configuration of features that do not require an entropy source
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/*
 * Minimal configuration of features that do not require an entropy source
 * Distinguishing features:
 * - no entropy module
 * - no TLS protocol implementation available due to absence of an entropy
 *   source
 *
 * See README.txt for usage instructions.
 */

/* System support */
// #define MBEDTLS_HAVE_ASM
// #define MBEDTLS_HAVE_TIME
#define MBEDTLS_PLATFORM_MEMORY

/* mbed TLS feature support */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_MODE_CTR
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#define MBEDTLS_ECP_NIST_OPTIM
#define MBEDTLS_ECDSA_DETERMINISTIC
#define MBEDTLS_PK_RSA_ALT_SUPPORT
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21
#define MBEDTLS_SELF_TEST
#define MBEDTLS_VERSION_FEATURES

/* mbed TLS modules */
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CCM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ERROR_C
#define MBEDTLS_GCM_C
#define MBEDTLS_HMAC_DRBG_C
#define MBEDTLS_MD_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_RSA_C
/* The library does not currently support enabling SHA-224 without SHA-256.
 * A future version of the library will have this option disabled
 * by default. */
#define MBEDTLS_SHA224_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA384_C
#define MBEDTLS_SHA512_C
#define MBEDTLS_VERSION_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_CRL_PARSE_C
//#define MBEDTLS_CMAC_C

/* Miscellaneous options */
#define MBEDTLS_AES_FEWER_TABLES

