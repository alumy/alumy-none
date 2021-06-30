#include <sys/cdefs.h>
#include "bsp/uart.h"


__BEGIN_DECLS

extern int main(int argc, char *argv[]);

static int32_t bsp_init(void)
{
    dbg_uart_init();

    return 0;
}

int entry(int argc, char *argv[])
{
	bsp_init();
	
	return main(argc, argv);
}

__END_DECLS

