#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/lrc.h"

__BEGIN_DECLS

uint8_t al_lrc(const void *data, size_t len)
{
	uint8_t lrc = 0;
	const uint8_t *p = (const uint8_t *)data;

	while (len--) {
		lrc += *p++;
	}

	return (~lrc) + 1;
}

__END_DECLS

