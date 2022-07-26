#include <string.h>
#include "alumy/driver/flash_header.h"
#include "alumy/errno.h"
#include "alumy/crc.h"
#include "alumy/bug.h"

__BEGIN_DECLS

int32_t al_flash_check_hcrc(const al_flash_header_t *hdr)
{
    uint32_t hcrc;
    uint32_t len = al_flash_get_header_size();
    al_flash_header_t header;

    /* Copy header so we can blank CRC field for re-calculation */
    memmove(&header, (char *)hdr, al_flash_get_header_size());
    al_flash_set_hcrc(&header, 0);

    hcrc = al_crc32(0, (const uint8_t *)&header, len);

    return (hcrc == al_flash_get_hcrc(hdr));
}

int32_t al_flash_check_dcrc(const al_flash_header_t *hdr)
{
    uint32_t data = al_flash_get_data(hdr);
    uint32_t len = al_flash_get_data_size(hdr);
    uint32_t dcrc = al_crc32(0, (const uint8_t *)data, len);

    return (dcrc == al_flash_get_dcrc(hdr));
}

int32_t al_flash_check(const void *ptr, size_t len)
{
    if (!al_flash_check_magic((const al_flash_header_t *)ptr)) {
        AL_ERROR(1, "Bad Magic Number");

        set_errno(EPERM);
        return -1;
    }

    if (!al_flash_check_hcrc((const al_flash_header_t *)ptr)) {
        AL_ERROR(1, "Has bad header checksum!");

        set_errno(EPERM);
        return -1;
    }

    if (al_flash_get_flash_size((const al_flash_header_t *)ptr) > len) {
        AL_ERROR(1, "Has corrupted size!");

        set_errno(EPERM);
        return -1;
    }

    if (al_flash_get_data_size((const al_flash_header_t *)ptr) > 0) {
        if (!al_flash_check_dcrc((const al_flash_header_t *)ptr)) {
            AL_ERROR(1, "Has corrupted data!");

            set_errno(EPERM);
            return -1;
        }
    }

    set_errno(0);

    return 0;
}

__END_DECLS

