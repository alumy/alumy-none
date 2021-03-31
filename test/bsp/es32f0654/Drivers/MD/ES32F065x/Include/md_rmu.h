/**
  *********************************************************************************
  *
  * @file    md_rmu.h
  * @brief   Header file of RMU module driver.
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

#ifndef __MD_RMU_H__
#define __MD_RMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_RMU RMU
  * @brief RMU micro driver
  * @{
  */
/**
  * @defgroup MD_RMU_Public_Types RMU Public Types
  * @{
  */
/**
  * @brief Standby wakeup port select
  */
typedef enum {
	MD_RMU_BORFLT_1 = 0x1U,	/**< 1 cycle  */
	MD_RMU_BORFLT_2 = 0x2U,	/**< 2 cycles */
	MD_RMU_BORFLT_3 = 0x3U,	/**< 3 cycles */
	MD_RMU_BORFLT_4 = 0x4U,	/**< 4 cycles */
	MD_RMU_BORFLT_5 = 0x5U,	/**< 5 cycles */
	MD_RMU_BORFLT_6 = 0x6U,	/**< 6 cycles */
	MD_RMU_BORFLT_7 = 0x7U,	/**< 7 cycles */
} md_rmu_bor_filter_t;

/**
  * @brief RMU BOR voltage
  */
typedef enum {
	MD_RMU_VOL_1_8 = 0x0U,	/**< 1.8V */
	MD_RMU_VOL_2_0 = 0x1U,	/**< 2.0V */
	MD_RMU_VOL_2_2 = 0x2U,	/**< 2.2V */
	MD_RMU_VOL_2_4 = 0x3U,	/**< 2.4V */
	MD_RMU_VOL_2_6 = 0x4U,	/**< 2.6V */
	MD_RMU_VOL_2_8 = 0x5U,	/**< 2.8V */
	MD_RMU_VOL_3_0 = 0x6U,	/**< 3.0V */
	MD_RMU_VOL_3_2 = 0x7U,	/**< 3.2V */
	MD_RMU_VOL_3_4 = 0x8U,	/**< 3.4V */
	MD_RMU_VOL_3_6 = 0x9U,	/**< 3.6V */
	MD_RMU_VOL_3_8 = 0xAU,	/**< 3.8v */
	MD_RMU_VOL_4_0 = 0xBU,	/**< 4.0V */
	MD_RMU_VOL_4_2 = 0xCU,	/**< 4.2V */
	MD_RMU_VOL_4_4 = 0xDU,	/**< 4.4V */
	MD_RMU_VOL_4_6 = 0xEU,	/**< 4.6V */
	MD_RMU_VOL_4_8 = 0xFU,	/**< 4.8V */
} md_rmu_bor_vol_t;

/**
  * @brief RMU reset status
  */
typedef enum {
	MD_RMU_RST_POR    = (1U << 0),	/**< POR */
	MD_RMU_RST_WAKEUP = (1U << 1),	/**< WAKEUP */
	MD_RMU_RST_BOR    = (1U << 2),	/**< BOR */
	MD_RMU_RST_NMRST  = (1U << 3),	/**< NMRST */
	MD_RMU_RST_IWDT   = (1U << 4),	/**< IWDT */
	MD_RMU_RST_WWDT   = (1U << 5),	/**< WWDT */
	MD_RMU_RST_LOCKUP = (1U << 6),	/**< LOCKUP */
	MD_RMU_RST_CHIP   = (1U << 7),	/**< CHIP */
	MD_RMU_RST_MCU    = (1U << 8),	/**< MCU */
	MD_RMU_RST_CPU    = (1U << 9),	/**< CPU */
	MD_RMU_RST_CFG    = (1U << 10),	/**< CFG */
	MD_RMU_RST_CFGERR = (1U << 16),	/**< CFG Error */
	MD_RMU_RST_ALL    = (0xFFFFFU),	/**< ALL */
} md_rmu_state_t;

/**
  * @brief RMU periperal select bit
  * @verbatim
      In this module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F065x series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> BS16T0
      TIMER2 ----> GP16C2T0
      TIMER3 ----> GP16C2T1
      TIMER4 ----> BS16T1
      TIMER5 ----> BS16T2
      TIMER6 ----> GP16C4T0
      TIMER7 ----> BS16T3
     
      2. For ES32F033x/ES32F093x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> BS16T0
      TIMER2 ----> GP16C2T0
      TIMER3 ----> GP16C2T1
      TIMER4 ----> BS16T1
      TIMER5 ----> BS16T2
      TIMER6 ----> GP16C4T1
      TIMER7 ----> BS16T3
    @endverbatim
  */
typedef enum {
	MD_RMU_PERH_GPIO    = (1U << 0),			/**< AHB1: GPIO */
	MD_RMU_PERH_CRC     = (1U << 1),			/**< AHB1: CRC */
	MD_RMU_PERH_CALC    = (1U << 2),			/**< AHB1: CALC */
	MD_RMU_PERH_CRYPT   = (1U << 3),			/**< AHB1: CRYPT */
	MD_RMU_PERH_TRNG    = (1U << 4),			/**< AHB1: TRNG */
	MD_RMU_PERH_PIS     = (1U << 5),			/**< AHB1: PIS */
	MD_RMU_PERH_CHIP    = (1U << 0)  | (1U << 27),	/**< AHB2: CHIP */
	MD_RMU_PERH_CPU     = (1U << 1)  | (1U << 27),	/**< AHB2: CPU */
	MD_RMU_PERH_TIMER0  = (1U << 0)  | (1U << 28),	/**< APB1: TIMER0 */
	MD_RMU_PERH_TIMER1  = (1U << 1)  | (1U << 28),	/**< APB1: TIMER1 */
	MD_RMU_PERH_TIMER2  = (1U << 2)  | (1U << 28),	/**< APB1: TIMER2 */
	MD_RMU_PERH_TIMER3  = (1U << 3)  | (1U << 28),	/**< APB1: TIMER3 */
	MD_RMU_PERH_TIMER4  = (1U << 4)  | (1U << 28),	/**< APB1: TIMER4 */
	MD_RMU_PERH_TIMER5  = (1U << 5)  | (1U << 28),	/**< APB1: TIMER5 */
	MD_RMU_PERH_TIMER6  = (1U << 6)  | (1U << 28),	/**< APB1: TIMER6 */
	MD_RMU_PERH_TIMER7  = (1U << 7)  | (1U << 28),	/**< APB1: TIMER7 */
	MD_RMU_PERH_UART0   = (1U << 8)  | (1U << 28),	/**< APB1: UART0 */
	MD_RMU_PERH_UART1   = (1U << 9)  | (1U << 28),	/**< APB1: UART1 */
	MD_RMU_PERH_UART2   = (1U << 10) | (1U << 28),	/**< APB1: UART2 */
	MD_RMU_PERH_UART3   = (1U << 11) | (1U << 28),	/**< APB1: UART3 */
	MD_RMU_PERH_USART0  = (1U << 12) | (1U << 28),	/**< APB1: EUART0 */
	MD_RMU_PERH_USART1  = (1U << 13) | (1U << 28),	/**< APB1: EUART1 */
	MD_RMU_PERH_SPI0    = (1U << 16) | (1U << 28),	/**< APB1: SPI0 */
	MD_RMU_PERH_SPI1    = (1U << 17) | (1U << 28),	/**< APB1: SPI1 */
	MD_RMU_PERH_SPI2    = (1U << 18) | (1U << 28),	/**< APB1: SPI2 */
	MD_RMU_PERH_I2C0    = (1U << 20) | (1U << 28),	/**< APB1: I2C0 */
	MD_RMU_PERH_I2C1    = (1U << 21) | (1U << 28),	/**< APB1: I2C1 */
	MD_RMU_PERH_CAN0    = (1U << 24) | (1U << 28),	/**< APB1: CAN0 */
	MD_RMU_PERH_LPTIM0  = (1U << 0)  | (1U << 29),	/**< APB2: LPTIM0 */
	MD_RMU_PERH_LPUART0 = (1U << 2)  | (1U << 29),	/**< APB2: LPUART */
	MD_RMU_PERH_ADC0    = (1U << 4)  | (1U << 29),	/**< APB2: ADC0 */
	MD_RMU_PERH_ADC1    = (1U << 5)  | (1U << 29),	/**< APB2: ADC1 */
	MD_RMU_PERH_ACMP0   = (1U << 6)  | (1U << 29),	/**< APB2: ACMP0 */
	MD_RMU_PERH_ACMP1   = (1U << 7)  | (1U << 29),	/**< APB2: ACMP1 */
	MD_RMU_PERH_OPAMP   = (1U << 8)  | (1U << 29),	/**< APB2: OPAMP */
	MD_RMU_PERH_DAC0    = (1U << 9)  | (1U << 29),	/**< APB2: DAC0 */
	MD_RMU_PERH_WWDT    = (1U << 12) | (1U << 29),	/**< APB2: WWDT */
	MD_RMU_PERH_LCD     = (1U << 13) | (1U << 29),	/**< APB2: LCD */
	MD_RMU_PERH_IWDT    = (1U << 14) | (1U << 29),	/**< APB2: IWDT */
	MD_RMU_PERH_RTC     = (1U << 15) | (1U << 29),	/**< APB2: RTC */
	MD_RMU_PERH_TSENSE  = (1U << 16) | (1U << 29),	/**< APB2: TSENSE */
	MD_RMU_PERH_BKPC    = (1U << 17) | (1U << 29),	/**< APB2: BKPC */
	MD_RMU_PERH_BKPRAM  = (1U << 18) | (1U << 29),	/**< APB2: BKPRAM */
} md_rmu_peripheral_t;
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions RMU Public Functions
  * @{
  */
/** @defgroup MD_RMU_Public_Functions_Group2 CR
  * @{
  */
/**
  * @brief  Set BOR threshold voltage.
  * @param  vol Voltage for BOR threshold.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor_voltage(md_rmu_bor_vol_t vol)
{
	MODIFY_REG(RMU->CR, RMU_CR_BORVS_MSK, vol << RMU_CR_BORVS_POSS);
}

/**
  * @brief  Get BOR threshold voltage.
  * @retval Voltage for BOR threshold.
  */
__STATIC_INLINE uint32_t md_rmu_get_bor_voltage(void)
{
	return READ_BITS(RMU->CR, RMU_CR_BORVS_MSK, RMU_CR_BORVS_POSS);
}

/**
  * @brief  Set period for BOR filter.
  * @param  period for BOR filter.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor_filter_period(md_rmu_bor_filter_t period)
{
	MODIFY_REG(RMU->CR, RMU_CR_BORFLT_MSK, period << RMU_CR_BORFLT_POSS);
}

/**
  * @brief  Enable rmu BOR.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bor(void)
{
	SET_BIT(RMU->CR, RMU_CR_BOREN_MSK);
}

/**
  * @brief  Disable rmu BOR.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_disable_bor(void)
{
	CLEAR_BIT(RMU->CR, RMU_CR_BOREN_MSK);
}

/**
  * @brief  Check if rmu is enable bor.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_enable_bor(void)
{
	return (READ_BIT(RMU->CR, RMU_CR_BOREN_MSK) == (RMU_CR_BOREN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group3 RSTSR
  * @{
  */
/**
  * @brief  Get rmu configuration byte flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cfgerr(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CFGERR_MSK) == (RMU_RSTSR_CFGERR_MSK));
}

/**
  * @brief  Get rmu configuration byte reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cfg(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CFG_MSK) == (RMU_RSTSR_CFG_MSK));
}

/**
  * @brief  Get rmu cpu reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cpu(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CPU_MSK) == (RMU_RSTSR_CPU_MSK));
}

/**
  * @brief  Get rmu mcu reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_mcu(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_MCU_MSK) == (RMU_RSTSR_MCU_MSK));
}

/**
  * @brief  Get rmu chip reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_rmu(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CHIP_MSK) == (RMU_RSTSR_CHIP_MSK));
}

/**
  * @brief  Get rmu lockup reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_lockup(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_LOCKUP_MSK) == (RMU_RSTSR_LOCKUP_MSK));
}

/**
  * @brief  Get rmu wwdt reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_wwdt(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_WWDT_MSK) == (RMU_RSTSR_WWDT_MSK));
}

/**
  * @brief  Get rmu iwdt reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_iwdt(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_IWDT_MSK) == (RMU_RSTSR_IWDT_MSK));
}

/**
  * @brief  Get rmu nmrst reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_nmrst(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_NMRST_MSK) == (RMU_RSTSR_NMRST_MSK));
}

/**
  * @brief  Get rmu bor reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_bor(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_BOR_MSK) == (RMU_RSTSR_BOR_MSK));
}

/**
  * @brief  Get rmu wake up reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_wakeup(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_WAKEUP_MSK) == (RMU_RSTSR_WAKEUP_MSK));
}

/**
  * @brief  Get rmu por reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_por(void)
{
	return (READ_BIT(RMU->RSTSR, RMU_RSTSR_POR_MSK) == (RMU_RSTSR_POR_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group4 CRSTSR
  * @{
  */
/**
  * @brief  Clear rmu configuration byte reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_cfg(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CFG_MSK);
}

/**
  * @brief  Clear rmu cpu reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_cpu(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CPU_MSK);
}

/**
  * @brief  Clear rmu mcu reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_mcu(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_MCU_MSK);
}

/**
  * @brief  Clear rmu chip reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_chip(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CHIP_MSK);
}

/**
  * @brief  Clear rmu lockup reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_lockup(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_LOCKUP_MSK);
}

/**
  * @brief  Clear rmu wwdt reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_wwdt(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_WWDT_MSK);
}

/**
  * @brief  Clear rmu iwdt reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_iwdt(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_IWDT_MSK);
}

/**
  * @brief  Clear rmu nmrst reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_nmrst(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_NMRST_MSK);
}

/**
  * @brief  Clear rmu bor reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_bor(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_BOR_MSK);
}

/**
  * @brief  Clear rmu wakeup reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_wakeup(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_WAKEUP_MSK);
}

/**
  * @brief  Clear rmu por reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_por(void)
{
	SET_BIT(RMU->CRSTSR, RMU_CRSTSR_POR_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group5 AHB1RSTR
  * @{
  */
/**
  * @brief  Reset pis periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_pis_reset(void)
{
	SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_PISRST_MSK);
}

/**
  * @brief  Reset trng periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_trng_reset(void)
{
	SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_TRNGRST_MSK);
}

/**
  * @brief  Reset crypt periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_crypt_reset(void)
{
	SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CRYPTRST_MSK);
}

/**
  * @brief  Reset calc periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_calc_reset(void)
{
	SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CALCRST_MSK);
}

/**
  * @brief  Reset crc periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_crc_reset(void)
{
	SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CRCRST_MSK);
}

/**
  * @brief  Reset gpio periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_gpio_reset(void)
{
	SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_GPIORST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group6 AHB2RSTR
  * @{
  */
/**
  * @brief  Reset kernel processor which depend on AHB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_cpu_reset(void)
{
	SET_BIT(RMU->AHB2RSTR, RMU_AHB2RSTR_CPURST_MSK);
}

/**
  * @brief  Reset full chip .
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_chip_reset(void)
{
	SET_BIT(RMU->AHB2RSTR, RMU_AHB2RSTR_CHIPRST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group7 APB1RSTR
  * @{
  */
/**
  * @brief  Reset can0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_can0_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_CAN0RST_MSK);
}

/**
  * @brief  Reset i2c1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_i2c1_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_I2C1RST_MSK);
}

/**
  * @brief  Reset i2c0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_i2c0_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_I2C0RST_MSK);
}

/**
  * @brief  Reset spi2 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_spi2_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_SPI2RST_MSK);
}

/**
  * @brief  Reset spi1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_spi1_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_SPI1RST_MSK);
}

/**
  * @brief  Reset spi0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_spi0_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_SPI0RST_MSK);
}

/**
  * @brief  Reset usart1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_usart1_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_USART1RST_MSK);
}


/**
  * @brief  Reset usart0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_usart0_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_USART0RST_MSK);
}

/**
  * @brief  Reset uart3 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart3_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART3RST_MSK);
}

/**
  * @brief  Reset uart2 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart2_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART2RST_MSK);
}

/**
  * @brief  Reset uart1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart1_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART1RST_MSK);
}

/**
  * @brief  Reset uart0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_uart0_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_UART0RST_MSK);
}

/**
  * @brief  Reset timer7 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer7_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM7RST_MSK);
}

/**
  * @brief  Reset timer6 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer6_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM6RST_MSK);
}

/**
  * @brief  Reset timer5 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer5_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM5RST_MSK);
}

/**
  * @brief  Reset timer4 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer4_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM4RST_MSK);
}

/**
  * @brief  Reset timer3 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer3_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM3RST_MSK);
}

/**
  * @brief  Reset timer2 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer2_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM2RST_MSK);
}

/**
  * @brief  Reset timer1 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer1_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM1RST_MSK);
}

/**
  * @brief  Reset timer0 periperal which depend on APB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_timer0_reset(void)
{
	SET_BIT(RMU->APB1RSTR, RMU_APB1RSTR_TIM0RST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group8 APB2RSTR
  * @{
  */
/**
  * @brief  Reset bkpram periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bkpram_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_BKPRAMRST_MSK);
}

/**
  * @brief  Reset bkpc periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bkpc_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_BKPCRST_MSK);
}

/**
  * @brief  Reset TSENSE periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_tsense_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_TSENSERST_MSK);
}

/**
  * @brief  Reset rtc periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_rtc_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_RTCRST_MSK);
}

/**
  * @brief  Reset iwdt periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_iwdt_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_IWDTRST_MSK);
}

/**
  * @brief  Reset lcd periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_lcdrst_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_LCDRST_MSK);
}

/**
  * @brief  Reset wwdt periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_wwdt_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_WWDTRST_MSK);
}

/**
  * @brief  Reset acmp1 periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_acmp1_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_ACMP1RST_MSK);
}

/**
  * @brief  Reset acmp0 periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_acmp0_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_ACMP0RST_MSK);
}

/**
  * @brief  Reset adc0 periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_adc0_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_ADC0RST_MSK);
}

/**
  * @brief  Reset lpuart0 periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_lpuart0_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_LPUART0RST_MSK);
}

/**
  * @brief  Reset lptim0 periperal which depend on APB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_lptim0_reset(void)
{
	SET_BIT(RMU->APB2RSTR, RMU_APB2RSTR_LPTIM0RST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_rmu_reset(void);
extern void md_rmu_bor_config(md_rmu_bor_filter_t flt, md_rmu_bor_vol_t vol, type_func_t state);
extern uint32_t md_rmu_get_reset_status(md_rmu_state_t state);
extern void md_rmu_clear_reset_status(md_rmu_state_t state);
extern void md_rmu_reset_periperal(md_rmu_peripheral_t perh);
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
