#ifndef __AL_YMODEM_H
#define __AL_YMODEM_H 1

#include <time.h>
#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/base.h"
#include "alumy/types.h"

__BEGIN_DECLS

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
    time_t last_time;
    time_t timeout;
    al_ymodem_finish_reason_t finish_reason;
    al_ymodem_callback_t *callback;
    al_ymodem_opt_t *opt;
} al_ymodem_t;

int32_t al_ymodem_init(al_ymodem_t *ym,
                       uint8_t *recv_buf, size_t recv_bufsz, time_t timeout,
                       al_ymodem_opt_t *opt, al_ymodem_callback_t *cb);
int32_t al_ymodem_recv(al_ymodem_t *ym);

__END_DECLS

#endif

