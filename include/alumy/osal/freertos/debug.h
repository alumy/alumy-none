#ifndef __AL_OSAL_FREERTOS_DEBUG_H
#define __AL_OSAL_FREERTOS_DEBUG_H 1

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy.h"

__BEGIN_DECLS

#define al_freertos_print_heap_free_size(type)		do {		\
	AL_DEBUG((type), "%s:%d, heap free size: %d", 			\
			 __func__, __LINE__, xPortGetFreeHeapSize());	\
} while (0)

void al_freertos_mutex_get_holder(SemaphoreHandle_t mutex, const char *name);

void al_freertos_print_mutex_lock(uint_t type, const char *name);

void al_freertos_print_mutex_unlock(uint_t type, const char *name);

const char *al_freertos_get_curr_task_name(void);

int32_t al_freertos_stat_task_init(int_t interval);

__END_DECLS

#endif
