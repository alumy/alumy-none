/**
 * @file slip.h
 * @brief SLIP (Serial Line Internet Protocol) implementation
 * 
 * This file provides the SLIP protocol implementation for serial communication.
 * SLIP is a simple protocol for transmitting IP packets over serial connections.
 */

#ifndef __AL_NET_SLIP_H
#define __AL_NET_SLIP_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/errno.h"

__BEGIN_DECLS

/**
 * SLIP protocol operation callbacks structure
 */
typedef struct al_slip_opt {
	int_t (*sl_putc)(int_t c);		/* Function to send a single character */
	int_t (*sl_getc)(void);			/* Function to receive a single character */
	int_t (*sl_flush)(void);		/* Function to flush output buffer, set to NULL if not needed */
} al_slip_opt_t;

/**
 * SLIP protocol context structure
 */
typedef struct al_slip {
    void * const recv_buf;			/* Receive buffer pointer */
    const size_t recv_size;			/* Receive buffer size */

	uintptr_t recv_wp;				/* Receive buffer write pointer */
	size_t recv_len;				/* Current received data length */
    uint_t recv_state;				/* Current receive state */

    const al_slip_opt_t * const opt;	/* Operation callbacks */
} al_slip_t;

/**
 * Initialize SLIP protocol context
 * @param slip SLIP context pointer
 * @param recv_buf Receive buffer pointer
 * @param recv_size Receive buffer size
 * @param opt Operation callbacks
 * @return 0 on success, negative error code on failure
 */
int_t al_slip_init(al_slip_t *slip, void *recv_buf, size_t recv_size,
				   const al_slip_opt_t *opt);

/**
 * Write data using SLIP protocol
 * @param slip SLIP context pointer
 * @param data Data to write
 * @param len Data length
 * @return Number of bytes written
 */
size_t al_slip_write(al_slip_t *slip, const void *data, size_t len);

/**
 * Flush SLIP output buffer
 * @param slip SLIP context pointer
 * @return 0 on success, negative error code on failure
 */
int_t al_slip_flush(al_slip_t *slip);

/**
 * Process a single received byte
 * @param slip SLIP context pointer
 * @param c Received byte
 * @return Number of complete packets received
 */
size_t al_slip_recv_byte(al_slip_t *slip, int_t c);

/**
 * Receive data using SLIP protocol
 * @param slip SLIP context pointer
 * @return Number of complete packets received
 */
size_t al_slip_recv(al_slip_t *slip);

/**
 * Get pointer to received data
 * @param slip SLIP context pointer
 * @return Pointer to received data buffer
 */
void *al_slip_get_recv(al_slip_t *slip);

__END_DECLS

#endif
