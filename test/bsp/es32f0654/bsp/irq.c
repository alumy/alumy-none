/**
  *********************************************************************************
  *
  * @file    irq.c
  * @brief   Interrupt handler
  *
  * @version V1.0
  * @date    01 Jul 2019
  * @author  AE Team
  * @note   
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */
#include "utils.h"
#include "ald_cmu.h"
#ifdef ALD_DMA
#include "ald_dma.h"
#endif
#include "ald_uart.h"
#include "bsp/uart.h"

/** @addtogroup Projects_Examples_ALD
  * @{
  */

/** @addtogroup Examples
  * @{
  */

/**
  * @brief  NMI IRQ handler
  * @retval None
  */
void NMI_Handler(void)
{
	/* Added Emergency operation */
	return;
}

/**
  * @brief  Hardfault IRQ handler
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Added debug information */
	while (1)
		;
}

/**
  * @brief  MemManage IRQ handler
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Added debug information */
	while (1)
		;
}

/**
  * @brief  BusFault IRQ handler
  * @retval None
  */
void BusFault_Handler(void)
{
	/* Added debug information */
	while (1)
		;
}

/**
  * @brief  UsageFault IRQ handler
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Added debug information */
	while (1)
		;
}

/**
  * @brief  Supervisor Call IRQ handler
  * @retval None
  */
void SVC_Handler(void)
{
	/* Added system callback */
	return;
}

/**
  * @brief  Debug Monitor IRQ handler
  * @retval None
  */
void DebugMon_Handler(void)
{
	/* Added debug operation */
	return;
}

/**
  * @brief  PendSV IRQ handler
  * @retval None
  */
void PendSV_Handler(void)
{
	/* Added thread switching operation */
	return;
}

void WWDG_IWDG_Handler()
{
	return;
}

/**
  * @brief  SysTick IRQ handler
  * @retval None
  */
void SysTick_Handler(void)
{
	ald_inc_tick();
	return;
}

#ifdef ALD_DMA
/**
  * @brief  DMA IRQ#66 handler
  * @retval None
  */
void DMA_Handler(void)
{
	ald_dma_irq_handler();
}
#endif

/**
  * @brief  UART IRQ handler
  * @retval None
  */
void UART2_Handler(void)
{	
	/* Handle uart interrupt */
	ald_uart_irq_handler(&dbg_uart);
	return;
}

/**
  * @}
  */
/**
  * @}
  */
