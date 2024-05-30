#include <stdlib.h>
#include <time.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

const char *mkname(char *buf, size_t bufsz, size_t len)
{
	const char asc_tab[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	if ((len + 1) > bufsz) {
		return NULL;
	}

	srand(time(NULL));

	char *p = buf;
	char *p_end = buf + len;

	for (; p < p_end; ++p) {
		*p = asc_tab[rand() % ARRAY_SIZE(asc_tab)];
	}

	*p = 0;

	return buf;
}



__END_DECLS

