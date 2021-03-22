/**
  *********************************************************************************
  *
  * @file    md_pmu.h
  * @brief   Header file of PMU module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __MD_PMU_H__
#define __MD_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_PMU PMU
  * @brief PMU micro driver
  * @{
  */
/**
  * @defgroup MD_PMU_Public_Types PMU Public Types
  * @{
  */
/**
  * @brief Low power mode
  */
typedef enum {
	MD_PMU_LP_STOP1   = 0x0U,        /**< Stop1 */
	MD_PMU_LP_STOP2   = 0x1U,        /**< Stop2 */
	MD_PMU_LP_STANDBY = 0x2U,        /**< Standby */
} md_pmu_lp_mode_t;

/**
  * @brief Standby wakeup port select
  */
typedef enum {
	MD_PMU_STANDBY_PORT_SEL_PA0  = 0x0U,	/**< Wakeup by PA0 */
	MD_PMU_STANDBY_PORT_SEL_PA1  = 0x1U,	/**< Wakeup by PA1 */
	MD_PMU_STANDBY_PORT_SEL_PA2  = 0x2U,	/**< Wakeup by PA2 */
	MD_PMU_STANDBY_PORT_SEL_PA3  = 0x3U,	/**< Wakeup by PA3 */
	MD_PMU_STANDBY_PORT_SEL_NONE = 0xFU,	/**< Wakeup by other source */
} md_pmu_wakeup_port_t;

/**
  * @brief Standby wakeup level
  */
typedef enum {
	MD_PMU_STANDBY_LEVEL_HIGH = 0x0U,	/**< High level */
	MD_PMU_STANDBY_LEVEL_LOW  = 0x1U,	/**< Low level */
} md_pmu_wakeup_level_t;

/**
  * @brief LVD voltage select
  */
typedef enum {
	MD_PMU_LVD_VOL_SEL_2_0 = 0x0U,        /**< 2.0V ~ 2.05V */
	MD_PMU_LVD_VOL_SEL_2_1 = 0x1U,        /**< 2.1V ~ 2.15V */
	MD_PMU_LVD_VOL_SEL_2_2 = 0x2U,        /**< 2.2V ~ 2.25V */
	MD_PMU_LVD_VOL_SEL_2_4 = 0x3U,        /**< 2.4V ~ 2.45V */
	MD_PMU_LVD_VOL_SEL_2_6 = 0x4U,        /**< 2.6V ~ 2.65V */
	MD_PMU_LVD_VOL_SEL_2_8 = 0x5U,        /**< 2.8V ~ 2.85V */
	MD_PMU_LVD_VOL_SEL_3_0 = 0x6U,        /**< 3.0V ~ 3.05V */
	MD_PMU_LVD_VOL_SEL_3_6 = 0x7U,        /**< 3.6V ~ 3.65V */
	MD_PMU_LVD_VOL_SEL_4_0 = 0x8U,        /**< 4.0V ~ 4.05V */
	MD_PMU_LVD_VOL_SEL_4_6 = 0x9U,        /**< 4.6V ~ 4.65V */
	MD_PMU_LVD_VOL_SEL_2_3 = 0xAU,        /**< 2.3V ~ 2.35V */
	MD_PMU_LVD_VOL_SEL_EXT = 0xFU,        /**< Select external input. It must be 1.2V */
} md_pmu_lvd_voltage_sel_t;

/**
  * @brief LVD trigger mode
  */
typedef enum {
	MD_PMU_LVD_TRIGGER_RISING_EDGE    = 0x0U,        /**< Rising edge */
	MD_PMU_LVD_TRIGGER_FALLING_EDGE   = 0x1U,        /**< Falling edge */
	MD_PMU_LVD_TRIGGER_HIGH_LEVEL     = 0x2U,        /**< High level */
	MD_PMU_LVD_TRIGGER_LOW_LEVEL      = 0x3U,        /**< Low level */
	MD_PMU_LVD_TRIGGER_RISING_FALLING = 0x4U,        /**< Rising and falling edge */
} md_pmu_lvd_trigger_mode_t;

/**
  * @brief SRAM power supply select
  */
typedef enum {
	MD_PMU_PWRCR_SRAM_DISABLE = 0x0U,        /**< Cut the Power for SRAM0 and SRAM1 */
	MD_PUM_PWRCR_SRAM0_ONLY   = 0x1U,        /**< Supply Power for SRAM0*/
	MD_PUM_PWRCR_SRAM1_ONLY   = 0x2U,        /**< Supply Power for SRAM1*/
	MD_PMU_PWRCR_SRAM_ENABLE  = 0x3U,        /**< Supply Power for SRAM0 and SRAM1 */
} md_pmu_sram_power_supply_t;
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions PMU Public Functions
  * @{
  */
/** @defgroup MD_PMU_Public_Functions_Group2 CR
  * @{
  */
/**
  * @brief  Set pmu low power mode.
  * @param  mode: low power mode @see md_pmu_lp_mode_t
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_low_power_mode(md_pmu_lp_mode_t mode)
{
	MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, mode << PMU_CR_LPM_POSS);
}

/**
  * @brief  Get pmu low power mode.
  * @retval low power mode @see md_pmu_lp_mode_t
  */
__STATIC_INLINE uint32_t md_pmu_get_low_power_mode(void)
{
	return READ_BITS(PMU->CR, PMU_CR_LPM_MSK, PMU_CR_LPM_POSS);
}

/**
  * @brief  Clear wuf flag.
  * @retval None
  */
__STATIC_INLINE void md_pmu_clear_flag_cwuf(void)
{
	SET_BIT(PMU->CR, PMU_CR_CWUF_MSK);
}

/**
  * @brief  Clear standby flag.
  * @retval None
  */
__STATIC_INLINE void md_pmu_clear_flag_standby(void)
{
	SET_BIT(PMU->CR, PMU_CR_CSTANDBYF_MSK);
}

/**
  * @brief  Enable Standby mode wake up.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_standby_wkp(void)
{
	SET_BIT(PMU->CR, PMU_CR_WKPEN_MSK);
}

/**
  * @brief  Disable Standby mode wake up.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_standby_wkp(void)
{
	CLEAR_BIT(PMU->CR, PMU_CR_WKPEN_MSK);
}

/**
  * @brief  Check if Standby mode wake up are enabled or disabled.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_standby_wkp(void)
{
	return (READ_BIT(PMU->CR, PMU_CR_WKPEN_MSK) == (PMU_CR_WKPEN_MSK));
}

/**
  * @brief  Set port of wake up from standby mode.
  * @param  port: wake up port @see md_pmu_wakeup_port_t.
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_standby_wkp_port(md_pmu_wakeup_port_t port)
{
	MODIFY_REG(PMU->CR, PMU_CR_WKPS_MSK, port << PMU_CR_WKPS_POSS);
}

/**
  * @brief  Get port which can wake up chip from standby mode.
  * @retval Value for wakeup port @see md_pmu_wakeup_port_t.
  */
__STATIC_INLINE uint32_t md_pmu_get_standby_wkp_port(void)
{
	return READ_BITS(PMU->CR, PMU_CR_WKPS_MSK, PMU_CR_WKPS_POSS);
}

/**
  * @brief  Set the LDO output voltage.
  * @param  vol: LDO output voltage
  *             @arg 0: 1.5V
  *             @arg 1: 1.4V
  *             @arg 2: 1.3V
  *             @arg 4: 1.2V
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_ldo_lp_output(uint32_t vol)
{
	MODIFY_REG(PMU->CR, PMU_CR_LPVS_MSK, vol << PMU_CR_LPVS_POSS);
}

/**
  * @brief  Get the LDO output voltage.
  * @retval Output voltage:
  *           - 0: 1.5V
  *           - 1: 1.4V
  *           - 2: 1.3V
  *           - 4: 1.2V
  */
__STATIC_INLINE uint32_t md_pmu_get_ldo_lp_output(void)
{
	return READ_BITS(PMU->CR, PMU_CR_LPVS_MSK, PMU_CR_LPVS_POSS);
}

/**
  * @brief  Enable LDO low power mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_ldo_lp(void)
{
	SET_BIT(PMU->CR, PMU_CR_LPRUN_MSK);
}

/**
  * @brief  Disable LDO low power mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_ldo_lp(void)
{
	CLEAR_BIT(PMU->CR, PMU_CR_LPRUN_MSK);
}

/**
  * @brief  Check if LDO low power is enabled or disabled.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_stop_lp(void)
{
	return (READ_BIT(PMU->CR, PMU_CR_LPRUN_MSK) == (PMU_CR_LPRUN_MSK));
}

/**
  * @brief  Enable the LDO low power in stop mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_stop_ldo(void)
{
	SET_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);
}

/**
  * @brief  Disable the LDO low power in stop mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_stop_ldo(void)
{
	CLEAR_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);
}

/**
  * @brief  Check if LDO low power in stop mode is enabled or disabled.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_stop_ldo(void)
{
	return (READ_BIT(PMU->CR, PMU_CR_LPSTOP_MSK) == (PMU_CR_LPSTOP_MSK));
}

/**
  * @brief  Enable the LDO maintain out in stop mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_ldo_mt_out_in_stop(void)
{
	SET_BIT(PMU->CR, PMU_CR_MTSTOP_MSK);
}

/**
  * @brief  Disable the LDO maintain out in stop mode.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_ldo_mt_out_in_stop(void)
{
	SET_BIT(PMU->CR, PMU_CR_MTSTOP_MSK);
}

/**
  * @brief  Check if LDO maintain out in stop mode is enabled or disabled.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_ldo_mt_out_in_stop(void)
{
	return (READ_BIT(PMU->CR, PMU_CR_MTSTOP_MSK) == (PMU_CR_MTSTOP_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group3 SR
  * @{
  */
/**
  * @brief  Get Standby flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_standby(void)
{
	return (READ_BIT(PMU->SR, PMU_SR_STANDBYF_MSK) == PMU_SR_STANDBYF_MSK);
}

/**
  * @brief  Get Wakeup flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_wakeup(void)
{
	return (READ_BIT(PMU->SR, PMU_SR_WUF_MSK) == PMU_SR_WUF_MSK);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group4 LVDCR
  * @{
  */
/**
  * @brief  Get LVD Status flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_lvdo(void)
{
	return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDO_MSK) == PMU_LVDCR_LVDO_MSK);
}

/**
  * @brief  Enable the LVD filter .
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_lvd_filter(void)
{
	SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Disable the LVD filter .
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_lvd_filter(void)
{
	CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Check if the LVD filter is enable or disable.
  * @retval State for bit (1 or 0)
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_lvd_filter(void)
{
	return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK) == PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Set LVD Interrupt mode.
  * @param  mode: lvd interrupt mode @see md_pmu_lvd_trigger_mode_t.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_it_mode(md_pmu_lvd_trigger_mode_t mode)
{
	MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, mode << PMU_LVDCR_LVIFS_POSS);
}

/**
  * @brief  Get LVD Interrupt mode.
  * @retval value for lvd it mode.
  */
__STATIC_INLINE uint32_t md_pmu_get_lvd_it_mode(void)
{
	return READ_BITS(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, PMU_LVDCR_LVIFS_POSS);
}

/**
  * @brief  Set LVD voltage threshold value.
  * @param  value: threshold value @see md_pmu_lvd_voltage_sel_t.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_vol_threshold(md_pmu_lvd_voltage_sel_t value)
{
	MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, value << PMU_LVDCR_LVDS_POSS);
}

/**
  * @brief  Get LVD voltage threshold value.
  * @retval value for lvd voltage threshold @see md_pmu_lvd_voltage_sel_t.
  */
__STATIC_INLINE uint32_t md_pmu_get_lvd_vol_threshold(void)
{
	return (READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, PMU_LVDCR_LVDS_POSS));
}

/**
  * @brief  Set LVD interrupt flag clear bit.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_it_flag(void)
{
	SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
}

/**
  * @brief  Get LVD interrupt flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_lvd_it(void)
{
	return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDIF_MSK) == PMU_LVDCR_LVDIF_MSK);
}

/**
  * @brief  Enable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_lvd_it(void)
{
	SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Disable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_lvd_it(void)
{
	CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Check if LVD interrupt is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_lvd_it(void)
{
	return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK) == PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Enable LVD.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_lvd(void)
{
	SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
}

/**
  * @brief  Disable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_lvd(void)
{
	CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
}

/**
  * @brief  Check if LVD is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_lvd_is_enable(void)
{
	return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK) == PMU_LVDCR_LVDEN_MSK);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group5 PWRCR
  * @{
  */
/**
  * @brief  Enable BXCAN power.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_bxcan(void)
{
	SET_BIT(PMU->PWRCR, PMU_PWRCR_BXCAN_MSK);
}

/**
  * @brief  Disable BXCAN power.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_bxcan(void)
{
	CLEAR_BIT(PMU->PWRCR, PMU_PWRCR_BXCAN_MSK);
}

/**
  * @brief  Check if BXCAN power is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_bxcan(void)
{
	return (READ_BIT(PMU->PWRCR, PMU_PWRCR_BXCAN_MSK) == PMU_PWRCR_BXCAN_MSK);
}

/**
  * @brief  Set SRAM which can be supply power.
  * @param  sel: sram power supply @see md_pmu_sram_power_supply_t.
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_sram_power_supply(md_pmu_sram_power_supply_t sel)
{
	MODIFY_REG(PMU->PWRCR, PMU_PWRCR_SRAM_MSK, sel << PMU_PWRCR_SRAM_POSS);
}

/**
  * @brief  Get status which SRAM is supply power.
  * @retval Status for SRAM power supply @see md_pmu_sram_power_supply_t.
  */
__STATIC_INLINE uint32_t md_pmu_get_sram_power_supply(void)
{
	return READ_BITS(PMU->PWRCR, PMU_PWRCR_SRAM_MSK, PMU_PWRCR_SRAM_POSS);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group6 TWUR
  * @{
  */
/**
  * @brief  Set wakeup time for deep sleep.
  * @param  time: deep wakeup time.
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_deep_wakeup_time(uint16_t time)
{
	if (time > 0x7FF)
		return;

	MODIFY_REG(PMU->TWUR, PMU_TWUR_TWU_MSK, time << PMU_TWUR_TWU_POSS);
}

/**
  * @brief  Get deep wakeup time.
  * @retval Time for deep wakeup.
  */
__STATIC_INLINE uint32_t md_pmu_get_deep_wakeup_time(void)
{
	return READ_BITS(PMU->TWUR, PMU_TWUR_TWU_MSK, PMU_TWUR_TWU_POSS);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group7 VREFCR
  * @{
  */
/**
  * @brief  Enable vref.
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_vrefen(void)
{
	SET_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK);
}

/**
  * @brief  Disable vref.
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_vrefen(void)
{
	CLEAR_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK);
}

/**
  * @brief  Check if vref is enable or disable.
  * @retval State for 1 or 0.
  */
__STATIC_INLINE uint8_t md_pmu_is_enable_vrefen(void)
{
	return (READ_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK) == PMU_VREFCR_VREFEN_MSK);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group1 Initialization
  * @{
  */
__STATIC_INLINE__ void md_pmu_sleep()
{
	__WFI();
}

__STATIC_INLINE__ void md_pmu_sleep_deep()
{
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
}

extern void md_pmu_reset(void);
extern void md_pmu_stop1_enter(void);
extern void md_pmu_stop2_enter(void);
extern void md_pmu_standby_enter(md_pmu_wakeup_port_t port, md_pmu_wakeup_level_t level);
extern void md_pmu_lvd_config(md_pmu_lvd_voltage_sel_t sel, md_pmu_lvd_trigger_mode_t mode, type_func_t state);
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif
