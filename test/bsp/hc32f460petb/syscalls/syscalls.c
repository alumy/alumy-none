/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>


/* Variables */
//#undef errno
extern int errno;
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));
extern time_t __time(time_t *pt) __attribute__((weak));
extern clock_t __clock(void) __attribute__((weak));

register char * stack_ptr asm("sp");

char *__env[1] = { 0 };
char **environ = __env;


/* Functions */
void initialise_monitor_handles()
{
}

__attribute__((weak)) int _getpid(void)
{
	return 1;
}

__attribute__((weak)) int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

__attribute__((weak)) void _exit (int status)
{
	_kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		*ptr++ = __io_getchar();
	}

	return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}

__attribute__((weak)) int _close(int file)
{
	return -1;
}


__attribute__((weak)) int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

__attribute__((weak)) int _isatty(int file)
{
	return 1;
}

__attribute__((weak)) int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _open(char *path, int flags, ...)
{
	/* Pretend like we always fail */
	return -1;
}

int _wait(int *status)
{
	errno = ECHILD;
	return -1;
}

int _unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

int _stat(char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _link(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}

/**
 _sbrk
 Increase program data space. Malloc and related functions depend on this
**/
caddr_t _sbrk(int incr)
{
	extern char end asm("end");
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0)
		heap_end = &end;

	prev_heap_end = heap_end;
	if (heap_end + incr > stack_ptr)
	{
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

int _gettimeofday (struct timeval * tp, void * tzvp)
{
    struct timezone *tzp = tzvp;
    if (tp)
    {
        tp->tv_sec = __time(NULL);
        tp->tv_usec = 0;
    }

    /* Return fixed data for the timezone.  */
    if (tzp)
    {
        tzp->tz_minuteswest = 0;
        tzp->tz_dsttime = 0;
    }

    return 0;
}

/* Return a clock that ticks at 100Hz.  */
clock_t _times (struct tms * tp)
{
    clock_t timeval = __clock();

    if (tp) {
        tp->tms_utime  = timeval;	/* user time */
        tp->tms_stime  = 0;	/* system time */
        tp->tms_cutime = 0;	/* user time, children */
        tp->tms_cstime = 0;	/* system time, children */
    }

    return timeval;
}


