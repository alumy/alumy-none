#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

char *strrmchr(char *s, char c)
{
	int_t i = 0;
	int_t j = 0;

	while (s[i] != '\0') {
		if (s[i] != c) {
			s[j++] = s[i];
		}

		i++;
	}

	s[j] = '\0';

	return s;
}

__END_DECLS

