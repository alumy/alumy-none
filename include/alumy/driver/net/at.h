/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-30     chenyong     first version
 * 2018-08-17     chenyong     multiple client support
 */

#ifndef __DRV_NET_AT_H__
#define __DRV_NET_AT_H__

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AT_SW_VERSION                  "1.3.1"

enum at_status
{
    AT_STATUS_UNINITIALIZED = 0,
    AT_STATUS_INITIALIZED,
    AT_STATUS_CLI,
};

typedef enum at_status at_status_t;

enum at_resp_status
{
     AT_RESP_OK = 0,                   /* AT response end is OK */
     AT_RESP_ERROR = -1,               /* AT response end is ERROR */
     AT_RESP_TIMEOUT = -2,             /* AT response is timeout */
     AT_RESP_BUFF_FULL= -3,            /* AT response buffer is full */
};
typedef enum at_resp_status at_resp_status_t;

struct at_response
{
    /* response buffer */
    char *buf;
    /* the maximum response buffer size, it set by `at_create_resp()` function */
    size_t buf_size;
    /* the length of current response buffer */
    size_t buf_len;
    /* the number of setting response lines, it set by `at_create_resp()` function
     * == 0: the response data will auto return when received 'OK' or 'ERROR'
     * != 0: the response data will return when received setting lines number data */
    size_t line_num;
    /* the count of received response lines */
    size_t line_counts;
    /* the maximum response time */
    int32_t timeout;
};

typedef struct at_response *at_response_t;

struct at_client;

/* URC(Unsolicited Result Code) object, such as: 'RING', 'READY' request by AT server */
struct at_urc
{
    const char *cmd_prefix;
    const char *cmd_suffix;
    void (*func)(struct at_client *client, const char *data, size_t size);
};
typedef struct at_urc *at_urc_t;

struct at_urc_table
{
    size_t urc_size;
    const struct at_urc *urc;
};
typedef struct at_urc *at_urc_table_t;

typedef struct at_client_opt {
	int_t (*ac_getc)(int_t timeout);
	int_t (*ac_putc)(int_t c);
	ssize_t (*ac_send)(const void *data, size_t len);
	ssize_t (*ac_recv)(void *buf, size_t bufsz, int_t timeout);
} at_client_opt_t;

struct at_client
{
    at_status_t status;
    char end_sign;

	char *send_buf;
    /* The maximum supported send cmd length */
    size_t send_bufsz;
    /* The length of last cmd */
    size_t last_cmd_len;

    /* the current received one line data buffer */
    char *recv_line_buf;
    /* The length of the currently received one line data */
    size_t recv_line_len;
    /* The maximum supported receive data length */
    size_t recv_bufsz;
    al_os_sem_t rx_notice;
    al_os_mutex_t lock;

    at_response_t resp;
    al_os_sem_t resp_notice;
    at_resp_status_t resp_status;

    struct at_urc_table *urc_table;
    size_t urc_table_size;
	const struct at_urc *urc;

    al_os_task_t parser;
	
	const at_client_opt_t *opt;
	void *user_data;
};
typedef struct at_client *at_client_t;

/* AT client initialize and start*/
int at_client_init(at_client_t client, size_t recv_bufsz, size_t send_bufsz,
					const at_client_opt_t *opt, void *user_data);

/* ========================== multiple AT client function ============================ */

/* AT client wait for connection to external devices. */
int at_client_obj_wait_connect(at_client_t client, uint32_t timeout);

/* AT client send or receive data */
size_t at_client_obj_send(at_client_t client, const char *buf, size_t size);
size_t at_client_obj_recv(at_client_t client, char *buf, size_t size, int32_t timeout);

/* set AT client a line end sign */
void at_obj_set_end_sign(at_client_t client, char ch);

/* Set URC(Unsolicited Result Code) table */
int at_obj_set_urc_table(at_client_t client, const struct at_urc * table, size_t size);

/* AT client send commands to AT server and waiter response */
int at_obj_exec_cmd(at_client_t client, at_response_t resp, const char *cmd_expr, ...);

/* AT response object create and delete */
at_response_t at_create_resp(size_t buf_size, size_t line_num, int32_t timeout);
void at_delete_resp(at_response_t resp);
at_response_t at_resp_set_info(at_response_t resp, size_t buf_size, size_t line_num, int32_t timeout);

/* AT response line buffer get and parse response buffer arguments */
const char *at_resp_get_line(at_response_t resp, size_t resp_line);
const char *at_resp_get_line_by_kw(at_response_t resp, const char *keyword);
int at_resp_parse_line_args(at_response_t resp, size_t resp_line, const char *resp_expr, ...);
int at_resp_parse_line_args_by_kw(at_response_t resp, const char *keyword, const char *resp_expr, ...);

/* ========================== single AT client function ============================ */

#ifdef __cplusplus
}
#endif

#endif /* __AT_H__ */
