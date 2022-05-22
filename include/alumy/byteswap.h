#ifndef __AL_BYTE_SWAP_H
#define __AL_BYTE_SWAP_H 1

#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/* The host byte order is the same as network byte order,
    so these functions are all just identity.  */
#if __BYTE_ORDER == __BIG_ENDIAN
    #define al_ntohl(x)         (x)
    #define al_ntohs(x)         (x)
    #define al_htonl(x)         (x)
    #define al_htons(x)         (x)
    #define al_cpu_to_le32(x)	al_swap_32(x)
#elif __BYTE_ORDER == __LITTLE_ENDIAN
    #define al_ntohl(x)         al_swap_32(x)
    #define al_ntohs(x)         al_swap_16(x)
    #define al_htonl(x)         al_swap_32(x)
    #define al_htons(x)         al_swap_16(x)
    #define al_cpu_to_le16(x)   (x)
    #define al_le16_to_cpu(x)   (x)
    #define al_be16_to_cpu(x)   al_swap_16(x)
    #define al_cpu_to_be16(x)   al_swap_16(x)
	#define al_cpu_to_le32(x)	(x)
    #define al_le32_to_cpu(x)	(x)
    #define al_be32_to_cpu(x)   al_swap_32(x)
    #define al_cpu_to_be32(x)   al_swap_32(x)
    #define al_cpu_to_le64(x)	(x)
    #define al_le64_to_cpu(x)	(x)
    #define al_be64_to_cpu(x)   al_swap_64(x)
    #define al_cpu_to_be64(x)   al_swap_64(x)
#else
    #error "Unknow byte order"
#endif

#define al_swap_16(x) \
	((((x) & 0xff00) >> 8) | \
	 (((x) & 0x00ff) << 8))
#define al_swap_32(x) \
	((((x) & 0xff000000) >> 24) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x000000ff) << 24))
#define al_swap_64(x, sfx) \
	((((x) & 0xff00000000000000##sfx) >> 56) | \
	 (((x) & 0x00ff000000000000##sfx) >> 40) | \
	 (((x) & 0x0000ff0000000000##sfx) >> 24) | \
	 (((x) & 0x000000ff00000000##sfx) >>  8) | \
	 (((x) & 0x00000000ff000000##sfx) <<  8) | \
	 (((x) & 0x0000000000ff0000##sfx) << 24) | \
	 (((x) & 0x000000000000ff00##sfx) << 40) | \
	 (((x) & 0x00000000000000ff##sfx) << 56))
#if defined(__GNUC__)
# define uswap_64(x) al_swap_64(x, ull)
#else
# define uswap_64(x) al_swap_64(x, )
#endif

__static_inline__ void al_split_write_two(void *_addr, uint16_t two, bool le)
{
	uint8_t *addr = (uint8_t *)_addr;

	if (le) {
		addr[0] = two & 0xFF;
		addr[1] = (two & 0xFF00) >> 8;
	} else {
		addr[1] = two & 0xFF;
		addr[0] = (two & 0xFF00) >> 8;
	}
}

__static_inline__ uint16_t al_split_read_two(const void *_addr, bool le)
{
	uint16_t ret;
	const uint8_t *two = (const uint8_t *)_addr;

	if (le) {
		ret = (two[1] << 8) | two[0];
	} else {
		ret = (two[0] << 8) | two[1];
	}

	return ret;
}


__static_inline__ void al_split_write_four(void *_addr, uint32_t four, bool le)
{
	uint8_t *addr = (uint8_t *)_addr;

	if (le) {
		addr[0] = four & 0xFF;
		addr[1] = (four & 0x0000FF00) >> 8;
		addr[2] = (four & 0x00FF0000) >> 16;
		addr[3] = (four & 0xFF000000) >> 24;
	} else {
		addr[3] = four & 0xFF;
		addr[2] = (four & 0x0000FF00) >> 8;
		addr[1] = (four & 0x00FF0000) >> 16;
		addr[0] = (four & 0xFF000000) >> 24;
	}
}

__static_inline__ uint32_t al_split_read_four(const void *addr, bool le)
{
	uint32_t ret;
	const uint8_t *four = (const uint8_t *)addr;

	if (le) {
		ret = four[0] | (four[1] << 8) | (four[2] << 16) | (four[3] << 24);
	} else {
		ret = four[3] | (four[2] << 8) | (four[1] << 16) | (four[0] << 24);
	}

	return ret;
}

__static_inline__
void al_split_write_eight(void *_addr, uint64_t eight, bool le)
{
	uint8_t *addr = (uint8_t *)_addr;

	if (le) {
		addr[0] = eight & 0x00000000000000FF;
		addr[1] = (eight & 0x000000000000FF00) >> 8;
		addr[2] = (eight & 0x0000000000FF0000) >> 16;
		addr[3] = (eight & 0x00000000FF000000) >> 24;
		addr[4] = (eight & 0x000000FF00000000) >> 32;
		addr[5] = (eight & 0x0000FF0000000000) >> 40;
		addr[6] = (eight & 0x00FF000000000000) >> 48;
		addr[7] = (eight & 0xFF00000000000000) >> 56;
	} else {
		addr[7] = eight & 0x00000000000000FF;
		addr[6] = (eight & 0x000000000000FF00) >> 8;
		addr[5] = (eight & 0x0000000000FF0000) >> 16;
		addr[4] = (eight & 0x00000000FF000000) >> 24;
		addr[3] = (eight & 0x000000FF00000000) >> 32;
		addr[2] = (eight & 0x0000FF0000000000) >> 40;
		addr[1] = (eight & 0x00FF000000000000) >> 48;
		addr[0] = (eight & 0xFF00000000000000) >> 56;
	}
}

__static_inline__ uint64_t al_split_read_eight(const void *addr, bool le)
{
	uint64_t ret;
	const uint8_t *eight = (const uint8_t *)addr;

	if (le) {
		ret = (((uint64_t)eight[7] << 56) | ((uint64_t)eight[6] << 48) |
			   ((uint64_t)eight[5] << 40) | ((uint64_t)eight[4] << 32) |
			   ((uint64_t)eight[3] << 24) | ((uint64_t)eight[2] << 16) |
			   ((uint64_t)eight[1] << 8) | (uint64_t)eight[0]);
	} else {
		ret = (((uint64_t)eight[0] << 56) | ((uint64_t)eight[1] << 48) |
			   ((uint64_t)eight[2] << 40) | ((uint64_t)eight[3] << 32) |
			   ((uint64_t)eight[4] << 24) | ((uint64_t)eight[5] << 16) |
			   ((uint64_t)eight[6] << 8) | (uint64_t)eight[7]);
	}

	return ret;
}


__END_DECLS

#endif

