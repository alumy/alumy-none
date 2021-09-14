#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "test.h"
#include "portal.h"

__BEGIN_DECLS

extern al_test_suite_initcall_t __test_suite_init_start;
extern al_test_suite_initcall_t __test_suite_init_end;

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

static int32_t add_example_tests(void)
{
    CU_pSuite suite;

    suite = CU_add_suite("example", example_suite_init, example_suite_clean);
    if (suite == NULL) {
        return -1;
    }

    if (CU_add_test(suite, "example", example_test) == NULL) {
        return -1;
    }

    return 0;
}

al_test_suite_init(add_example_tests);

static void do_initcalls(void)
{
    al_test_suite_initcall_t *init_ptr = &__test_suite_init_start;

    for (; init_ptr < &__test_suite_init_end; init_ptr++) {
        (*init_ptr)();
    }
}

int main(int argc, char *argv[])
{
    if (CU_initialize_registry()) {
        fprintf(stderr, "\nInitialization of Test Registry failed.");
        return -1;
    }

    do_initcalls();

    CU_set_output_filename("test");
    CU_list_tests_to_file();
    CU_automated_run_tests();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

__END_DECLS

