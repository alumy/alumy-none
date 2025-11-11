#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "alumy.h"
#include "alumy/osal/freertos.h"
#include "tinyprintf.h"

__BEGIN_DECLS

void al_freertos_mutex_get_holder(SemaphoreHandle_t mutex, const char *name)
{
	if (mutex == NULL) {
		AL_WARN(1, "%s is null", name);
		return;
	}

	TaskHandle_t task = xSemaphoreGetMutexHolder(mutex);
	if (task == NULL) {
		AL_WARN(1, "%s holder is null", name);
		return;
	}

	const char *task_name = (const char *)pcTaskGetName(task);
	uint32_t cnt = uxSemaphoreGetCount(task);

	AL_DEBUG(1, "%s, holder = %p, name = %s, count = %u",
			 name, task, task_name ? task_name : "", cnt);
}

void al_freertos_print_mutex_lock(uint_t type, const char *name)
{
	AL_DEBUG(type, "%s lock, task = %s",
			 name, pcTaskGetName(xTaskGetCurrentTaskHandle()));
}

void al_freertos_print_mutex_unlock(uint_t type, const char *name)
{
	AL_DEBUG(type, "%s unlock, task = %s",
			 name, pcTaskGetName(xTaskGetCurrentTaskHandle()));
}

const char *al_freertos_get_curr_task_name(void)
{
    return pcTaskGetName(xTaskGetCurrentTaskHandle());
}

static const char *get_cpu_usage(char *buf, size_t bufsz,
                                 uint32_t run, uint32_t total)
{
    int32_t cpu_usage;

    if (run > 0) {
        cpu_usage = run / total;

        if (cpu_usage > 0) {
            tfp_snprintf(buf, bufsz, "%d", cpu_usage);
        } else {
            tfp_snprintf(buf, bufsz, "<1");
        }
    } else {
        tfp_snprintf(buf, bufsz, "-");
    }

    return buf;
}

static int task_stat(int argc, char *argv[])
{
#if (configUSE_TRACE_FACILITY == 1)
    int32_t task_cnt = uxTaskGetNumberOfTasks();
    if (task_cnt == 0) {
        return 0;
    }

    TaskStatus_t *tasks = al_os_malloc(task_cnt * sizeof(TaskStatus_t));
    if (tasks == NULL) {
        return -1;
    }

    uint32_t run_time;

    task_cnt = uxTaskGetSystemState(tasks, task_cnt, &run_time);

    run_time /= 100;

    AL_DEBUG(1, "############################################");
    AL_DEBUG(1, "%-16s%-8s%-8s%-8s%-8s",
             "NAME", "PRIO", "NUM", "STACK", "%CPU");
    AL_DEBUG(1, "############################################");

    for (int32_t i = 0; i < task_cnt; ++i) {
        char cpu_usage[16];

        AL_DEBUG(1, "%-16s%-8d%-8d%-8d%-8s",
                 tasks[i].pcTaskName, tasks[i].uxCurrentPriority,
                 tasks[i].xTaskNumber, tasks[i].usStackHighWaterMark,
                 get_cpu_usage(cpu_usage, sizeof(cpu_usage),
                               tasks[i].ulRunTimeCounter, run_time));
    }

	AL_DEBUG(1, "heap free %u bytes, min ever free %u bytes",
			 xPortGetFreeHeapSize(), xPortGetMinimumEverFreeHeapSize());

    al_os_free(tasks);
#endif

    return 0;
}

void al_freertos_stat_task(void *arg)
{
    static intptr_t interval;

    interval = (intptr_t)arg;

    if (interval < 1000) {
        interval = 1000;
    }

    while (1) {
        task_stat(0, NULL);
        al_os_delay(interval);
    }
}

__END_DECLS

