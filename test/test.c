#include <setjmp.h>
#include <stdio.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/test.h"

__BEGIN_DECLS

static void run_all_test(void)
{
    RUN_TEST_GROUP(base64);

#if AL_TEST_FILTER
    RUN_TEST_GROUP(filter);
#endif
}

int32_t alumy_test(void)
{
    const char *argv[] = {
        "alumy",
        "-v",
    };

    int32_t argc = ARRAY_SIZE(argv);

    return UnityMain(argc, argv, run_all_test);
}

__END_DECLS

