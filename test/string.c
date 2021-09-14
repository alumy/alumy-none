#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

static int string_suite_init(void)
{
	return 0;
}

static int string_suite_clean(void)
{
	return 0;
}

static void strlcpy_test(void)
{
	const char src[] = "0123456789";
	char dst[32];

	/* Enough buffer */
	CU_ASSERT((strlcpy(dst, src, sizeof(dst)) == strlen(src)) &&
			  (strcmp(dst, src) == 0));

	/* Just right */
	CU_ASSERT((strlcpy(dst, src, 11) == strlen(src)) &&
			  (strcmp(dst, src) == 0));

	/* One less */
	CU_ASSERT((strlcpy(dst, src, 10) == strlen(src)) &&
			  (strcmp(dst, "012345678") == 0));

	/* Only one */
	CU_ASSERT((strlcpy(dst, src, 1) == strlen(src)) &&
			  (strcmp(dst, "") == 0));

	/* No buffer */
	memset(dst, 0xAA, sizeof(dst));
	CU_ASSERT((strlcpy(dst, src, 0) == strlen(src)) &&
			  al_mem_is_filled(dst, 0xAA, sizeof(dst)));
}

static void str_add_null_test(void)
{
	const char src[] = "0123456789";
	char dst[128];

	CU_ASSERT((str_add_null(dst, sizeof(dst),
							src, strlen(src)) == strlen(src)) &&
			  (strcmp(dst, src) == 0));

	CU_ASSERT((str_add_null(dst, 11, src, strlen(src)) == strlen(src)) &&
			  (strcmp(dst, src) == 0));

	CU_ASSERT((str_add_null(dst, 8, src, strlen(src)) == 7) &&
			  (strcmp(dst, "0123456") == 0));

	CU_ASSERT((str_add_null(dst, 1, src, strlen(src)) == 0) &&
			  (strcmp(dst, "") == 0));

	memset(dst, 0xAA, sizeof(dst));
	CU_ASSERT((str_add_null(dst, 0, src, strlen(src)) == 0) &&
			  al_mem_is_filled(dst, 0xAA, sizeof(dst)));
}


static int32_t add_string_tests(void)
{
	CU_pSuite suite;

	suite = CU_add_suite("string", string_suite_init, string_suite_clean);

	CU_add_test(suite, "strlcpy", strlcpy_test);
	CU_add_test(suite, "str_add_null", str_add_null_test);

    return 0;
}

al_test_suite_init(add_string_tests);

__END_DECLS

