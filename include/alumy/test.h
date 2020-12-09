#ifndef __AL_TEST_H
#define __AL_TEST_H

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/unity/unity.h"
#include "alumy/unity/unity_fixture.h"

__BEGIN_DECLS

#define AL_TEST_FILTER      0

#if 0
#define RUN_TEST(func, line)		do {	\
	Unity.CurrentTestName = #func; 			\
	Unity.CurrentTestLineNumber = line;		\
	Unity.NumberOfTests++;					\
	if (TEST_PROTECT())						\
	{										\
		setUp();							\
		TestFunc();							\
	}										\
	if (TEST_PROTECT())						\
	{										\
		tearDown();							\
	}										\
	UnityConcludeTest();					\
} while(0)
#endif

int32_t alumy_test(void);

__END_DECLS

#endif
