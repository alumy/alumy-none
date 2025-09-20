/**
 * @file fifo.h
 * @brief First In First Out (FIFO) buffer implementation
 * 
 * This header provides a circular buffer (FIFO) implementation for efficient
 * data storage and retrieval. The FIFO supports both single-byte and bulk
 * operations with automatic wraparound handling.
 */

#ifndef __AL_FIFO_H
#define __AL_FIFO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/log2.h"

__BEGIN_DECLS

/**
 * @brief The data struct of fifo
 *
 * @param buf The buffer which is used by fifo
 * @param size The size of buffer
 * @param in The write in pointer
 * @param out The read out pointer
 * @param put The put function pointer
 * @param get The get function pointer
 */
typedef struct al_fifo{
	uint8_t *buf;
	size_t size;
	uintptr_t in;
	uintptr_t out;
} al_fifo_t;

/**
 * @brief Initialize a fifo
 *
 * @author jackchen (2017/8/22)
 *
 * @param fifo The fifo handle
 * @param buf The buffer which is used by fifo
 * @param size The size of buffer
 */
void al_fifo_init(al_fifo_t *fifo, uint8_t *buf, size_t size);

/**
 * @brief Get data from fifo
 *
 * @param fifo The fifo handle
 * @param data Buffer to store the retrieved data
 * @param len Maximum number of bytes to retrieve
 * @return Number of bytes actually retrieved
 */
size_t al_fifo_get(al_fifo_t *fifo, uint8_t *data, size_t len);

/**
 * @brief Put data into fifo
 *
 * @param fifo The fifo handle
 * @param data The data to be stored
 * @param len Number of bytes to store
 * @return Number of bytes actually stored
 */
size_t al_fifo_put(al_fifo_t *fifo, const uint8_t *data, size_t len);

/**
 * @brief Get the current length of data in fifo
 *
 * @param fifo The fifo handle
 * @return Number of bytes currently stored in the fifo
 */
size_t al_fifo_len(al_fifo_t *fifo);

/**
 * @brief Check if the fifo is empty
 *
 * @param fifo The fifo handle
 * @return true if fifo is empty, false otherwise
 */
bool al_fifo_is_empty(al_fifo_t *fifo);

/**
 * @brief Check if the fifo is full
 *
 * @param fifo The fifo handle
 * @return true if fifo is full, false otherwise
 */
bool al_fifo_is_full(al_fifo_t *fifo);

/**
 * @brief Get the total size of the fifo buffer
 *
 * @param fifo The fifo handle
 * @return Total size of the fifo buffer in bytes
 */
size_t al_fifo_size(al_fifo_t *fifo);

__END_DECLS

#endif // FIFO_H
