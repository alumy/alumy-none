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

extern int32_t bsp_init(void);

static int example_suite_init(void)
{
	return 0;
}

static int example_suite_clean(void)
{
	return 0;
}

static void example_test(void)
{
	CU_ASSERT(1);
}

static void add_example_tests(void)
{
	CU_pSuite suite;

	suite = CU_add_suite("example", example_suite_init, example_suite_clean);
	CU_add_test(suite, "example", example_test);
}

static void add_tests(void)
{
	void (*add_test_tab[])(void) = {
		add_example_tests,
		add_mem_tests,
		add_string_tests,
        add_filter_tests,
        add_bitband_tests,
	};

	assert(CU_get_registry() != NULL);
	assert(!CU_is_test_running());

	for (int32_t i = 0; i < ARRAY_SIZE(add_test_tab); ++i) {
		if (add_test_tab[i] != NULL) {
			add_test_tab[i]();
		}
	}
}

int main(int argc, char *argv[])
{
    bsp_init();

	if (CU_initialize_registry()) {
		fprintf(stderr, "\nInitialization of Test Registry failed.");
		return -1;
	}

	add_tests();

    CU_set_output_filename("test");
    CU_list_tests_to_file();
    CU_automated_run_tests();

	CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}

__END_DECLS

