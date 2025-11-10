#ifndef __AL_YMODEM_H
#define __AL_YMODEM_H 1

#include <time.h>
#include "alumy/byteorder.h"
#include "alumy/config.h"
#include "alumy/base.h"
#include "alumy/types.h"

__BEGIN_DECLS

/* YMODEM protocol packet structure constants */
#define YMODEM_HEADER_SIZE      3       /* Header + Seq + Seq_comp */
#define YMODEM_END_SIZE         2       /* CRC16 size */

/* YMODEM packet data sizes */
#define YMODEM_PACKET_SIZE_128      (128)
#define YMODEM_PACKET_SIZE_1K       (1024)

/* Default timeout values in milliseconds */
#define YMODEM_ACK_WAIT_TIMEOUT_DFT		(500)	/* ms */
#define YMODEM_GETC_TIMEOUT_DFT			(10)	/* ms */
#define YMODEM_MAX_ERR_CNT_DFT			(10)	/* times */

/* Calculate total packet length including header and CRC */
#define YMODEM_TOTAL_LEN(pack_size)     \
    ((pack_size) + YMODEM_HEADER_SIZE + YMODEM_END_SIZE)

/* Packet field offsets */
#define YMODEM_HEADER       0           /* Header byte position */
#define YMODEM_SEQ          1           /* Sequence number position */
#define YMODEM_SEQ_COMP     2           /* Sequence complement position */
#define YMODEM_CRC(pack_size)       \
    (YMODEM_HEADER_SIZE + (pack_size))  /* CRC position */

/* Maximum retransmission count */
#define YMODEM_RETRANS_CNT      10

/* Validation macros */
/* Check if valid header */
#define YMODEM_IS_HEADER(h)         ((h) == AL_SOH || (h) == AL_STX)
/* Check if fill byte */
#define YMODEM_IS_FILL(f)           ((f) == 0x00 || (f) == 0x1A)
/* Check if valid length */
#define YMODEM_IS_LEN(l)            ((l) < YMODEM_PACKET_SIZE_1K)

/* Get appropriate header byte based on packet length */
#define YMODEM_GET_HEADER(len)      ((len) > 128 ? AL_STX : AL_SOH)

/* YMODEM transfer completion reasons */
typedef enum al_ymodem_finish_reason {
    AL_YM_FINISH_OK = 0,                    /* Transfer completed successfully */
    AL_YM_FINISH_TIMEOUT = -1,              /* Transfer timed out */
    AL_YM_FINISH_TERM = -2,                 /* Transfer terminated by user */
    AL_YM_FINISH_HEADER_RECV_ERR = -3,      /* Header reception error */
    AL_YM_FINISH_HEADER_PROC_ERR = -4,      /* Header processing error */
    AL_YM_FINISH_PACKET_PROC_ERR = -5,      /* Packet processing error */
    AL_YM_FINISH_END_RECV_ERR = -6,         /* End reception error */
} al_ymodem_finish_reason_t;

/* YMODEM callback functions structure */
typedef struct al_ymodem_callback {
    /* Called when file header is received with filename and size */
    int32_t (*recv_header)(const char *filename, size_t filesize);
    /* Called when data packet is received */
    int32_t (*recv_packet)(const void *data, size_t len);
    /* Called when transfer is finished with completion reason */
    int32_t (*recv_finish)(al_ymodem_finish_reason_t reason);
} al_ymodem_callback_t;

/* YMODEM operation functions structure */
typedef struct al_ymodem_opt {
    int32_t (*ym_putc)(int32_t c);          /* Send a single character */
    /* Receive a single character with timeout */
    int32_t (*ym_getc)(int32_t timeout);
	void (*ym_flush)(void);                 /* Flush output buffer */
    /* Receive data into buffer */
    ssize_t (*recv)(void *buf, size_t size);
    int32_t (*recv_clear)(void);            /* Clear receive buffer */
	uint32_t (*tick_ms)(void);              /* Get system tick in ms */
    /* Delay for specified milliseconds */
    void (*delay_ms)(int32_t ms);
} al_ymodem_opt_t;

/* YMODEM context structure */
typedef struct al_ymodem {
    bool session;                           /* Session active flag */
    uint8_t seq;                            /* Package sequence number */
    int32_t status;                         /* Status machine state */
    /* Receive packet status machine state */
    int32_t recv_status;
    size_t packet_size;                     /* Current packet size */
    uint8_t *recv_buf;                      /* Receive buffer pointer */
    size_t recv_bufsz;                      /* Receive buffer size */
    uintptr_t recv_wp;                      /* Receive write pointer */
    uint8_t *send_buf;                      /* Send buffer pointer */
    size_t send_bufsz;                      /* Send buffer size */
    uint8_t send_seq;                       /* Send sequence number */
    uint32_t last_time;                       /* Last operation timestamp */
    int32_t timeout;                         /* Operation timeout */
    int32_t err_cnt;                        /* Timeout counter */
    int32_t max_err_cnt;                    /* Maximum error count */
    int32_t eot_timeout;                    /* EOT timeout in ms */
    bool rcvd_eot;                          /* Received EOT flag */
	uint32_t wait_ack_timeout;              /* ACK wait timeout in ms */
	uint32_t getc_timeout;                  /* Character receive timeout in ms */
	bool send_packet_1k;                    /* Use 1K packets for sending */
    /* Transfer completion reason */
    al_ymodem_finish_reason_t finish_reason;
    const al_ymodem_callback_t *callback;  /* Callback functions */
    const al_ymodem_opt_t *opt;             /* Operation functions */
} al_ymodem_t;

/* Initialize YMODEM context with buffers and options */
int32_t al_ymodem_init(al_ymodem_t *ym,
					   uint8_t *recv_buf, size_t recv_bufsz, int32_t timeout,
					   uint8_t *send_buf, size_t send_bufsz,
					   const al_ymodem_opt_t *opt,
					   const al_ymodem_callback_t *cb);

/* Set maximum error count */
int32_t al_ymodem_set_max_err_cnt(al_ymodem_t *ym, int32_t cnt);

/* Set EOT timeout value */
int32_t al_ymodem_set_eot_timeout(al_ymodem_t *ym, int32_t timeout);

/* Set operation timeout value */
int32_t al_ymodem_set_timeout(al_ymodem_t *ym, int32_t timeout);

/* Receive data using YMODEM protocol */
int32_t al_ymodem_recv(al_ymodem_t *ym);

/* Wait for send request from receiver */
int32_t al_ymodem_wait_send(al_ymodem_t *ym);

/* Send file using YMODEM protocol */
int32_t al_ymodem_send_file(al_ymodem_t *ym, const char *file_name,
                            const void *data, size_t file_size);

/* Set ACK wait timeout value */
int32_t al_ymodem_set_ack_wait_timeout(al_ymodem_t *ym, uint32_t timeout);

/* Set character receive timeout value */
int32_t al_ymodem_set_getc_timeout(al_ymodem_t *ym, uint32_t timeout);

/* Set whether to use 1K packets for sending */
int32_t al_ymodem_set_send_packet_1k(al_ymodem_t *ym, bool send_1k);

__END_DECLS

#endif
