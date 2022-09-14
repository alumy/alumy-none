/*
 * Copyright (c) 2017 Simon Goldschmidt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Simon Goldschmidt <goldsimon@gmx.de>
 *
 */

/* lwIP includes. */
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/stats.h"
#include "lwip/err.h"
#include "alumy.h"

#if (!NO_SYS)

/* Initialize this module (see description in sys.h) */
__weak void sys_init(void)
{

}

__weak u32_t sys_now(void)
{
  return 0;
}

__weak u32_t sys_jiffies(void)
{
  return 0;
}

#if SYS_LIGHTWEIGHT_PROT

__weak sys_prot_t sys_arch_protect(void)
{
  return 1;
}

__weak void sys_arch_unprotect(sys_prot_t pval)
{
  LWIP_UNUSED_ARG(pval);
}

#endif /* SYS_LIGHTWEIGHT_PROT */

__weak void sys_arch_msleep(u32_t delay_ms)
{
	LWIP_UNUSED_ARG(delay_ms);
}

#if !LWIP_COMPAT_MUTEX

/* Create a new mutex*/
__weak err_t sys_mutex_new(sys_mutex_t *mutex)
{
  return ERR_OK;
}

__weak void sys_mutex_lock(sys_mutex_t *mutex)
{

}

__weak void sys_mutex_unlock(sys_mutex_t *mutex)
{

}

__weak void sys_mutex_free(sys_mutex_t *mutex)
{

}

#endif /* !LWIP_COMPAT_MUTEX */

__weak err_t sys_sem_new(sys_sem_t *sem, u8_t initial_count)
{
  return ERR_OK;
}

__weak void sys_sem_signal(sys_sem_t *sem)
{

}

__weak u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout_ms)
{
  return 1;
}

__weak void sys_sem_free(sys_sem_t *sem)
{

}

__weak err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
  return ERR_OK;
}

__weak void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{

}

__weak err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
  return ERR_OK;
}

__weak err_t sys_mbox_trypost_fromisr(sys_mbox_t *mbox, void *msg)
{
  return ERR_OK;
}

__weak u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout_ms)
{
  return 1;
}

__weak u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
  return 1;
}

__weak void sys_mbox_free(sys_mbox_t *mbox)
{
}

__weak sys_thread_t
sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
	sys_thread_t dummy = { 0 };

	return dummy;
}

#if LWIP_NETCONN_SEM_PER_THREAD

__weak sys_sem_t *sys_arch_netconn_sem_get(void)
{
  return NULL;
}

__weak void sys_arch_netconn_sem_alloc(void)
{
  return NULL;
}

__weak void sys_arch_netconn_sem_free(void)
{

}

#endif /* LWIP_NETCONN_SEM_PER_THREAD */

#if LWIP_TCPIP_CORE_LOCKING

__weak void sys_lock_tcpip_core(void)
{

}

__weak void sys_unlock_tcpip_core(void)
{

}

#endif /* LWIP_TCPIP_CORE_LOCKING */

__weak void sys_mark_tcpip_thread(void)
{

}

__weak void sys_check_core_locking(void)
{

}

#endif

