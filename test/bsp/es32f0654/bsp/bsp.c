#include <sys/cdefs.h>
#include "ald_cmu.h"
#include "ald_gpio.h"
#include "md_gpio.h"
#include "bsp/uart.h"


__BEGIN_DECLS

int32_t bsp_init(void)
{
    ald_cmu_init();

    /* Configure system clock */
//    ald_cmu_pll1_config(CMU_PLL1_INPUT_HOSC_3, CMU_PLL1_OUTPUT_48M);
//    ald_cmu_clock_config(CMU_CLOCK_PLL1, 48000000);

    dbg_uart_init();

    return 0;
}

__END_DECLS

