#include "bsp.h"
#include "hc32_ddl.h"
#include "core_cm4.h"

extern int main(void);

static void clk_init(void)
{
    stc_clk_sysclk_cfg_t stcSysClkCfg;
    stc_clk_xtal_cfg_t stcXtalCfg;
    stc_clk_mpll_cfg_t stcMpllCfg;
    stc_sram_config_t stcSramConfig;

    MEM_ZERO_STRUCT(stcSysClkCfg);
    MEM_ZERO_STRUCT(stcXtalCfg);
    MEM_ZERO_STRUCT(stcMpllCfg);
    MEM_ZERO_STRUCT(stcSramConfig);

    /* Set bus clk div. */
    stcSysClkCfg.enHclkDiv  = ClkSysclkDiv1;
    stcSysClkCfg.enExclkDiv = ClkSysclkDiv2;
    stcSysClkCfg.enPclk0Div = ClkSysclkDiv1;
    stcSysClkCfg.enPclk1Div = ClkSysclkDiv2;
    stcSysClkCfg.enPclk2Div = ClkSysclkDiv4;
    stcSysClkCfg.enPclk3Div = ClkSysclkDiv4;
    stcSysClkCfg.enPclk4Div = ClkSysclkDiv2;
    CLK_SysClkConfig(&stcSysClkCfg);

    /* Config Xtal and Enable Xtal */
    stcXtalCfg.enMode = ClkXtalModeOsc;
    stcXtalCfg.enDrv = ClkXtalLowDrv;
    stcXtalCfg.enFastStartup = Enable;
    CLK_XtalConfig(&stcXtalCfg);
    CLK_XtalCmd(Enable);

    /* sram init include read/write wait cycle setting */
    stcSramConfig.u8SramIdx = Sram12Idx | Sram3Idx | SramHsIdx | SramRetIdx;
    stcSramConfig.enSramRC = SramCycle2;
    stcSramConfig.enSramWC = SramCycle2;
    SRAM_Init(&stcSramConfig);

    /* flash read wait cycle setting */
    EFM_Unlock();
    EFM_SetLatency(EFM_LATENCY_5);
    EFM_Lock();

    /* MPLL config (XTAL / pllmDiv * plln / PllpDiv = 200M). */
    stcMpllCfg.pllmDiv = 3ul;
    stcMpllCfg.plln    = 100ul;
    stcMpllCfg.PllpDiv = 2ul;
    stcMpllCfg.PllqDiv = 2ul;
    stcMpllCfg.PllrDiv = 2ul;
    CLK_SetPllSource(ClkPllSrcXTAL);
    CLK_MpllConfig(&stcMpllCfg);

    /* Enable MPLL. */
    CLK_MpllCmd(Enable);
    /* Wait MPLL ready. */
    while (Set != CLK_GetFlagStatus(ClkFlagMPLLRdy)) {
        ;
    }
    /* Switch driver ability */
    PWC_HS2HP();
    /* Switch system clock source to MPLL. */
    CLK_SetSysClkSource(CLKSysSrcMPLL);

    SystemCoreClockUpdate();
}

int32_t bsp_init(void)
{
    clk_init();

	// dbg_uart_init();
    // pulse_timer_init();

    return 0;
}

int entry(void)
{
	bsp_init();
	return main();
}
