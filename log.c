#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/log.h"
#include "alumy/time.h"

__BEGIN_DECLS

#define BIN_LINE_SIZE	16

static const char hex[] = "0123456789ABCDEF";

static int32_t logmask = 0xFF;

__weak void al_vlog(int32_t pri, const char *fmt, va_list ap)
{
    FILE *stream = stdout;

    if (pri == AL_LOG_EMERG || pri == AL_LOG_ERR ||
        pri == AL_LOG_WARN || pri == AL_LOG_CRIT ||
        pri == AL_LOG_ALERT) {
        stream = stderr;
    }

    fprintf(stream, "%s ", al_log_timestamp());
    vfprintf(stream, fmt, ap);
}

__weak const char *al_log_timestamp(void)
{
    static char str[16];
    al_tick_t tick;

    al_tick_get(&tick);

    snprintf(str, sizeof(str), "[%5ld.%03d]", (long)tick.tv_sec, tick.tv_msec);

    return str;
}

void al_log(int32_t pri, const char *file, int32_t line, const char *func,
			const char *fmt, ...)
{
	UNUSED(file);
	UNUSED(line);
	UNUSED(func);
	
	if (pri & ~(AL_LOG_PRIMASK)) {
		/* unknown prio mask */
		pri &= AL_LOG_PRIMASK;
	}

	if ((AL_LOG_MASK(AL_LOG_PRI(pri)) & logmask) == 0) {
		return;
	}

	va_list ap;

	va_start(ap, fmt);

    al_vlog(pri, fmt, ap);

	va_end(ap);
}

/**
 * @brief Format address as 00000000, the result exclude EOF
 *
 * @author jack (4/26/2018)
 *
 * @param buf
 * @param addr
 *
 * @return String length
 */
static size_t hex_addr_fmt(char buf[8], intptr_t addr)
{
	char *wp = buf;

	*wp++ = hex[addr >> 28 & 0x0F];
	*wp++ = hex[addr >> 24 & 0x0F];
	*wp++ = hex[addr >> 20 & 0x0F];
	*wp++ = hex[addr >> 16 & 0x0F];
	*wp++ = hex[addr >> 12 & 0x0F];
	*wp++ = hex[addr >> 8 & 0x0F];
	*wp++ = hex[addr >> 4 & 0x0F];
	*wp = hex[addr & 0x0F];

	return 8;
}

/**
 * @brief Format a line
 *  A line format:
 * 00000000: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F ;
 * 000000000000000000\n
 *
 * @author jack (4/27/2018)
 *
 * @param buf
 * @param data
 * @param len
 *
 * @return size_t
 */
static ssize_t hex_raw_fmt_line(char *buf, size_t bufsz, intptr_t addr,
								const void *data, size_t len)
{
    size_t line_size = 8 + 2 + 16 * 3 + 2 + 16 + 1;
    size_t i;

    if ((len > BIN_LINE_SIZE) || (bufsz < line_size)) {
        return -1;
    }

	char *_buf = buf;

	/**
	 * Add address and other fixed characters
	 */
	hex_addr_fmt(_buf, addr);
	_buf[8] = ':';
	_buf[9] = ' ';
	_buf[58] = ';';
	_buf[59] = ' ';

	char *h_wp = &_buf[10];
	char *c_wp = &_buf[60];

	const uint8_t *rp = (const uint8_t *)data;

	for (i = 0; i < len; ++i) {
        *h_wp++ = hex[(*rp >> 4) & 0x0F];
        *h_wp++ = hex[*rp & 0x0F];
        *h_wp++ = ' ';

#if defined (__GNUC__)
        *c_wp++ = isprint(*rp) ? (char)*rp : '.';
#elif defined (__CC_ARM)
        *c_wp++ = ((*rp <= 0x7F) && isprint(*rp)) ? *rp : '.';
#else
        *c_wp++ = ((*rp <= 0x7F) && isprint(*rp)) ? *rp : '.';
#endif

        ++rp;
    }

	for (i = len; i < BIN_LINE_SIZE; ++i) {
		*h_wp++ = ' ';
		*h_wp++ = ' ';
		*h_wp++ = ' ';
		*c_wp++ = ' ';
	}

    _buf[76] = 0;

	return (ssize_t)line_size - 1;
}

void al_log_bin(int32_t pri,
				const char *file, int32_t line, const char *func,
				const void *data, size_t len)
{
    char buf[80];

    int32_t nline = len >> 4;
    int32_t remain = len & 0x0F;

    intptr_t addr = 0;
    const uint8_t *rp = (const uint8_t *)data;

    while (nline--) {
        hex_raw_fmt_line(buf, sizeof(buf),
                         addr, rp + addr, BIN_LINE_SIZE);
        addr += BIN_LINE_SIZE;

        al_log(pri, file, line, func, "%s\r\n", buf);
    }

    if (remain > 0) {
        hex_raw_fmt_line(buf, sizeof(buf),
                         addr, rp + addr, (size_t)remain);

        al_log(pri, file, line, func, "%s\r\n", buf);
    }
}

int32_t al_log_set_mask(int32_t mask)
{
	int32_t omask = logmask;

	if (mask != 0) {
		logmask = mask;
	}

	return omask;
}

__END_DECLS
