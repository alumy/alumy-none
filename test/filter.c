#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/cunit/CUnit.h"
#include "alumy/cunit/Automated.h"
#include "alumy/cunit/Basic.h"
#include "alumy.h"
#include "test.h"

__BEGIN_DECLS

static int filter_suite_init(void)
{
	return 0;
}

static int filter_suite_clean(void)
{
	return 0;
}

static void kalman_filter_succ_test(void)
{

}

void add_filter_tests(void)
{
	CU_pSuite suite;

	suite = CU_add_suite("filter", filter_suite_init, filter_suite_clean);

	CU_add_test(suite, "kalman_filter", kalman_filter_succ_test);
}

__END_DECLS

