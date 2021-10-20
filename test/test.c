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

static void do_initcalls(void)
{
    al_test_suite_initcall_t *init_ptr = &__test_suite_init_start;

    for (; init_ptr < &__test_suite_init_end; init_ptr++) {
        (*init_ptr)();
    }
}

static void run_all_test(void)
{
    do_initcalls();
}

int main(int argc, char *argv[])
{
    bsp_init();

    const char *__argv[] = {
        "alumy",
    };

    int32_t __argc = ARRAY_SIZE(__argv);

    return UnityMain(__argc, __argv, run_all_test);
}

__END_DECLS

