#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"

__BEGIN_DECLS

al_os_mutex_t al_os_mutex_create(void)
{
	return NULL;
}

void al_os_mutex_del(al_os_mutex_t mutex)
{

}

al_os_sem_t al_os_sem_bin_create(void)
{
	return NULL;
}

void al_os_sem_bin_del(al_os_sem_t sem)
{

}

al_os_sem_t al_os_sem_count_create(uint_t max_count, uint_t init_count)
{
	return NULL;
}

void al_os_sem_count_del(al_os_sem_t sem)
{

}

int_t al_os_sem_take(al_os_sem_t sem, int_t timeout)
{
	return 0;
}

int_t al_os_sem_take_isr(al_os_sem_t sem, bool_t *yield)
{
	return 0;
}

int_t al_os_sem_give(al_os_sem_t sem)
{
	return 0;
}

int_t al_os_sem_give_isr(al_os_sem_t sem, bool_t *yield)
{
	return 0;
}

int_t al_os_mutex_take(al_os_mutex_t mutex, int_t timeout)
{
	return 0;
}

int_t al_os_mutex_take_isr(al_os_mutex_t mutex, bool_t *yield)
{
	return 0;
}

int_t al_os_mutex_give(al_os_mutex_t mutex)
{
	return 0;
}

int_t al_os_mutex_give_isr(al_os_mutex_t mutex, bool_t *yield)
{
	return 0;
}

__END_DECLS
