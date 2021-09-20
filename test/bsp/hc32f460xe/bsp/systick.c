#include <time.h>
#include "hc32_ddl.h"
#include "alumy.h"

__BEGIN_DECLS

static uint32_t tick = 0;
static clock_t clk = 0;

static void clock_update(void)
{
    if ((tick % CLOCKS_PER_SEC) == 0) {
        clk++;
    }
}

clock_t clock(void)
{
    return clk;
}

int32_t systick_init(void)
{
    SysTick_Init(1000ul);

    return 0;
}

void SysTick_IrqHandler(void)
{
    tick++;

    clock_update();
    SysTick_IncTick();
}

__END_DECLS

