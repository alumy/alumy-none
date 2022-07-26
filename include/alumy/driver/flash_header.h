#ifndef __AL_DRV_FLASH_HEADER_H
#define __AL_DRV_FLASH_HEADER_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/byteorder.h"
#include "alumy/byteswap.h"

__BEGIN_DECLS

#define AL_FLASH_MAGIC      0x20220706ul

typedef struct al_flash_header {
    uint32_t fh_magic;
    uint32_t fh_hcrc;
    uint32_t fh_size;
    uint32_t fh_dcrc;
    uint32_t fh_version;
} al_flash_header_t;

static inline uint32_t al_flash_get_header_size(void)
{
    return (sizeof(al_flash_header_t));
}

#define al_flash_get_hdr_l(f) \
    static inline uint32_t al_flash_get_##f(const al_flash_header_t *hdr) \
    { \
        return al_be32_to_cpu(hdr->fh_##f); \
    }
al_flash_get_hdr_l(magic)
al_flash_get_hdr_l(hcrc)
al_flash_get_hdr_l(size)
al_flash_get_hdr_l(dcrc)
al_flash_get_hdr_l(version)

static inline uint32_t al_flash_get_data_size(const al_flash_header_t *hdr)
{
    return al_flash_get_size(hdr);
}

static inline uintptr_t al_flash_get_data(const al_flash_header_t *hdr)
{
    return ((uintptr_t)hdr + al_flash_get_header_size());
}

static inline uint16_t al_flash_get_flash_size(const al_flash_header_t *hdr)
{
    return (al_flash_get_size(hdr) + al_flash_get_header_size());
}

#define al_flash_set_hdr_l(f) \
    static inline void al_flash_set_##f(al_flash_header_t *hdr, uint32_t val) \
    { \
        hdr->fh_##f = al_cpu_to_be32(val); \
    }

al_flash_set_hdr_l(magic)
al_flash_set_hdr_l(hcrc)
al_flash_set_hdr_l(dcrc)
al_flash_set_hdr_l(size)
al_flash_set_hdr_l(version)

static inline int32_t al_flash_check_magic(const al_flash_header_t *hdr)
{
    return (al_flash_get_magic(hdr) == AL_FLASH_MAGIC);
}

int32_t al_flash_check_hcrc(const al_flash_header_t *hdr);
int32_t al_flash_check_dcrc(const al_flash_header_t *hdr);
int32_t al_flash_check(const void *ptr, size_t len);

__END_DECLS

#endif

