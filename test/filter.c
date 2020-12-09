#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/unity/unity.h"
#include "alumy/unity/unity_fixture.h"
#include "alumy/filter.h"

__BEGIN_DECLS

TEST_GROUP(filter);

TEST_SETUP(filter)
{

}

TEST_TEAR_DOWN(filter)
{

}

TEST(filter, kalman_succ)
{
}

TEST_GROUP_RUNNER(filter)
{
    RUN_TEST_CASE(filter, kalman_succ);
}

__END_DECLS

