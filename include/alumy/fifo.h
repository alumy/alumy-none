#ifndef __AL_FIFO_H
#define __AL_FIFO_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

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
size_t al_fifo_get(al_fifo_t *fifo, uint8_t *data, size_t len);
size_t al_fifo_put(al_fifo_t *fifo, const uint8_t *data, size_t len);
size_t al_fifo_len(al_fifo_t *fifo);
bool al_fifo_is_empty(al_fifo_t *fifo);
bool al_fifo_is_full(al_fifo_t *fifo);
size_t al_fifo_size(al_fifo_t *fifo);

__END_DECLS

#endif // FIFO_H

