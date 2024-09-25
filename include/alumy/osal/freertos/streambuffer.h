#ifndef __AL_OSAL_FREERTOS_STREAM_BUFFER_H
#define __AL_OSAL_FREERTOS_STREAM_BUFFER_H 1

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "alumy.h"

__BEGIN_DECLS

#define AL_FREERTOS_STREAM_CREATE_STATIC(name, size, trig) ({           \
    static uint8_t stream_##name[(size)];                               \
    static StaticStreamBuffer_t stream_##name##_static;                 \
    xStreamBufferCreateStatic(                                          \
            (size), (trig), stream_##name, &stream_##name##_static);})

__END_DECLS

#endif

