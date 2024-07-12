#ifndef __AL_OSAL_FREERTOS_TASK_H
#define __AL_OSAL_FREERTOS_TASK_H 1

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy.h"

__BEGIN_DECLS

#define AL_FREERTOS_TASK_CREATE_STATIC(name, func, stack_size, prio, arg) ({ \
    static StaticTask_t task_##name; \
    static StackType_t stack_##name[(stack_size)]; \
    xTaskCreateStatic((func), #name, (stack_size), (arg), (prio), \
                      stack_##name, &(task_##name));})

__END_DECLS

#endif

