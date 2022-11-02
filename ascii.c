#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS

const char al_hex_asc_tab[16] = "0123456789ABCDEF";

uint8_t al_hex2asc(uint8_t value)
{
	if (value < ARRAY_SIZE(al_hex_asc_tab)) {
		return al_hex_asc_tab[value];
	}

	return 0;
}

__END_DECLS

