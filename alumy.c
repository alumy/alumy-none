#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/time.h"

__BEGIN_DECLS

static uint32_t initialized = 0;

__static_inline__ int32_t __al_init(void)
{
	al_tick_init();

	return 0;
}

__static_inline__ int32_t __al_cleanup(void)
{
	return 0;
}

int32_t alumy_init(void)
{
	if (initialized++) {
		/* already initialized */
		return 1;
	}

	if (__al_init() != 0) {
		return -1;
	}

	return 0;
}

int32_t alumy_cleanup(void)
{
	if (!initialized) {
		/* not initialized */
		return -1;
	}

	if (--initialized) {
		/* multi initialze, need cleanup all */
		return 1;
	}

	if (__al_cleanup() != 0) {
		/* cleanup failed */
		return -1;
	}

	return 0;
}

__END_DECLS

