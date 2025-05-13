/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-30     chenyong     first version
 * 2018-04-12     chenyong     add client implement
 * 2018-08-17     chenyong     multiple client support
 * 2021-03-17     Meco Man     fix a buf of leaking memory
 * 2021-07-14     Sszl         fix a buf of leaking memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "alumy/config.h"
#include "alumy/driver/net/at.h"
#include "alumy/log.h"
#include "alumy/check.h"

#define AT_RESP_END_OK                 "OK"
#define AT_RESP_END_ERROR              "ERROR"
#define AT_RESP_END_FAIL               "FAIL"
#define AT_END_CR_LF                   "\r\n"

extern void at_print_raw_cmd(const char *type, const char *cmd, size_t size);

const char *at_client_get_last_cmd(at_client_t client, size_t *cmd_size)
{
    *cmd_size = client->last_cmd_len;
    return client->send_buf;
}

size_t at_client_vprintf(at_client_t client, const char *format, va_list args)
{
	size_t len = vsnprintf(client->send_buf, client->send_bufsz - 2,
						   format, args);
	if (len == 0) {
        return 0;
	}

	client->send_buf[len++] = '\r';
    client->send_buf[len++] = '\n';

	client->last_cmd_len = len;

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("sendline", client->send_buf, len);
#endif

	return client->opt->ac_send(client->send_buf, client->last_cmd_len);
}

size_t at_client_vprintfln(at_client_t client, const char *format, va_list args)
{
    size_t len;

    len = at_client_vprintf(client, format, args);

    return len + 2;
}

/**
 * Create response object.
 *
 * @param buf_size the maximum response buffer size
 * @param line_num the number of setting response lines
 *         = 0: the response data will auto return when received 'OK' or 'ERROR'
 *        != 0: the response data will return when received setting lines number data
 * @param timeout the maximum response time
 *
 * @return != NULL: response object
 *          = NULL: no memory
 */
at_response_t at_create_resp(size_t buf_size, size_t line_num, int32_t timeout)
{
    at_response_t resp = NULL;

    resp = (at_response_t)al_os_malloc(sizeof(struct at_response));
    if (resp == NULL)
    {
        AL_ERROR(1, "AT create response object failed! No memory for response object!");
        return NULL;
    }

    resp->buf = (char *) al_os_malloc(buf_size);
    if (resp->buf == NULL)
    {
        AL_ERROR(1, "AT create response object failed! No memory for response buffer!");
        al_os_free(resp);
        return NULL;
    }

    resp->buf_size = buf_size;
    resp->line_num = line_num;
    resp->line_counts = 0;
    resp->timeout = timeout;

    return resp;
}

/**
 * Delete and free response object.
 *
 * @param resp response object
 */
void at_delete_resp(at_response_t resp)
{
    if (resp && resp->buf)
    {
        al_os_free(resp->buf);
    }

    if (resp)
    {
        al_os_free(resp);
        resp = NULL;
    }
}

/**
 * Set response object information
 *
 * @param resp response object
 * @param buf_size the maximum response buffer size
 * @param line_num the number of setting response lines
 *         = 0: the response data will auto return when received 'OK' or 'ERROR'
 *        != 0: the response data will return when received setting lines number data
 * @param timeout the maximum response time
 *
 * @return  != NULL: response object
 *           = NULL: no memory
 */
at_response_t at_resp_set_info(at_response_t resp, size_t buf_size, size_t line_num, int32_t timeout)
{
    AL_ASSERT(resp);

    if (resp->buf_size != buf_size)
    {
        resp->buf_size = buf_size;
		
		al_os_free(resp->buf);

        resp->buf = (char *) al_os_malloc(buf_size);
        if (resp->buf == NULL)
        {
            AL_ERROR(1, "No memory for realloc response buffer size(%d).", buf_size);
            return NULL;
        }
    }

    resp->line_num = line_num;
    resp->timeout = timeout;

    return resp;
}

/**
 * Get one line AT response buffer by line number.
 *
 * @param resp response object
 * @param resp_line line number, start from '1'
 *
 * @return != NULL: response line buffer
 *          = NULL: input response line error
 */
const char *at_resp_get_line(at_response_t resp, size_t resp_line)
{
    char *resp_buf = resp->buf;
    size_t line_num = 1;

    AL_ASSERT(resp);

    if (resp_line > resp->line_counts || resp_line <= 0)
    {
        AL_ERROR(1, "AT response get line failed! Input response line(%d) error!", resp_line);
        return NULL;
    }

    for (line_num = 1; line_num <= resp->line_counts; line_num++)
    {
        if (resp_line == line_num)
        {
            return resp_buf;
        }

        resp_buf += strlen(resp_buf) + 1;
    }

    return NULL;
}

/**
 * Get one line AT response buffer by keyword
 *
 * @param resp response object
 * @param keyword query keyword
 *
 * @return != NULL: response line buffer
 *          = NULL: no matching data
 */
const char *at_resp_get_line_by_kw(at_response_t resp, const char *keyword)
{
    char *resp_buf = resp->buf;
    size_t line_num = 1;

    AL_ASSERT(resp);
    AL_ASSERT(keyword);

    for (line_num = 1; line_num <= resp->line_counts; line_num++)
    {
        if (strstr(resp_buf, keyword))
        {
            return resp_buf;
        }

        resp_buf += strlen(resp_buf) + 1;
    }

    return NULL;
}

/**
 * Get and parse AT response buffer arguments by line number.
 *
 * @param resp response object
 * @param resp_line line number, start from '1'
 * @param resp_expr response buffer expression
 *
 * @return -1 : input response line number error or get line buffer error
 *          0 : parsed without match
 *         >0 : the number of arguments successfully parsed
 */
int at_resp_parse_line_args(at_response_t resp, size_t resp_line, const char *resp_expr, ...)
{
    va_list args;
    int resp_args_num = 0;
    const char *resp_line_buf = NULL;

    AL_ASSERT(resp);
    AL_ASSERT(resp_expr);

    if ((resp_line_buf = at_resp_get_line(resp, resp_line)) == NULL)
    {
        return -1;
    }

    va_start(args, resp_expr);

    resp_args_num = vsscanf(resp_line_buf, resp_expr, args);

    va_end(args);

    return resp_args_num;
}

/**
 * Get and parse AT response buffer arguments by keyword.
 *
 * @param resp response object
 * @param keyword query keyword
 * @param resp_expr response buffer expression
 *
 * @return -1 : input keyword error or get line buffer error
 *          0 : parsed without match
 *         >0 : the number of arguments successfully parsed
 */
int at_resp_parse_line_args_by_kw(at_response_t resp, const char *keyword, const char *resp_expr, ...)
{
    va_list args;
    int resp_args_num = 0;
    const char *resp_line_buf = NULL;

    AL_ASSERT(resp);
    AL_ASSERT(resp_expr);

    if ((resp_line_buf = at_resp_get_line_by_kw(resp, keyword)) == NULL)
    {
        return -1;
    }

    va_start(args, resp_expr);

    resp_args_num = vsscanf(resp_line_buf, resp_expr, args);

    va_end(args);

    return resp_args_num;
}

/**
 * Send commands to AT server and wait response.
 *
 * @param client current AT client object
 * @param resp AT response object, using NULL when you don't care response
 * @param cmd_expr AT commands expression
 *
 * @return 0 : success
 *        -1 : response status error
 *        -2 : wait timeout
 *        -7 : enter AT CLI mode
 */
int at_obj_exec_cmd(at_client_t client, at_response_t resp, const char *cmd_expr, ...)
{
    va_list args;
    int_t result = 0;

    AL_ASSERT(cmd_expr);

    if (client == NULL)
    {
        AL_ERROR(1, "input AT Client object is NULL, please create or get AT Client object!");
        return -EINVAL;
    }

    /* check AT CLI mode */
    if (client->status == AT_STATUS_CLI && resp)
    {
        return -EBUSY;
    }

    al_os_mutex_take(client->lock, -1);

    client->resp_status = AT_RESP_OK;

    if (resp != NULL)
    {
        resp->buf_len = 0;
        resp->line_counts = 0;
    }

	client->resp = resp;
    al_os_sem_reset(client->resp_notice);

    va_start(args, cmd_expr);
    at_client_vprintfln(client, cmd_expr, args);
    if (client->last_cmd_len > 2)
    {
        client->last_cmd_len -= 2; /* "\r\n" */
    }
    va_end(args);

    if (resp != NULL)
    {
        if (al_os_sem_take(client->resp_notice, resp->timeout) != 0)
        {
			AL_WARN(1, "execute command (%.*s) timeout (%d ticks)!", 
					client->last_cmd_len, client->send_buf, resp->timeout);
            client->resp_status = AT_RESP_TIMEOUT;
            result = -ETIMEDOUT;
        }
        if (client->resp_status != AT_RESP_OK)
        {
			AL_ERROR(1, "execute command (%.*s) failed!", client->last_cmd_len, client->send_buf);
            result = -EPERM;
        }
    }

    client->resp = NULL;

    al_os_mutex_give(client->lock);

    return result;
}

/**
 * Waiting for connection to external devices.
 *
 * @param client current AT client object
 * @param timeout millisecond for timeout
 *
 * @return 0 : success
 *        -2 : timeout
 *        -5 : no memory
 */
int at_client_obj_wait_connect(at_client_t client, uint32_t timeout)
{
    int_t result = 0;
    at_response_t resp = NULL;
    uint32_t start_time = 0;

    if (client == NULL)
    {
        AL_ERROR(1, "input AT client object is NULL, please create or get AT Client object!");
        return -EPERM;
    }

    resp = at_create_resp(64, 0, al_os_ms2tick(300));
    if (resp == NULL)
    {
        AL_ERROR(1, "no memory for AT client response object.");
        return -ENOMEM;
    }

    al_os_mutex_take(client->lock, -1);
    client->resp = resp;
	al_os_sem_reset(client->resp_notice);

    start_time = al_os_get_tick();

    while (1)
    {
        /* Check whether it is timeout */
        if (al_os_get_tick() - start_time > al_os_ms2tick(timeout))
        {
            AL_ERROR(1, "wait AT client connect timeout(%d tick).", timeout);
            result = -ETIMEDOUT;
            break;
        }

        /* Check whether it is already connected */
        resp->buf_len = 0;
        resp->line_counts = 0;
        client->opt->ac_send("AT\r\n", 4);

        if (al_os_sem_take(client->resp_notice, resp->timeout) == 0) {
            break;
		}
    }

    at_delete_resp(resp);

    client->resp = NULL;

    al_os_mutex_give(client->lock);

    return result;
}

/**
 * Send data to AT server, send data don't have end sign(eg: \r\n).
 *
 * @param client current AT client object
 * @param buf   send data buffer
 * @param size  send fixed data size
 *
 * @return >0: send data size
 *         =0: send failed
 */
size_t at_client_obj_send(at_client_t client, const char *buf, size_t size)
{
    AL_ASSERT(buf);

    if (client == NULL)
    {
        AL_ERROR(1, "input AT Client object is NULL, please create or get AT Client object!");
        return 0;
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("sendline", buf, size);
#endif
	
	return client->opt->ac_send(buf, size);
}

static int_t at_client_getchar(at_client_t client, char *ch, int32_t timeout)
{
	int_t c;

	if ((c = client->opt->ac_getc(timeout)) == EOF) {
		return -1;
	}

	*ch = c;
	return 0;
}

/**
 * AT client receive fixed-length data.
 *
 * @param client current AT client object
 * @param buf   receive data buffer
 * @param size  receive fixed data size
 * @param timeout  receive data timeout (ms)
 *
 * @note this function can only be used in execution function of URC data
 *
 * @return >0: receive data size
 *         =0: receive failed
 */
size_t at_client_obj_recv(at_client_t client, char *buf, size_t size, int32_t timeout)
{
    size_t read_idx = 0;
    int_t result = 0;
    char ch;

    AL_ASSERT(buf);

    if (client == NULL)
    {
        AL_ERROR(1, "input AT Client object is NULL, please create or get AT Client object!");
        return 0;
    }

    while (1)
    {
        if (read_idx < size)
        {
            result = at_client_getchar(client, &ch, timeout);
            if (result != 0)
            {
                AL_ERROR(1, "AT Client receive failed, uart device get data error(%d)", result);
                return 0;
            }

            buf[read_idx++] = ch;
        }
        else
        {
            break;
        }
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("urc_recv", buf, size);
#endif

    return read_idx;
}

/**
 *  AT client set end sign.
 *
 * @param client current AT client object
 * @param ch the end sign, can not be used when it is '\0'
 */
void at_obj_set_end_sign(at_client_t client, char ch)
{
    if (client == NULL)
    {
        AL_ERROR(1, "input AT Client object is NULL, please create or get AT Client object!");
        return;
    }

    client->end_sign = ch;
}

/**
 * set URC(Unsolicited Result Code) table
 *
 * @param client current AT client object
 * @param table URC table
 * @param size table size
 */
int at_obj_set_urc_table(at_client_t client, const struct at_urc *urc_table, size_t table_sz)
{
    size_t idx;

    if (client == NULL)
    {
        AL_ERROR(1, "input AT Client object is NULL, please create or get AT Client object!");
        return -EPERM;
    }

    for (idx = 0; idx < table_sz; idx++)
    {
        AL_ASSERT(urc_table[idx].cmd_prefix);
        AL_ASSERT(urc_table[idx].cmd_suffix);
    }

    if (client->urc_table_size == 0)
    {
        client->urc_table = (struct at_urc_table *) al_os_malloc(sizeof(struct at_urc_table));
        if (client->urc_table == NULL)
        {
            return -ENOMEM;
        }

        client->urc_table[0].urc = urc_table;
        client->urc_table[0].urc_size = table_sz;
        client->urc_table_size++;
    }
    else
    {
        struct at_urc_table *old_urc_table = NULL;
        size_t old_table_size = client->urc_table_size * sizeof(struct at_urc_table);

        old_urc_table = (struct at_urc_table *) al_os_malloc(old_table_size);
        if (old_urc_table == NULL)
        {
            return -ENOMEM;
        }
        memcpy(old_urc_table, client->urc_table, old_table_size);

        /* realloc urc table space */
        client->urc_table = (struct at_urc_table *) al_os_malloc(old_table_size + sizeof(struct at_urc_table));
        if (client->urc_table == NULL)
        {
            al_os_free(old_urc_table);
            return -ENOMEM;
        }
        memcpy(client->urc_table, old_urc_table, old_table_size);
        client->urc_table[client->urc_table_size].urc = urc_table;
        client->urc_table[client->urc_table_size].urc_size = table_sz;
        client->urc_table_size++;

        al_os_free(old_urc_table);
    }

    return 0;
}

static const struct at_urc *get_urc_obj(at_client_t client)
{
    size_t i, j, prefix_len, suffix_len;
    size_t bufsz;
    char *buffer = NULL;
    const struct at_urc *urc = NULL;
    struct at_urc_table *urc_table = NULL;

    if (client->urc_table == NULL)
    {
        return NULL;
    }

    buffer = client->recv_line_buf;
    bufsz = client->recv_line_len;

    for (i = 0; i < client->urc_table_size; i++)
    {
        for (j = 0; j < client->urc_table[i].urc_size; j++)
        {
            urc_table = client->urc_table + i;
            urc = urc_table->urc + j;

            prefix_len = strlen(urc->cmd_prefix);
            suffix_len = strlen(urc->cmd_suffix);
            if (bufsz < prefix_len + suffix_len)
            {
                continue;
            }
            if ((prefix_len ? !strncmp(buffer, urc->cmd_prefix, prefix_len) : 1)
                    && (suffix_len ? !strncmp(buffer + bufsz - suffix_len, urc->cmd_suffix, suffix_len) : 1))
            {
                return urc;
            }
        }
    }

    return NULL;
}

static int at_recv_readline(at_client_t client)
{
    size_t read_len = 0;
    char ch = 0, last_ch = 0;
    bool_t is_full = false;

    memset(client->recv_line_buf, 0x00, client->recv_bufsz);
    client->recv_line_len = 0;

    while (1)
    {        
        at_client_getchar(client, &ch, -1);

        if (read_len < client->recv_bufsz)
        {
            client->recv_line_buf[read_len++] = ch;
            client->recv_line_len = read_len;
        }
        else
        {
            is_full = true;
        }

        /* is newline or URC data */
        if ((client->urc = get_urc_obj(client)) != NULL || (ch == '\n' && last_ch == '\r')
                || (client->end_sign != 0 && ch == client->end_sign))
        {
            if (is_full)
            {
                AL_ERROR(1, "read line failed. The line data length is out of buffer size(%d)!", client->recv_bufsz);
                memset(client->recv_line_buf, 0x00, client->recv_bufsz);
                client->recv_line_len = 0;
                return -ENOBUFS;
            }
            break;
        }
        last_ch = ch;
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("recvline", client->recv_line_buf, client->recv_line_len);
#endif

    return client->recv_line_len;
}

static void client_parser(at_client_t client)
{
    while(1)
    {       
        if (at_recv_readline(client) > 0)
        {                        
            if (client->urc != NULL)
            {
                /* current receive is request, try to execute related operations */
                if (client->urc->func != NULL)
                {
                    client->urc->func(client, client->recv_line_buf, client->recv_line_len);
                }
            }
            else if (client->resp != NULL)
            {
                at_response_t resp = client->resp;

                char end_ch = client->recv_line_buf[client->recv_line_len - 1];

                /* current receive is response */
                client->recv_line_buf[client->recv_line_len - 1] = '\0';
                if (resp->buf_len + client->recv_line_len < resp->buf_size)
                {
                    /* copy response lines, separated by '\0' */
                    memcpy(resp->buf + resp->buf_len, client->recv_line_buf, client->recv_line_len);

                    /* update the current response information */
                    resp->buf_len += client->recv_line_len;
                    resp->line_counts++;
                }
                else
                {
                    client->resp_status = AT_RESP_BUFF_FULL;
                    AL_ERROR(1, "Read response buffer failed. The Response buffer size is out of buffer size(%d)!", resp->buf_size);
                }
                /* check response result */
                if ((client->end_sign != 0) && (end_ch == client->end_sign) && (resp->line_num == 0))
                {
                    /* get the end sign, return response state END_OK.*/
                    client->resp_status = AT_RESP_OK;
                }
                else if (memcmp(client->recv_line_buf, AT_RESP_END_OK, strlen(AT_RESP_END_OK)) == 0
                        && resp->line_num == 0)
                {
                    /* get the end data by response result, return response state END_OK. */
                    client->resp_status = AT_RESP_OK;
                }
                else if (strstr(client->recv_line_buf, AT_RESP_END_ERROR)
                        || (memcmp(client->recv_line_buf, AT_RESP_END_FAIL, strlen(AT_RESP_END_FAIL)) == 0))
                {
                    client->resp_status = AT_RESP_ERROR;
                }
                else if (resp->line_counts == resp->line_num && resp->line_num)
                {
                    /* get the end data by response line, return response state END_OK.*/
                    client->resp_status = AT_RESP_OK;
                }
                else
                {
                    continue;
                }

                client->resp = NULL;
                al_os_sem_give(client->resp_notice);
            }
            else
            {
//                log_d("unrecognized line: %.*s", client->recv_line_len, client->recv_line_buf);
            }
        }
    }
}

/* initialize the client object parameters */
static int at_client_para_init(at_client_t client, int32_t prio, size_t stack)
{
    int result = 0;

    client->status = AT_STATUS_UNINITIALIZED;

    client->recv_line_len = 0;
    client->recv_line_buf = (char *) al_os_malloc(client->recv_bufsz);
    if (client->recv_line_buf == NULL)
    {
        AL_ERROR(1, "AT client initialize failed! No memory for receive buffer.");
        result = -ENOMEM;
        goto __exit;
    }

    client->last_cmd_len = 0;
    client->send_buf = (char *) al_os_malloc(client->send_bufsz);
    if (client->send_buf == NULL)
    {
        AL_ERROR(1, "AT client initialize failed! No memory for send buffer.");
        result = -ENOMEM;
        goto __exit;
    }
    client->lock = al_os_mutex_create();
    if (client->lock == NULL)
    {
        AL_ERROR(1, "AT client initialize failed! at_client_recv_lock create failed!");
        result = -ENOMEM;
        goto __exit;
    }

    client->rx_notice = al_os_sem_bin_create();
    if (client->rx_notice == NULL)
    {
        AL_ERROR(1, "AT client initialize failed! at_client_notice semaphore create failed!");
        result = -ENOMEM;
        goto __exit;
    }

    client->resp_notice = al_os_sem_bin_create();
    if (client->resp_notice == NULL)
    {
        AL_ERROR(1, "AT client initialize failed! at_client_resp semaphore create failed!");
        result = -ENOMEM;
        goto __exit;
    }

    client->urc_table = NULL;
    client->urc_table_size = 0;

	client->parser = al_os_task_create(
							"at_client", prio, stack, 
							(void (*)(void *))client_parser, client); 
    if(client->parser == NULL)
    {
        result = -ENOMEM;
        goto __exit;
    }

__exit:
    if (result != 0)
    {
        if (client->lock)
        {
            al_os_mutex_del(client->lock);
        }

        if (client->rx_notice)
        {
            al_os_sem_bin_del(client->rx_notice);
        }

        if (client->resp_notice)
        {
            al_os_sem_bin_del(client->resp_notice);
        }

        if (client->recv_line_buf)
        {
            al_os_free(client->recv_line_buf);
        }

        memset(client, 0x00, sizeof(struct at_client));
    }

    return result;
}

/**
 * AT client initialize.
 *
 * @param dev_name AT client device name
 * @param recv_bufsz the maximum number of receive buffer length
 *
 * @return 0 : initialize success
 *        -1 : initialize failed
 *        -5 : no memory
 */
int at_client_init(at_client_t client, size_t recv_bufsz, size_t send_bufsz, 
                   int32_t prio, size_t stack_size,
                   const at_client_opt_t *opt, void *user_data)
{
    int result = 0;

    AL_ASSERT(opt);
    AL_ASSERT(recv_bufsz > 0);
	AL_ASSERT(send_bufsz > 0);
	
	client->opt = opt;
    client->recv_bufsz = recv_bufsz;
    client->send_bufsz = send_bufsz;
	client->user_data = user_data;

    result = at_client_para_init(client, prio, stack_size);
    if (result != 0)
    {
        goto __exit;
    }

__exit:
    if (result == 0)
    {
        client->status = AT_STATUS_INITIALIZED;
        AL_INFO(1, "AT client(V%s) on device initialize success.", AT_SW_VERSION);
    }
    else
    {
        AL_ERROR(1, "AT client(V%s) on device initialize failed(%d).", AT_SW_VERSION, result);
    }

    return result;
}

