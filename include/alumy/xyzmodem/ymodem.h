#ifndef __AL_YMODEM_H
#define __AL_YMODEM_H 1

#include <time.h>
#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/base.h"
#include "alumy/types.h"

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

#define YMODEM_RETRANS_CNT      10

#define YMODEM_IS_HEADER(h)         ((h) == SOH || (h) == STX)
#define YMODEM_IS_FILL(f)           ((f) == 0x00 || (f) == 0x1A)
#define YMODEM_IS_LEN(l)            ((l) < YMODEM_PACKET_SIZE_1K)

#define YMODEM_GET_HEADER(len)      ((len) > 128 ? STX : SOH)

typedef enum al_ymodem_finish_reason {
    AL_YM_FINISH_OK = 0,
    AL_YM_FINISH_TIMEOUT = -1,
    AL_YM_FINISH_TERM = -2,
    AL_YM_FINISH_HEADER_RECV_ERR = -3,
    AL_YM_FINISH_HEADER_PROC_ERR = -4,
    AL_YM_FINISH_PACKET_PROC_ERR = -5,
    AL_YM_FINISH_END_RECV_ERR = -6,
} al_ymodem_finish_reason_t;

typedef struct al_ymodem_callback {
    int32_t (*recv_header)(const char *filename, size_t filesize);
    int32_t (*recv_packet)(const void *data, size_t len);
    int32_t (*recv_finish)(al_ymodem_finish_reason_t reason);
} al_ymodem_callback_t;

typedef struct al_ymodem_opt {
    int32_t (*putc)(int32_t c);
    int32_t (*getc)(void);
    ssize_t (*recv)(void *buf, size_t size);
    int32_t (*recv_clear)(void);
    time_t (*uptime)(void);
    void (*delay_ms)(int32_t ms);
} al_ymodem_opt_t;

typedef struct al_ymodem {
    bool session;
    uint8_t seq;        /* package sequence number */
    int32_t status;     /* status machine */
    int32_t recv_status;        /* recv packet status machine */
    size_t packet_size;         /* packet size */
    uint8_t *recv_buf;
    size_t recv_bufsz;
    uintptr_t recv_wp;
    uint8_t *send_buf;
    size_t send_bufsz;
    uint8_t send_seq;
    time_t last_time;
    time_t timeout;
    al_ymodem_finish_reason_t finish_reason;
    al_ymodem_callback_t *callback;
    al_ymodem_opt_t *opt;
} al_ymodem_t;

int32_t al_ymodem_init(al_ymodem_t *ym,
                       uint8_t *recv_buf, size_t recv_bufsz, time_t timeout,
                       uint8_t *send_buf, size_t send_bufsz,
                       al_ymodem_opt_t *opt, al_ymodem_callback_t *cb);

int32_t al_ymodem_recv(al_ymodem_t *ym);

int32_t al_ymodem_wait_send(al_ymodem_t *ym);
int32_t al_ymodem_send_file(al_ymodem_t *ym, const char *file_name,
                            const void *data, size_t file_size);

__END_DECLS

#endif

