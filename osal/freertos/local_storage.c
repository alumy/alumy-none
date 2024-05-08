#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/bug.h"
#include "alumy/osal.h"
#include "alumy/errno.h"

__BEGIN_DECLS

#define LSP_ERRNO_INDEX     0

#if (configNUM_THREAD_LOCAL_STORAGE_POINTERS >= 1)
int *__al_errno(void)
{
    int *e;

    e = (int *)pvTaskGetThreadLocalStoragePointer(NULL, LSP_ERRNO_INDEX);
    if (e == NULL) {
        e = al_os_malloc(sizeof(int));
        vTaskSetThreadLocalStoragePointer(NULL, LSP_ERRNO_INDEX, e);

        e = (int *)pvTaskGetThreadLocalStoragePointer(NULL, LSP_ERRNO_INDEX);
        BUG_ON(e == NULL);
    }

    return (int *)e;
}
#else
#error("configNUM_THREAD_LOCAL_STORAGE_POINTERS must greather than 1 and \
the index 0 is reserved for errno");
#endif

__END_DECLS

