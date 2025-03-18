#include <stdio.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"
#include "alumy/time.h"
#include "alumy/osal.h"
#include "alumy/cJSON.h"
#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
#include "mbedtls/platform.h"
#include "tinyprintf.h"

__BEGIN_DECLS

static uint32_t initialized = 0;

static void *__mbedtls_calloc(size_t n, size_t size)
{
	return al_os_malloc(n * size);
}

static void __mbedtls_free(void *p)
{
	al_os_free(p);
}

static void __putc(void *p, char c)
{
    al_putc(c);
}

__static_inline__ int32_t __al_init(void)
{
	cJSON_Hooks cjson_hooks = {
		.malloc_fn = al_os_malloc,
		.free_fn = al_os_free,
	};

    init_printf(NULL, __putc);

	al_tick_init();

	mbedtls_platform_set_calloc_free(__mbedtls_calloc, __mbedtls_free);

    cJSON_InitHooks(&cjson_hooks);

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

