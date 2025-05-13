#include "alumy/errno.h"
#include "alumy/check.h"
#include "alumy/bug.h"
#include "alumy/initialized.h"
#include "alumy/thread/worker.h"

__BEGIN_DECLS

typedef struct al_worker_item {
	void (*func)(void *arg);
	void *arg;
} al_worker_item_t;

static void al_worker_task(void *arg);

int32_t al_worker_init(al_worker_t *ctx, int_t cnt,
					   const char *name, uint32_t prio, uint32_t stack)
{
	int32_t ret;

	ctx->queue = NULL;

	if (!al_initialized_init(&ctx->init)) {
		set_errno(EEXIST);
		return -1;
	}

	ctx->queue = al_os_queue_create(cnt, sizeof(al_worker_item_t));
	AL_CHECK_RET(ctx->queue, ENOMEM, -1);

	ctx->task = al_os_task_create(name, prio, stack, al_worker_task, ctx);
	AL_CHECK_RET(ctx->task != NULL, ENOMEM, -1);

	return 0;
}

int_t al_worker_check(al_worker_t *ctx)
{
	return (ctx->queue && ctx->task) ? 0 : -1;
}

__static_inline__ __always_inline void al_worker_loop(al_worker_t *ctx)
{
	al_worker_item_t item;

	if (ctx->queue == NULL) {
		return;
	}

	for (;;) {
		if (al_os_queue_recv(ctx->queue, &item, -1) == 0) {
			if (item.func) {
				item.func(item.arg);
			}
		}
	}
}

int32_t al_worker_run(al_worker_t *ctx,
                      void (*func)(void *arg), void *arg, int32_t timeout)
{
    al_worker_item_t item;

    if (func == NULL) {
        set_errno(ENOEXEC);
        return -1;
    }

    item.func = func;
    item.arg = arg;

    if (al_os_queue_send(ctx->queue, &item, timeout) != 0) {
        set_errno(ENOMEM);
        return -1;
    }

    return 0;
}

static void al_worker_task(void *arg)
{
	al_worker_loop((al_worker_t *)arg);

    BUG_ON("i am worker, never run to here");

    al_os_task_delete(((al_worker_t *)arg)->task);
}

__END_DECLS

