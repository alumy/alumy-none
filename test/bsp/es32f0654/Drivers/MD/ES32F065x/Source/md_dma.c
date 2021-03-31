/**
  *********************************************************************************
  *
  * @file    md_dma.c
  * @brief   DMA module driver.
  *
  * @version V1.0
  * @date    20 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "md_dma.h"

/** @addtogroup Micro_Driver
  * @{
  */
#ifdef MD_DMA

/** @addtogroup MD_DMA
  * @{
  */

/** @addtogroup MD_DMA_Public_Functions
  * @{
  */
/** @addtogroup MD_DMA_Public_Functions_Group1
  * @{
  */

md_dma_descriptor_t md_dma0_ctrl_base[28] __attribute__ ((aligned(512)));
  
/**
  * @brief  Reset the DMA register
  * @param  DMAx: Pointer to DMA peripheral
  * @retval None
  */
void md_dma_reset(DMA_TypeDef *DMAx)
{
	uint32_t i;

	WRITE_REG(DMAx->CFG, 0x0);
	WRITE_REG(DMAx->CHUSEBURSTCLR, 0xFFF);
	WRITE_REG(DMAx->CHREQMASKCLR, 0xFFF);
	WRITE_REG(DMAx->CHENCLR, 0xFFF);
	WRITE_REG(DMAx->CHPRIALTCLR, 0xFFF);
	WRITE_REG(DMAx->CHPRCLR, 0xFFF);
	WRITE_REG(DMAx->ERRCLR, 0x1);
	WRITE_REG(DMAx->IER, 0x0);
	WRITE_REG(DMAx->ICFR, 0x80000FFF);

	for (i = 0; i < 6; ++i)
		WRITE_REG(DMAx->CH_SELCON[i], 0x0);

	return;
}

/**
  * @brief  Configure DMA channel using md_dma_config_t structure
  * @param  DMAx: Pointer to DMA peripheral
  * @param  mode: DMA transfer mode. see @ref md_dma_cycle_ctrl_t
  * @param  p: Pointer to md_dma_cycle_ctrl_t which contains
  *            DMA channel parameter. see @ref md_dma_config_t
  * @retval None
  */
void md_dma_config_base(DMA_TypeDef *DMAx, md_dma_cycle_ctrl_t mode, md_dma_config_t *p)
{
	md_dma_descriptor_t *descr;

	if (p->primary)
		descr = (md_dma_descriptor_t *)(DMAx->CTRLBASE) + p->channel;
	else
		descr = (md_dma_descriptor_t *)(DMAx->ALTCTRLBASE) + p->channel;

	if (p->src_inc == MD_DMA_DATA_INC_NONE)
		descr->src = p->src;
	else
		descr->src = (void *)((uint32_t)p->src + ((p->size - 1) << (uint32_t)p->src_inc));

	if (p->dst_inc == MD_DMA_DATA_INC_NONE)
		descr->dst = p->dst;
	else
		descr->dst = (void *)((uint32_t)p->dst + ((p->size - 1) << (uint32_t)p->dst_inc));

	descr->ctrl.cycle_ctrl    = mode;
	descr->ctrl.next_useburst = 0;
	descr->ctrl.n_minus_1     = p->size - 1;
	descr->ctrl.R_power       = p->R_power;
	descr->ctrl.src_prot_ctrl = 0,
	descr->ctrl.dst_prot_ctrl = 0,
	descr->ctrl.src_size      = p->data_width;
	descr->ctrl.src_inc       = p->src_inc;
	descr->ctrl.dst_size      = p->data_width;
	descr->ctrl.dst_inc       = p->dst_inc;

	if (p->primary)
		WRITE_REG(DMAx->CHPRIALTCLR, (1 << p->channel));
	else
		WRITE_REG(DMAx->CHPRIALTSET, (1 << p->channel));

	if (p->burst)
		WRITE_REG(DMAx->CHUSEBURSTSET, (1 << p->channel));
	else
		WRITE_REG(DMAx->CHUSEBURSTCLR, (1 << p->channel));

	if (p->high_prio)
		WRITE_REG(DMAx->CHPRSET, (1 << p->channel));
	else
		WRITE_REG(DMAx->CHPRCLR, (1 << p->channel));

	if (p->interrupt)
		SET_BIT(DMAx->IER, (1 << p->channel));
	else
		CLEAR_BIT(DMAx->IER, (1 << p->channel));

	MODIFY_REG(DMAx->CH_SELCON[p->channel], DMA_CH0_SELCON_MSEL_MSK, p->msel << DMA_CH0_SELCON_MSEL_POSS);
	MODIFY_REG(DMAx->CH_SELCON[p->channel], DMA_CH0_SELCON_MSIGSEL_MSK, p->msigsel << DMA_CH0_SELCON_MSIGSEL_POSS);
	return;
}

/**
  * @brief  Configure dma_config_t structure using default parameter.
  *         User can invoked this function, before configure md_dma_config_t
  * @param  p: Pointer to dma_config_t structure, see @ref md_dma_config_t
  * @retval None
  */
void md_dma_config_struct(md_dma_config_t *p)
{
	p->data_width = MD_DMA_DATA_SIZE_BYTE;
	p->src_inc    = MD_DMA_DATA_INC_BYTE;
	p->dst_inc    = MD_DMA_DATA_INC_BYTE;
	p->R_power    = MD_DMA_R_POWER_1;
	p->primary    = ENABLE;
	p->burst      = DISABLE;
	p->high_prio  = DISABLE;
	p->interrupt  = ENABLE;

	return;
}

/**
  * @brief  Configure md_dma_descriptor_t structure using specified parameter.
  * @note   This function used in scatter-gather mode(memory or peripheral).
  * @param  desc: Address of the alternate descriptor.
  * @param  config: Pointer to the dma_config_t structure.
  * @param  memory: Memory or peripheral scatter-gather.
  * @retval None
  */
void md_dma_config_sg_alt_desc(md_dma_descriptor_t *desc, md_dma_config_t *config, uint8_t memory)
{
	if (config->src_inc == MD_DMA_DATA_INC_NONE)
		desc->src = config->src;
	else
		desc->src = (void *)((uint32_t)config->src + ((config->size - 1) << (uint32_t)config->data_width));

	if (config->dst_inc == MD_DMA_DATA_INC_NONE)
		desc->dst = config->dst;
	else
		desc->dst = (void *)((uint32_t)config->dst + ((config->size - 1) << (uint32_t)config->data_width));

	desc->ctrl.cycle_ctrl    = memory ? MD_DMA_CYCLE_CTRL_MEM_SG_ALTERNATE : MD_DMA_CYCLE_CTRL_PER_SG_ALTERNATE;
	desc->ctrl.next_useburst = memory ? 0 : 1;
	desc->ctrl.n_minus_1     = config->size - 1;
	desc->ctrl.R_power       = config->R_power;
	desc->ctrl.src_prot_ctrl = 0;
	desc->ctrl.dst_prot_ctrl = 0;
	desc->ctrl.src_size      = config->data_width;
	desc->ctrl.src_inc       = config->src_inc;
	desc->ctrl.dst_size      = config->data_width;
	desc->ctrl.dst_inc       = config->dst_inc;

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
