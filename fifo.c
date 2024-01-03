#include <string.h>
#include "alumy/fifo.h"
#include "alumy/bug.h"

__BEGIN_DECLS

/**
 * @brief Put data to fifo
 *
 * @author jackchen (2017/8/22)
 *
 * @param fifo The fifo handle
 * @param data The data to put
 * @param len The length of data
 *
 * @return size_t The size of put into
 */
static size_t __fifo_put(al_fifo_t *fifo, const uint8_t *data, size_t len)
{
	size_t l;

	len = min(len, fifo->size - fifo->in + fifo->out);

	/* first put the data starting from fifo->in to buffer end */
	l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
	memcpy(fifo->buf + (fifo->in & (fifo->size - 1)), data, l);

	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(fifo->buf, data + l, len - l);

	fifo->in += len;

	return len;
}

/**
 * @brief Get data from fifo
 *
 * @author jackchen (2017/8/22)
 *
 * @param fifo The fifo handle
 * @param data The buffer to read
 * @param len The length to read
 *
 * @return size_t The size of read
 */
static size_t __fifo_get(al_fifo_t *fifo, uint8_t *data, size_t len)
{
	size_t l;

	len = min(len, fifo->in - fifo->out);

	/* first get the data from fifo->out until the end of the buffer */
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
	memcpy(data, fifo->buf + (fifo->out & (fifo->size - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(data + l, fifo->buf, len - l);

	fifo->out += len;

	return len;
}

size_t al_fifo_put(al_fifo_t *fifo, const uint8_t *data, size_t len)
{
	size_t ret;

	ret = __fifo_put(fifo, data, len);

	return ret;
}

size_t al_fifo_len(al_fifo_t *fifo)
{
    return fifo->in - fifo->out;
}

bool al_fifo_is_empty(al_fifo_t *fifo)
{
	return (al_fifo_len(fifo) == 0);
}

bool al_fifo_is_full(al_fifo_t *fifo)
{
	return (al_fifo_len(fifo) == fifo->size);
}

size_t al_fifo_size(al_fifo_t *fifo)
{
	return fifo->size;
}

size_t al_fifo_get(al_fifo_t *fifo, uint8_t *data, size_t len)
{
	size_t ret;

	ret = __fifo_get(fifo, data, len);
	if(fifo->in == fifo->out){
		fifo->in = fifo->out = 0;
	}

	return ret;
}

void al_fifo_init(al_fifo_t *fifo, uint8_t *buf, size_t size)
{
    BUG_ON(!is_power_of_2(size));

    fifo->buf = buf;
	fifo->size = size;
	fifo->in = fifo->out = 0;
}

__END_DECLS

