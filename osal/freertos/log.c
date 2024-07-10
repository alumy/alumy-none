#include <time.h>
#include <inttypes.h>
#include "alumy.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "SEGGER_RTT.h"

__BEGIN_DECLS

const char *al_log_timestamp(void)
{
    static char buf[32];

    snprintf(buf, sizeof(buf), "[%5u.%03u]", al_uptime(), al_tick_get_msec());

    return buf;
}

void al_vlog(int32_t pri, const char *fmt, va_list ap)
{
#define VLOG_SIZE       256
    static char buf[VLOG_SIZE];
    char *pbuf;
    ssize_t n;

    SEGGER_RTT_printf(0, "%s ", al_log_timestamp());

    if (__unlikely(vPortGetIPSR() || (xTaskGetCurrentTaskHandle() == NULL))) {
        n = vsnprintf(buf, sizeof(buf), fmt, ap);
        if (n > 0)
            SEGGER_RTT_Write(0, buf, min((ssize_t)VLOG_SIZE - 1, n));

        return;
    }

    pbuf = (char *)al_os_malloc(VLOG_SIZE);
    if (pbuf) {
        n = vsnprintf(pbuf, VLOG_SIZE, fmt, ap);
        if (n > 0)
            SEGGER_RTT_Write(0, pbuf, min((ssize_t)VLOG_SIZE - 1, n));

        al_os_free(pbuf);
    }
#undef VLOG_SIZE
}

__END_DECLS

