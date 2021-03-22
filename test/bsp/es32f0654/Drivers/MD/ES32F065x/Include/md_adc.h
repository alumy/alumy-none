/**
  *********************************************************************************
  *
  * @file    md_adc.h
  * @brief   Header file of ADC module driver.
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


#ifndef __ALD_ADC_H__
#define __ALD_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_ADC ADC
  * @brief ADC micro driver
  * @{
  */
/** @defgroup MD_ADC_Pubulic_Types ADC Pubulic Types
  * @{
  */
/**
  * @brief ADC  State structures definition
  */
typedef enum {
	MD_ADC_STATE_RESET    = 0x0U,	/**< ADC not yet initialized or disabled */
	MD_ADC_STATE_READY    = 0x1U,	/**< ADC peripheral ready for use */
	MD_ADC_STATE_BUSY     = 0x2U,	/**< ADC is busy to internal process */
	MD_ADC_STATE_TIMEOUT  = 0x4U,	/**< TimeOut occurrence */
	MD_ADC_STATE_ERROR    = 0x8U,	/**< Internal error occurrence */
	MD_ADC_STATE_BUSY_N   = 0x10U,	/**< Normal channel busy */
	MD_ADC_STATE_BUSY_I   = 0x20U,	/**< Insert channel busy */
	MD_ADC_STATE_BUSY_WDG = 0x40U,	/**< Insert channel busy */
} md_adc_state_t;

/**
  *@brief ADC Error Code
  */
typedef enum {
	MD_ADC_ERROR_NONE     = 0x0U,	/**< No error */
	MD_ADC_ERROR_INTERNAL = 0x1U,	/**< ADC IP internal error*/
	MD_ADC_ERROR_OVR      = 0x2U,	/**< Overrun error */
	MD_ADC_ERROR_DMA      = 0x4U, 	/**< DMA transfer error */
} md_adc_error_t;

/**
  *@brief ADC data alignment
  */
typedef enum {
	MD_ADC_DATAALIGN_RIGHT = 0x0U,	/**< ADC data alignment right */
	MD_ADC_DATAALIGN_LEFT  = 0x1U,	/**< ADC data alignment left */
} md_adc_align_t;

/**
  *@brief ADC config  hannal trigger the EOC IT mode
  */
typedef enum {
	MD_ADC_NCHESEL_MODE_ALL = 0x0U,	/**< ADC set RCHE after convert sequence finish */
	MD_ADC_NCHESEL_MODE_ONE = 0x1U,	/**< ADC set RCHE after one convert finish */
} md_adc_nchesel_t;

/**
  *@brief  ADC channels
  */
typedef enum {
	MD_ADC_CHANNEL_0  = 0x0U, 	/**< ADC channel 0 */
	MD_ADC_CHANNEL_1  = 0x1U, 	/**< ADC channel 1 */
	MD_ADC_CHANNEL_2  = 0x2U, 	/**< ADC channel 2 */
	MD_ADC_CHANNEL_3  = 0x3U, 	/**< ADC channel 3 */
	MD_ADC_CHANNEL_4  = 0x4U, 	/**< ADC channel 4 */
	MD_ADC_CHANNEL_5  = 0x5U, 	/**< ADC channel 5 */
	MD_ADC_CHANNEL_6  = 0x6U, 	/**< ADC channel 6 */
	MD_ADC_CHANNEL_7  = 0x7U, 	/**< ADC channel 7 */
	MD_ADC_CHANNEL_8  = 0x8U, 	/**< ADC channel 8 */
	MD_ADC_CHANNEL_9  = 0x9U, 	/**< ADC channel 9 */
	MD_ADC_CHANNEL_10 = 0xAU, 	/**< ADC channel 10 */
	MD_ADC_CHANNEL_11 = 0xBU, 	/**< ADC channel 11 */
	MD_ADC_CHANNEL_12 = 0xCU, 	/**< ADC channel 12 */
	MD_ADC_CHANNEL_13 = 0xDU, 	/**< ADC channel 13 */
	MD_ADC_CHANNEL_14 = 0xEU, 	/**< ADC channel 14 */
	MD_ADC_CHANNEL_15 = 0xFU, 	/**< ADC channel 15 */
	MD_ADC_CHANNEL_16 = 0x10U,	/**< ADC channel 16 */
	MD_ADC_CHANNEL_17 = 0x11U,	/**< ADC channel 17 */
	MD_ADC_CHANNEL_18 = 0x12U,	/**< ADC channel 18 */
	MD_ADC_CHANNEL_19 = 0x13U,	/**< ADC channel 19 */
} md_adc_channel_t;

/**
  *@brief  ADC sampling times
  */
typedef enum {
	MD_ADC_SAMPLETIME_1  = 0x0U,	/**< ADC sampling times 1 clk */
	MD_ADC_SAMPLETIME_2  = 0x1U,	/**< ADC sampling times 2 clk */
	MD_ADC_SAMPLETIME_4  = 0x2U,	/**< ADC sampling times 4 clk */
	MD_ADC_SAMPLETIME_15 = 0x3U,	/**< ADC sampling times 15 clk */
} md_adc_samp_t;

/**
  *@brief   ADC index into normal group
  */
typedef enum {
	MD_ADC_NCH_IDX_1  = 0x1U, 	/**< ADC normal channel index 1 */
	MD_ADC_NCH_IDX_2  = 0x2U, 	/**< ADC normal channel index 2 */
	MD_ADC_NCH_IDX_3  = 0x3U, 	/**< ADC normal channel index 3 */
	MD_ADC_NCH_IDX_4  = 0x4U, 	/**< ADC normal channel index 4 */
	MD_ADC_NCH_IDX_5  = 0x5U, 	/**< ADC normal channel index 5 */
	MD_ADC_NCH_IDX_6  = 0x6U, 	/**< ADC normal channel index 6 */
	MD_ADC_NCH_IDX_7  = 0x7U, 	/**< ADC normal channel index 7 */
	MD_ADC_NCH_IDX_8  = 0x8U, 	/**< ADC normal channel index 8 */
	MD_ADC_NCH_IDX_9  = 0x9U, 	/**< ADC normal channel index 9 */
	MD_ADC_NCH_IDX_10 = 0xAU, 	/**< ADC normal channel index 10 */
	MD_ADC_NCH_IDX_11 = 0xBU, 	/**< ADC normal channel index 11 */
	MD_ADC_NCH_IDX_12 = 0xCU, 	/**< ADC normal channel index 12 */
	MD_ADC_NCH_IDX_13 = 0xDU, 	/**< ADC normal channel index 13 */
	MD_ADC_NCH_IDX_14 = 0xEU, 	/**< ADC normal channel index 14 */
	MD_ADC_NCH_IDX_15 = 0xFU, 	/**< ADC normal channel index 15 */
	MD_ADC_NCH_IDX_16 = 0x10U,	/**< ADC normal channel index 16 */
} md_adc_nch_idx_t;

/**
  * @brief ADC index into insert group
  */
typedef enum {
	MD_ADC_ICH_IDX_1 = 0x1U,	/**< ADC insert channel index 1 */
	MD_ADC_ICH_IDX_2 = 0x2U,	/**< ADC insert channel index 2 */
	MD_ADC_ICH_IDX_3 = 0x3U,	/**< ADC insert channel index 3 */
	MD_ADC_ICH_IDX_4 = 0x4U,	/**< ADC insert channel index 4 */
} md_adc_ich_idx_t;

/**
  * @brief ADC analog watchdog mode
  */
typedef enum {
	MD_ADC_ANAWTD_NONE       = 0x0U,     	/**< No watch dog */
	MD_ADC_ANAWTD_SING_NM    = 0x800200U,	/**< One normal channel watch dog */
	MD_ADC_ANAWTD_SING_IST   = 0x400200U,	/**< One inset channel Injec watch dog */
	MD_ADC_ANAWTD_SING_NMIST = 0xC00200U,	/**< One normal and inset channel watch dog */
	MD_ADC_ANAWTD_ALL_NM     = 0x800000U,	/**< All normal channel watch dog */
	MD_ADC_ANAWTD_ALL_IST    = 0x400000U,	/**< All inset channel watch dog */
	MD_ADC_ANAWTD_ALL_NMIST  = 0xC00000U,	/**< All normal and inset channel watch dog */
} md_adc_ana_wdg_t;

/**
  * @brief ADC Event type
  */
typedef enum {
	MD_ADC_AWD_EVENT = (1U << 0),	/**< ADC analog watch dog event */
} md_adc_event_type_t;

/**
  * @brief ADC interrupts definition
  */
typedef enum {
	MD_ADC_IT_NH  = (1U << 5), 	/**< ADC it normal */
	MD_ADC_IT_AWD = (1U << 6), 	/**< ADC it awd */
	MD_ADC_IT_IH  = (1U << 7), 	/**< ADC it insert */
	MD_ADC_IT_OVR = (1U << 26),	/**< ADC it overring */
} md_adc_it_t;

/**
  * @brief ADC flags definition
  */
typedef enum {
	MD_ADC_FLAG_AWD = (1U << 0),	/**<ADC flag awd */
	MD_ADC_FLAG_NH  = (1U << 1),	/**<ADC flag normal mode */
	MD_ADC_FLAG_IH  = (1U << 2),	/**<ADC flag inset mode */
	MD_ADC_FLAG_OVR = (1U << 3),	/**<ADC flag ovr */
	MD_ADC_FLAG_NHS = (1U << 8),	/**<ADC flag normal start */
	MD_ADC_FLAG_IHS = (1U << 9),	/**<ADC flag inset start */
} md_adc_flag_t;

/**
  * @brief ADC CLD DIV definition
  */
typedef enum {
	MD_ADC_CKDIV_1   = 0x0U,	/**< ADC CLK DIV 1 */
	MD_ADC_CKDIV_2   = 0x1U,	/**< ADC CLK DIV 2 */
	MD_ADC_CKDIV_4   = 0x2U,	/**< ADC CLK DIV 4 */
	MD_ADC_CKDIV_8   = 0x3U,	/**< ADC CLK DIV 8 */
	MD_ADC_CKDIV_16  = 0x4U,	/**< ADC CLK DIV 16 */
	MD_ADC_CKDIV_32  = 0x5U,	/**< ADC CLK DIV 32 */
	MD_ADC_CKDIV_64  = 0x6U,	/**< ADC CLK DIV 64 */
	MD_ADC_CKDIV_128 = 0x7U,	/**< ADC CLK DIV 128 */
} md_adc_clk_div_t;

/**
  * @brief ADC negative reference voltage definition
  */
typedef enum {
	MD_ADC_NEG_REF_VSS   = 0x0U,	/**< ADC negative regerence voltage vss */
	MD_ADC_NEG_REF_VREFN = 0x1U,	/**< ADC negative regerence voltage vrefn */
} md_adc_neg_ref_t;

/**
  * @brief ADC positive reference voltage definition
  */
typedef enum {
	MD_ADC_POS_REF_VDD        = 0x0U,	/**< ADC posotove reference is VDD */
	MD_ADC_POS_REF_VREEFP     = 0x2U,	/**< ADC posotove reference is VREEFP */
	MD_ADC_POS_REF_VREEFP_BUF = 0x3U,	/**< ADC posotove reference is VREEFP BUFFER */
} md_adc_pos_ref_t;

/**
  * @brief ADC numbers of normal conversion channals
  */
typedef enum {
	MD_ADC_NCH_NR_1  = 0x0U,	/**< ADC number of normal conversion 1 */
	MD_ADC_NCH_NR_2  = 0x1U,	/**< ADC number of normal conversion 2 */
	MD_ADC_NCH_NR_3  = 0x2U,	/**< ADC number of normal conversion 3 */
	MD_ADC_NCH_NR_4  = 0x3U,	/**< ADC number of normal conversion 4 */
	MD_ADC_NCH_NR_5  = 0x4U,	/**< ADC number of normal conversion 5 */
	MD_ADC_NCH_NR_6  = 0x5U,	/**< ADC number of normal conversion 6 */
	MD_ADC_NCH_NR_7  = 0x6U,	/**< ADC number of normal conversion 7 */
	MD_ADC_NCH_NR_8  = 0x7U,	/**< ADC number of normal conversion 8 */
	MD_ADC_NCH_NR_9  = 0x8U,	/**< ADC number of normal conversion 9 */
	MD_ADC_NCH_NR_10 = 0x9U,	/**< ADC number of normal conversion 10 */
	MD_ADC_NCH_NR_11 = 0xAU,	/**< ADC number of normal conversion 11 */
	MD_ADC_NCH_NR_12 = 0xBU,	/**< ADC number of normal conversion 12 */
	MD_ADC_NCH_NR_13 = 0xCU,	/**< ADC number of normal conversion 13 */
	MD_ADC_NCH_NR_14 = 0xDU,	/**< ADC number of normal conversion 14 */
	MD_ADC_NCH_NR_15 = 0xEU,	/**< ADC number of normal conversion 15 */
	MD_ADC_NCH_NR_16 = 0xFU,	/**< ADC number of normal conversion 16 */
} md_adc_nch_nr_t;

/**
  * @brief ADC numbers of insert conversion channals
  */
typedef enum {
	MD_ADC_ICH_NR_1 = 0x0U,	/**< ADC number of insert conversion 1 */
	MD_ADC_ICH_NR_2 = 0x1U,	/**< ADC number of insert conversion 2 */
	MD_ADC_ICH_NR_3 = 0x2U,	/**< ADC number of insert conversion 3 */
	MD_ADC_ICH_NR_4 = 0x3U,	/**< ADC number of insert conversion 4 */
} md_adc_ich_nr_t;

/**
  * @brief ADC discontinuous mode choose
  */
typedef enum {
	MD_ADC_ALL_DISABLE = 0x0U,	/**< ADC discontinuous mode all disable */
	MD_ADC_NCH_DISC_EN = 0x1U,	/**< ADC normal channel discontinuous mode enable */
	MD_ADC_ICH_DISC_EN = 0x2U,	/**< ADC insert channel discontinuous mode enable */
} md_adc_disc_mode_t;

/**
  * @brief ADC numbers of channals in discontinuous conversion mode
  */
typedef enum {
	MD_ADC_DISC_NR_1 = 0x0U,	/**< ADC number of discontinuous conversion 1 */
	MD_ADC_DISC_NR_2 = 0x1U,	/**< ADC number of discontinuous conversion 2 */
	MD_ADC_DISC_NR_3 = 0x2U,	/**< ADC number of discontinuous conversion 3 */
	MD_ADC_DISC_NR_4 = 0x3U,	/**< ADC number of discontinuous conversion 4 */
	MD_ADC_DISC_NR_5 = 0x4U,	/**< ADC number of discontinuous conversion 5 */
	MD_ADC_DISC_NR_6 = 0x5U,	/**< ADC number of discontinuous conversion 6 */
	MD_ADC_DISC_NR_7 = 0x6U,	/**< ADC number of discontinuous conversion 7 */
	MD_ADC_DISC_NR_8 = 0x7U,	/**< ADC number of discontinuous conversion 8 */
} md_adc_disc_nr_t;

/**
  * @brief ADC resolution of conversion
  */
typedef enum {
	MD_ADC_CONV_BIT_6  = 0x0U,	/**< ADC resolution of conversion 6 */
	MD_ADC_CONV_BIT_8  = 0x1U,	/**< ADC resolution of conversion 8 */
	MD_ADC_CONV_BIT_10 = 0x2U,	/**< ADC resolution of conversion 10 */
	MD_ADC_CONV_BIT_12 = 0x3U,	/**< ADC resolution of conversion 12 */
} md_adc_conv_bit_t;

/**
  * @brief ADC trigger conversion mode
  */
typedef enum {
	MD_ADC_TRIG_SOFT     = 0x0U,	/**< ADC tirgger conversion soft */
	MD_ADC_TRIG_PIS      = 0x1U,	/**< ADC tirgger conversion pis */
	MD_ADC_TRIG_PIS_SOFT = 0x2U,	/**< ADC tirgger conversion all */
} md_adc_trig_mode_t;

/**
  * @brief  Structure definition of ADC and normal group initialization
  */
typedef struct {
	md_adc_align_t align;		/**< Specifies ADC data alignment */
	type_func_t scan;         	/**< Choose scan mode enable or not */
	type_func_t cont;       	/**< Choose continuous mode enable or not */
	md_adc_nch_nr_t nch_nr;  	/**< Number of normal ranks will be converted */
	md_adc_disc_mode_t disc;    	/**< Discontinuous mode enable or not */
	md_adc_disc_nr_t disc_nr;	/**< Number of discontinuous conversions channel */
	md_adc_conv_bit_t data_bit;   	/**< The precision of conversion */
	md_adc_clk_div_t div;		/**< ADCCLK divider */
	md_adc_nchesel_t nche_sel;	/**< Trigger the NCHE FALG mode */
	type_func_t gaincal;		/**< Enable or disable the gainal*/
	type_func_t offcal;		/**< Enable or disable the offcal*/
	md_adc_neg_ref_t n_ref;    	/**< The negative reference voltage*/
	md_adc_pos_ref_t p_ref;    	/**< The positive reference voltage*/
	type_func_t diff;		/**< Enable or disable the diff */
	type_func_t lsen;		/**< Enable or disable the lsen */
	type_func_t vrbuf;		/**< Enable or disable the vrbuf*/
	type_func_t vcmen;		/**< Enable or disable the vvmen*/
	type_func_t vrefen;		/**< Enable or disable the vrefen*/
	type_func_t irefen;		/**< Enable or disable the irefen*/
} md_adc_init_t;

/**
  * @brief  Structure definition of ADC channel for normal group
  */
typedef struct {
	md_adc_channel_t ch;	/**< The channel to configure into ADC normal group */
	md_adc_nch_idx_t idx;	/**< The index in the normal group sequencer */
	md_adc_samp_t samp;	/**< Sampling time value to be set */
} md_adc_nch_conf_t;

/**
  * @brief  ADC Configuration insert Channel structure definition
  */
typedef struct {
	md_adc_channel_t ch;	/**< Selection of ADC channel to configure */
	md_adc_ich_idx_t idx;	/**< Index in the insert group sequencer */
	md_adc_samp_t samp;	/**< Sampling time value for selected channel */
	uint32_t offset;	/**< The offset about converted data */
	md_adc_ich_nr_t nr;	/**< The number of insert ranks */
	type_func_t auto_m;	/**< insert sequence's auto function */
} md_adc_ich_conf_t;
/**
  * @}
  */

/**
  * @defgroup MD_ADC_Public_Macros ADC Public Macros
  * @{
  */
#define MD_ADC_ENABLE(x)		(SET_BIT((x)->CON1, ADC_CON1_ADCEN_MSK))
#define MD_ADC_DISABLE(x)		(CLEAR_BIT((x)->CON1, ADC_CON1_ADCEN_MSK))
#define MD_ADC_NH_TRIG_BY_SOFT(x)	(SET_BIT((x)->CON1, ADC_CON1_NCHTRG_MSK))
#define MD_ADC_IH_TRIG_BY_SOFT(x)	(SET_BIT((x)->CON1, ADC_CON1_ICHTRG_MSK))
#define MD_ADC_VREF_OUT_ENABLE(x)	(SET_BIT((x)->CCR, ADC_CCR_VREFOEN_MSK))
#define MD_ADC_VREF_OUT_DISABLE(x)	(CLEAR_BIT((x)->CCR, ADC_CCR_VREFOEN_MSK))
#define MD_ADC_SPEED_HIGH_ENABLE(x)	(SET_BIT((x)->CCR, ADC_CCR_PWRMODSEL_MSK))
#define MD_ADC_SPEED_HIGH_DISABLE(x)	(CLEAR_BIT((x)->CCR, ADC_CCR_PWRMODSEL_MSK))
#define MD_ADC_CALIBRATE_ENABLE(x)	(SET_BIT((x)->CCR, ADC_CCR_TRMEN_MSK))
#define MD_ADC_CALIBRATE_DISABLE(x)	(CLEAR_BIT((x)->CCR, ADC_CCR_TRMEN_MSK))
/**
  * @}
  */

/** @defgroup MD_ADC_Public_Functions ADC Public Functions
  * @{
  */
/** @defgroup MD_ADC_Public_Functions_Group2 STAT
  * @{
  */

/**
  * @brief  Get Status of Watch_dog flag.
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_stat_awdf(ADC_TypeDef *adc)
{
	return READ_BITS(adc->STAT, ADC_STAT_AWDF_MSK, ADC_STAT_AWDF_POS);
}

/**
  * @brief  Get Status of Normal channel convert complete flag.
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_stat_nche(ADC_TypeDef *adc)
{
	return READ_BITS(adc->STAT, ADC_STAT_NCHE_MSK, ADC_STAT_NCHE_POS);
}

/**
  * @brief  Get Status of Insert channel convert complete flag.
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_stat_iche(ADC_TypeDef *adc)
{
	return READ_BITS(adc->STAT, ADC_STAT_ICHE_MSK, ADC_STAT_ICHE_POS);
}

/**
  * @brief  Get Status of over flag.
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_stat_ovr(ADC_TypeDef *adc)
{
	return READ_BITS(adc->STAT, ADC_STAT_OVR_MSK, ADC_STAT_OVR_POS);
}

/**
  * @brief  Get Status of Normal channel convert start flag.
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_stat_nchs(ADC_TypeDef *adc)
{
	return READ_BITS(adc->STAT, ADC_STAT_NCHS_MSK, ADC_STAT_NCHS_POS);
}

/**
  * @brief  Get Status of Insert channel convert start flag.
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_stat_ichs(ADC_TypeDef *adc)
{
	return READ_BITS(adc->STAT, ADC_STAT_ICHS_MSK, ADC_STAT_ICHS_POS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group3 CLR
  * @{
  */
/**
  * @brief  Clear Watch_dog flag.
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_clr_awdf(ADC_TypeDef *adc)
{
	SET_BIT(adc->CLR, ADC_CLR_AWDF_MSK);
}

/**
  * @brief  Clear Normal channel convert complete flag.
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_clr_nche(ADC_TypeDef *adc)
{
	SET_BIT(adc->CLR, ADC_CLR_NCHE_MSK);
}

/**
  * @brief  Clear Insert channel convert complete flag.
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_clr_iche(ADC_TypeDef *adc)
{
	SET_BIT(adc->CLR, ADC_CLR_ICHE_MSK);
}

/**
  * @brief  Clear over flag.
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_clr_ovr(ADC_TypeDef *adc)
{
	SET_BIT(adc->CLR, ADC_CLR_OVR_MSK);
}

/**
  * @brief  Clear Normal channel convert start flag.
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_clr_nchs(ADC_TypeDef *adc)
{
	SET_BIT(adc->CLR, ADC_CLR_NCHS_MSK);
}

/**
  * @brief  Clear Insert channel convert start flag.
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_clr_ichs(ADC_TypeDef *adc)
{
	SET_BIT(adc->CLR, ADC_CLR_ICHS_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group4 CON0
  * @{
  */
/**
  * @brief  Set analog watchdog channel selection
  * @param  adc ADC Instance
  * @param  sel This parameter write 0 to 18 to represent channel 0 to channel 18
  * @retval None
  */
__STATIC_INLINE void md_adc_set_channel_awdch(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CON0, ADC_CON0_AWDCH_MSK, sel << ADC_CON0_AWDCH_POSS);
}

/**
  * @brief  Get analog watchdog channel selection
  * @param  adc ADC Instance
  * @retval watch-dog choose which channel 
  */
__STATIC_INLINE uint32_t md_adc_get_channel_awdch(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_AWDCH_MSK, ADC_CON0_AWDCH_POSS);
}

/**
  * @brief  Interrupt enable for end of normal channel conversion
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_conv_end_interrupt_enable_ncheie(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_NCHEIE_MSK);
}

/**
  * @brief  Interrupt disable for end of normal channel conversion
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_conv_end_interrupt_disable_ncheie(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_NCHEIE_MSK);
}

/**
  * @brief  Check if interrupt enable for end of normal channel conversion 
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_conv_end_interrupt_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_NCHEIE_MSK, ADC_CON0_NCHEIE_POS);
}

/**
  * @brief  Analog watchdog interrupt enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_analog_wdt_interrupt_enable_awdie(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_AWDIE_MSK);
}

/**
  * @brief  Analog watchdog interrupt disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_analog_wdt_interrupt_disable_awdie(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_AWDIE_MSK);
}

/**
  * @brief  Check if interrupt enable for analog watchdog 
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_analog_wdt_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_AWDIE_MSK, ADC_CON0_AWDIE_POS);
}

/**
  * @brief  Interrupt enable for inserted channels convert complete
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_inserted_channel_interrupt_enable_icheie(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_ICHEIE_MSK);
}

/**
  * @brief  Interrupt disable for inserted channels convert complete
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_inserted_channel_interrupt_disable_icheie(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_ICHEIE_MSK);
}

/**
  * @brief  Check if interrupt enable for inserted channels convert complete
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_inserted_channel_interrupt_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_ICHEIE_MSK, ADC_CON0_ICHEIE_POS);
}

/**
  * @brief  Scan mode enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_scan_mode_enable_scanen(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_SCANEN_MSK);
}

/**
  * @brief  Scan mode disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_scanen(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_SCANEN_MSK);
}

/**
  * @brief  Check if enable for scan mode
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_scan_mode_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_SCANEN_MSK, ADC_CON0_SCANEN_POS);
}

/**
  * @brief  Enable the watchdog on a single channel in scan mode
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_wdt_single_channel_scan_mode_enable_awdsgl(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_AWDSGL_MSK);
}

/**
  * @brief  Disable the watchdog on a single channel in scan mode
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_wdt_single_channel_scan_mode_disable_awdsgl(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_AWDSGL_MSK);
}

/**
  * @brief  Check if enable for watchdog on a single channel in scan mode
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_awdsgl(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_AWDSGL_MSK, ADC_CON0_AWDSGL_POS);
}

/**
  * @brief  Automatic inserted group conversion enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_auto_inserted_conversion_enable_iauto(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_IAUTO_MSK);
}

/**
  * @brief  Automatic inserted group conversion disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_auto_inserted_conversion_disable_iauto(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_IAUTO_MSK);
}

/**
  * @brief  Check if enable for automatic inserted group conversion
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_iauto(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_IAUTO_MSK, ADC_CON0_IAUTO_POS);
}

/**
  * @brief  Discontinuous mode on normal channels enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_normal_channel_discon_mode_enable_nchdcen(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_NCHDCEN_MSK);
}

/**
  * @brief  Discontinuous mode on normal channels disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_normal_channel_discon_mode_disable_nchdcen(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_NCHDCEN_MSK);
}

/**
  * @brief  Check if enable for discontinuous mode on normal channels
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_normal_channel_discon_mode_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_NCHDCEN_MSK, ADC_CON0_NCHDCEN_POS);
}

/**
  * @brief  Discontinuous mode on inserted channels enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_inserted_channel_discon_mode_enable_ichdcen(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_ICHDCEN_MSK);
}

/**
  * @brief  Discontinuous mode on inserted channels disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_inserted_channel_discon_mode_disable_ichdcen(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_ICHDCEN_MSK);
}

/**
  * @brief  Check if enable for discontinuous mode on inserted channels
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_inserted_channel_discon_mode_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_ICHDCEN_MSK, ADC_CON0_ICHDCEN_POS);
}

/**
  * @brief  External trigger enable for discontinuous channels number set
  * @param  adc ADC Instance
  * @param  sel number of channels 0 to 7 to represent number of 1 channel to number of 8 channels 
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ex_trigger_discon_etrgn(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CON0, ADC_CON0_ETRGN_MSK, sel << ADC_CON0_ETRGN_POSS);
}
/**
  * @brief  gets channels of extrigger noncontinuous.
  * @param  adc ADC Instance
  * @retval return number of channel	
  */
__STATIC_INLINE uint32_t md_adc_get_ex_trigger_discon_etrgn(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_ETRGN_MSK, ADC_CON0_ETRGN_POSS);
}

/**
  * @brief  Analog watchdog enable on inserted channels
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_wdt_inserted_channel_enable_ichwdten(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_ICHWDTEN_MSK);
}

/**
  * @brief  Analog watchdog disable on inserted channels
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_wdt_inserted_channel_disable_ichwdten(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_ICHWDTEN_MSK);
}

/**
  * @brief  Check if enable for analog watchdog on inserted channels
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_wdt_inserted_channel_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_ICHWDTEN_MSK, ADC_CON0_ICHWDTEN_POS);
}

/**
  * @brief  Analog watchdog enable on normal channels
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_wdt_normal_channel_enable_nchwden(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_NCHWDEN_MSK);
}

/**
  * @brief  Analog watchdog disable on normal channels
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_wdt_normal_channel_disable_nchwden(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_NCHWDEN_MSK);
}

/**
  * @brief  Check if enable for analog watchdog on normal channels
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_wdt_normal_channel_enable_nchwden(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_NCHWDEN_MSK, ADC_CON0_NCHWDEN_POS);
}

/**
  * @brief  Sets convert bit
  * @param  adc ADC Instance
  * @param  rsel adc convert bit choose
  * @retval NONE
  */
__STATIC_INLINE void md_adc_set_resolution_rsel(ADC_TypeDef *adc, uint32_t rsel)
{
	MODIFY_REG(adc->CON0, ADC_CON0_RSEL_MSK, rsel << ADC_CON0_RSEL_POSS);
}

/**
  * @brief  Gets convert bit
  * @param  adc ADC Instance
  * @retval  Value of the resolution bits
  */
__STATIC_INLINE uint32_t md_adc_get_resolution_rsel(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_RSEL_MSK, ADC_CON0_RSEL_POSS);
}

/**
  * @brief  Overrun interrupt enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_overrun_interrupt_enable_ovrie(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON0, ADC_CON0_OVRIE_MSK);
}

/**
  * @brief  Overrun interrupt disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_overrun_interrupt_disable_ovrie(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON0, ADC_CON0_OVRIE_MSK);
}

/**
  * @brief  Check if interrupt enable for overrun
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ovrie(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON0, ADC_CON0_OVRIE_MSK, ADC_CON0_OVRIE_POS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group5 CON1
  * @{
  */
/**
  * @brief  A/D converter enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_converter_enable_adcen(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON1, ADC_CON1_ADCEN_MSK);
}

/**
  * @brief  A/D converter disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_converter_disable_adcen(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON1, ADC_CON1_ADCEN_MSK);
}

/**
  * @brief  Check if converter enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_converter_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON1, ADC_CON1_ADCEN_MSK, ADC_CON1_ADCEN_POS);
}

/**
  * @brief  Continuous conversion enable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_continuous_conversion_enable_cm(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON1, ADC_CON1_CM_MSK);
}

/**
  * @brief  Continuous conversion disable
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_continuous_conversion_disable_cm(ADC_TypeDef *adc)
{
	CLEAR_BIT(adc->CON1, ADC_CON1_CM_MSK);
}

/**
  * @brief  Check if continuous conversion enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_continuous_conversion_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON1, ADC_CON1_CM_MSK, ADC_CON1_CM_POS);
}

/**
  * @brief  Set overflow detection
  * @param  adc ADC Instance
  * @param  sel set 0 to not forbid or 1 to forbid 
  * @retval None
  */
__STATIC_INLINE void md_adc_set_overflow_detection_state_ovrdis(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CON1, ADC_CON1_OVRDIS_MSK, sel << ADC_CON1_OVRDIS_POS);
}

/**
  * @brief  Get overflow detection
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_overflow_detection_state_ovrdis(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON1, ADC_CON1_OVRDIS_MSK, ADC_CON1_OVRDIS_POS);
}

/**
  * @brief  Set end of conversion selection
  * @param  adc ADC Instance
  * @param  sel normal channel finish flag trigger condition
  * @retval None
  */
__STATIC_INLINE void md_adc_set_eoc_selection_nchesel(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CON1, ADC_CON1_NCHESEL_MSK, sel << ADC_CON1_NCHESEL_POS);
}

/**
  * @brief  Get end of conversion selection
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_eoc_selection_nchesel(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON1, ADC_CON1_NCHESEL_MSK, ADC_CON1_NCHESEL_POS);
}

/**
  * @brief  Set data alignment
  * @param  adc ADC Instance
  * @param  sel set 0 to rignt alignment or set 1 to left alignment
  * @retval None
  */
__STATIC_INLINE void md_adc_set_data_alignment_align(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CON1, ADC_CON1_ALIGN_MSK, sel << ADC_CON1_ALIGN_POS);
}

/**
  * @brief  Get data alignment
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_data_alignment_align(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CON1, ADC_CON1_ALIGN_MSK, ADC_CON1_ALIGN_POS);
}

/**
  * @brief  Start conversion of inserted channels
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_inserted_channel_conv_start_ichtrg(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON1, ADC_CON1_ICHTRG_MSK);
}

/**
  * @brief  Start conversion of normal channels
  * @param  adc ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_channel_conv_start_nchtrg(ADC_TypeDef *adc)
{
	SET_BIT(adc->CON1, ADC_CON1_NCHTRG_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group6 SMPT1
  * @{
  */
/**
  * @brief  Set channel sampling time configuration
  * @param  adc ADC Instance
  * @param  val value of Sampling time of each channels[0 ~ 15]	
  * @retval None
  */
__STATIC_INLINE void md_adc_set_smpt1_cht(ADC_TypeDef *adc, uint32_t val)
{
	WRITE_REG(adc->SMPT1, val);
}

/**
  * @brief  Get channel sampling time configuration
  * @param  adc ADC Instance
  * @retval Sampling time of each channels[0 ~ 15]		
  */
__STATIC_INLINE uint32_t md_adc_get_smpt1_cht(ADC_TypeDef *adc)
{
	return READ_REG(adc->SMPT1);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group7 SMPT2
  * @{
  */
/**
  * @brief  Set channel sampling time configuration
  * @param  adc ADC Instance
  * @param  val value of Sampling time of each channels[16 ~ 19]	
  * @retval None
  */
__STATIC_INLINE void md_adc_set_smpt2_cht(ADC_TypeDef *adc, uint32_t val)
{
	WRITE_REG(adc->SMPT2, val);
}

/**
  * @brief  Get channel sampling time configuration
  * @param  adc ADC Instance
  * @retval Sampling time of each channels[16 ~ 19]		
  */
__STATIC_INLINE uint32_t md_adc_get_smpt2_cht(ADC_TypeDef *adc)
{
	return READ_REG(adc->SMPT2) & 0xff;
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group8 ICHOFF1
  * @{
  */
/**
  * @brief  Set data offset for inserted channel(ADC_ICHDR1) 
  * @param  adc ADC Instance
  * @param  val Offset data	
  * @retval None
  */
__STATIC_INLINE void md_adc_set_joffset_ichoff1_ioff(ADC_TypeDef *adc, uint32_t val)
{
	WRITE_REG(adc->ICHOFF[0], val);
}

/**
  * @brief  Get data offset for inserted channel(ADC_ICHDR1) 
  * @param  adc ADC Instance
  * @param  val Offset data	
  * @retval Offset data	
  */
__STATIC_INLINE uint32_t md_adc_get_joffset_ichoff1_ioff(ADC_TypeDef *adc, uint32_t val)
{
	return (READ_REG(adc->ICHOFF[0]) & 0xfff);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group9 ICHOFF2
  * @{
  */
/**
  * @brief  Set data offset for inserted channel(ADC_ICHDR2)
  * @param  adc ADC Instance
  * @param  val value of Offset data	
  * @retval None
  */
__STATIC_INLINE void md_adc_set_joffset_ichoff2_ioff(ADC_TypeDef *adc, uint32_t val)
{
	WRITE_REG(adc->ICHOFF[1], val);
}

/**
  * @brief  Get data offset for inserted channel(ADC_ICHDR2)
  * @param  adc ADC Instance
  * @retval Offset data	
  */
__STATIC_INLINE uint32_t md_adc_get_joffset_ichoff2_ioff(ADC_TypeDef *adc)
{
	return (READ_REG(adc->ICHOFF[1]) & 0xfff);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group10 ICHOFF3
  * @{
  */
/**
  * @brief  Set data offset for inserted channel(ADC_ICHDR3) 
  * @param  adc ADC Instance
  * @param  val value of Offset data	
  * @retval None
  */
__STATIC_INLINE void md_adc_set_joffset_ichoff3_ioff(ADC_TypeDef *adc, uint32_t val)
{
	WRITE_REG(adc->ICHOFF[2], val);
}

/**
  * @brief  Get data offset for inserted channel(ADC_ICHDR3)
  * @param  adc ADC Instance
  * @retval Offset data	
  */
__STATIC_INLINE uint32_t md_adc_get_joffset_ichoff3_ioff(ADC_TypeDef *adc)
{
	return (READ_REG(adc->ICHOFF[2]) & 0xfff) ;
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group11 ICHOFF4
  * @{
  */
/**
  * @brief  Set data offset for inserted channel(ADC_ICHDR4)
  * @param  adc ADC Instance
  * @param  val value of Offset data	
  * @retval None
  */
__STATIC_INLINE void md_adc_set_joffset_ichoff4_ioff(ADC_TypeDef *adc, uint32_t val)
{
	WRITE_REG(adc->ICHOFF[3], val);
}

/**
  * @brief  Get data offset for inserted channel(ADC_ICHDR4)
  * @param  adc ADC Instance
  * @retval Offset data	
  */
__STATIC_INLINE uint32_t md_adc_get_joffset_ichoff4_ioff(ADC_TypeDef *adc)
{
	return (READ_REG(adc->ICHOFF[3]) & 0xfff) ;
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group12 WDTH
  * @{
  */
/**
  * @brief  Set analog watchdog higher threshold
  * @param  adc ADC Instance
  * @param  val value of Higher threshold value
  * @retval None	
  */
__STATIC_INLINE void md_adc_set_higher_threshold_ht(ADC_TypeDef *adc, uint32_t val)
{
	MODIFY_REG(adc->WDTH, ADC_WDTH_HT_MSK, val << ADC_WDTH_HT_POSS);
}

/**
  * @brief  Get analog watchdog higher threshold
  * @param  adc ADC Instance
  * @retval Higher threshold value
  */
__STATIC_INLINE uint32_t md_adc_get_higher_threshold_ht(ADC_TypeDef *adc)
{
	return READ_BITS(adc->WDTH, ADC_WDTH_HT_MSK, ADC_WDTH_HT_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group13 WDTL
  * @{
  */
/**
  * @brief  Set analog watchdog lower threshold
  * @param  adc ADC Instance
  * @param  lt value of Lower threshold value
  * @retval None	
  */
__STATIC_INLINE void md_adc_set_lower_threshold_lt(ADC_TypeDef *adc, uint32_t lt)
{
	MODIFY_REG(adc->WDTL, ADC_WDTL_LT_MSK, lt << ADC_WDTL_LT_POSS);
}

/**
  * @brief  Get analog watchdog lower threshold
  * @param  adc ADC Instance
  * @retval Lower threshold value
  */
__STATIC_INLINE uint32_t md_adc_get_lower_threshold_lt(ADC_TypeDef *adc)
{
	return READ_BITS(adc->WDTL, ADC_WDTL_LT_MSK, ADC_WDTL_LT_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group14 NCHS1
  * @{
  */
/**
  * @brief  Set 1st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns1 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_1st_conv_ns1(ADC_TypeDef *adc, uint32_t ns1)
{
	MODIFY_REG(adc->NCHS1, ADC_NCHS1_NS1_MSK, ns1 << ADC_NCHS1_NS1_POSS);
}

/**
  * @brief  Get 1st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval  Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_1st_conv_ns1(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS1, ADC_NCHS1_NS1_MSK, ADC_NCHS1_NS1_POSS);
}
/**
  * @brief  Set 2st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns2 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_2st_conv_ns2(ADC_TypeDef *adc, uint32_t ns2)
{
	MODIFY_REG(adc->NCHS1, ADC_NCHS1_NS2_MSK, ns2 << ADC_NCHS1_NS2_POSS);
}

/**
  * @brief  Get 2st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_2st_conv_ns2(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS1, ADC_NCHS1_NS2_MSK, ADC_NCHS1_NS2_POSS);
}
/**
  * @brief  Set 3st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns3 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_3st_conv_ns3(ADC_TypeDef *adc, uint32_t ns3)
{
	MODIFY_REG(adc->NCHS1, ADC_NCHS1_NS3_MSK, ns3 << ADC_NCHS1_NS3_POSS);
}

/**
  * @brief  Get 3st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_3st_conv_ns3(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS1, ADC_NCHS1_NS3_MSK, ADC_NCHS1_NS3_POSS);
}
/**
  * @brief  Set 4st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns4 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_4st_conv_ns4(ADC_TypeDef *adc, uint32_t ns4)
{
	MODIFY_REG(adc->NCHS1, ADC_NCHS1_NS4_MSK, ns4 << ADC_NCHS1_NS4_POSS);
}

/**
  * @brief  Get 4st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_4st_conv_ns4(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS1, ADC_NCHS1_NS4_MSK, ADC_NCHS1_NS4_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group15 NCHS2
  * @{
  */
/**
  * @brief  Set 5st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns5 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_5st_conv_ns5(ADC_TypeDef *adc, uint32_t ns5)
{
	MODIFY_REG(adc->NCHS2, ADC_NCHS2_NS5_MSK, ns5 << ADC_NCHS2_NS5_POSS);
}

/**
  * @brief  Get 5st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_5st_conv_ns5(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS2, ADC_NCHS2_NS5_MSK, ADC_NCHS2_NS5_POSS);
}

/**
  * @brief  Set 6st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns6 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_6st_conv_ns6(ADC_TypeDef *adc, uint32_t ns6)
{
	MODIFY_REG(adc->NCHS2, ADC_NCHS2_NS6_MSK, ns6 << ADC_NCHS2_NS6_POSS);
}

/**
  * @brief  Get 6st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval  Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_6st_conv_ns6(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS2, ADC_NCHS2_NS6_MSK, ADC_NCHS2_NS6_POSS);
}

/**
  * @brief  Set 7st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns7 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_7st_conv_ns7(ADC_TypeDef *adc, uint32_t ns7)
{
	MODIFY_REG(adc->NCHS2, ADC_NCHS2_NS7_MSK, ns7 << ADC_NCHS2_NS7_POSS);
}

/**
  * @brief  Get 7st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval  Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_7st_conv_ns7(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS2, ADC_NCHS2_NS7_MSK, ADC_NCHS2_NS7_POSS);
}

/**
  * @brief  Set 8st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns8 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_8st_conv_ns8(ADC_TypeDef *adc, uint32_t ns8)
{
	MODIFY_REG(adc->NCHS2, ADC_NCHS2_NS8_MSK, ns8 << ADC_NCHS2_NS8_POSS);
}

/**
  * @brief  Get 8st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval  Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_8st_conv_ns8(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS2, ADC_NCHS2_NS8_MSK, ADC_NCHS2_NS8_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group16 NCHS3
  * @{
  */
/**
  * @brief  Set 9st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns9 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_9st_conv_ns9(ADC_TypeDef *adc, uint32_t ns9)
{
	MODIFY_REG(adc->NCHS3, ADC_NCHS3_NS9_MSK, ns9 << ADC_NCHS3_NS9_POSS);
}

/**
  * @brief  Get 9st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_9st_conv_ns9(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS3, ADC_NCHS3_NS9_MSK, ADC_NCHS3_NS9_POSS);
}

/**
  * @brief  Set 10st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns10 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_10st_conv_ns10(ADC_TypeDef *adc, uint32_t ns10)
{
	MODIFY_REG(adc->NCHS3, ADC_NCHS3_NS10_MSK, ns10 << ADC_NCHS3_NS10_POSS);
}

/**
  * @brief  Get 10st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_10st_conv_ns10(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS3, ADC_NCHS3_NS10_MSK, ADC_NCHS3_NS10_POSS);
}

/**
  * @brief  Set 11st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns11 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_11st_conv_ns11(ADC_TypeDef *adc, uint32_t ns11)
{
	MODIFY_REG(adc->NCHS3, ADC_NCHS3_NS10_MSK, ns11 << ADC_NCHS3_NS11_POSS);
}

/**
  * @brief  Get 11st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_11st_conv_ns11(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS3, ADC_NCHS3_NS11_MSK, ADC_NCHS3_NS11_POSS);
}

/**
  * @brief  Set 12st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns12 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_12st_conv_ns12(ADC_TypeDef *adc, uint32_t ns12)
{
	MODIFY_REG(adc->NCHS3, ADC_NCHS3_NS12_MSK, ns12 << ADC_NCHS3_NS12_POSS);
}

/**
  * @brief  Get 12st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_12st_conv_ns12(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS3, ADC_NCHS3_NS12_MSK, ADC_NCHS3_NS12_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group17 NCHS4
  * @{
  */
/**
  * @brief  Set 13st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns13 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_13st_conv_ns13(ADC_TypeDef *adc, uint32_t ns13)
{
	MODIFY_REG(adc->NCHS4, ADC_NCHS4_NS13_MSK, ns13 << ADC_NCHS4_NS13_POSS);
}

/**
  * @brief  Get 13st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_13st_conv_ns13(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS4, ADC_NCHS4_NS13_MSK, ADC_NCHS4_NS13_POSS);
}

/**
  * @brief  Set 14st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns14 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_14st_conv_ns14(ADC_TypeDef *adc, uint32_t ns14)
{
	MODIFY_REG(adc->NCHS4, ADC_NCHS4_NS14_MSK, ns14 << ADC_NCHS4_NS14_POSS);
}

/**
  * @brief  Get 14st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_14st_conv_ns14(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS4, ADC_NCHS4_NS14_MSK, ADC_NCHS4_NS14_POSS);
}

/**
  * @brief  Set 15st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns15 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_15st_conv_ns15(ADC_TypeDef *adc, uint32_t ns15)
{
	MODIFY_REG(adc->NCHS4, ADC_NCHS4_NS15_MSK, ns15 << ADC_NCHS4_NS15_POSS);
}

/**
  * @brief  Get 15st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_15st_conv_ns15(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS4, ADC_NCHS4_NS15_MSK, ADC_NCHS4_NS15_POSS);
}

/**
  * @brief  Set 16st conversion in normal sequence
  * @param  adc ADC Instance
  * @param  ns16 Channel number[0 ~ 18]
  * @retval None
  */
__STATIC_INLINE void md_adc_set_normal_16st_conv_ns16(ADC_TypeDef *adc, uint32_t ns16)
{
	MODIFY_REG(adc->NCHS4, ADC_NCHS4_NS16_MSK, ns16 << ADC_NCHS4_NS16_POSS);
}

/**
  * @brief  Get 16st conversion in normal sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_normal_16st_conv_ns16(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHS4, ADC_NCHS4_NS16_MSK, ADC_NCHS4_NS16_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group18 ICHS
  * @{
  */
/**
  * @brief  Set 1st conversion in inserted sequence
   * @param  adc ADC Instance
  * @param  is1 Channel number[0 ~ 18]
  * @retval None
  */
 __STATIC_INLINE void md_adc_set_insert_1st_conv_is1(ADC_TypeDef *adc, uint32_t is1)
{
	MODIFY_REG(adc->ICHS, ADC_ICHS_IS1_MSK, is1 << ADC_ICHS_IS1_POSS);
}

/**
  * @brief  Get 1st conversion in inserted sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_insert_1st_conv_is1(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHS, ADC_ICHS_IS1_MSK, ADC_ICHS_IS1_POSS);
}

/**
  * @brief  Set 2st conversion in inserted sequence
  * @param  adc ADC Instance
  * @param  is2 Channel number[0 ~ 18]
  * @retval None
  */
 __STATIC_INLINE void md_adc_set_insert_2st_conv_is2(ADC_TypeDef *adc, uint32_t is2)
{
	MODIFY_REG(adc->ICHS, ADC_ICHS_IS2_MSK, is2 << ADC_ICHS_IS2_POSS);
}

/**
  * @brief  Get 2st conversion in inserted sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_insert_2st_conv_is2(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHS, ADC_ICHS_IS2_MSK, ADC_ICHS_IS2_POSS);
}

/**
  * @brief  Set 3st conversion in inserted sequence
  * @param  adc ADC Instance
  * @param  is3 Channel number[0 ~ 18]
  * @retval None
  */
 __STATIC_INLINE void md_adc_set_insert_3st_conv_is3(ADC_TypeDef *adc, uint32_t is3)
{
	MODIFY_REG(adc->ICHS, ADC_ICHS_IS3_MSK, is3 << ADC_ICHS_IS3_POSS);
}

/**
  * @brief  Get 3st conversion in inserted sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_insert_3st_conv_is3(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHS, ADC_ICHS_IS3_MSK, ADC_ICHS_IS3_POSS);
}

/**
  * @brief  Set 4st conversion in inserted sequence
  * @param  adc ADC Instance
  * @param  is4 Channel number[0 ~ 18]
  * @retval None
  */
 __STATIC_INLINE void md_adc_set_insert_4st_conv_is4(ADC_TypeDef *adc, uint32_t is4)
{
	MODIFY_REG(adc->ICHS, ADC_ICHS_IS4_MSK, is4 << ADC_ICHS_IS4_POSS);
}

/**
  * @brief  Get 4st conversion in inserted sequence
  * @param  adc ADC Instance
  * @retval Channel number[0 ~ 18]
  */
__STATIC_INLINE uint32_t md_adc_get_insert_4st_conv_is4(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHS, ADC_ICHS_IS4_MSK, ADC_ICHS_IS4_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group19 CHSL
  * @{
  */
/**
  * @brief  Set normal channel sequence length
  * @param  adc ADC Instance
  * @param  sel value of normal channel sequence length
  * @retval NONE
  */
__STATIC_INLINE void md_adc_set_normal_channel_length_nsl(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CHSL, ADC_CHSL_NSL_MSK, sel << ADC_CHSL_NSL_POSS);
}

/**
  * @brief  Get normal channel sequence length
  * @param  adc ADC Instance
  * @retval  Value of normal channel sequence length
  */
__STATIC_INLINE uint32_t md_adc_get_normal_channel_length_nsl(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CHSL, ADC_CHSL_NSL_MSK, ADC_CHSL_NSL_POSS);
}

/**
  * @brief  Set insert channel sequence length
  * @param  adc ADC Instance
  * @param  sel value of insert channel sequence length
  * @retval NONE
  */
__STATIC_INLINE void md_adc_set_insert_channel_length_isl(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CHSL, ADC_CHSL_ISL_MSK, sel << ADC_CHSL_ISL_POSS);
}


/**
  * @brief  Get insert channel sequence length
  * @param  adc ADC Instance
  * @retval  Value of insert channel sequence length
  */
__STATIC_INLINE uint32_t md_adc_get_insert_channel_length_isl(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CHSL, ADC_CHSL_ISL_MSK, ADC_CHSL_ISL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group20 ICHDR1
  * @{
  */
/**
  * @brief  Get the conversion result from inserted channel 1
  * @param  adc ADC Instance
  * @retval Injected data		
  */
__STATIC_INLINE uint32_t md_adc_get_insert_channel1_val(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHDR[0], ADC_ICHDR1_VAL_MSK, ADC_ICHDR1_VAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group21 ICHDR2
  * @{
  */
/**
  * @brief  Get the conversion result from inserted channel 2
  * @param  adc ADC Instance
  * @retval Injected data		
  */
__STATIC_INLINE uint32_t md_adc_get_insert_channel2_val(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHDR[1], ADC_ICHDR2_VAL_MSK, ADC_ICHDR2_VAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group22 ICHDR3
  * @{
  */
/**
  * @brief  Get the conversion result from inserted channel 3
  * @param  adc ADC Instance
  * @retval Injected data		
  */
__STATIC_INLINE uint32_t md_adc_get_insert_channel3_val(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHDR[2], ADC_ICHDR3_VAL_MSK, ADC_ICHDR3_VAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group23 ICHDR4
  * @{
  */
/**
  * @brief  Get the conversion result from inserted channel 4
  * @param  adc ADC Instance
  * @retval Injected data		
  */
__STATIC_INLINE uint32_t md_adc_get_insert_channel4_val(ADC_TypeDef *adc)
{
	return READ_BITS(adc->ICHDR[3], ADC_ICHDR4_VAL_MSK, ADC_ICHDR4_VAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group24 NCHDR
  * @{
  */
/**
  * @brief  Get the conversion result from normal channel 
  * @param  adc ADC Instance
  * @retval Injected data		
  */
__STATIC_INLINE uint32_t md_adc_get_normal_channel_val(ADC_TypeDef *adc)
{
	return READ_BITS(adc->NCHDR, ADC_NCHDR_VAL_MSK, ADC_NCHDR_VAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group25 CCR
  * @{
  */
/**
  * @brief  Set ADC clock clock divider value
  * @param  adc ADC Instance
  * @param  sel value of clock divider
  * @retval NONE
  */
__STATIC_INLINE void md_adc_set_clock_divide_val_ckdiv(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_CKDIV_MSK, sel << ADC_CCR_CKDIV_POSS);
}

/**
  * @brief  Get ADC clock clock divider value
  * @param  adc ADC Instance
  * @retval value of clock divider
  */
__STATIC_INLINE uint32_t md_adc_get_clock_divide_val_ckdiv(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_CKDIV_MSK, ADC_CCR_CKDIV_POSS);
}

/**
  * @brief  Set internal reference voltage enable
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_internal_ref_voltage_vrefen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_VREFEN_MSK, sel << ADC_CCR_VREFEN_POS);
}

/**
  * @brief  Check if internal reference voltage enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_internal_ref_voltage_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_VREFEN_MSK, ADC_CCR_VREFEN_POS);
}

/**
  * @brief  Set common voltage buffer enable
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_common_voltage_buffer_vrefen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_VCMBUFEN_MSK, sel << ADC_CCR_VCMBUFEN_POS);
}

/**
  * @brief  Check if common voltage buffer enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_common_voltage_buffer_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_VCMBUFEN_MSK, ADC_CCR_VCMBUFEN_POS);
}

/**
  * @brief  Set reference voltage buffer enable
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_reference_voltage_buffer_vrefen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_VRBUFEN_MSK, sel << ADC_CCR_VRBUFEN_POS);
}

/**
  * @brief  Check if reference voltage buffer enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_reference_voltage_buffer_vrefen(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_VRBUFEN_MSK, ADC_CCR_VRBUFEN_POS);
}

/**
  * @brief  Set buffer reference current enable
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_buffer_reference_current_vrefen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_IREFEN_MSK, sel << ADC_CCR_IREFEN_POS);
}

/**
  * @brief  Check if buffer reference current enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_buffer_reference_current_vrefen(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_IREFEN_MSK, ADC_CCR_IREFEN_POS);
}

/**
  * @brief  Set diff mode enable
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_diff_mode_diffen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_DIFFEN_MSK, sel << ADC_CCR_DIFFEN_POS);
}

/**
  * @brief  Check if diff mode enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_diff_mode_diffen(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_DIFFEN_MSK, ADC_CCR_DIFFEN_POS);
}

/**
  * @brief  Set VREF mode enable
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_vref_mode_pwrmodsel(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_PWRMODSEL_MSK, sel << ADC_CCR_PWRMODSEL_POS);
}

/**
  * @brief  Get VREF mode enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_vref_mode_pwrmodsel(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_PWRMODSEL_MSK, ADC_CCR_PWRMODSEL_POS);
}

/**
  * @brief  Set forward reference voltage 
  * @param  adc ADC Instance
  * @param  sel set 0-3 to choose VDD、2.0V、VREFP PIN not pass buffer or pass buffer.
  * @retval None
  */
__STATIC_INLINE void md_adc_set_forward_ref_voltage_vrpsel(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_VRPSEL_MSK, sel << ADC_CCR_VRPSEL_POSS);
}

/**
  * @brief  Get forward reference voltage
  * @param  adc ADC Instance
  * @retval choose of VREFP
  */
__STATIC_INLINE uint32_t md_adc_get_forward_ref_voltage_vrpsel(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_VRPSEL_MSK, ADC_CCR_VRPSEL_POSS);
}

/**
  * @brief  Set backward reference voltage 
  * @param  adc ADC Instance
  * @param  sel set 0 to choose vss or set 1 to choose vrefn pin.
  * @retval None
  */
__STATIC_INLINE void md_adc_set_backward_ref_voltage_vrnsel(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_VRNSEL_MSK, sel << ADC_CCR_VRNSEL_POS);
}

/**
  * @brief  Get backward reference voltage 
  * @param  adc ADC Instance
  * @retval choose of VREFN
  */
__STATIC_INLINE uint32_t md_adc_get_backward_ref_voltage_vrnsel(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_VRNSEL_MSK, ADC_CCR_VRNSEL_POS);
}

/**
  * @brief  Set internal 2.0v acted on VREFP pin
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_v2_acted_on_vrefp_vrefoen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_VREFOEN_MSK, sel << ADC_CCR_VREFOEN_POS);
}

/**
  * @brief  Check if internal 2.0v acted on VREFP pin enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_v2_acted_on_vrefp_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_VREFOEN_MSK, ADC_CCR_VREFOEN_POS);
}

/**
  * @brief  Set offset calibration
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_offset_calibration_offcalen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_OFFCALEN_MSK, sel << ADC_CCR_OFFCALEN_POS);
}

/**
  * @brief  Check if offset calibration enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_offset_calibration_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_OFFCALEN_MSK, ADC_CCR_OFFCALEN_POS);
}

/**
  * @brief  Set gain calibration
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gain_calibration_gaincalen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_GAINCALEN_MSK, sel << ADC_CCR_GAINCALEN_POS);
}

/**
  * @brief  Check if gain calibration enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_gain_calibration_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_GAINCALEN_MSK, ADC_CCR_GAINCALEN_POS);
}

/**
  * @brief  Set A/D data modified 
  * @param  adc ADC Instance
  * @param  sel set 0 to disable or set 1 to enable
  * @retval None
  */
__STATIC_INLINE void md_adc_set_data_modified_trmen(ADC_TypeDef *adc, uint32_t sel)
{
	MODIFY_REG(adc->CCR, ADC_CCR_TRMEN_MSK, sel << ADC_CCR_TRMEN_POS);
}

/**
  * @brief  Check if A/D data modified enable
  * @param  adc ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_data_modified_enable(ADC_TypeDef *adc)
{
	return READ_BITS(adc->CCR, ADC_CCR_TRMEN_MSK, ADC_CCR_TRMEN_POS);
}

/**
  * @}
  */
/** @defgroup MD_ADC_Public_Functions_Group1 Initialization
  * @{
  */
extern md_status_t md_adc_init(ADC_TypeDef *adcx, md_adc_init_t *init);
extern void md_adc_struct_init(md_adc_init_t *init);
extern void md_adc_normal_channel_config(ADC_TypeDef *adcx, md_adc_nch_conf_t *config);
extern void md_adc_normal_struct_init(md_adc_nch_conf_t *config);
extern void md_adc_insert_channel_config(ADC_TypeDef *adcx, md_adc_ich_conf_t *config);
extern void md_adc_insert_struct_init(md_adc_ich_conf_t *config);
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
