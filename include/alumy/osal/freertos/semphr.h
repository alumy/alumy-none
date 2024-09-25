#ifndef __AL_OSAL_FREERTOS_SEMPHR_H
#define __AL_OSAL_FREERTOS_SEMPHR_H 1

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy.h"

__BEGIN_DECLS

#define AL_FREERTOS_SEM_BIN_CREATE_STATIC(name) ({                  \
    static StaticSemaphore_t sem_bin_##name##_static;               \
    xSemaphoreCreateBinaryStatic(&sem_bin_##name##_static);})

#define AL_FREERTOS_SEM_COUNT_CREATE_STATIC(name, _max, init) ({    \
    static StaticSemaphore_t sem_count_##name##_static;             \
    xSemaphoreCreateCountingStatic(                                 \
        (_max), (init), &sem_count_##name##_static);})

#define AL_FREERTOS_MUTEX_CREATE_STATIC(name) ({                    \
    static StaticSemaphore_t mutex_##name##_static;                 \
    xSemaphoreCreateMutexStatic(&mutex_##name##_static);})

__END_DECLS

#endif

