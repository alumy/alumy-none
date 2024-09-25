#ifndef __AL_OSAL_FREERTOS_QUEUE_H
#define __AL_OSAL_FREERTOS_QUEUE_H 1

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy.h"

__BEGIN_DECLS

#define AL_FREERTOS_QUEUE_CREATE_STATIC(name, size, nmeb) ({        \
    static uint8_t queue_##name[(size) * (nmeb)];                   \
    static StaticQueue_t queue_##name##_static;                     \
    xQueueCreateStatic((nmeb), (size), queue_##name, &queue_##name##_static);})

__END_DECLS

#endif

