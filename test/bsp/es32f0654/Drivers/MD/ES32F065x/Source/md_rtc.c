/**
  *********************************************************************************
  *
  * @file    md_rtc.c
  * @brief   RTC module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_rtc.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_RTC

/** @addtogroup MD_RTC
  * @{
  */
/** @addtogroup MD_RTC_Public_Functions
  * @{
  */
/** @addtogroup MD_RTC_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Converts form 2 digit BCD to Binary.
  * @param  bcd: BCD value to be converted.
  * @retval Converted word.
  */
uint32_t md_rtc_bcd_to_dec(uint32_t bcd)
{
	return ((bcd & 0xF) + ((bcd >> 4) & 0xF) * 10);
}
  
/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  dec: Byte to be converted.
  * @retval Converted byte.
  */
uint32_t md_rtc_dec_to_bcd(uint32_t dec)
{
	return (((dec / 10) << 4) | (dec % 10));
}

/**
  * @brief  Reset RTC register.
  * @retval None
  */
void md_rtc_reset(void)
{
	MD_RTC_UNLOCK();
	WRITE_REG(RTC->CON, 0x0);
	WRITE_REG(RTC->TAMPCON, 0x0);
	WRITE_REG(RTC->WUMAT, 0x0);
	WRITE_REG(RTC->IER, 0x0);
	WRITE_REG(RTC->IFCR, ~0x0);
	MD_RTC_LOCK();
	
	return;
}

/**
  * @brief  Initialize the RTC module.
  * @param  init: Pointer to md_rtc_init_t structure which contains
  *                         the configuration parameters.
  * @retval None
  */
void md_rtc_init(md_rtc_init_t *init)
{
	md_rtc_reset();
	MD_RTC_UNLOCK();

	MODIFY_REG(RTC->CON, RTC_CON_HFM_MSK, init->hour_format << RTC_CON_HFM_POS);
	MODIFY_REG(RTC->CON, RTC_CON_EOS_MSK, init->output << RTC_CON_EOS_POSS);
	MODIFY_REG(RTC->CON, RTC_CON_POL_MSK, init->output_polarity << RTC_CON_POL_POS);
	MODIFY_REG(RTC->PSR, RTC_PSR_SPRS_MSK, init->synch_pre_div << RTC_PSR_SPRS_POSS);
	MODIFY_REG(RTC->PSR, RTC_PSR_APRS_MSK, init->asynch_pre_div << RTC_PSR_APRS_POSS);
	SET_BIT(RTC->CON, RTC_CON_GO_MSK);

	MD_RTC_LOCK();
	return;
}

/**
  * @brief  Set each @ref md_rtc_init_t field to default value.
  * @param  init: pointer to a @ref md_rtc_init_t structure which will be initialized.
  * @retval None
  */
void md_rtc_struct_init(md_rtc_init_t *init)
{
	init->asynch_pre_div  = 0;
	init->synch_pre_div   = 32767;
	init->hour_format     = MD_RTC_HOUR_FORMAT_24;
	init->output          = MD_RTC_ALARMOUT_DISABLE;
	init->output_polarity = MD_RTC_OUTPUT_POLARITY_HIGH;

	return;
}

/**
  * @brief  Set each @ref md_rtc_time_t field to default value.
  * @param  time pointer to a @ref md_rtc_time_t structure which will be initialized.
  * @retval None
  */
void md_rtc_time_struct_init(md_rtc_time_t *time)
{
	time->hour    = 0;
	time->minute  = 0;
	time->second  = 0;
	time->sub_sec = 0;

	return;
}

/**
  * @brief  Set each @ref md_rtc_date_t field to default value.
  * @param  date: pointer to a @ref md_rtc_date_t structure which will be initialized.
  * @retval None
  */
void md_rtc_date_struct_init(md_rtc_date_t *date)
{
	date->week  = 1;
	date->day   = 1;
	date->month = 1;
	date->year  = 18;

	return;
}

/**
  * @brief  Set specified time.
  * @param  time: pointer to a md_rtc_time_t structure.
  * @param  format: Data format.
  * @retval None.
  */
void md_rtc_set_time(md_rtc_time_t *time, md_rtc_format_t format)
{
	uint32_t tmp;

	if (format == MD_RTC_FORMAT_DEC) {
		tmp = (md_rtc_dec_to_bcd(time->second)) |
			(md_rtc_dec_to_bcd(time->minute) << 8) |
			(md_rtc_dec_to_bcd(time->hour) << 16);
	}
	else {
		tmp = time->second | (time->minute << 8) | (time->hour << 16);
	}

	MD_RTC_UNLOCK();
	WRITE_REG(RTC->TIME, tmp);
	MD_RTC_LOCK();

	tmp = 4000;
	while ((READ_BIT(RTC->CON, RTC_CON_BUSY_MSK)) && (tmp--));
	return;
}

/**
  * @brief  Set specified date.
  * @param  date: pointer to a md_rtc_date_t structure.
  * @param  format: Data format.
  * @retval ALD status.
  */
void md_rtc_set_date(md_rtc_date_t *date, md_rtc_format_t format)
{
	uint32_t tmp;

	if (format == MD_RTC_FORMAT_DEC) {
		tmp = (md_rtc_dec_to_bcd(date->day)) |
			(md_rtc_dec_to_bcd(date->month) << 8) |
			(md_rtc_dec_to_bcd(date->year) << 16) |
			(md_rtc_dec_to_bcd(date->week) << 24);
	}
	else {
		tmp = date->day | (date->month << 8) |
			(date->year << 16) | (date->week << 24);
	}

	MD_RTC_UNLOCK();
	WRITE_REG(RTC->DATE, tmp);
	MD_RTC_LOCK();

	tmp = 4000;
	while ((READ_BIT(RTC->CON, RTC_CON_BUSY_MSK)) && (tmp--));
	return;
}

/**
  * @brief  Get current time.
  * @param  time: pointer to a md_rtc_time_t structure.
  * @param  format: Data format.
  * @retval None
  */
void md_rtc_get_time(md_rtc_time_t *time, md_rtc_format_t format)
{
	uint32_t tmp;

	time->sub_sec = RTC->SSEC & 0xFFFF;
	tmp = RTC->TIME;

	if (format == MD_RTC_FORMAT_DEC) {
		time->second = md_rtc_bcd_to_dec(tmp & 0x7F);
		time->minute = md_rtc_bcd_to_dec((tmp >> 8) & 0x7F);
		time->hour   = md_rtc_bcd_to_dec((tmp >> 16) & 0x7F);
	}
	else {
		time->second = tmp & 0x7F;
		time->minute = (tmp >> 8) & 0x7F;
		time->hour   = (tmp >> 16) & 0x7F;
	}

	return;
}

/**
  * @brief  Get current date.
  * @param  date: pointer to a md_rtc_date_t structure.
  * @param  format: Data format.
  * @retval None
  */
void md_rtc_get_date(md_rtc_date_t *date, md_rtc_format_t format)
{
	uint32_t tmp = RTC->DATE;

	if (format == MD_RTC_FORMAT_DEC) {
		date->day   = md_rtc_bcd_to_dec(tmp & 0x3F);
		date->month = md_rtc_bcd_to_dec((tmp >> 8) & 0x1F);
		date->year  = md_rtc_bcd_to_dec((tmp >> 16) & 0xFF);
		date->week  = md_rtc_bcd_to_dec((tmp >> 24) & 0x7);
	}
	else {
		date->day   = tmp & 0x3F;
		date->month = (tmp >> 8) & 0x1F;
		date->year  = (tmp >> 16) & 0xFF;
		date->week  = (tmp >> 24) & 0x7;
	}

	return;
}

/**
  * @brief  Set each @ref md_rtc_alarm_t field to default value.
  * @param  init pointer to a @ref md_rtc_alarm_t structure which will be initialized.
  * @retval None
  */
void md_rtc_alarm_struct_init(md_rtc_alarm_t *init)
{
	init->idx          = MD_RTC_ALARM_A;
	init->time.hour    = 0;
	init->time.minute  = 0;
	init->time.second  = 0;
	init->time.sub_sec = 0;
	init->mask         = 0;
	init->ss_mask      = MD_RTC_ALARM_SS_MASK_NONE;
	init->sel          = MD_RTC_SELECT_DAY;

	return;
}

/**
  * @brief  Set alarm.
  * @param  alarm: pointer to md_rtc_alarm_t struct.
  * @param  format: Data format.
  * @retval None
  */
void md_rtc_set_alarm(md_rtc_alarm_t *alarm, md_rtc_format_t format)
{
	unsigned int tmp, ss_tmp;

	if (format == MD_RTC_FORMAT_DEC) {

		tmp = (md_rtc_dec_to_bcd(alarm->time.second)) |
		      (md_rtc_dec_to_bcd(alarm->time.minute) << 8) |
		      (md_rtc_dec_to_bcd(alarm->time.hour) << 16) |
		      alarm->mask;

		if (alarm->sel == MD_RTC_SELECT_DAY) {
			tmp |= (md_rtc_dec_to_bcd(alarm->day) << 24);
			tmp &= 0x7FFFFFFF; /* Reset bit31 */
		}
		else {
			tmp |= (1 << (alarm->week + 24));
			tmp |= 0x80000000; /* Set bit31 */
		}
	}
	else {

		tmp = alarm->time.second |
		      (alarm->time.minute << 8) |
		      (alarm->time.hour << 16) |
		      alarm->mask;

		if (alarm->sel == MD_RTC_SELECT_DAY) {
			tmp |= (alarm->day << 24);
			tmp &= 0x7FFFFFFF; /* Reset bit31 */
		}
		else {
			tmp |= (1 << (alarm->week + 24));
			tmp |= 0x80000000; /* Set bit31 */
		}
	}

	ss_tmp = (alarm->time.sub_sec & 0x7F) |
	         (alarm->ss_mask << 24);

	MD_RTC_UNLOCK();

	if (alarm->idx == MD_RTC_ALARM_A) {
		WRITE_REG(RTC->ALMA, tmp);
		WRITE_REG(RTC->ALMASSEC, ss_tmp);
		SET_BIT(RTC->CON, RTC_CON_ALMAEN_MSK);
	}
	else {
		WRITE_REG(RTC->ALMB, tmp);
		WRITE_REG(RTC->ALMBSSEC, ss_tmp);
		SET_BIT(RTC->CON, RTC_CON_ALMBEN_MSK);
	}

	MD_RTC_LOCK();
	return;
}

/**
  * @brief  Set time stamp.
  * @param  sel: time stamp signal select:
  *           @arg MD_RTC_TS_SIGNAL_SEL_TAMPER0
  *           @arg MD_RTC_TS_SIGNAL_SEL_TAMPER1
  * @param  style: time stamp trigger style:
  *           @arg MD_RTC_TS_RISING_EDGE
  *           @arg MD_RTC_TS_FALLING_EDGE
  * @retval None
  */
void md_rtc_set_time_stamp(md_rtc_ts_signal_sel_t sel, md_rtc_ts_trigger_style_t style)
{
	MD_RTC_UNLOCK();

	CLEAR_BIT(RTC->CON, RTC_CON_TSEN_MSK);
	MODIFY_REG(RTC->CON, RTC_CON_TSSEL_MSK, style << RTC_CON_TSSEL_POS);
	MODIFY_REG(RTC->CON, RTC_CON_TSPIN_MSK, sel << RTC_CON_TSPIN_POS);
	SET_BIT(RTC->CON, RTC_CON_TSEN_MSK);

	MD_RTC_LOCK();
	return;
}

/**
  * @brief  Set tamper parameters.
  * @param  tamper: pointer to md_rtc_tamper_t structure.
  * @retval None
  */
void md_rtc_set_tamper(md_rtc_tamper_t *tamper)
{
	MD_RTC_UNLOCK();
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPTS_MSK, tamper->ts << RTC_TAMPCON_TAMPTS_POS);
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPCKS_MSK, tamper->freq << RTC_TAMPCON_TAMPCKS_POSS);
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPFLT_MSK, tamper->dur << RTC_TAMPCON_TAMPFLT_POSS);

	if (tamper->idx == MD_RTC_TAMPER_0) {
		MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMP0LV_MSK, tamper->trig << RTC_TAMPCON_TAMP0LV_POS);
		SET_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMP0EN_MSK);
	}
	else {
		MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMP1LV_MSK, tamper->trig << RTC_TAMPCON_TAMP1LV_POS);
		SET_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMP1EN_MSK);
	}

	MD_RTC_LOCK();
	return;
}

/**
  * @brief  Set each @ref md_rtc_tamper_t field to default value.
  * @param  init pointer to a @ref md_rtc_tamper_t structure which will be initialized.
  * @retval None
  */
void md_rtc_tamper_struct_init(md_rtc_tamper_t *init)
{
	init->idx  = MD_RTC_TAMPER_0;
	init->trig = MD_RTC_TAMPER_TRIGGER_LOW;
	init->freq = MD_RTC_TAMPER_SAMPLING_FREQ_32768;
	init->dur  = MD_RTC_TAMPER_DURATION_2;
	init->ts   = DISABLE;
}
/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
#endif
/**
 * @}
 */
