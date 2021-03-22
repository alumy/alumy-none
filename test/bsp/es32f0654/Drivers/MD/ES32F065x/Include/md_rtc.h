 /**
  *********************************************************************************
  *
  * @file    md_rtc.h
  * @brief   Header file of RTC module driver.
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

#ifndef __MD_RTC_H__
#define __MD_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_RTC RTC
  * @brief RTC micro driver
  * @{
  */

/** @defgroup MD_RTC_Public_Types RTC Public Types
  * @{
  */

/**
  * @brief Hours format
  */
typedef enum {
	MD_RTC_HOUR_FORMAT_24 = 0x0U,	/**< 24-hours format */
	MD_RTC_HOUR_FORMAT_12 = 0x1U,	/**< 12-hours format */
} md_rtc_hour_format_t;

/**
  * @brief Output mode
  */
typedef enum {
	MD_RTC_ALARMOUT_DISABLE = 0x0U,	/**< Output disabled */
	MD_RTC_ALARMOUT_ALMA    = 0x1U,	/**< Alarm A output enabled */
	MD_RTC_ALARMOUT_ALMB    = 0x2U,	/**< Alarm B output enabled */
	MD_RTC_ALARMOUT_WAKEUP  = 0x3U,	/**< Wakeup output enabled */
} md_rtc_alarm_output_t;

/**
  * @brief Output polarity
  */
typedef enum {
	MD_RTC_OUTPUT_POLARITY_HIGH = 0x0U,	/**< Polarity is high */
	MD_RTC_OUTPUT_POLARITY_LOW  = 0x1U,	/**< Polarity is low */
} md_rtc_output_polarity_t;

/**
  * @brief Initialization structure
  */
typedef struct {
	md_rtc_hour_format_t hour_format;	  /**< Hours format */
	uint32_t asynch_pre_div;		  /**< Asynchronous predivider value */
	uint32_t synch_pre_div;			  /**< Synchronous predivider value */
	md_rtc_alarm_output_t output;		  /**< Output signal type */
	md_rtc_output_polarity_t output_polarity; /**< Output polarity */
} md_rtc_init_t;

/**
  * @brief Wakeup clock
  */
typedef enum {
	MD_RTC_WAKEUP_CLOCK_DIV_16   = 0x0U,	/**< RTC/16 */
	MD_RTC_WAKEUP_CLOCK_DIV_8    = 0x1U,	/**< RTC/8 */
	MD_RTC_WAKEUP_CLOCK_DIV_4    = 0x2U,	/**< RTC/4 */
	MD_RTC_WAKEUP_CLOCK_DIV_2    = 0x3U,	/**< RTC/2 */
	MD_RTC_WAKEUP_CLOCK_1HZ      = 0x4U,	/**< 1Hz */
	MD_RTC_WAKEUP_CLOCK_1HZ_PULS = 0x6U,	/**< 1Hz and WUT + 65536 */
} md_rtc_wakeup_clock_t;

/**
  * @brief Clock output
  */
typedef enum {
	 MD_RTC_CLOCK_OUTPUT_32768 = 0x0U,	/**< output is 32768 Hz */
	 MD_RTC_CLOCK_OUTPUT_1024  = 0x1U,	/**< output is 1024 Hz */
	 MD_RTC_CLOCK_OUTPUT_32    = 0x2U,	/**< output is 32 Hz */
	 MD_RTC_CLOCK_OUTPUT_1     = 0x3U,	/**< output is 1 Hz */
	 MD_RTC_CLOCK_OUTPUT_CAL_1 = 0x4U,	/**< 1Hz after calibration */
	 MD_RTC_CLOCK_OUTPUT_EXA_1 = 0x5U,	/**< Exact 1Hz */
} md_rtc_clock_output_t;

/**
  * @brief Alarm mask 
  */
typedef enum {
	MD_RTC_ALARM_MASK_NONE     = 0x0U,		/**< Mask is disable */
	MD_RTC_ALARM_MASK_WEEK_DAY = (1U << 30),	/**< Mask week or day */
	MD_RTC_ALARM_MASK_HOUR     = (1U << 23),	/**< Mask hour */
	MD_RTC_ALARM_MASK_MINUTE   = (1U << 15),	/**< Mask minute */
	MD_RTC_ALARM_MASK_SECOND   = (1U << 7),		/**< Mask second */
	MD_RTC_ALARM_MASK_ALL      = 0x40808080U,	/**< Mask all */ 	
} md_rtc_alarm_mask_t;

/**
  * @brief Time structure
  */
typedef struct {
	uint8_t hour;		/**< Hours */
	uint8_t minute;		/**< Minutes */
	uint8_t second;		/**< Seconds */
	uint16_t sub_sec;	/**< Sub-seconds */
} md_rtc_time_t;

/**
  * @brief Date structure
  */
typedef struct {
	uint8_t week;	/**< Weeks */
	uint8_t day;	/**< days */
	uint8_t month;	/**< months */
	uint8_t year;	/**< years */
} md_rtc_date_t;

/**
  * @brief Data format
  */
typedef enum {
	MD_RTC_FORMAT_DEC = 0x0U,	/**< DEC format */
	MD_RTC_FORMAT_BCD = 0x1U,	/**< BCD format */
} md_rtc_format_t;

/**
  * @brief Index of alarm
  */
typedef enum {
	MD_RTC_ALARM_A = 0x0U,	/**< Alarm-A */
	MD_RTC_ALARM_B = 0x1U,	/**< Alarm-B */
} md_rtc_alarm_idx_t;

/**
  * @brief Alarm sub-second mask
  */
typedef enum {
	MD_RTC_ALARM_SS_MASK_NONE  = 0xFU,	/**< Mask is disable */
	MD_RTC_ALARM_SS_MASK_14_1  = 0x1U,	/**< Mask bit(1-14) */
	MD_RTC_ALARM_SS_MASK_14_2  = 0x2U,	/**< Mask bit(2-14) */
	MD_RTC_ALARM_SS_MASK_14_3  = 0x3U,	/**< Mask bit(3-14) */
	MD_RTC_ALARM_SS_MASK_14_4  = 0x4U,	/**< Mask bit(4-14) */
	MD_RTC_ALARM_SS_MASK_14_5  = 0x5U,	/**< Mask bit(5-14) */
	MD_RTC_ALARM_SS_MASK_14_6  = 0x6U,	/**< Mask bit(6-14) */
	MD_RTC_ALARM_SS_MASK_14_7  = 0x7U,	/**< Mask bit(7-14) */
	MD_RTC_ALARM_SS_MASK_14_8  = 0x8U,	/**< Mask bit(8-14) */
	MD_RTC_ALARM_SS_MASK_14_9  = 0x9U,	/**< Mask bit(9-14) */
	MD_RTC_ALARM_SS_MASK_14_10 = 0xAU,	/**< Mask bit(10-14) */
	MD_RTC_ALARM_SS_MASK_14_11 = 0xBU,	/**< Mask bit(11-14) */
	MD_RTC_ALARM_SS_MASK_14_12 = 0xCU,	/**< Mask bit(12-14) */
	MD_RTC_ALARM_SS_MASK_14_13 = 0xDU,	/**< Mask bit(13-14) */
	MD_RTC_ALARM_SS_MASK_14    = 0xEU,	/**< Mask bit14 */
	MD_RTC_ALARM_SS_MASK_ALL   = 0x0U,	/**< Mask bit(0-14) */
} md_rtc_sub_second_mask_t;

/**
  * @brief Alarm select week or day */
typedef enum {
	MD_RTC_SELECT_DAY  = 0x0U,	/**< Alarm select day */
	MD_RTC_SELECT_WEEK = 0x1U,	/**< Alarm select week */
} md_rtc_week_day_sel_t;

/**
  * @brief Alarm structure
  */
typedef struct {
	md_rtc_alarm_idx_t idx;			/**< Index of alarm */
	md_rtc_time_t time;			/**< Time structure */
	uint32_t mask;				/**< Alarm mask */
	md_rtc_sub_second_mask_t ss_mask;	/**< Alarm sub-second mask */
	md_rtc_week_day_sel_t sel;		/**< Select week or day */

	union {
		uint8_t week;			/**< Alarm select week */
		uint8_t day;			/**< Alarm select day */
	};
} md_rtc_alarm_t;

/**
  * @brief Time stamp signel select
  */
typedef enum {
	MD_RTC_TS_SIGNAL_SEL_TAMPER0 = 0x0U,	/**< Select tamper0 */
	MD_RTC_TS_SIGNAL_SEL_TAMPER1 = 0x1U,	/**< Select tamper1 */
} md_rtc_ts_signal_sel_t;

/**
  * @brief Time stamp trigger style
  */
typedef enum {
	MD_RTC_TS_RISING_EDGE  = 0x0U,	/**< Rising edge */
	MD_RTC_TS_FALLING_EDGE = 0x1U,	/**< Falling edge */
} md_rtc_ts_trigger_style_t;

/**
  * @brief Index of tamper
  */
typedef enum {
	MD_RTC_TAMPER_0 = 0x0U,	/**< Tamper0 */
	MD_RTC_TAMPER_1 = 0x1U,	/**< Tamper1 */
} md_rtc_tamper_idx_t;

/**
  * @brief Tamper trigger type
  */
typedef enum {
	MD_RTC_TAMPER_TRIGGER_LOW  = 0x0U,	/**< High trigger */
	MD_RTC_TAMPER_TRIGGER_HIGH = 0x1U,	/**< Low trigger */
} md_rtc_tamper_trigger_t;

/**
  * @brief Tamper sampling frequency
  */
typedef enum {
	MD_RTC_TAMPER_SAMPLING_FREQ_32768 = 0x0U,	/**< RTCCLK / 32768 */
	MD_RTC_TAMPER_SAMPLING_FREQ_16384 = 0x1U,	/**< RTCCLK / 16384 */
	MD_RTC_TAMPER_SAMPLING_FREQ_8192  = 0x2U,	/**< RTCCLK / 8192 */
	MD_RTC_TAMPER_SAMPLING_FREQ_4096  = 0x3U,	/**< RTCCLK / 4096 */
	MD_RTC_TAMPER_SAMPLING_FREQ_2048  = 0x4U,	/**< RTCCLK / 2048 */
	MD_RTC_TAMPER_SAMPLING_FREQ_1024  = 0x5U,	/**< RTCCLK / 1024 */
	MD_RTC_TAMPER_SAMPLING_FREQ_512   = 0x6U,	/**< RTCCLK / 512 */
	MD_RTC_TAMPER_SAMPLING_FREQ_256   = 0x7U,	/**< RTCCLK / 256 */
} md_rtc_tamper_sampling_freq_t;

/**
  * @brief Tamper filter time
  */
typedef enum {
	MD_RTC_TAMPER_DURATION_1 = 0x0U,	/**< Duration 1 sampling */
	MD_RTC_TAMPER_DURATION_2 = 0x1U,	/**< Duration 2 sampling */
	MD_RTC_TAMPER_DURATION_4 = 0x2U,	/**< Duration 4 sampling */
	MD_RTC_TAMPER_DURATION_8 = 0x3U,	/**< Duration 8 sampling */
} md_rtc_tamper_duration_t;

/**
  * @brief Tamper structure
  */
typedef struct {
	md_rtc_tamper_idx_t idx;		/**< Index of tamper */
	md_rtc_tamper_trigger_t trig;		/**< Trigger type */
	md_rtc_tamper_sampling_freq_t freq;	/**< Sampling frequency */
	md_rtc_tamper_duration_t dur;		/**< Filter time */
	type_func_t ts;				/**< Enable/Disable trigger time stamp event */
} md_rtc_tamper_t;
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Macro RTC Public Macros
  * @{
  */
#define MD_RTC_UNLOCK()		(WRITE_REG(RTC->WPR, 0x55AAAA55U))
#define MD_RTC_LOCK()		(WRITE_REG(RTC->WPR, 0x0U))
#define MD_RTC_CALI_UNLOCK()	(WRITE_REG(RTC->CALWPR, 0x699655AAU))
#define MD_RTC_CALI_LOCK()	(WRITE_REG(RTC->CALWPR, 0x0U))
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions RTC Public Functions
  * @{
  */
/** @defgroup MD_RTC_Public_Functions_Group2 CON
  * @{
  */
/**
  * @brief  Enable RTC
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_go(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_GO_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if RTC is going.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_go(void)
{
	return (uint32_t)READ_BITS(RTC->CON, RTC_CON_GO_MSK, RTC_CON_GO_POS);
}

/**
  * @brief  Enable RTC alarm A
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_alarm_a(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_ALMAEN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC alarm A
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_alarm_a(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_ALMAEN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if alarmA is enable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_alarm_a(void)
{
	return (uint32_t)READ_BITS(RTC->CON, RTC_CON_ALMAEN_MSK, RTC_CON_ALMAEN_POS);
}

/**
  * @brief  Enable RTC alarm B
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_alarm_b(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_ALMBEN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC alarm B
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_alarm_b(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_ALMBEN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if alarmB is enable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_alarm_b(void)
{
	return (uint32_t)READ_BITS(RTC->CON, RTC_CON_ALMBEN_MSK, RTC_CON_ALMBEN_POS);
}

/**
  * @brief  Set Hours format (24 hour/day or 12 hour/day format)
  * @param  format: This parameter can be one of the following values:
  *         @arg @ref MD_RTC_HOUR_FORMAT_24
  *         @arg @ref MD_RTC_HOUR_FORMAT_12
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_hour_format(uint32_t format)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_HFM_MSK, format << RTC_CON_HFM_POS);
	MD_RTC_LOCK();
}


/**
  * @brief  Get Hours format (24 hour/day or 12 hour/day format)
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_RTC_HOUR_FORMAT_24
  *         @arg @ref MD_RTC_HOUR_FORMAT_12
  */
__STATIC_INLINE uint32_t md_rtc_get_hour_format(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_HFM_MSK, RTC_CON_HFM_POS));
}

/**
  * @brief  Enable Bypass the shadow registers
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_shadow_reg_bypass(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_SHDBP_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable Bypass the shadow registers
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_shadow_reg_bypass(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_SHDBP_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if Shadow registers bypass is enabled or not.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_shadow_reg_bypass(void)
{
	return (READ_BIT(RTC->CON, RTC_CON_SHDBP_MSK) == (RTC_CON_SHDBP_MSK));
}

/**
  * @brief  Enable timestamp
  * @retval None
  */
__STATIC_INLINE void md_rtc_ts_enable(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_TSEN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable timestamp
  * @retval None
  */
__STATIC_INLINE void md_rtc_ts_disable(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_TSEN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if timestamp is enabled or not.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_ts(void)
{
	return (READ_BIT(RTC->CON, RTC_CON_TSEN_MSK) == (RTC_CON_TSEN_MSK));
}

/**
  * @brief  Set Time-stamp event active edge
  * @param  edge This parameter can be one of the following values:
  *         @arg @ref MD_RTC_TS_RISING_EDGE
  *         @arg @ref MD_RTC_TS_FALLING_EDGE
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_ts_active_edge(uint32_t edge)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_TSSEL_MSK, edge << RTC_CON_TSSEL_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Time-stamp event active edge
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_RTC_TS_RISING_EDGE
  *         @arg @ref MD_RTC_TS_FALLING_EDGE
  */
__STATIC_INLINE uint32_t md_rtc_get_ts_active_edge(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_TSSEL_MSK, RTC_CON_TSSEL_POS));
}

/**
  * @brief  Set timestamp Pin
  * @param  sel: specifies the RTC TimeStamp Pin.
  *         This parameter can be one of the @ref md_rtc_ts_signal_sel_t
  *            
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_ts_pin(md_rtc_ts_signal_sel_t sel)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_TSPIN_MSK , sel << RTC_CON_TSPIN_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get timestamp Pin
  * @retval Returned value can be one of the @ref md_rtc_ts_signal_sel_t
  *            
  */
__STATIC_INLINE uint32_t md_rtc_get_ts_pin(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_TSPIN_MSK, RTC_CON_TSPIN_POS));
}

/**
  * @brief  Add 1 hour (summer time change)
  * @retval None
  */
__STATIC_INLINE void md_rtc_time_inc_hour(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_ADD1H_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Subtract 1 hour (winter time change)
  * @retval None
  */
__STATIC_INLINE void md_rtc_time_dec_hour(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_SUB1H_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Memorize whether the daylight saving time change has been performed
  * @param  wstime specifies the daylight, 0-Winter, 1-Summer.
  * @retval None
  */
__STATIC_INLINE void md_rtc_time_daylight_select(uint32_t wstime)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_DSTS_MSK, wstime << RTC_CON_DSTS_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get current daylight
  * @retval Returned value can be one of the following values:
  *           - 0: Winter
  *           - 1: Summer
  */
__STATIC_INLINE uint32_t md_rtc_get_current_daylight(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_DSTS_MSK, RTC_CON_DSTS_POS));
}

/**
  * @brief  Enable Wakeup timer 
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_wute(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_WUTE_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable Wakeup timer 
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_wute(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_WUTE_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if wakeup timer is enable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_wute(void)
{
	return (uint32_t)READ_BITS(RTC->CON, RTC_CON_WUTE_MSK, RTC_CON_WUTE_POS);
}

/**
  * @brief  Select Wakeup clock
  * @param  clock: This parameter can be one of the @ref md_rtc_wakeup_clock_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_wakeup_clock(md_rtc_wakeup_clock_t clock)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_WUCKS_MSK, clock << RTC_CON_WUCKS_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Wakeup clock
  * @retval Returned value can be one of the @ref md_rtc_wakeup_clock_t

  */
__STATIC_INLINE uint32_t md_rtc_get_wakeup_clock(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_WUCKS_MSK, RTC_CON_WUCKS_POSS));
}

/**
  * @brief  Clock output enable 
  * @retval None
  */
__STATIC_INLINE void md_rtc_clock_output_enable(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->CON, RTC_CON_CKOE_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clock output disable 
  * @retval None
  */
__STATIC_INLINE void md_rtc_clock_output_disable(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_CKOE_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check if clock output is enable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_clock_output(void)
{
	return (uint32_t)READ_BITS(RTC->CON, RTC_CON_CKOE_MSK, RTC_CON_CKOE_POS);
}

/**
  * @brief  Select the output clock
  * @param  outputclk This parameter can be one of the @ref md_rtc_clock_output_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_output_clock(md_rtc_clock_output_t outputclk)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_CKOS_MSK, outputclk << RTC_CON_CKOS_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get the output clock
  * @retval Returned value can be one of the the @ref md_rtc_clock_output_t
  */
__STATIC_INLINE uint32_t md_rtc_get_output_clock(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_CKOS_MSK, RTC_CON_CKOS_POSS));
}

/**
  * @brief  Select the flag to be routed to RTC_ALARM output
  * @param  almoutput This parameter can be one of the following values:
  *         @arg @ref MD_RTC_ALARMOUT_DISABLE
  *         @arg @ref MD_RTC_ALARMOUT_ALMA
  *         @arg @ref MD_RTC_ALARMOUT_ALMB
  *         @arg @ref MD_RTC_ALARMOUT_WAKEUP
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_event_out(md_rtc_alarm_output_t almoutput)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_EOS_MSK, almoutput << RTC_CON_EOS_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get the flag to be routed to RTC_ALARM output
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_RTC_ALARMOUT_DISABLE
  *         @arg @ref MD_RTC_ALARMOUT_ALMA
  *         @arg @ref MD_RTC_ALARMOUT_ALMB
  *         @arg @ref MD_RTC_ALARMOUT_WAKEUP
  */
__STATIC_INLINE uint32_t md_rtc_get_event_out(void)
{
  return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_EOS_MSK, RTC_CON_EOS_POSS));
}

/**
  * @brief  Set Output polarity (pin is low when ALRAF/ALRBF/WUTF is asserted)
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref MD_RTC_OUTPUT_POLARITY_HIGH
  *         @arg @ref MD_RTC_OUTPUT_POLARITY_LOW
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_out_put_polarity(md_rtc_output_polarity_t polarity)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_POL_MSK, polarity << RTC_CON_POL_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Output polarity
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_RTC_OUTPUT_POLARITY_HIGH
  *         @arg @ref MD_RTC_OUTPUT_POLARITY_LOW
  */
__STATIC_INLINE uint32_t md_rtc_get_out_put_polarity(void)
{
	return (uint32_t)(READ_BITS(RTC->CON, RTC_CON_POL_MSK, RTC_CON_POL_POS));
}

/**
  * @brief  Get register synchronization flag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_busy(void)
{
	return (READ_BIT(RTC->CON, RTC_CON_BUSY_MSK) == (RTC_CON_BUSY_MSK));
}

/**
  * @brief  Get subsecond modification flag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_ssec(void)
{
	return (READ_BIT(RTC->CON, RTC_CON_SSEC_MSK) == (RTC_CON_SSEC_MSK));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group3 PSR
  * @{
  */
/**
  * @brief  Set Asynchronous prescaler factor
  * @param  psc Value between Min_Data = 0 and Max_Data = 0x7F
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_asynch_prescaler(uint32_t psc)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->PSR, RTC_PSR_APRS_MSK, psc << RTC_PSR_APRS_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Asynchronous prescaler factor
  * @retval Value between Min_Data = 0 and Max_Data = 0x7F
  */
__STATIC_INLINE uint32_t md_rtc_get_asynch_prescaler(void)
{
	return (uint32_t)(READ_BITS(RTC->PSR, RTC_PSR_APRS_MSK, RTC_PSR_APRS_POSS));
}

/**
  * @brief  Set Synchronous prescaler factor
  * @param  psc Value between Min_Data = 0 and Max_Data = 0x7FFF
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_synch_prescaler(uint32_t psc)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->PSR, RTC_PSR_SPRS_MSK, psc << RTC_PSR_SPRS_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Synchronous prescaler factor
  * @retval Value between Min_Data = 0 and Max_Data = 0x7FFF
  */
__STATIC_INLINE uint32_t md_rtc_get_synch_prescaler(void)
{
	return (uint32_t)(READ_BITS(RTC->PSR, RTC_PSR_SPRS_MSK, RTC_PSR_SPRS_POSS));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group4 TAMPCON
  * @{
  */
/**
  * @brief  Enable RTC_TAMPx input detection
  * @param  tamper This parameter can be a combination of the @ref md_rtc_tamper_idx_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_tamper_enable(md_rtc_tamper_idx_t tamper)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->TAMPCON, (tamper == MD_RTC_TAMPER_0 ? RTC_TAMPCON_TAMP0EN_MSK : RTC_TAMPCON_TAMP1EN_MSK));
	MD_RTC_LOCK();
}

/**
  * @brief  Clear RTC_TAMPx input detection
  * @param  tamper This parameter can be a combination of the @ref md_rtc_tamper_idx_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_tamper_disable(md_rtc_tamper_idx_t tamper)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->TAMPCON, (tamper == MD_RTC_TAMPER_0 ? RTC_TAMPCON_TAMP0EN_MSK : RTC_TAMPCON_TAMP1EN_MSK));
	MD_RTC_LOCK();
}

/**
  * @brief  Enable High level for Tamper input
  * @param  tamper This parameter can be a combination of the @ref md_rtc_tamper_idx_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_tamper_high_level_enable(md_rtc_tamper_idx_t tamper)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->TAMPCON, (tamper == MD_RTC_TAMPER_0 ? RTC_TAMPCON_TAMP0LV_MSK : RTC_TAMPCON_TAMP1LV_MSK));
	MD_RTC_LOCK();
}

/**
  * @brief  Enable Low level for Tamper input
  * @param  tamper This parameter can be a combination of the @ref md_rtc_tamper_idx_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_tamper_low_level_enable(md_rtc_tamper_idx_t tamper)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->TAMPCON, (tamper == MD_RTC_TAMPER_0 ? RTC_TAMPCON_TAMP0LV_MSK : RTC_TAMPCON_TAMP1LV_MSK));
	MD_RTC_LOCK();
}

/**
  * @brief  Activate timestamp on tamper detection event
  * @retval None
  */
__STATIC_INLINE void md_rtc_ts_enable_on_tamper(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMPTS_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable timestamp on tamper detection event
  * @retval None
  */
__STATIC_INLINE void md_rtc_ts_disable_on_tamper(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMPTS_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Set Tamper sampling frequency
  * @param  samplingfreq This parameter can be one of the @ref md_rtc_tamper_sampling_freq_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_tamper_set_sampling_freq(md_rtc_tamper_sampling_freq_t samplingfreq)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPCKS_MSK, samplingfreq << RTC_TAMPCON_TAMPCKS_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Tamper sampling frequency
  * @retval Returned value can be one of the @ref md_rtc_tamper_sampling_freq_t
  */
__STATIC_INLINE uint32_t md_rtc_tamper_get_sampling_freq(void)
{
	return (uint32_t)(READ_BITS(RTC->TAMPCON, RTC_TAMPCON_TAMPCKS_MSK, RTC_TAMPCON_TAMPCKS_POSS));
}

/**
  * @brief  Set RTC_TAMPx filter count
  * @param  filter This parameter can be one of the @ref md_rtc_tamper_duration_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_tamper_set_filter_count(md_rtc_tamper_duration_t filter)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPFLT_MSK, filter << RTC_TAMPCON_TAMPFLT_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get RTC_TAMPx filter count
  * @retval Returned value can be one of the @ref md_rtc_tamper_duration_t
  */
__STATIC_INLINE uint32_t md_rtc_tamper_get_filter_count(void)
{
	return (uint32_t)(READ_BITS(RTC->TAMPCON, RTC_TAMPCON_TAMPFLT_MSK, RTC_TAMPCON_TAMPFLT_POSS));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group5 TIME
  * @{
  */
/**
  * @brief  Set time in BCD format
  * @param  hour: Value of the hour in BCD format
  * @param  min: Value of the minute in BCD format
  * @param  sec: Value of the second in BCD format
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_time_easy(uint8_t hour, uint8_t min, uint8_t sec)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->TIME, 0x3FFFFFU);
	SET_BIT(RTC->TIME, sec | (min << 8) | (hour << 16));
	MD_RTC_LOCK();
}

/**
  * @brief  Get time in BCD format
  * @param  hour: Value of the hour in BCD format
  * @param  min: Value of the minute in BCD format
  * @param  sec: Value of the second in BCD format
  * @retval None
  */
__STATIC_INLINE void md_rtc_get_time_easy(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
	uint32_t tmp = RTC->TIME;

	*hour = (tmp >> 16) & 0x7F;
	*min  = (tmp >> 8) & 0x7F;
	*sec  = tmp & 0x7F;
}

/**
  * @brief  Set time format (AM/24-hour or PM notation)
  * @param  format: 0-AM/24H, 1-PM
  * @retval None
  */
__STATIC_INLINE void md_rtc_time_set_format(uint32_t format)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->TIME, RTC_TIME_PM_MSK, format << RTC_TIME_PM_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get time format (AM or PM notation)
  * @retval Returned value can be one of the following values:
  *           - 0: AM/24H
  *           - 1: PM
  */
__STATIC_INLINE uint32_t md_rtc_time_get_format(void)
{
	return (uint32_t)(READ_BITS(RTC->TIME, RTC_TIME_PM_MSK, RTC_TIME_PM_POS));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group6 DATE
  * @{
  */
/**
  * @brief  Set date in BCD format
  * @param  year: Value of the year in BCD format
  * @param  mon: Value of the month in BCD format
  * @param  day: Value of the day in BCD format
  * @param  week: Value of the week
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_date_easy(uint8_t year, uint8_t mon, uint8_t day, uint8_t week)
{
	MD_RTC_UNLOCK();
	RTC->DATE = 0U;
	RTC->DATE = (day | (mon << 8) | (year << 16) | (week << 24));
	MD_RTC_LOCK();
}

/**
  * @brief  Get date in BCD format
  * @param  year: Value of the year in BCD format
  * @param  month: Value of the month in BCD format
  * @param  day: Value of the day in BCD format
  * @param  week: Value of the week
  * @retval None
  */
__STATIC_INLINE void md_rtc_get_date_easy(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *week)
{
	uint32_t tmp = RTC->DATE;

	*day   = tmp & 0x3F;
	*month = (tmp >> 8) & 0x1F;
	*year  = (tmp >> 16) & 0xFF;
	*week  = (tmp >> 24) & 0x7;
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group7 SSEC
  * @{
  */
/**
  * @brief  Get Sub second value in the synchronous prescaler counter.
  * @retval Sub second value (number between 0 and 65535)
  */
__STATIC_INLINE uint32_t md_rtc_time_get_sub_second(void)
{
	return (uint32_t)(READ_BIT(RTC->SSEC, RTC_SSEC_VAL_MSK));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group8 WUMAT
  * @{
  */
/**
  * @brief  Set Wakeup reload value
  * @param  value Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_rtc_wakeup_set_reload(uint32_t value)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->WUMAT, RTC_WUMAT_VAL_MSK, value);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Wakeup reload value
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t md_rtc_wakeup_get_reload(void)
{
	return (uint32_t)(READ_BIT(RTC->WUMAT, RTC_WUMAT_VAL_MSK));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group9 ALMA
  * @{
  */
/**
  * @brief  Set ALARM A Seconds in BCD format
  * @param  second Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_second(uint32_t second)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, (RTC_ALMA_SECU_MSK | RTC_ALMA_SECT_MSK), second);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM A Seconds in BCD format
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t rtc_alma_get_second(void)
{
	return (uint32_t)READ_BITS(RTC->ALMA, (RTC_ALMA_SECU_MSK | RTC_ALMA_SECT_MSK), RTC_ALMA_SECU_POSS);
}

/**
  * @brief  Specify the Alarm A masks.
  * @param  mask This parameter can be a combination of the @ref md_rtc_alarm_mask_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_mask(md_rtc_alarm_mask_t mask)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, RTC_ALMA_SECMSK_MSK | RTC_ALMA_MINMSK_MSK | RTC_ALMA_HRMSK_MSK | RTC_ALMA_DAYMSK_MSK, mask);
	MD_RTC_LOCK();
}

/**
  * @brief  Get the Alarm A masks.
  * @retval Returned value can be can be a combination of the @ref md_rtc_alarm_mask_t
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_mask(void)
{
	return (uint32_t)(READ_BIT(RTC->ALMA, RTC_ALMA_SECMSK_MSK | RTC_ALMA_MINMSK_MSK | RTC_ALMA_HRMSK_MSK | RTC_ALMA_DAYMSK_MSK));
}

/**
  * @brief  Set ALARM A Minutes in BCD format
  * @param  minute Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_minute(uint32_t minute)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, (RTC_ALMA_MINT_MSK | RTC_ALMA_MINU_MSK), minute << RTC_ALMA_MINU_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM A Minutes in BCD format
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_minute(void)
{
	return (uint32_t)READ_BITS(RTC->ALMA, (RTC_ALMA_MINT_MSK | RTC_ALMA_MINU_MSK), RTC_ALMA_MINU_POSS);
}

/**
  * @brief  Set ALARM A Hours in BCD format
  * @param  hour Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_hour(uint32_t hour)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, (RTC_ALMA_HRT_MSK | RTC_ALMA_HRU_MSK), hour << RTC_ALMA_HRU_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM A Hours in BCD format
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_hour(void)
{
	return (uint32_t)READ_BITS(RTC->ALMA, (RTC_ALMA_HRT_MSK | RTC_ALMA_HRU_MSK), RTC_ALMA_HRU_POSS);
}

/**
  * @brief  Set Alarm A time format (AM/24-hour or PM notation)
  * @param  format: 0-AM/24H, 1-PM
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_time_format(uint32_t format)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, RTC_ALMA_PM_MSK, format << RTC_ALMA_PM_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Alarm A time format (AM or PM notation)
  * @retval Returned value can be one of the following values:
  *           - 0: AM/24H
  *           - 1: PM
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_time_format(void)
{
	return (uint32_t)(READ_BITS(RTC->ALMA, RTC_ALMA_PM_MSK, RTC_ALMA_PM_POS));
}

/**
  * @brief  Set ALARM A Day in BCD format
  * @param  day Value between Min_Data=0x01 and Max_Data=0x31
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_day(uint32_t day)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, (RTC_ALMA_DAWD_DAYT_MSK | RTC_ALMA_DAWD_DAYU_MSK), day << RTC_ALMA_DAWD_DAYU_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM A Day in BCD format
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_day(void)
{
	return (uint32_t)READ_BITS(RTC->ALMA, (RTC_ALMA_DAWD_DAYT_MSK | RTC_ALMA_DAWD_DAYU_MSK), RTC_ALMA_DAWD_DAYU_POSS);
}

/**
  * @brief  Set ALARM A Weekday
  * @param  week: Week, bit0-Sunday, ..., bit6-Saturday.
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_weekday(uint32_t week)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMA, RTC_ALMA_DAWD_MSK, week << RTC_ALMA_DAWD_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM A Weekday
  * @retval Week, bit0-Sunday, ..., bit6-Saturday.
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_weekday(void)
{
	return (uint32_t)(READ_BITS(RTC->ALMA, RTC_ALMA_DAWD_MSK, RTC_ALMA_DAWD_POSS));
}

/**
  * @brief  Enable AlarmB Week day selection (DAWD[24:30] represents the week day)
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_enable_weekday(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->ALMA, RTC_ALMA_WDS_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable AlarmA Week day selection (DU[24:30] represents the date )
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_disable_weekday(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->ALMA, RTC_ALMA_WDS_MSK);
	MD_RTC_LOCK();
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group10 ALMB
  * @{
  */
/**
  * @brief  Set ALARM B Seconds in BCD format
  * @param  second Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void rtc_almb_set_second(uint32_t second)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, (RTC_ALMB_SECU_MSK | RTC_ALMB_SECT_MSK), second);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM B Seconds in BCD format
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t rtc_almb_get_second(void)
{
	return (uint32_t)READ_BITS(RTC->ALMB, (RTC_ALMB_SECU_MSK | RTC_ALMB_SECT_MSK), RTC_ALMB_SECU_POSS);
}

/**
  * @brief  Specify the Alarm B masks.
  * @param  mask This parameter can be a combination of the @ref md_rtc_alarm_mask_t
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_mask(md_rtc_alarm_mask_t mask)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, RTC_ALMB_SECMSK_MSK | RTC_ALMB_MINMSK_MSK | RTC_ALMB_HRMSK_MSK | RTC_ALMB_DAYMSK_MSK, mask);
	MD_RTC_LOCK();
}

/**
  * @brief  Get the Alarm B masks.
  * @retval Returned value can be can be a combination of the @ref md_rtc_alarm_mask_t
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_mask(void)
{
	return (uint32_t)(READ_BIT(RTC->ALMB, RTC_ALMB_SECMSK_MSK | RTC_ALMB_MINMSK_MSK | RTC_ALMB_HRMSK_MSK | RTC_ALMB_DAYMSK_MSK));
}

/**
  * @brief  Set ALARM B Minutes in BCD format
  * @param  minute Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_minute(uint32_t minute)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, (RTC_ALMB_MINT_MSK | RTC_ALMB_MINU_MSK), minute << RTC_ALMB_MINU_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM B Minutes in BCD format
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_minute(void)
{
	return (uint32_t)READ_BITS(RTC->ALMB, (RTC_ALMB_MINT_MSK | RTC_ALMB_MINU_MSK), RTC_ALMB_MINU_POSS);
}

/**
  * @brief  Set ALARM B Hours in BCD format
  * @param  hour Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_hour(uint32_t hour)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, (RTC_ALMB_HRT_MSK | RTC_ALMB_HRU_MSK), hour << RTC_ALMB_HRU_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM B Hours in BCD format
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_hour(void)
{
	return (uint32_t)READ_BITS(RTC->ALMB, (RTC_ALMB_HRT_MSK | RTC_ALMB_HRU_MSK), RTC_ALMB_HRU_POSS);
}

/**
  * @brief  Set Alarm B time format (AM/24-hour or PM notation)
  * @param  format: 0-AM/24H, 1-PM
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_time_format(uint32_t format)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, RTC_ALMB_PM_MSK, format << RTC_ALMB_PM_POS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Alarm B time format (AM or PM notation)
  * @retval Returned value can be one of the following values:
  *           - 0: AM/24H
  *           - 1: PM
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_time_format(void)
{
	return (uint32_t)(READ_BITS(RTC->ALMB, RTC_ALMB_PM_MSK, RTC_ALMB_PM_POS));
}

/**
  * @brief  Set ALARM B Day in BCD format
  * @param  day Value between Min_Data=0x01 and Max_Data=0x31
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_day(uint32_t day)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, (RTC_ALMB_DAWD_DAYT_MSK | RTC_ALMB_DAWD_DAYU_MSK), day << RTC_ALMB_DAWD_DAYU_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM B Day in BCD format
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_day(void)
{
	return (uint32_t)READ_BITS(RTC->ALMB, (RTC_ALMB_DAWD_DAYT_MSK | RTC_ALMB_DAWD_DAYU_MSK), RTC_ALMB_DAWD_DAYU_POSS);
}

/**
  * @brief  Set ALARM B Weekday
  * @param  week: Week, bit0-Sunday, ..., bit6-Saturday.
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_weekday(uint8_t week)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMB, RTC_ALMB_DAWD_MSK, week << RTC_ALMB_DAWD_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get ALARM B Weekday
  * @retval Week, bit0-Sunday, ..., bit6-Saturday.
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_weekday(void)
{
	return (uint32_t)(READ_BITS(RTC->ALMB, RTC_ALMB_DAWD_MSK, RTC_ALMB_DAWD_POSS));
}

/**
  * @brief  Enable AlarmB Week day selection (DAWD[24:30] represents the week day.
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_enable_weekday(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->ALMB, RTC_ALMB_WDS_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable AlarmB Week day selection (DU[24:30] represents the date )
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_disable_weekday(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->ALMB, RTC_ALMB_WDS_MSK);
	MD_RTC_LOCK();
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group11 ALMASSEC
  * @{
  */
/**
  * @brief  Set Alarm A Sub seconds value
  * @param  subsecond Value between Min_Data=0x00 and Max_Data=0x7FFF
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_sub_second(uint32_t subsecond)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMASSEC, RTC_ALMASSEC_SSEC_MSK, subsecond);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Alarm A Sub seconds value
  * @retval Value between Min_Data=0x00 and Max_Data=0x7FFF
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_sub_second(void)
{
	return (uint32_t)(READ_BIT(RTC->ALMASSEC, RTC_ALMASSEC_SSEC_MSK));
}

/**
  * @brief  Set Alarm A Mask the most-significant bits starting at this bit
  * @param  mask Value between Min_Data=0x00 and Max_Data=0xF
  * @retval None
  */
__STATIC_INLINE void md_rtc_alma_set_sub_second_mask(uint32_t mask)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMASSEC, RTC_ALMASSEC_SSECM_MSK, mask << RTC_ALMASSEC_SSECM_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Alarm A Mask the most-significant bits starting at this bit
  * @retval Value between Min_Data=0x00 and Max_Data=0xF
  */
__STATIC_INLINE uint32_t md_rtc_alma_get_sub_second_mask(void)
{
	return (uint32_t)(READ_BITS(RTC->ALMASSEC, RTC_ALMASSEC_SSECM_MSK, RTC_ALMASSEC_SSECM_POSS));
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group12 ALMBSSEC
  * @{
  */
/**
  * @brief  Set Alarm B Sub seconds value
  * @param  subsecond Value between Min_Data=0x00 and Max_Data=0x7FFF
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_sub_second(uint32_t subsecond)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMBSSEC, RTC_ALMBSSEC_SSEC_MSK, subsecond);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Alarm B Sub seconds value
  * @retval Value between Min_Data=0x00 and Max_Data=0x7FFF
  */
__STATIC_INLINE uint32_t md_rtc_alma_bet_sub_second(void)
{
	return (uint32_t)(READ_BIT(RTC->ALMBSSEC, RTC_ALMBSSEC_SSEC_MSK));
}

/**
  * @brief  Set Alarm B Mask the most-significant bits starting at this bit
  * @param  mask Value between Min_Data=0x00 and Max_Data=0xF
  * @retval None
  */
__STATIC_INLINE void md_rtc_almb_set_sub_second_mask(uint32_t mask)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->ALMBSSEC, RTC_ALMBSSEC_SSECM_MSK, mask << RTC_ALMBSSEC_SSECM_POSS);
	MD_RTC_LOCK();
}

/**
  * @brief  Get Alarm B Mask the most-significant bits starting at this bit
  * @retval Value between Min_Data=0x00 and Max_Data=0xF
  */
__STATIC_INLINE uint32_t md_rtc_almb_get_sub_second_mask(void)
{
	return (uint32_t)(READ_BITS(RTC->ALMBSSEC, RTC_ALMBSSEC_SSECM_MSK, RTC_ALMBSSEC_SSECM_POSS));
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group13 TSTIME
  * @{
  */
/**
  * @brief  Get Timestamp time in BCD format
  * @param  hour: Value of the hour in BCD format
  * @param  min: Value of the minute in BCD format
  * @param  sec: Value of the second in BCD format
  * @retval None
  */
__STATIC_INLINE void md_rtc_get_ts_time(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
	uint32_t tmp = RTC->TSTIME;

	*hour = (tmp >> 16) & 0x7F;
	*min  = (tmp >> 8) & 0x7F;
	*sec  = tmp & 0x7F;
}

/**
  * @brief  Get Timestamp AM/PM notation (AM or 24-hour format)
  * @retval Returned value can be one of the following values:
  *           - 0: AM/24H
  *           - 1: PM
  */
__STATIC_INLINE uint32_t md_rtc_get_ts_time_format(void)
{
	return (uint32_t)(READ_BITS(RTC->TSTIME, RTC_TSTIME_PM_MSK, RTC_TSTIME_PM_POS));
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group14 TSDATE
  * @{
  */
/**
  * @brief  Get Timestamp date in BCD format
  * @param  year: Value of the year in BCD format
  * @param  month: Value of the month in BCD format
  * @param  day: Value of the day in BCD format
  * @param  week: Value of the week
  * @retval None
  */
__STATIC_INLINE void md_rtc_ts_get_day(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *week)
{
	uint32_t tmp = RTC->TSDATE;

	*day   = tmp & 0x3F;
	*month = (tmp >> 8) & 0x1F;
	*year  = (tmp >> 16) & 0xFF;
	*week  = (tmp >> 24) & 0x7;
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group15 TSSSEC
  * @{
  */
/**
  * @brief  Get time-stamp sub second value
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t md_rtc_get_ts_subsecond(void)
{
	return (uint32_t)(READ_BIT(RTC->TSSSEC, RTC_TSSSEC_SSEC_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group16 SSECTR
  * @{
  */
/**
  * @brief  Sub second revise
  * @param  revisevalue Sub second revise value.
  * @retval None
  */
__STATIC_INLINE void md_rtc_subsecond_revise(uint32_t revisevalue)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->SSECTR, RTC_SSECTR_TRIM_MSK, revisevalue);
	MD_RTC_LOCK();
}

/**
  * @brief  Enable second revise
  * @retval None
  */
__STATIC_INLINE void md_rtc_second_revise_enable_inc(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->SSECTR, RTC_SSECTR_INC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable second revise
  * @retval None
  */
__STATIC_INLINE void md_rtc_second_revise_disable_inc(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->SSECTR, RTC_SSECTR_INC_MSK);
	MD_RTC_LOCK();
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group17 IER
  * @{
  */
/**
  * @brief  Enable RTC second interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_sec_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_SEC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC second interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_sec_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_SEC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC second interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_sec_intrrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_SEC_MSK, RTC_IER_SEC_POS);
}

/**
  * @brief  Enable RTC minute interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_minute_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_MIN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC minute interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_minute_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_MIN_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC minute interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_minute_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_MIN_MSK, RTC_IER_MIN_POS);
}

/**
  * @brief  Enable RTC hour interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_hour_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_HR_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC hour interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_hour_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_HR_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC hour interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_hour_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_HR_MSK, RTC_IER_HR_POS);
}

/**
  * @brief  Enable RTC day interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_day_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_DAY_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC day interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_day_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_DAY_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC day interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_day_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_DAY_MSK, RTC_IER_DAY_POS);
}

/**
  * @brief  Enable RTC month interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_month_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_MON_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC month interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_month_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_MON_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC month interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_month_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_MON_MSK, RTC_IER_MON_POS);
}

/**
  * @brief  Enable RTC year interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_year_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_YR_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC year interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_year_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_YR_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC year interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_year_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_YR_MSK, RTC_IER_MON_POS);
}

/**
  * @brief  Enable RTC ALMA interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_alma_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_ALMA_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC ALMA interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_alma_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_ALMA_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC ALMA interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_alma_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_ALMA_MSK, RTC_IER_ALMA_POS);
}

/**
  * @brief  Enable RTC ALMB interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_almb_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_ALMB_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC ALMB interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_almb_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_ALMB_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC ALMB interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_almb_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_ALMB_MSK, RTC_IER_ALMB_POS);
}

/**
  * @brief  Enable RTC TS interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_ts_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_TS_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC TS interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_ts_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_TS_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC TS interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_ts_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_TS_MSK, RTC_IER_TS_POS);
}

/**
  * @brief  Enable RTC TSOV interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_tsov_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_TSOV_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC TSOV interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_tsov_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_TSOV_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC TSOV interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_tsov_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_TSOV_MSK, RTC_IER_TSOV_POS);
}

/**
  * @brief  Enable RTC TAMP0 interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_tamp0_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_TAMP0_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC TAMP0 interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_tamp0_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_TAMP0_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC TAMP0 interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_tamp0_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_TAMP0_MSK, RTC_IER_TAMP0_POS);
}

/**
  * @brief  Enable RTC TAMP1 interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_tamp1_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_TAMP1_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC TAMP1 interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_tamp1_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_TAMP1_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC TAMP1 interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_tamp1_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_TAMP1_MSK, RTC_IER_TAMP1_POS);
}

/**
  * @brief  Enable RTC RSC interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_rsc_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_RSC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC RSC interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_rsc_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_RSC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC RSC interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_rsc_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_RSC_MSK, RTC_IER_RSC_POS);
}

/**
  * @brief  Enable RTC SSTC interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_sstc_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_SSTC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC SSTC interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_sstc_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_SSTC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC SSTC interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_sstc_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_SSTC_MSK, RTC_IER_SSTC_POS);
}

/**
  * @brief  Enable RTC WU interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_enable_wu_intrrupt(void)
{
	MD_RTC_UNLOCK();
	SET_BIT(RTC->IER, RTC_IER_WU_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC WU interrupt
  * @retval None
  */
__STATIC_INLINE void md_rtc_disable_wu_intrrupt(void)
{
	MD_RTC_UNLOCK();
	CLEAR_BIT(RTC->IER, RTC_IER_WU_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Check RTC WU interrupt is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_rtc_wu_interrupt_is_enable(void)
{
	return READ_BITS(RTC->IER, RTC_IER_WU_MSK, RTC_IER_WU_POS);
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group18 IFR
  * @{
  */
/**
  * @brief  Get SECF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_sec(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_SECF_MSK, RTC_IFR_SECF_POS);
}

/**
  * @brief  Get MINF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_min(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_MINF_MSK, RTC_IFR_MINF_POS);
}

/**
  * @brief  Get HRF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_hr(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_HRF_MSK, RTC_IFR_HRF_POS);
}

/**
  * @brief  Get DAYF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_day(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_DAYF_MSK, RTC_IFR_DAYF_POS);
}

/**
  * @brief  Get MONF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_mon(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_MONF_MSK, RTC_IFR_MONF_POS);
}

/**
  * @brief  Get YRF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_yr(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_YRF_MSK, RTC_IFR_YRF_POS);
}

/**
  * @brief  Get ALMAF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_alma(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_ALMAF_MSK, RTC_IFR_ALMAF_POS);
}

/**
  * @brief  Get ALMBF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_almb(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_ALMBF_MSK, RTC_IFR_ALMBF_POS);
}

/**
  * @brief  Get TSF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_ts(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_TSF_MSK, RTC_IFR_TSF_POS);
}

/**
  * @brief  Get TSOVF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_tsov(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_TSOVF_MSK, RTC_IFR_TSOVF_POS);
}

/**
  * @brief  Get TAMP0F flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_tamp0(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_TAMP0F_MSK, RTC_IFR_TAMP0F_POS);
}

/**
  * @brief  Get TAMP1F flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_tamp1(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_TAMP1F_MSK, RTC_IFR_TAMP1F_POS);
}

/**
  * @brief  Get RSCF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_rsc(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_RSCF_MSK, RTC_IFR_RSCF_POS);
}

/**
  * @brief  Get SSTCF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_sstc(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_SSTCF_MSK, RTC_IFR_SSTCF_POS);
}

/**
  * @brief  Get WUF flag state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_is_active_flag_wu(void)
{
	return READ_BITS(RTC->IFR, RTC_IFR_WUF_MSK, RTC_IFR_WUF_POS);
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group19 IFCR
  * @{
  */
/**
  * @brief  Clear SECF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_sec(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_SECFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear MINF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_min(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_MINFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear HRF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_hr(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_HRFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear DAYF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_day(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_DAYFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear MONF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_mon(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_MONFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear YRF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_yr(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_YRFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear ALMAF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_alma(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_ALMAFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear ALMBF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_almb(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_ALMBFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear TSF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_tc(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_TSFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear TSOVF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_tsov(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_TSOVFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear TAMP0F flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_tamp0(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_TAMP0FC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear TAMP1F flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_tamp1(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_TAMP1FC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear RSCF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_rsc(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_RSCFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear SSTCF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_sstc(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_SSTCFC_MSK);
	MD_RTC_LOCK();
}

/**
  * @brief  Clear WUF flag
  * @retval None
  */
__STATIC_INLINE void md_rtc_clear_flag_wu(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, RTC_IFCR_WUFC_MSK);
	MD_RTC_LOCK();
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group20 ISR
  * @{
  */
/**
  * @brief  Get SECF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_sec_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_SECF_MSK, RTC_ISR_SECF_POS);
}

/**
  * @brief  Get MINF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_min_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_MINF_MSK, RTC_ISR_MINF_POS);
}

/**
  * @brief  Get HRF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_hr_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_HRF_MSK, RTC_ISR_HRF_POS);
}

/**
  * @brief  Get DAYF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_day_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_DAYF_MSK, RTC_ISR_DAYF_POS);
}

/**
  * @brief  Get MONF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_mon_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_MONF_MSK, RTC_ISR_MONF_POS);
}

/**
  * @brief  Get YRF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_yr_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_YRF_MSK, RTC_ISR_YRF_POS);
}

/**
  * @brief  Get ALMAF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_alma_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_ALMAF_MSK, RTC_ISR_ALMAF_POS);
}

/**
  * @brief  Get ALMBF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_almb_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_ALMBF_MSK, RTC_ISR_ALMBF_POS);
}

/**
  * @brief  Get TSF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_ts_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_TSF_MSK, RTC_ISR_TSF_POS);
}

/**
  * @brief  Get TSOVF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_tsov_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_TSOVF_MSK, RTC_ISR_TSOVF_POS);
}

/**
  * @brief  Get TAMP0F interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_tamp0_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_TAMP0F_MSK, RTC_ISR_TAMP0F_POS);
}

/**
  * @brief  Get TAMP1F interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_tamp1_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_TAMP1F_MSK, RTC_ISR_TAMP1F_POS);
}

/**
  * @brief  Get RSCF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_rsc_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_RSCF_MSK, RTC_ISR_RSCF_POS);
}

/**
  * @brief  Get SSTCF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_sstc_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_SSTCF_MSK, RTC_ISR_SSTCF_POS);
}

/**
  * @brief  Get WUF interrutpt state
  * @retval Status:
  *         - 0: RESET
  *         - 1: SET
  */
__STATIC_INLINE uint32_t md_rtc_get_wu_interrupt_state(void)
{
	return READ_BITS(RTC->ISR, RTC_ISR_WUF_MSK, RTC_ISR_WUF_POS);
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group21 CALCON
  * @{
  */
/**
  * @brief  Enable RTC calibration
  * @retval None
  */
__STATIC_INLINE void md_rtc_calibration_enable_cali(void)
{
	MD_RTC_UNLOCK();
	MD_RTC_CALI_UNLOCK();
	SET_BIT(RTC->CALCON, RTC_CALCON_CALEN_MSK);
	MD_RTC_CALI_LOCK();
	MD_RTC_LOCK();
}

/**
  * @brief  Disable RTC calibration
  * @retval None
  */
__STATIC_INLINE void md_rtc_calibration_disable_cali(void)
{
	MD_RTC_UNLOCK();
	MD_RTC_CALI_UNLOCK();
	CLEAR_BIT(RTC->CALCON, RTC_CALCON_CALEN_MSK);
	MD_RTC_CALI_LOCK();
	MD_RTC_LOCK();
}

/**
  * @brief  Check if RTC calibration enable
  * @retval None
  */
__STATIC_INLINE uint32_t md_rtc_is_enable_cali(void)
{
	return READ_BITS(RTC->CALCON, RTC_CALCON_CALEN_MSK, RTC_CALCON_CALEN_POS);
}

/**
  * @brief  Set calibration mode
  * @param  calpvalue: Value of following:
  *         - 0x0: 10s
  *         - 0x1: 20s
  *         - 0x2: 1min
  *         - 0x3: 2min
  *         - 0x4: 5min
  *         - 0x5: 10min
  *         - 0x6: 20min
  *         - 0x7: 1s
  * @retval None
  */
__STATIC_INLINE void md_rtc_set_calibration_mode(uint32_t calpvalue)
{
	MD_RTC_UNLOCK();
	MD_RTC_CALI_UNLOCK();
	MODIFY_REG(RTC->CALCON, RTC_CALCON_CALP_MSK, calpvalue << RTC_CALCON_CALP_POSS);
	MD_RTC_CALI_LOCK();
	MD_RTC_LOCK();
}

/**
  * @brief  Get clibration mode
  * @retval None
  */
__STATIC_INLINE uint32_t md_rtc_get_calibration_mode(void)
{
	return READ_BITS(RTC->CALCON, RTC_CALCON_CALP_MSK, RTC_CALCON_CALP_POSS);
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group22 CALDR
  * @{
  */
/**
  * @brief  Set Calibration minus
  * @param  calibminus Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void md_rtc_cal_set_minus(int16_t calibminus)
{
	MD_RTC_UNLOCK();
	MD_RTC_CALI_UNLOCK();
	MODIFY_REG(RTC->CALDR, RTC_CALDR_VAL_MSK, calibminus);
	MD_RTC_CALI_LOCK();
	MD_RTC_LOCK();
}

/**
  * @brief  Get Calibration minus
  * @retval Value between Min_Data=0x0000 and Max_Data= 0xFFFF
  */
__STATIC_INLINE uint32_t md_rtc_cal_get_minus(void)
{
	return (uint32_t)(READ_BITS(RTC->CALDR, RTC_CALDR_VAL_MSK, RTC_CALDR_VAL_POSS));
}

/**
  * @brief  Get real-time calibration value
  * @retval Value between Min_Data=0x0000 and Max_Data= 0xFFFF
  */
__STATIC_INLINE uint32_t md_rtc_get_realtime_cal_value(void)
{
	return (uint32_t)(READ_BITS(RTC->CALDR, RTC_CALDR_DATA_MSK, RTC_CALDR_DATA_POSS));
}
/**
  * @}
  */
/** @defgroup MD_RTC_Public_Functions_Group23 BKPxR
  * @{
  */
/**
  * @brief  Writes a data in a specified RTC Backup data register.
  * @param  idx: (0 ~ 31)
  * @param  data: Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void md_rtc_write_backup_sram(uint32_t idx, uint32_t data)
{
	MD_RTC_UNLOCK();
	RTC->BKPR[idx] = data;
	MD_RTC_LOCK();
}

/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @param  idx: (0 ~ 31)
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t md_rtc_bak_get_register(uint32_t idx)
{
	return RTC->BKPR[idx];
}
/**
  * @}
  */

/** @defgroup MD_RTC_Public_Functions_Group1 Initialization/Utilities
  * @{
  */
extern uint32_t md_rtc_bcd_to_dec(uint32_t bcd);
extern uint32_t md_rtc_dec_to_bcd(uint32_t dec);
extern void md_rtc_reset(void);
extern void md_rtc_init(md_rtc_init_t *init);
extern void md_rtc_struct_init(md_rtc_init_t *init);
extern void md_rtc_time_struct_init(md_rtc_time_t *time);
extern void md_rtc_date_struct_init(md_rtc_date_t *date);
extern void md_rtc_set_time(md_rtc_time_t *time, md_rtc_format_t format);
extern void md_rtc_set_date(md_rtc_date_t *date, md_rtc_format_t format);
extern void md_rtc_get_time(md_rtc_time_t *time, md_rtc_format_t format);
extern void md_rtc_get_date(md_rtc_date_t *date, md_rtc_format_t format);
extern void md_rtc_alarm_struct_init(md_rtc_alarm_t *init);
extern void md_rtc_set_alarm(md_rtc_alarm_t *alarm, md_rtc_format_t format);
extern void md_rtc_set_time_stamp(md_rtc_ts_signal_sel_t sel, md_rtc_ts_trigger_style_t style);
extern void md_rtc_set_tamper(md_rtc_tamper_t *tamper);
extern void md_rtc_tamper_struct_init(md_rtc_tamper_t *init);
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

#endif /* __MD_RTC_H__ */
