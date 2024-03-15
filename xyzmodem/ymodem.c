#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
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
#include "alumy/check.h"

__BEGIN_DECLS

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

static uint16_t ymodem_crc16(uint16_t crc, const void *data, uint32_t len)
{
    const uint8_t *p = (const uint8_t *)data;
    int32_t i;

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

            int32_t c = ym->opt->ym_getc(ym->getc_timeout);
            switch (c) {
                case AL_EOF:
                    break;

                case AL_SOH:
                    ym->packet_size = 128;
                    ym->recv_status = YMODEM_RECV_STATUS_DATA;
                    ym->recv_buf[ym->recv_wp++] = c;
                    break;

                case AL_STX:
                    ym->packet_size = 1024;
                    ym->recv_status = YMODEM_RECV_STATUS_DATA;
                    ym->recv_buf[ym->recv_wp++] = c;
                    break;

                case AL_ACK:
                case AL_NAK:
                case AL_EOT:
                case AL_CAN:
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

    if ((header == AL_ACK) || (header == AL_EOT) ||
        (header == AL_NAK) || (header == AL_CAN)) {
        return header;
    }

    if ((header != AL_SOH) && (header != AL_STX)) {
        return -1;
    }

    if ((header == AL_SOH) && (len != YMODEM_TOTAL_LEN(YMODEM_PACKET_SIZE_128))) {
        return -1;
    }

    if ((header == AL_STX) && (len != YMODEM_TOTAL_LEN(YMODEM_PACKET_SIZE_1K))) {
        return -1;
    }

    if ((seq | seq_comp) != 0xFF) {
        return -1;
    }

    if (seq != __seq) {
        return -1;
    }

    if (header == AL_SOH) {
        packet_size = YMODEM_PACKET_SIZE_128;
    } else {
        packet_size = YMODEM_PACKET_SIZE_1K;
    }

    uint16_t crc = ymodem_crc16(0, data + YMODEM_HEADER_SIZE, packet_size);

    pkg_crc = al_split_read_two(&data[YMODEM_CRC(packet_size)], false);

    if (crc != pkg_crc) {
        return -1;
    }

    return 0;
}

int32_t al_ymodem_init(al_ymodem_t *ym,
					   uint8_t *recv_buf, size_t recv_bufsz, time_t timeout,
					   uint8_t *send_buf, size_t send_bufsz,
					   const al_ymodem_opt_t *opt,
					   const al_ymodem_callback_t *cb)
{
    memset(ym, 0, sizeof(al_ymodem_t));

    BUG_ON(cb == NULL);
    BUG_ON(opt == NULL);
    BUG_ON(cb->recv_header == NULL);
    BUG_ON(cb->recv_packet == NULL);
    BUG_ON(cb->recv_finish == NULL);
    BUG_ON(opt->ym_putc == NULL);
    BUG_ON(opt->ym_getc == NULL);
    BUG_ON(opt->ym_flush == NULL);
    BUG_ON(opt->recv == NULL);
    BUG_ON(opt->uptime == NULL);
    BUG_ON(opt->delay_ms == NULL);
    BUG_ON(opt->tick_ms == NULL);

    ym->recv_buf = recv_buf;
    ym->recv_bufsz = recv_bufsz;
    ym->send_buf = send_buf;
    ym->send_bufsz = send_bufsz;
    ym->timeout = timeout;
    ym->opt = opt;
    ym->callback = cb;
    ym->session = false;
    ym->wait_ack_timeout = YMODEM_ACK_WAIT_TIMEOUT_DFT;
	ym->getc_timeout = YMODEM_GETC_TIMEOUT_DFT;
    ym->send_packet_1k = true;

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

    if (*endptr != 0x20 && *endptr != 0x00) {
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

            ym->opt->ym_putc('C');
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
                    ym->timeout_cnt = 0;

                    char *filename = NULL;
                    size_t filesize = 0;

                    if (al_ymodem_header_parse(ym, ym->recv_buf, ym->recv_wp,
                                               &filename, &filesize) != 0) {
                        ym->status = YMODEM_STATUS_RECV_ERR;
                        ym->finish_reason = AL_YM_FINISH_HEADER_RECV_ERR;
                        break;
                    }

                    if (ym->callback->recv_header(filename, filesize) == 0) {
                        ym->opt->ym_putc(AL_ACK);
                        ym->opt->ym_putc('C');

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
                ym->timeout_cnt = 0;

                ret = ymodem_check_pkg(ym->recv_buf, ym->recv_wp, ym->seq);
                switch (ret) {
                    case AL_EOT:
                        ym->status = YMODEM_STATUS_RECV_EOT_CONFIRM;
                        ym->opt->ym_putc(AL_NAK);
                        break;

                    case AL_CAN:
                        ym->status = YMODEM_STATUS_RECV_TERM;
                        ym->finish_reason = AL_YM_FINISH_TERM;
                        break;

                    case 0:
                        if (ym->callback->recv_packet(
                                ym->recv_buf + YMODEM_HEADER_SIZE,
                                ym->packet_size) == 0) {
                            ym->seq++;
                            ym->opt->ym_putc(AL_ACK);
                        } else {
                            ym->status = YMODEM_STATUS_RECV_ERR;
                            ym->finish_reason = AL_YM_FINISH_PACKET_PROC_ERR;
                        }

                        break;

                    default:
                        ym->opt->ym_putc(AL_NAK);
                        ymodem_recv_status_reset(ym);
                        break;
                }
            }

            if ((ym->opt->uptime() - ym->last_time) > ym->timeout) {
                ym->opt->ym_putc(AL_NAK);
                ym->last_time = ym->opt->uptime();
                ymodem_recv_status_reset(ym);

                if (ym->timeout_cnt++ > 3) {
                    ym->status = YMODEM_STATUS_RECV_ERR;
                    ym->finish_reason = AL_YM_FINISH_TIMEOUT;
                }

                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_EOT_CONFIRM:
        {
            if (ymodem_recv_pkg(ym) > 0) {
                ym->last_time = ym->opt->uptime();
                ym->timeout_cnt = 0;

                int32_t ret = ymodem_check_pkg(ym->recv_buf, ym->recv_wp, 0);
                switch (ret) {
                    case AL_EOT:
                        ym->status = YMODEM_STATUS_RECV_FINISH;
                        ym->opt->ym_putc(AL_ACK);
                        ym->opt->ym_putc('C');
                        break;

                    case AL_CAN:
                        ym->status = YMODEM_STATUS_RECV_TERM;
                        ym->finish_reason = AL_YM_FINISH_TERM;
                        break;

                    default:
                        ym->opt->ym_putc(AL_NAK);
                        ymodem_recv_status_reset(ym);
                        break;
                }
            }

            if ((ym->opt->uptime() - ym->last_time) > ym->timeout) {
                ym->opt->ym_putc(AL_NAK);
                ym->last_time = ym->opt->uptime();
                ymodem_recv_status_reset(ym);

                if (ym->timeout_cnt++ > 3) {
                    ym->status = YMODEM_STATUS_RECV_ERR;
                    ym->finish_reason = AL_YM_FINISH_TIMEOUT;
                }

                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_FINISH:
        {
            if (ymodem_recv_pkg(ym) > 0) {
                ym->last_time = ym->opt->uptime();
                ym->timeout_cnt = 0;

                int32_t ret = ymodem_check_pkg(ym->recv_buf, ym->recv_wp, 0);

                switch (ret) {
                    case AL_CAN:
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
                            ym->opt->ym_putc(AL_ACK);

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
                ym->opt->ym_putc(AL_NAK);
                ym->last_time = ym->opt->uptime();
                ymodem_recv_status_reset(ym);

                if (ym->timeout_cnt++ > 3) {
                    ym->status = YMODEM_STATUS_RECV_ERR;
                    ym->finish_reason = AL_YM_FINISH_TIMEOUT;
                }

                break;
            }

            break;
        }

        case YMODEM_STATUS_RECV_TERM:
        case YMODEM_STATUS_RECV_ERR:
            ym->opt->ym_putc(AL_CAN);
            ym->opt->ym_putc(AL_CAN);
            ym->opt->ym_putc(AL_CAN);
            ym->opt->ym_putc(AL_CAN);
            ym->opt->ym_putc(AL_CAN);

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

static int32_t al_ymodem_send_check_ack(al_ymodem_t *ym, uint8_t expect)
{
	int32_t c;
	uint32_t t_end = ym->opt->tick_ms() + ym->wait_ack_timeout;

	while (ym->opt->tick_ms() < t_end) {
		c = ym->opt->ym_getc(ym->getc_timeout);

		if (c == expect) {
			return 0;
		}
	}

	return -1;
}

static ssize_t __al_ymodem_send_packet(al_ymodem_t *ym,
                    uint8_t header, uint8_t seq, uint8_t fill,
                    const void *data, size_t len)
{
    ssize_t n = len;
    ssize_t cal_len;
    uint16_t crc = 0;
    ssize_t total_len = 0;
    const uint8_t *p;

    if (ym == NULL) {
        set_errno(EINVAL);
        return -1;
    }

    BUG_ON(!YMODEM_IS_HEADER(header));
    BUG_ON(!YMODEM_IS_FILL(fill));

    if (header == AL_STX) {
        cal_len = YMODEM_PACKET_SIZE_1K;
    } else {
        cal_len = YMODEM_PACKET_SIZE_128;
    }

    if (len > cal_len) {
        set_errno(EINVAL);
        return -1;
    }

    ym->opt->ym_putc(header);
    ym->opt->ym_putc(seq);
    ym->opt->ym_putc(~seq);

    total_len += 3;
    
    p = (const uint8_t *)data;

    while ((n--) > 0) {
        ym->opt->ym_putc(*p);
        crc = ymodem_crc16(crc, p, 1);

        p++;
        total_len++;
    }

    n = cal_len - len;

    while ((n--) > 0) {
        ym->opt->ym_putc(fill);
        crc = ymodem_crc16(crc, &fill, 1);

        total_len++;
    }

    ym->opt->ym_putc((crc & 0xFF00) >> 8);
    ym->opt->ym_putc(crc & 0x00FF);

	ym->opt->ym_flush();

    total_len += 2;

    return total_len;
}

static int32_t al_ymodem_send_packet(al_ymodem_t *ym,
                                     uint8_t header, uint8_t seq, uint8_t fill,
                                     const void *data, size_t len)
{
    int32_t i = 0;

    for (i = 0; i < YMODEM_RETRANS_CNT; ++i) {
        if (__al_ymodem_send_packet(ym, header, seq, fill, data, len) <= 0) {
            return -1;
        }

        if (al_ymodem_send_check_ack(ym, AL_ACK) == 0) {
            ym->send_seq++;

            break;
        }
    }

    if (i >= YMODEM_RETRANS_CNT) {
        return -1;
    }

    return 0;
}

static int32_t al_ymodem_send_file_data(al_ymodem_t *ym,
                                        const char *file_name,
                                        const void *data, size_t file_size)
{
    ssize_t len;
    int32_t ret;
    ssize_t remain = file_size;
    const uint8_t *p = (const uint8_t *)data;

	if (ym->send_packet_1k) {
		while (remain >= YMODEM_PACKET_SIZE_1K) {
			len = YMODEM_PACKET_SIZE_1K;
			ret = al_ymodem_send_packet(ym, YMODEM_GET_HEADER(len),
										ym->send_seq, 0x1A, p, len);
			if (ret < 0) {
				return -1;
			}

			remain -= YMODEM_PACKET_SIZE_1K;
			p += YMODEM_PACKET_SIZE_1K;
		}
	}

    while (remain >= YMODEM_PACKET_SIZE_128) {
        len = YMODEM_PACKET_SIZE_128;
        ret = al_ymodem_send_packet(ym, YMODEM_GET_HEADER(len),
                                    ym->send_seq, 0x1A, p, len);
        if (ret != 0) {
            return -1;
        }

        remain -= YMODEM_PACKET_SIZE_128;
        p += YMODEM_PACKET_SIZE_128;
    }

    len = remain;
    ret = al_ymodem_send_packet(ym, YMODEM_GET_HEADER(len),
                                ym->send_seq, 0x1A, p, len);
    if (ret != 0) {
        return -1;
    }

    return 0;
}

int32_t al_ymodem_wait_send(al_ymodem_t *ym)
{
    if (ym->opt->ym_getc(ym->getc_timeout) != 'C') {
        return -1;
    }

    return 0;
}

int32_t al_ymodem_set_ack_wait_timeout(al_ymodem_t *ym, uint32_t timeout)
{
	AL_CHECK_RET(ym, EINVAL, -1);

	ym->wait_ack_timeout = timeout;

	return 0;
}

int32_t al_ymodem_set_getc_timeout(al_ymodem_t *ym, uint32_t timeout)
{
	AL_CHECK_RET(ym, EINVAL, -1);

	ym->getc_timeout = timeout;

	return 0;
}

int32_t al_ymodem_set_send_packet_1k(al_ymodem_t *ym, bool send_1k)
{
	AL_CHECK_RET(ym, EINVAL, -1);

	ym->send_packet_1k = send_1k;

	return 0;
}

int32_t al_ymodem_send_file(al_ymodem_t *ym, const char *file_name,
                            const void *data, size_t file_size)
{
    ssize_t len;
    ssize_t ret;
    ssize_t remain;
    size_t send_len;

    ym->opt->recv_clear();

    len = snprintf((char *)ym->send_buf, YMODEM_PACKET_SIZE_128,
                   "%s", file_name);

    if ((len <= 0) || (len >= YMODEM_PACKET_SIZE_128)) {
        set_errno(EINVAL);
        return -1;
    }

    send_len = len + 1;
	remain = YMODEM_PACKET_SIZE_128 - (len + 1);

    len = snprintf((char *)ym->send_buf + (len + 1), remain,
				   "%"PRIuPTR, file_size);

    if ((len <= 0) || (len >= remain)) {
        set_errno(EINVAL);
        return -1;
    }

    send_len = send_len + len + 1;

    ym->send_seq = 0;

    ret = al_ymodem_send_packet(ym, AL_SOH, ym->send_seq, 0x00,
                                ym->send_buf, send_len);
    if (ret < 0) {
        return -1;
    }

    if (al_ymodem_send_check_ack(ym, 'C') != 0) {
        AL_ERROR(1, "al_ymodem_send_check_ack failed @ %s:%d",
                 __FILE__, __LINE__);
        return -1;
    }

    if (al_ymodem_send_file_data(ym, file_name, data, file_size) != 0) {
        AL_ERROR(1, "al_ymodem_send_file_data failed @ %s:%d",
                 __FILE__, __LINE__);	}

    ym->opt->ym_putc(AL_EOT);

    if (al_ymodem_send_check_ack(ym, AL_NAK) != 0) {
        AL_ERROR(1, "al_ymodem_send_check_ack failed @ %s:%d",
                 __FILE__, __LINE__);
        return -1;
    }

    ym->opt->ym_putc(AL_EOT);

    if (al_ymodem_send_check_ack(ym, AL_ACK) != 0) {
        AL_ERROR(1, "al_ymodem_send_check_ack failed @ %s:%d",
                 __FILE__, __LINE__);
        return -1;
    }

    if (al_ymodem_send_check_ack(ym, 'C') != 0) {
        AL_ERROR(1, "al_ymodem_send_check_ack failed @ %s:%d",
                 __FILE__, __LINE__);
        return -1;
    }

    ym->send_seq = 0;

    memset(ym->send_buf, 0, YMODEM_PACKET_SIZE_128);
    ret = al_ymodem_send_packet(ym, AL_SOH, ym->send_seq, 0x00,
                                ym->send_buf, YMODEM_PACKET_SIZE_128);
    if (ret < 0) {
        return -1;
    }

    return 0;
}

__END_DECLS

