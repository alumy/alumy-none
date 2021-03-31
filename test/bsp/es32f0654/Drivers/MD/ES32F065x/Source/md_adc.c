/**
  *********************************************************************************
  *
  * @file    md_adc.c
  * @brief   ADC module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_adc.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_ADC

/** @addtogroup MD_ADC
  * @{
  */
/** @addtogroup MD_ADC_Public_Functions
  * @{
  */
/** @addtogroup MD_ADC_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Initializes the ADC peripheral and normal group according to
  *         parameters specified in structure ADC_TypeDef.
  * @param  adcx: adc peripheral
  * @param  init: Pointer to a md_adc_init_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval md_status_t, see @ref md_status_t.
  */
md_status_t md_adc_init(ADC_TypeDef *adcx, md_adc_init_t *init)
{
	CLEAR_BIT(adcx->CON1, ADC_CON1_ADCEN_MSK);
	MODIFY_REG(adcx->CON1, ADC_CON1_ALIGN_MSK, init->align << ADC_CON1_ALIGN_POS);
	MODIFY_REG(adcx->CON0, ADC_CON0_RSEL_MSK, init->data_bit << ADC_CON0_RSEL_POSS);

	if (init->disc == MD_ADC_NCH_DISC_EN) {
		init->scan = ENABLE;
		SET_BIT(adcx->CON0, ADC_CON0_NCHDCEN_MSK);
		MODIFY_REG(adcx->CON0, ADC_CON0_ETRGN_MSK, init->disc_nr << ADC_CON0_ETRGN_POSS);
	}
	else if (init->disc == MD_ADC_ICH_DISC_EN) {
		init->scan = ENABLE;
		SET_BIT(adcx->CON0, ADC_CON0_ICHDCEN_MSK);
		MODIFY_REG(adcx->CON0, ADC_CON0_ETRGN_MSK, init->disc_nr << ADC_CON0_ETRGN_POSS);
	}
	else {
		CLEAR_BIT(adcx->CON0, ADC_CON0_NCHDCEN_MSK);
		CLEAR_BIT(adcx->CON0, ADC_CON0_ICHDCEN_MSK);
	}

	if ((init->scan == ENABLE) || (init->disc == MD_ADC_NCH_DISC_EN))
		MODIFY_REG(adcx->CHSL, ADC_CHSL_NSL_MSK, init->nch_nr << ADC_CHSL_NSL_POSS);

	MODIFY_REG(adcx->CON1, ADC_CON1_CM_MSK, init->scan << ADC_CON1_CM_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_GAINCALEN_MSK, init->gaincal << ADC_CCR_GAINCALEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_OFFCALEN_MSK, init->offcal << ADC_CCR_OFFCALEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_DIFFEN_MSK, init->diff << ADC_CCR_DIFFEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_PWRMODSEL_MSK, init->lsen << ADC_CCR_PWRMODSEL_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_VRBUFEN_MSK, init->vrbuf << ADC_CCR_VRBUFEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_VCMBUFEN_MSK, init->vcmen << ADC_CCR_VCMBUFEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_VREFEN_MSK, init->vrefen << ADC_CCR_VREFEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_IREFEN_MSK, init->irefen << ADC_CCR_IREFEN_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_CKDIV_MSK, init->div << ADC_CCR_CKDIV_POSS);
	MODIFY_REG(adcx->CCR, ADC_CCR_VRNSEL_MSK, init->n_ref << ADC_CCR_VRNSEL_POS);
	MODIFY_REG(adcx->CCR, ADC_CCR_VRPSEL_MSK, init->p_ref << ADC_CCR_VRPSEL_POSS);
	MODIFY_REG(adcx->CON1, ADC_CON1_NCHESEL_MSK, init->nche_sel << ADC_CON1_NCHESEL_POS);

	SET_BIT(adcx->CON0, ADC_CON0_OVRIE_MSK);
	return MD_OK;
}

/**
  * @brief  Set each @ref md_adc_init_t field to default value.
  * @param  init: Pointer to a @ref md_adc_init_t structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void md_adc_struct_init(md_adc_init_t *init)
{
	init->align    = MD_ADC_DATAALIGN_RIGHT;
	init->scan     = DISABLE;
	init->cont     = DISABLE;
	init->nch_nr   = MD_ADC_NCH_NR_1;
	init->disc     = MD_ADC_ALL_DISABLE;
	init->disc_nr  = MD_ADC_DISC_NR_1;
	init->data_bit = MD_ADC_CONV_BIT_12;
	init->div      = MD_ADC_CKDIV_128;
	init->nche_sel = MD_ADC_NCHESEL_MODE_ALL;
	init->gaincal  = DISABLE;
	init->offcal   = DISABLE;
	init->n_ref    = MD_ADC_NEG_REF_VSS;
	init->p_ref    = MD_ADC_POS_REF_VDD;
	init->diff     = DISABLE;
	init->lsen     = DISABLE;
	init->vrbuf    = ENABLE;
	init->vcmen    = ENABLE;
	init->vrefen   = ENABLE;
	init->irefen   = ENABLE;
}

/**
  * @brief  Configures the the selected channel to be linked to the normal group.
  * @param  adcx: adc peripheral
  * @param  config: Structure of ADC channel for normal group.
  * @retval None
  */
void md_adc_normal_channel_config(ADC_TypeDef *adcx, md_adc_nch_conf_t *config)
{
	if (config->idx <= MD_ADC_NCH_IDX_4 ) {
		adcx->NCHS1 &= ~(0x1f << (uint32_t)((config->idx - 1) << 3));
		adcx->NCHS1 |= (config->ch << (uint32_t)((config->idx - 1) << 3));
	}
	else if (config->idx <= MD_ADC_NCH_IDX_8) {
		adcx->NCHS2 &= ~(0x1f << (uint32_t)((config->idx - 5) << 3));
		adcx->NCHS2 |= (config->ch << (uint32_t)((config->idx - 5) << 3));
	}
	else if (config->idx <= MD_ADC_NCH_IDX_12) {
		adcx->NCHS3 &= ~(0x1f << (uint32_t)((config->idx - 9) << 3));
		adcx->NCHS3 |= (config->ch << (uint32_t)((config->idx - 9) << 3));
	}
	else {
		adcx->NCHS4 &= ~(0x1f << (uint32_t)((config->idx - 13) << 3));
		adcx->NCHS4 |= (config->ch << (uint32_t)((config->idx - 13) << 3));
	}

	if (config->ch <= 15) {
		adcx->SMPT1 &=  ~(0x03 << (uint32_t)(config->ch << 1));
		adcx->SMPT1 |= config->samp << (uint32_t)(config->ch << 1);
	}
	else {
		adcx->SMPT2 &=  ~(0x03 << (uint32_t)((config->ch - 16) << 1));
		adcx->SMPT2 |= config->samp << (uint32_t)((config->ch - 16) << 1);
	}

	CLEAR_BIT(adcx->CON0, ADC_CON0_SCANEN_MSK);
	return;
}

/**
  * @brief  Set each @ref md_adc_nch_conf_t field to default value.
  * @param  config: Pointer to a @ref md_adc_nch_conf_t structure
  *                 whose fields will be set to default values.
  * @retval None
  */
void md_adc_normal_struct_init(md_adc_nch_conf_t *config)
{
	config->ch   = MD_ADC_CHANNEL_0;
	config->idx  = MD_ADC_NCH_IDX_1;
	config->samp = MD_ADC_SAMPLETIME_4;

	return;
}

/**
  * @brief  Configures the the selected channel to be linked to the insert group.
  * @param  adcx: adc peripheral
  * @param  config: Structure of ADC channel for insert group.
  * @retval None
  */
void md_adc_insert_channel_config(ADC_TypeDef *adcx, md_adc_ich_conf_t *config)
{
	MODIFY_REG(adcx->CHSL, ADC_CHSL_ISL_MSK, config->nr << ADC_CHSL_ISL_POSS);
	adcx->ICHS &= ~(0x1f << (uint32_t)((config->idx - 1) << 3));
	adcx->ICHS |= config->ch << (uint32_t)((config->idx - 1) << 3);

	if (config->nr > 0)
		SET_BIT(adcx->CON0, ADC_CON0_SCANEN_MSK);
	else
		CLEAR_BIT(adcx->CON0, ADC_CON0_SCANEN_MSK);

	if (config->auto_m == ENABLE)
		SET_BIT(adcx->CON0, ADC_CON0_IAUTO_MSK);
	else
		CLEAR_BIT(adcx->CON0, ADC_CON0_IAUTO_MSK);

	if (config->ch <= 15) {
		adcx->SMPT1 &=  ~(0x03 << (uint32_t)(config->ch << 1));
		adcx->SMPT1 |= config->samp << (uint32_t)(config->ch << 1);
	}
	else {
		adcx->SMPT2 &=  ~(0x03 << (uint32_t)((config->ch - 16) << 1));
		adcx->SMPT2 |= config->samp << (uint32_t)((config->ch - 16) << 1);
	}

	adcx->ICHOFF[config->idx] = config->offset;
	return;
}

/**
  * @brief  Set each @ref md_adc_ich_conf_t field to default value.
  * @param  config: Pointer to a @ref md_adc_ich_conf_t structure
  *                   whose fields will be set to default values.
  * @retval None
  */
void md_adc_insert_struct_init(md_adc_ich_conf_t *config)
{
	config->ch     = MD_ADC_CHANNEL_2;
	config->idx    = MD_ADC_ICH_IDX_1;
	config->samp   = MD_ADC_SAMPLETIME_4;
	config->offset = 0;
	config->nr     = MD_ADC_ICH_NR_1;
	config->auto_m = DISABLE;

	return;
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
