#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "alumy/mem.h"

__BEGIN_DECLS

bool al_mem_is_filled(const void *buf, uint_fast8_t c, size_t len)
{
	uintptr_t p = (uintptr_t)buf;

	if (len >= OP_T_THRES) {
		/**
		 * Alignment loop
		 */
		while ((p % OPSIZ) != 0) {
			if (*((uint8_t *)p) != c) {
				return false;
			}

			p += 1;
			len -= 1;
		}

		/**
		 * Now p is alignment to uint_fast32_t
		 */
		op_t cccc = (uint8_t)c;

		cccc |= cccc << 8;
		cccc |= cccc << 16;

		if (OPSIZ > 4) {		/*lint !e506 !e774 */
			/**
			 * Do the shift in two steps to avoid warning if long has 32
			 * bits.
			 */
			cccc |= (cccc << 16) << 16;

		}

		while (len >= OPSIZ) {
			if (*((op_t *)p) != cccc) {
				return false;
			}

			p += OPSIZ;
			len -= OPSIZ;
		}
	}

	while (len != 0) {
		if (*((uint8_t *)p) != c) {
			return false;
		}

		p += 1;
		len -= 1;
	}

	return true;
}

__END_DECLS

