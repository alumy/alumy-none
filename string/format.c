#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/log.h"
#include "alumy/config.h"

__BEGIN_DECLS

char *proc_gen_format(const char *name, int more, FILE *fh, ...)
{
	char buf[512], format[512] = "";
	char *title, *head, *hdr;
	va_list ap;

	if (!fgets(buf, (sizeof buf) - 1, fh))
		return NULL;

	strcat(buf, " ");

	va_start(ap, fh);
	title = va_arg(ap, char *);

	for (hdr = buf; hdr;) {
		while (isspace((int)*hdr) || *hdr == '|')
			hdr++;

		head = hdr;
		hdr = strpbrk(hdr, "| \t\n");
		if (hdr)
			*hdr++ = 0;

		if (!strcmp(title, head)) {
			strcat(format, va_arg(ap, char *));
			title = va_arg(ap, char *);
			if (!title || !head)
				break;
		} else {
			strcat(format, "%*s");  /* XXX */
		}
		strcat(format, " ");
	}
	va_end(ap);

	if (!more && title) {
		AL_ERROR(AL_LOG,
				 "warning: %s does not contain required field %s",
				 name, title);
		return NULL;
	}

	return strdup(format);
}

__END_DECLS

