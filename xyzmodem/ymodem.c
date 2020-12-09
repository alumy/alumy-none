#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/base.h"
#include "alumy/types.h"
#include "alumy/byteswap.h"
#include "alumy/xyzmodem/ymodem.h"
#include "alumy/ascii.h"
#include "alumy/mem.h"
#include "alumy/log.h"
#include "alumy/errno.h"
#include "alumy/bug.h"

__BEGIN_DECLS

#define YMODEM_HEADER_SIZE      3
#define YMODEM_END_SIZE         2

#define YMODEM_PACKET_SIZE_128      (128)
#define YMODEM_PACKET_SIZE_1K       (1024)

#define YMODEM_TOTAL_LEN(pack_size)     \
    ((pack_size) + YMODEM_HEADER_SIZE + YMODEM_END_SIZE)

#define YMODEM_HEADER       0
#define YMODEM_SEQ          1
#define YMODEM_SEQ_COMP     2
#define YMODEM_CRC(pack_size)       (YMODEM_HEADER_SIZE + (pack_size))

enum {
    YMODEM_STATUS_IDLE,
    YMODEM_STATUS_RECV_HEADER,
    YMODEM_STATUS_RECV_DATA,
    YMODEM_STATUS_RECV_EOT_CONFIRM,
    YMODEM_STATUS_RECV_FINISH,
    YMODEM_STATUS_RECV_ERR,
    YMODEM_STATUS_RECV_TERM,
};

enum {
    YMODEM_RECV_STATUS_SOH,
    YMODEM_RECV_STATUS_DATA,
};

static uint16_t ymodem_crc16(const void *data, uint32_t len)
{
    const uint8_t *p = (const uint8_t *)data;
    uint16_t crc = 0;
    int i;

    while (len--) {
        crc = crc ^ *p++ << 8;

        for (i = 0; i < 8; i++) {
            if (crc & 0x8000) {
                crc = crc << 1 ^ 0x1021;
            } else {
                crc = crc << 1;
            }
        }
    }

    return crc;
}

static void ymodem_recv_status_reset(al_ymodem_t *ym)
{
    ym->recv_status = YMODEM_RECV_STATUS_SOH;
}

static ssize_t ymodem_recv_pkg(al_ymodem_t *ym)
{
    switch (ym->recv_status) {
        case YMODEM_RECV_STATUS_SOH:
        {
            ym->recv_wp = 0;

            int32_t c = ym->opt->getc();
            switch (c) {
                case EOF:
                    break;

                case SOH:
                    ym->packet_size = 128;
                    ym->recv_status = YMODEM_RECV_STATUS_DATA;
                    ym->recv_buf[ym->recv_wp++] = c;
                    break;

                case STX:
                    ym->packet_size = 1024;
                    ym->recv_status = YMODEM_RECV_STATUS_DATA;
                    ym->recv_buf[ym->recv_wp++] = c;
                    break;

                case ACK:
                case NAK:
                case EOT:
                case CAN:
                    ym->recv_buf[ym->recv_wp++] = c;
                    ym->recv_status = YMODEM_RECV_STATUS_SOH;
                    return 1;

                default:
                    return -1;
            }

            break;
        }

        case YMODEM_RECV_STATUS_DATA:
        {
            size_t total_len;
            size_t len;
            ssize_t recv_len;

            total_len = ym->packet_size + YMODEM_HEADER_SIZE + YMODEM_END_SIZE;
            len = min(ym->recv_bufsz, total_len) - ym->recv_wp;

            recv_len = ym->opt->recv(&ym->recv_buf[ym->recv_wp], len);

            if (recv_len > 0) {
                ym->recv_wp += recv_len;

                if (ym->recv_wp >= total_len) {
                    ym->recv_status = YMODEM_RECV_STATUS_SOH;
                    return ym->recv_wp;
                }
            }

            break;
        }

        default:
            break;
    }

    return 0;
}

static int32_t ymodem_check_pkg(const void *__data, size_t len, int32_t __seq)
{
    const uint8_t *data = (const uint8_t *)__data;

    uint8_t header = data[YMODEM_HEADER];
    uint8_t seq = data[YMODEM_SEQ];
    uint8_t seq_comp = data[YMODEM_SEQ_COMP];
    uint32_t packet_size;
    uint16_t pkg_crc;

    if ((header == ACK) || (header == EOT) ||
        (header == NAK) || (header == CAN)) {
        return header;
    }

    if ((header != SOH) && (header != STX)) {
        return -1;
    }

    if ((header == SOH) && (len != YMODEM_TOTAL_LEN(YMODEM_PACKET_SIZE_128))) {
        return -1;
    }

    if ((header == STX) && (len != YMODEM_TOTAL_LEN(YMODEM_PACKET_SIZE_1K))) {
        return -1;
    }

    if ((seq | seq_comp) != 0xFF) {
        return -1;
    }

    if (seq != __seq) {
        return -1;
    }

    if (header == SOH) {
        packet_size = YMODEM_PACKET_SIZE_128;
    } else {
        packet_size = YMODEM_PACKET_SIZE_1K;
    }

    uint16_t crc = ymodem_crc16(data + YMODEM_HEADER_SIZE, packet_size);

    pkg_crc = al_split_read_two(&data[YMODEM_CRC(packet_size)], false);

    if (crc != pkg_crc) {
        return -1;
    }

    return 0;
}

int32_t al_ymodem_init(al_ymodem_t *ym,
                       uint8_t *recv_buf, size_t recv_bufsz, time_t timeout,
                       al_ymodem_opt_t *opt, al_ymodem_callback_t *cb)
{
    memset(ym, 0, sizeof(al_ymodem_t));

    BUG_ON(cb == NULL);
    BUG_ON(opt == NULL);
    BUG_ON(cb->recv_header == NULL);
    BUG_ON(cb->recv_packet == NULL);
    BUG_ON(cb->recv_finish == NULL);
    BUG_ON(opt->putc == NULL);
    BUG_ON(opt->getc == NULL);
    BUG_ON(opt->recv == NULL);
    BUG_ON(opt->uptime == NULL);

    ym->recv_buf = recv_buf;
    ym->recv_bufsz = recv_bufsz;
    ym->timeout = timeout;
    ym->opt = opt;
    ym->callback = cb;
    ym->session = false;

    return 0;
}

static int32_t al_ymodem_header_parse(al_ymodem_t *ym,
                                      const void *__data, size_t len,
                                      char **filename, size_t *filesize)
{
    const uint8_t *data = (const uint8_t *)__data;
    const char *c, *c_end;
    char *endptr;

    *filename = (char *)&data[YMODEM_HEADER_SIZE];

    c = *filename;
    c_end = (const char *)__data + len;

    size_t name_len = strlen(*filename);
    if ((name_len == 0) || ((*filename + name_len) >= c_end)) {
        return -1;
    }

    c += name_len + 1;

    uint32_t val = strtoul(c, &endptr, 10);

    if (val == 0 || val == LONG_MAX || val == LONG_MIN) {
        return -1;
    }

    if (endptr == c) {
        return -1;
    }

    if (*endptr != 0x20) {
        return -1;
    }

    *filesize = val;

    return 0;
}

int32_t al_ymodem_recv(al_ymodem_t *ym)
{
    int32_t res = 0;

    switch (ym->status) {
        case YMODEM_STATUS_IDLE:
        {
            if (ym->opt->recv_clear) {
                ym->opt->recv_clear();
            }

            ym->opt->putc('C');
            ym->status = YMODEM_STATUS_RECV_HEADER;
            ym->last_time = ym->opt->uptime();
            ym->seq = 0;
            ym->finish_reason = AL_YM_FINISH_OK;
            ymodem_recv_status_reset(ym);

            break;
        }

        case YMODEM_STATUS_RECV_HEADER:
        {
            if (ymodem_recv_pkg(ym) > 0) {
                int32_t header = ymodem_check_pkg(ym->recv_buf,
                                                  ym->recv_wp, 0);
                if (header == 0) {
                    ym->last_time = ym->opt->uptime();

                    char *filename = NULL;
                    size_t filesize = 0;

                    if (al_ymodem_header_parse(ym, ym->recv_buf, ym->recv_wp,
                                               &filename, &filesize) != 0) {
                        ym->status = YMODEM_STATUS_RECV_ERR;
                        ym->finish_reason = AL_YM_FINISH_HEADER_RECV_ERR;
                        break;
                    }

                    if (ym->callback->recv_header(filename, filesize) == 0) {
                        ym->opt->putc(ACK);
                        ym->opt->putc('C');

                        ym->seq++;
                        ym->status = YMODEM_STATUS_RECV_DATA;
                        ym->session = true;
                    } else {
                        ym->status = YMODEM_STATUS_RECV_ERR;
                        ym->finish_reason = AL_YM_FINISH_HEADER_PROC_ERR;
                    }
                }
            }

            if ((ym->opt->uptime() - ym->last_time) > ym->timeout) {
                ym->status = YMODEM_STATUS_IDLE;
                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_DATA:
        {
            if (ymodem_recv_pkg(ym) > 0) {
                int32_t ret;

                ym->last_time = ym->opt->uptime();

                ret = ymodem_check_pkg(ym->recv_buf, ym->recv_wp, ym->seq);
                switch (ret) {
                    case EOT:
                        ym->status = YMODEM_STATUS_RECV_EOT_CONFIRM;
                        ym->opt->putc(NAK);
                        break;

                    case CAN:
                        ym->status = YMODEM_STATUS_RECV_TERM;
                        ym->finish_reason = AL_YM_FINISH_TERM;
                        break;

                    case 0:
                        if (ym->callback->recv_packet(
                                ym->recv_buf + YMODEM_HEADER_SIZE,
                                ym->packet_size) == 0) {
                            ym->seq++;
                            ym->opt->putc(ACK);
                        } else {
                            ym->status = YMODEM_STATUS_RECV_ERR;
                            ym->finish_reason = AL_YM_FINISH_PACKET_PROC_ERR;
                        }

                        break;

                    default:
                        ym->opt->putc(NAK);
                        ymodem_recv_status_reset(ym);
                        break;
                }
            }

            if ((ym->opt->uptime() - ym->last_time) > ym->timeout) {
                ym->status = YMODEM_STATUS_RECV_ERR;
                ym->finish_reason = AL_YM_FINISH_TIMEOUT;
                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_EOT_CONFIRM:
        {
            if (ymodem_recv_pkg(ym) > 0) {
                ym->last_time = ym->opt->uptime();

                int32_t ret = ymodem_check_pkg(ym->recv_buf, ym->recv_wp, 0);
                switch (ret) {
                    case EOT:
                        ym->status = YMODEM_STATUS_RECV_FINISH;
                        ym->opt->putc(ACK);
                        ym->opt->putc('C');
                        break;

                    case CAN:
                        ym->status = YMODEM_STATUS_RECV_TERM;
                        ym->finish_reason = AL_YM_FINISH_TERM;
                        break;

                    default:
                        ym->opt->putc(NAK);
                        ymodem_recv_status_reset(ym);
                        break;
                }
            }

            if ((ym->opt->uptime() - ym->last_time) > ym->timeout) {
                ym->status = YMODEM_STATUS_RECV_ERR;
                ym->finish_reason = AL_YM_FINISH_TIMEOUT;
                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_FINISH:
        {
            if (ymodem_recv_pkg(ym) > 0) {
                ym->last_time = ym->opt->uptime();

                int32_t ret = ymodem_check_pkg(ym->recv_buf, ym->recv_wp, 0);

                switch (ret) {
                    case CAN:
                        ym->status = YMODEM_STATUS_RECV_TERM;
                        ym->finish_reason = AL_YM_FINISH_TERM;
                        break;

                    case 0:
                    {
                        uint8_t *packet = ym->recv_buf + YMODEM_HEADER_SIZE;
                        size_t packet_size = ym->packet_size;
                        bool zero = al_mem_is_filled(packet, 0, packet_size);
                        bool more = (packet[0] != 0);   /* more files */

                        if (zero || !(more)) {
                            ym->opt->putc(ACK);

                            ym->session = false;
                            ym->status = YMODEM_STATUS_IDLE;
                            res = 1;

                            ym->callback->recv_finish(AL_YM_FINISH_OK);

                            break;
                        }

                        /**
                         * not support multi files, terminate transmit
                         */
                        if (more) {
                            ym->status = YMODEM_STATUS_RECV_TERM;
                            ym->finish_reason = AL_YM_FINISH_TERM;
                            break;
                        }

                        break;
                    }

                    default:
                        ym->status = YMODEM_STATUS_RECV_ERR;
                        ym->finish_reason = AL_YM_FINISH_END_RECV_ERR;
                        break;
                }
            }

            if ((ym->opt->uptime() - ym->last_time) > ym->timeout) {
                ym->status = YMODEM_STATUS_RECV_ERR;
                ym->finish_reason = AL_YM_FINISH_TIMEOUT;
                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_TERM:
        case YMODEM_STATUS_RECV_ERR:
            ym->opt->putc(CAN);
            ym->opt->putc(CAN);
            ym->opt->putc(CAN);
            ym->opt->putc(CAN);
            ym->opt->putc(CAN);

            ym->callback->recv_finish(ym->finish_reason);

            ym->status = YMODEM_STATUS_IDLE;
            ym->session = false;
            ymodem_recv_status_reset(ym);
            res = -1;
            break;

        default:
            break;

    }

    return res;
}

__END_DECLS

