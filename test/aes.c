#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

#define AES_KEY		"3KKso3iyakmzl&ii"
#define AES_IV		"lajpnbtubz6&V8fS"

static const char proverb[] =
	"\"I wonder\", he said to himself, \"what's in a book while it's closed.  "
	"Oh, I know it's full of letters printed on paper, "
	"but all the same, something must be happening, "
	"because as soon as I open it, there's a whole story with people "
	"I don't know yet and all kinds of adventures and battles.\"";

static const uint8_t proverb_enc[] = {
	0xA3, 0xCC, 0x5B, 0x56, 0xC2, 0x1B, 0x98, 0x73,
	0xD6, 0x22, 0x2B, 0x90, 0xEA, 0x6A, 0xBB, 0xA9,
	0xCB, 0xA7, 0x35, 0x57, 0x17, 0x6E, 0x75, 0x93,
	0xFB, 0xA3, 0xA4, 0x9E, 0x47, 0x09, 0x19, 0x58,
	0xA2, 0x14, 0xF3, 0x4B, 0x70, 0x46, 0x69, 0x56,
	0xD3, 0x65, 0xC8, 0xD4, 0xA8, 0x06, 0x67, 0x6E,
	0xF3, 0xF5, 0x3A, 0x2C, 0x87, 0x39, 0x19, 0x25,
	0xD3, 0x89, 0x61, 0xDD, 0x9C, 0x05, 0x09, 0xE6,
	0x0C, 0x20, 0x87, 0xB2, 0xD5, 0x5E, 0x6F, 0x86,
	0xE8, 0x59, 0x6F, 0x02, 0x40, 0x40, 0xC7, 0x8E,
	0xE7, 0xD0, 0xE8, 0x22, 0x87, 0xEA, 0x35, 0x6F,
	0x77, 0x1F, 0xFA, 0x65, 0x5B, 0x3E, 0xE2, 0x77,
	0x37, 0x97, 0x31, 0x4D, 0x25, 0x4B, 0x42, 0x4F,
	0xC8, 0x12, 0xEC, 0xBE, 0x28, 0x6D, 0xE9, 0xC1,
	0xE2, 0x0B, 0xEC, 0xD3, 0xA5, 0xD6, 0x65, 0x22,
	0x03, 0xB5, 0xB9, 0x19, 0xCC, 0xAE, 0x42, 0x0E,
	0x8D, 0x54, 0x17, 0x0C, 0x2C, 0xE2, 0xC9, 0xBD,
	0xEA, 0x3F, 0xF3, 0xDF, 0x23, 0x55, 0x88, 0x1D,
	0xF0, 0x48, 0xA4, 0xE3, 0x69, 0x85, 0x7F, 0xFB,
	0xA1, 0xA2, 0xD7, 0x6D, 0xC9, 0xD2, 0xB8, 0x55,
	0xED, 0x5C, 0xF6, 0x50, 0x4C, 0x35, 0x7F, 0x5D,
	0x4B, 0x49, 0x2D, 0x2B, 0x83, 0x18, 0x95, 0x1E,
	0xDE, 0x74, 0x59, 0x2C, 0xC7, 0x5E, 0x23, 0x36,
	0x0F, 0xAD, 0xFA, 0x21, 0x52, 0xFB, 0x88, 0x5B,
	0x47, 0x3A, 0xA0, 0x6E, 0xD1, 0x3A, 0x24, 0xC9,
	0x4C, 0x9A, 0xDE, 0x76, 0xBB, 0x6B, 0x39, 0x3D,
	0xC8, 0x06, 0xBA, 0x6F, 0x37, 0x35, 0x43, 0x37,
	0xEA, 0x77, 0x9F, 0xA8, 0xAF, 0xC8, 0xA4, 0x2C,
	0x4B, 0x6A, 0x39, 0x13, 0x9E, 0xD3, 0x64, 0x9A,
	0xE4, 0x35, 0xC8, 0x42, 0x77, 0xAC, 0xCE, 0xFB,
	0x24, 0x91, 0xA9, 0x14, 0x95, 0x76, 0xEE, 0xE2,
	0xF1, 0x2E, 0x0C, 0xBA, 0x3B, 0x15, 0xE9, 0x79,
	0x48, 0x31, 0x80, 0xAE, 0x10, 0xAB, 0x12, 0x8A,
	0xAF, 0xEF, 0x13, 0x52, 0x2A, 0x2C, 0x7D, 0x55,
	0xFF, 0x35, 0x73, 0xDF, 0xF5, 0xBC, 0x32, 0xC0,
	0x2C, 0x3C, 0xA8, 0xA6, 0xC2, 0x16, 0xEE, 0xF8,
	0x5C,
};

TEST_GROUP(aes);

TEST_SETUP(aes)
{

}

TEST_TEAR_DOWN(aes)
{

}

TEST(aes, aes_128_ctr)
{
al_aes_128_key_t key = AES_KEY;
al_aes_128_key_t iv = AES_IV;
uint8_t *enc, *dec;
ssize_t enc_len, dec_len;
const size_t len = sizeof(proverb) - 1;;
const size_t size = 2048;

BUILD_BUG_ON(sizeof(proverb_enc) != sizeof(proverb) - 1);

enc = al_os_malloc(size);
TEST_ASSERT(enc != NULL);

dec = al_os_malloc(size);
TEST_ASSERT(dec != NULL);

enc_len = aes_128_ctr_enc(enc, size, proverb, len, key, iv);
TEST_ASSERT(enc_len == len);

TEST_ASSERT(memcmp(enc, proverb_enc, enc_len) == 0);

dec_len = aes_128_ctr_dec(dec, size, enc, enc_len, key, iv);
TEST_ASSERT(dec_len == len);

TEST_ASSERT(memcmp(dec, proverb, len) == 0);

al_os_free(enc);
al_os_free(dec);
}

TEST_GROUP_RUNNER(aes)
{
    RUN_TEST_CASE(aes, aes_128_ctr);
}

static int32_t __add_aes_tests(void)
{
    RUN_TEST_GROUP(aes);
    return 0;
}

al_test_suite_init(__add_aes_tests);

