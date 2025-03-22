#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy.h"
#include "SEGGER_RTT.h"

__BEGIN_DECLS

#define LSP_ERRNO_INDEX     0
#define LSP_LOGBUF_INDEX    1

#if (configNUM_THREAD_LOCAL_STORAGE_POINTERS >= 2)

int *__al_errno(void)
{
    /* in the interrupt or scheduler is not running */
    if(vPortGetIPSR() || (xTaskGetCurrentTaskHandle() == NULL)) {
        static volatile int __e;

        return (int *)&__e;
    }

    /* get the current task storage */
    int *e = (int *)pvTaskGetThreadLocalStoragePointer(NULL, LSP_ERRNO_INDEX);
    if (e == NULL) {
        e = al_os_malloc(sizeof(int));
        vTaskSetThreadLocalStoragePointer(NULL, LSP_ERRNO_INDEX, e);

        e = (int *)pvTaskGetThreadLocalStoragePointer(NULL, LSP_ERRNO_INDEX);
        BUG_ON(e == NULL);
    }

    return (int *)e;
}

void al_vlog(int32_t pri, const char *fmt, va_list ap)
{
#define VLOG_SIZE       128
    static char buf[VLOG_SIZE];
    ssize_t n;

    n = tfp_snprintf(
            buf, sizeof(buf), "[%5u.%03u]", al_uptime(), al_tick_get_msec());

    SEGGER_RTT_Write(0, buf, n);

    /* Check if in interrupt or scheduler not running */
    if (__unlikely(vPortGetIPSR() || (xTaskGetCurrentTaskHandle() == NULL))) {
        n = tfp_vsnprintf(buf, sizeof(buf), fmt, ap);
        if (n > 0)
            SEGGER_RTT_Write(0, buf, min((ssize_t)VLOG_SIZE - 1, n));
		
        return;
    }

    /* get the current task storage */
    char *logbuf = pvTaskGetThreadLocalStoragePointer(NULL, LSP_LOGBUF_INDEX);
    if (logbuf == NULL) {
        logbuf = al_os_malloc(VLOG_SIZE);
        vTaskSetThreadLocalStoragePointer(NULL, LSP_LOGBUF_INDEX, logbuf);

        logbuf = pvTaskGetThreadLocalStoragePointer(NULL, LSP_LOGBUF_INDEX);
        BUG_ON(logbuf == NULL);
    }

    /* In task context */
    n = tfp_vsnprintf(logbuf, VLOG_SIZE, fmt, ap);
    if (n > 0)
        SEGGER_RTT_Write(0, logbuf, min((ssize_t)VLOG_SIZE - 1, n));
#undef VLOG_SIZE
}

#else
#error("configNUM_THREAD_LOCAL_STORAGE_POINTERS must greather than 1 and \
the index 0 is reserved for errno");
#endif

__END_DECLS

