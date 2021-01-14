#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

__weak const char *al_get_arch(void)
{
#if defined(__arm__)
	const char *arch = "arm";
#elif defined(__amd64__)
	const char *arch = "amd64";
#elif defined(__i386__)
	const char *arch = "i386";
#else
	const char *arch = "noarch";
#endif

	return arch;
}

__weak const char *al_get_os(void)
{
#if defined(__linux__)
	const char *os = "linux";
#elif defined(__unix__)
	const char *os = "unix";
#else
	const char *os = "none";
#endif

	return os;
}

__END_DECLS

