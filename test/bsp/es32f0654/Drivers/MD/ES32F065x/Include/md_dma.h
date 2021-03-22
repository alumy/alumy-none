/**
  *********************************************************************************
  *
  * @file    md_dma.h
  * @brief   Header file of DMA module driver.
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


#ifndef __MD_DMA_H__
#define __MD_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */
/** @defgroup MD_DMA DMA
  * @brief DMA micro driver
  * @{
  */
/** @defgroup MD_DMA_Public_Types DMA Public Types
  * @{
  */
/**
  * @brief Input source to DMA channel
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
	MD_DMA_MSEL_NONE    = 0x0U,	/**< NONE */
	MD_DMA_MSEL_GPIO    = 0x1U,	/**< GPIO */
	MD_DMA_MSEL_CRYPT   = 0x2U,	/**< CRYPT */
	MD_DMA_MSEL_ACMP    = 0x3U,	/**< ACMP */
	MD_DMA_MSEL_DAC0    = 0x4U,	/**< DAC0 */
	MD_DMA_MSEL_ADC0    = 0x6U,	/**< ADC0 */
	MD_DMA_MSEL_CRC     = 0x7U,	/**< CRC */
	MD_DMA_MSEL_UART0   = 0x8U,	/**< UART0 */
	MD_DMA_MSEL_UART1   = 0x9U,	/**< UART1 */
	MD_DMA_MSEL_UART2   = 0xAU,	/**< UART2 */
	MD_DMA_MSEL_UART3   = 0xBU,	/**< UART3 */
	MD_DMA_MSEL_USART0  = 0xCU,	/**< USART0 */
	MD_DMA_MSEL_USART1  = 0xDU,	/**< USART1 */
	MD_DMA_MSEL_SPI0    = 0xEU,	/**< SPI0 */
	MD_DMA_MSEL_SPI1    = 0xFU,	/**< SPI1 */
	MD_DMA_MSEL_I2C0    = 0x10U,	/**< I2C0 */
	MD_DMA_MSEL_I2C1    = 0x11U,	/**< I2C1 */
	MD_DMA_MSEL_TIMER0  = 0x12U,	/**< TIMER0 */
	MD_DMA_MSEL_TIMER1  = 0x13U,	/**< TIMER1 */
	MD_DMA_MSEL_TIMER2  = 0x14U,	/**< TIMER2 */
	MD_DMA_MSEL_TIMER3  = 0x15U,	/**< TIMER3 */
	MD_DMA_MSEL_RTC     = 0x16U,	/**< RTC */
	MD_DMA_MSEL_LPTIM0  = 0x17U,	/**< LPTIM0 */
	MD_DMA_MSEL_LPUART0 = 0x18U,	/**< LPUART0 */
	MD_DMA_MSEL_DMA     = 0x19U,	/**< DMA */
	MD_DMA_MSEL_SPI2    = 0x1AU,	/**< SPI2 */
	MD_DMA_MSEL_TIMER4  = 0x1BU,	/**< TIMER4 */
	MD_DMA_MSEL_TIMER5  = 0x1CU,	/**< TIMER5 */
	MD_DMA_MSEL_TIMER6  = 0x1DU,	/**< TIMER6 */
	MD_DMA_MSEL_TIMER7  = 0x1EU,	/**< TIMER7 */
	MD_DMA_MSEL_ADC1    = 0x1FU,	/**< ADC1 */
	MD_DMA_MSEL_PIS     = 0x20U,	/**< PIS */
	MD_DMA_MSEL_TRNG    = 0x21U,	/**< TRNG */
} md_dma_msel_t;

/**
  * @brief Input signal to DMA channel
  */
typedef enum {
	MD_DMA_MSIGSEL_NONE           = 0x0U,	/**< NONE */
	MD_DMA_MSIGSEL_EXTI_0         = 0x0U,	/**< External interrupt 0 */
	MD_DMA_MSIGSEL_EXTI_1         = 0x1U,	/**< External interrupt 1 */
	MD_DMA_MSIGSEL_EXTI_2         = 0x2U,	/**< External interrupt 2 */
	MD_DMA_MSIGSEL_EXTI_3         = 0x3U,	/**< External interrupt 3 */
	MD_DMA_MSIGSEL_EXTI_4         = 0x4U,	/**< External interrupt 4 */
	MD_DMA_MSIGSEL_EXTI_5         = 0x5U,	/**< External interrupt 5 */
	MD_DMA_MSIGSEL_EXTI_6         = 0x6U,	/**< External interrupt 6 */
	MD_DMA_MSIGSEL_EXTI_7         = 0x7U,	/**< External interrupt 7 */
	MD_DMA_MSIGSEL_EXTI_8         = 0x8U,	/**< External interrupt 8 */
	MD_DMA_MSIGSEL_EXTI_9         = 0x9U,	/**< External interrupt 9 */
	MD_DMA_MSIGSEL_EXTI_10        = 0xAU,	/**< External interrupt 10 */
	MD_DMA_MSIGSEL_EXTI_11        = 0xBU,	/**< External interrupt 11 */
	MD_DMA_MSIGSEL_EXTI_12        = 0xCU,	/**< External interrupt 12 */
	MD_DMA_MSIGSEL_EXTI_13        = 0xDU,	/**< External interrupt 13 */
	MD_DMA_MSIGSEL_EXTI_14        = 0xEU,	/**< External interrupt 14 */
	MD_DMA_MSIGSEL_EXTI_15        = 0xFU,	/**< External interrupt 15 */
	MD_DMA_MSIGSEL_CRYPT_WRITE    = 0x0U,	/**< CRYPT write mode */
	MD_DMA_MSIGSEL_CRYPT_READ     = 0x1U,	/**< CRYPT read mode */
	MD_DMA_MSIGSEL_CALC_WRITE     = 0x0U,	/**< CALC write mode */
	MD_DMA_MSIGSEL_CALC_READ      = 0x1U,	/**< CALC read mode */
	MD_DMA_MSIGSEL_DAC0_CH0       = 0x0U,	/**< DAC0 channel 0 complete */
	MD_DMA_MSIGSEL_DAC0_CH1       = 0x1U,	/**< DAC0 channel 1 complete */
	MD_DMA_MSIGSEL_ADC            = 0x0U,	/**< ADC mode */
	MD_DMA_MSIGSEL_UART_TXEMPTY   = 0x0U,	/**< UART transmit */
	MD_DMA_MSIGSEL_UART_RNR       = 0x1U,	/**< UART receive */
	MD_DMA_MSIGSEL_USART_RNR      = 0x0U,	/**< USART reveive */
	MD_DMA_MSIGSEL_USART_TXEMPTY  = 0x1U,	/**< USART transmit */
	MD_DMA_MSIGSEL_SPI_RNR        = 0x0U,	/**< SPI receive */
	MD_DMA_MSIGSEL_SPI_TXEMPTY    = 0x1U,	/**< SPI transmit */
	MD_DMA_MSIGSEL_I2C_RNR        = 0x0U,	/**< I2C receive */
	MD_DMA_MSIGSEL_I2C_TXEMPTY    = 0x1U,	/**< I2C transmit */
	MD_DMA_MSIGSEL_TIMER_CH1      = 0x0U,	/**< TIM channal 1 */
	MD_DMA_MSIGSEL_TIMER_CH2      = 0x1U,	/**< TIM channal 2 */
	MD_DMA_MSIGSEL_TIMER_CH3      = 0x2U,	/**< TIM channal 3 */
	MD_DMA_MSIGSEL_TIMER_CH4      = 0x3U,	/**< TIM channal 4 */
	MD_DMA_MSIGSEL_TIMER_TRI      = 0x4U,	/**< TIM trigger */
	MD_DMA_MSIGSEL_TIMER_COMP     = 0x5U,	/**< TIM compare */
	MD_DMA_MSIGSEL_TIMER_UPDATE   = 0x6U,	/**< TIM update */
	MD_DMA_MSIGSEL_LPUART_RNR     = 0x0U,	/**< LPUART receive */
	MD_DMA_MSIGSEL_LPUART_TXEMPTY = 0x1U,	/**< LPUART transmit */
	MD_DMA_MSIGSEL_PIS_CH0        = 0x0U,	/**< PIS channal 0 */
	MD_DMA_MSIGSEL_PIS_CH1        = 0x1U,	/**< PIS channal 1 */
	MD_DMA_MSIGSEL_PIS_CH2        = 0x2U,	/**< PIS channal 2 */
	MD_DMA_MSIGSEL_PIS_CH3        = 0x3U,	/**< PIS channal 3 */
	MD_DMA_MSIGSEL_PIS_CH4        = 0x4U,	/**< PIS channal 4 */
	MD_DMA_MSIGSEL_PIS_CH5        = 0x5U,	/**< PIS channal 5 */
	MD_DMA_MSIGSEL_PIS_CH6        = 0x6U,	/**< PIS channal 6 */
	MD_DMA_MSIGSEL_PIS_CH7        = 0x7U,	/**< PIS channal 7 */
	MD_DMA_MSIGSEL_PIS_CH8        = 0x8U,	/**< PIS channal 8 */
	MD_DMA_MSIGSEL_PIS_CH9        = 0x9U,	/**< PIS channal 9 */
	MD_DMA_MSIGSEL_PIS_CH10       = 0xAU,	/**< PIS channal 10 */
	MD_DMA_MSIGSEL_PIS_CH11       = 0xBU,	/**< PIS channal 11 */
	MD_DMA_MSIGSEL_PIS_CH12       = 0xCU,	/**< PIS channal 12 */
	MD_DMA_MSIGSEL_PIS_CH13       = 0xDU,	/**< PIS channal 13 */
	MD_DMA_MSIGSEL_PIS_CH14       = 0xEU,	/**< PIS channal 14 */
	MD_DMA_MSIGSEL_PIS_CH15       = 0xFU,	/**< PIS channal 15 */
} md_dma_msigsel_t;

/**
  * @brief DMA Descriptor control type
  */
typedef union {
	struct {
		uint32_t cycle_ctrl    :3;	/**< DMA operating mode */
		uint32_t next_useburst :1;	/**< Uses the alternate data structure when complete a DMA cycle */
		uint32_t n_minus_1     :10;	/**< Represent the total number of DMA transfers that DMA cycle contains. */
		uint32_t R_power       :4;	/**< Control how many DMA transfers can occur before re-arbitrates */
		uint32_t src_prot_ctrl :3;	/**< Control the state of HPROT when reads the source data. */
		uint32_t dst_prot_ctrl :3;	/**< Control the state of HPROT when writes the destination data */
		uint32_t src_size      :2;	/**< Source data size */
		uint32_t src_inc       :2;	/**< Control the source address increment */
		uint32_t dst_size      :2;	/**< Destination data size */
		uint32_t dst_inc       :2;	/**< Destination address increment */
	};
	uint32_t word;
} md_dma_ctrl_t;

/**
  * @brief Channel control data structure
  */
typedef struct {
	void *src;		/**< Source data end pointer */
	void *dst;		/**< Destination data end pointer */
	md_dma_ctrl_t ctrl;	/**< Control data configuration */
	uint32_t use;		/**< Reserve for user */
} md_dma_descriptor_t;

/**
  * @brief data increment
  */
typedef enum {
	MD_DMA_DATA_INC_BYTE     = 0x0U,	/**< Address increment by byte */
	MD_DMA_DATA_INC_HALFWORD = 0x1U,	/**< Address increment by halfword */
	MD_DMA_DATA_INC_WORD     = 0x2U,	/**< Address increment by word */
	MD_DMA_DATA_INC_NONE     = 0x3U,	/**< No increment */
} md_dma_data_inc_t;

/**
  * @brief Data size
  */
typedef enum {
	MD_DMA_DATA_SIZE_BYTE     = 0x0U,	/**< Byte */
	MD_DMA_DATA_SIZE_HALFWORD = 0x1U,	/**< Halfword */
	MD_DMA_DATA_SIZE_WORD     = 0x2U,	/**< Word */
} md_dma_data_size_t;

/**
  * @brief The operating mode of the DMA cycle
  */
typedef enum {
	MD_DMA_CYCLE_CTRL_NONE             = 0x0U,	/**< Stop */
	MD_DMA_CYCLE_CTRL_BASIC            = 0x1U,	/**< Basic */
	MD_DMA_CYCLE_CTRL_AUTO             = 0x2U,	/**< Auto-request */
	MD_DMA_CYCLE_CTRL_PINGPONG         = 0x3U,	/**< Ping-pong */
	MD_DMA_CYCLE_CTRL_MEM_SG_PRIMARY   = 0x4U,	/**< Memory scatter-gather using the primary structure */
	MD_DMA_CYCLE_CTRL_MEM_SG_ALTERNATE = 0x5U,	/**< Memory scatter-gather using the alternate structure */
	MD_DMA_CYCLE_CTRL_PER_SG_PRIMARY   = 0x6U,	/**< Peripheral scatter-gather using the primary structure */
	MD_DMA_CYCLE_CTRL_PER_SG_ALTERNATE = 0x7U,	/**< Peripheral scatter-gather using the alternate structure */
} md_dma_cycle_ctrl_t;

/**
  * @brief Control how many DMA transfers can occur
  *        before the controller re-arbitrates
  */
typedef enum {
	MD_DMA_R_POWER_1    = 0x0U,	/**< Arbitrates after each DMA transfer */
	MD_DMA_R_POWER_2    = 0x1U,	/**< Arbitrates after 2 DMA transfer */
	MD_DMA_R_POWER_4    = 0x2U,	/**< Arbitrates after 4 DMA transfer */
	MD_DMA_R_POWER_8    = 0x3U,	/**< Arbitrates after 8 DMA transfer */
	MD_DMA_R_POWER_16   = 0x4U,	/**< Arbitrates after 16 DMA transfer */
	MD_DMA_R_POWER_32   = 0x5U,	/**< Arbitrates after 32 DMA transfer */
	MD_DMA_R_POWER_64   = 0x6U,	/**< Arbitrates after 64 DMA transfer */
	MD_DMA_R_POWER_128  = 0x7U,	/**< Arbitrates after 128 DMA transfer */
	MD_DMA_R_POWER_256  = 0x8U,	/**< Arbitrates after 256 DMA transfer */
	MD_DMA_R_POWER_512  = 0x9U,	/**< Arbitrates after 512 DMA transfer */
	MD_DMA_R_POWER_1024 = 0xAU,	/**< Arbitrates after 1024 DMA transfer */
} md_dma_arbiter_config_t;

/**
  * @brief DMA channal configure structure
  */
typedef struct {
	void *src;				/**< Source data begin pointer */
	void *dst;				/**< Destination data begin pointer */
	uint16_t size;				/**< The total number of DMA transfers that DMA cycle contains */
	md_dma_data_size_t data_width;		/**< Data width */
	md_dma_data_inc_t src_inc;		/**< Source increment type */
	md_dma_data_inc_t dst_inc;		/**< Destination increment type */
	md_dma_arbiter_config_t R_power;	/**< Control how many DMA transfers can occur before re-arbitrates */
	type_func_t primary;			/**< Use primary descriptor or alternate descriptor */
	type_func_t burst;			/**< Uses the alternate data structure when complete a DMA cycle */
	type_func_t high_prio;			/**< High priority or default priority */
	type_func_t interrupt;			/**< Enable/disable interrupt */
	md_dma_msel_t msel;			/**< Input source to DMA channel */
	md_dma_msigsel_t msigsel;		/**< Input signal to DMA channel */
	uint8_t channel;			/**< Channel index */
} md_dma_config_t;
/**
  * @}
  */

/** @defgroup MD_DMA_Public_Constants DMA Public Constants
  * @{
  */
/**
  * defgroup MD_DMA_CHANNEL DMA channel
  * @{
  */
#define MD_DMA_CH_0	0x1U	/**< Channel 0 */
#define MD_DMA_CH_1	0x2U	/**< Channel 1 */
#define MD_DMA_CH_2	0x4U	/**< Channel 2 */
#define MD_DMA_CH_3	0x8U	/**< Channel 3 */
#define MD_DMA_CH_4	0x10U	/**< Channel 4 */
#define MD_DMA_CH_5	0x20U	/**< Channel 5 */
/**
  * @}
  */
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions DMA Public Functions
  * @{
  */
/** @defgroup MD_DMA_Public_Functions_Group2 STATUS
  * @{
  */
/**
  * @brief  Check if DMA peripheral is enabled
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_dma_is_enabled(void)
{
	return READ_BITS(DMA0->STATUS, DMA_STATUS_MASTER_ENABLE_MSK, DMA_STATUS_MASTER_ENABLE_POS);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group3 CFG
  * @{
  */
/**
  * @brief  Enable DMA peripheral
  * @retval None
  */
__STATIC_INLINE void md_dma_enable(void)
{
	SET_BIT(DMA0->CFG, DMA_CFG_MASTER_ENABLE_MSK);
}

/**
  * @brief  Disable DMA peripheral
  * @retval None
  */
__STATIC_INLINE void md_dma_disable(void)
{
	CLEAR_BIT(DMA0->CFG, DMA_CFG_MASTER_ENABLE_MSK);
}

/**
  * @brief  Set the AHB-Lite protection controlling the HPROT[3:1] signal levels
  * @param  port_ctrl: The HPROT[3:1] value
  * @retval None
  */
__STATIC_INLINE void md_dma_set_protctrl(uint32_t port_ctrl)
{
	MODIFY_REG(DMA0->CFG, DMA_CFG_CHNL_PROT_CTRL_MSK, port_ctrl << DMA_CFG_CHNL_PROT_CTRL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group4 Descriptor
  * @{
  */
/**
  * @brief  Set DMA source data address
  * @param  dscp: DMA descriptor struct
  * @param  addr: Source data address
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_source_addr(md_dma_descriptor_t *dscp, uint32_t addr)
{
	WRITE_REG(dscp->src, (void *)addr);
}

/**
  * @brief  Get DMA source data address
  * @param  dscp: DMA descriptor struct
  * @retval DMA source data address
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_source_addr(md_dma_descriptor_t *dscp)
{
	return (uint32_t)dscp->src;
}

/**
  * @brief  Set DMA destination data address
  * @param  dscp: DMA descriptor struct
  * @param  addr: DMA destination data address
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_dest_addr(md_dma_descriptor_t *dscp, uint32_t addr)
{
	WRITE_REG(dscp->dst, (void *)addr);
}

/**
  * @brief  Get DMA destination data address
  * @param  dscp: DMA descriptor struct
  * @retval The destination data address
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_dest_addr(md_dma_descriptor_t *dscp)
{
	return (uint32_t)dscp->dst;
}

/**
  * @brief  Sets DMA data width
  * @param  dscp: DMA descriptor struct
  * @param  data_width: This parameter can be one of the @ref md_dma_data_size_t
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_size(md_dma_descriptor_t *dscp, uint32_t data_width)
{
	dscp->ctrl.src_size = data_width;
	dscp->ctrl.dst_size = data_width;
}

/**
  * @brief  Gets DMA data width
  * @param  dscp: DMA descriptor struct
  * @retval The return data width, see @ref md_dma_data_size_t
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_size(md_dma_descriptor_t *dscp)
{
	return dscp->ctrl.src_size;
}

/**
  * @brief  Set DMA source data increment
  * @param  dscp: DMA descriptor struct
  * @param  src_inc: This parameter can be one of the @ref md_dma_data_inc_t
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_source_inc(md_dma_descriptor_t *dscp, uint32_t src_inc)
{
	dscp->ctrl.src_inc = src_inc;
}

/**
  * @brief  Get DMA source data increment
  * @param  dscp: DMA descriptor struct
  * @retval The return source data increment, see @ref md_dma_data_inc_t
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_source_inc(md_dma_descriptor_t *dscp)
{
	return dscp->ctrl.src_inc;
}

/**
  * @brief  Set DMA destination data increment
  * @param  dscp: DMA descriptor struct
  * @param  dst_inc: This parameter can be one of the @ref md_dma_data_inc_t
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_dest_inc(md_dma_descriptor_t *dscp, uint32_t dst_inc)
{
	dscp->ctrl.dst_inc = dst_inc;
}

/**
  * @brief  Get DMA destination data increment
  * @param  dscp: DMA descriptor struct
  * @retval The return destination data increment, see @ref md_dma_data_inc_t
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_dest_inc(md_dma_descriptor_t *dscp)
{
	return dscp->ctrl.dst_inc;
}

/**
  * @brief  Set how many DMA transfers can occur before the controller rearbitrates
  * @param  dscp: DMA descriptor struct
  * @param  R_power: The R_power value, see @ref md_dma_arbiter_config_t
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_rpower(md_dma_descriptor_t *dscp, uint32_t R_power)
{
	dscp->ctrl.R_power = R_power;
}

/**
  * @brief  Get how many DMA transfers can occur before the controller rearbitrates
  * @param  dscp: DMA descriptor struct
  * @retval The R_power value: see @ref md_dma_arbiter_config_t
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_rpower(md_dma_descriptor_t *dscp)
{
	return dscp->ctrl.R_power;
}

/**
  * @brief  Set the total numbers of DMA transfers
  * @param  dscp: DMA descriptor struct
  * @param  n_minus_1: The size.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrl_nminus(md_dma_descriptor_t *dscp, uint32_t n_minus_1)
{
	dscp->ctrl.n_minus_1 = n_minus_1;
}

/**
  * @brief  Get the total numbers of DMA transfers
  * @param  dscp: DMA descriptor struct
  * @retval The size
  */
__STATIC_INLINE uint32_t md_dma_get_ctrl_nminus(md_dma_descriptor_t *dscp)
{
	return dscp->ctrl.n_minus_1;
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group5 CTRLBASE
  * @{
  */
/**
  * @brief  Set the base address of the primary data structure
  * @param  addr: The base address value
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ctrlbase(uint32_t addr)
{
	/* Make sure the lower 9bits-data of base address is equal to 0  */
	WRITE_REG(DMA0->CTRLBASE, addr);
}

/**
  * @brief  Get the base address of the primary data structure
  * @retval The Base Address value
  */
__STATIC_INLINE uint32_t md_dma_get_ctrlbase(void)
{
	return (READ_REG(DMA0->CTRLBASE));
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group6 ALTCTRLBASE
  * @{
  */
/**
  * @brief  Get the base address of the alternate data structure
  * @retval The Base Address value
  */
__STATIC_INLINE uint32_t md_dma_get_altctrlbase(void)
{
	return (READ_REG(DMA0->ALTCTRLBASE));
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group7 CHSWREQ
  * @{
  */
/**
  * @brief  Enable single request
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_soft_req(uint32_t channel)
{
	SET_BIT(DMA0->CHSWREQ, channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group8 CHREQMASKSET
  * @{
  */
/**
  * @brief  Enable DMA mask request(Disable request)
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_mask_req(uint32_t channel)
{
	SET_BIT(DMA0->CHREQMASKSET, channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group9 CHREQMASKCLR
  * @{
  */
/**
  * @brief  Disable DMA mask request(Enable request)
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_disable_mask_set(uint32_t channel)
{
	SET_BIT(DMA0->CHREQMASKCLR, channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group10 CHREQMASKSET
  * @{
  */
/**
  * @brief  Check if channelx request is enabled
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval State:
  *         - 0: Disable mask request(Enable request)
  *         - 1: Enable mask request(Enable request)
  */
__STATIC_INLINE uint32_t md_dma_is_enabled_mask_req(uint32_t channel)
{
	return (READ_BIT(DMA0->CHREQMASKSET, channel) == channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group11 CHENSET
  * @{
  */
/**
  * @brief  Enable DMA channel
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_channel(uint32_t channel)
{
	SET_BIT(DMA0->CHENSET, channel);
}

/**
  * @brief  Check if channelx is enabled
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval State:
  *         - 0: Disable channel
  *         - 1: Enable channel
  */
__STATIC_INLINE uint32_t md_dma_is_enabled_channel(uint32_t channel)
{
	return (READ_BIT(DMA0->CHENSET, channel) == channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group12 CHENCLR
  * @{
  */
/**
  * @brief  Disable DMA channel
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_disable_channel(uint32_t channel)
{
	SET_BIT(DMA0->CHENCLR, channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group13 CHPRIALTSET
  * @{
  */
/**
  * @brief  Set use alternate structure
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_use_alternate(uint32_t channel)
{
	SET_BIT(DMA0->CHPRIALTSET, channel);
}

/**
  * @brief  Check if DMA channelx use alternate structure
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval State:
  *         - 0: Primary descriptor
  *         - 1: Alternate descriptor
  */
__STATIC_INLINE uint32_t md_dma_is_set_use_alternate(uint32_t channel)
{
	return (READ_BIT(DMA0->CHPRIALTSET, channel) == channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group14 CHPRIALTCLR
  * @{
  */
/**
  * @brief  Set use primary structure
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_use_primary(uint32_t channel)
{
	SET_BIT(DMA0->CHPRIALTCLR, channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group15 CHPRSET
  * @{
  */
/**
  * @brief  Set channel priority high
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_priority_high(uint32_t channel)
{
	SET_BIT(DMA0->CHPRSET, channel);
}

/**
  * @brief  Check if the priority of DMA channelx is set for high
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval State:
  *         - 0: Primary descriptor
  *         - 1: Alternate descriptor
  */
__STATIC_INLINE uint32_t md_dma_is_set_priority_high(uint32_t channel)
{
	return (READ_BIT(DMA0->CHPRSET, channel) == channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group16 CHPRCLR
  * @{
  */
/**
  * @brief  Set channel priority default
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_priority_default(uint32_t channel)
{
	SET_BIT(DMA0->CHPRCLR, channel);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group17 IFLAG
  * @{
  */
/**
  * @brief  Get DMA done flag
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_is_active_flag_done(uint32_t channel)
{
	return (READ_BIT(DMA0->IFLAG, channel) == channel);
}

/**
  * @brief  Get DMA error flag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_is_active_flag_err(void)
{
	return (READ_BIT(DMA0->IFLAG, DMA_IFLAG_DMAERRIF_MSK) == (DMA_IFLAG_DMAERRIF_MSK));
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group18 ICFR
  * @{
  */
/**
  * @brief  Clear DMA done flag
  * @param  channel: This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_flag_done(uint32_t channel)
{
	SET_BIT(DMA0->ICFR, channel);
}

/**
  * @brief  Clear DMA error flag
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_flag_err(void)
{
	SET_BIT(DMA0->ICFR, DMA_ICFR_DMAERRC_MSK);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group19 IER
  * @{
  */
/**
  * @brief  Enable DMA CHx done interrupt
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_it_done(uint32_t channel)
{
	SET_BIT(DMA0->IER, channel);
}

/**
  * @brief  Enable DMA error interrupt
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_it_err(void)
{
	SET_BIT(DMA0->IER, DMA_IER_DMAERRIE_MSK);
}

/**
  * @brief  Disable DMA CHx done interrupt
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval None
  */
__STATIC_INLINE void md_dma_disable_it_done(uint32_t channel)
{
	CLEAR_BIT(DMA0->IER, channel);
}

/**
  * @brief  Disable DMA error interrupt
  * @retval None
  */
__STATIC_INLINE void md_dma_disable_it_err(void)
{
	CLEAR_BIT(DMA0->IER, DMA_IER_DMAERRIE_MSK);
}

/**
  * @brief  Check if DMA CHx done interrupt is enabled
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CH_0
  *         @arg @ref MD_DMA_CH_1
  *         @arg @ref MD_DMA_CH_2
  *         @arg @ref MD_DMA_CH_3
  *         @arg @ref MD_DMA_CH_4
  *         @arg @ref MD_DMA_CH_5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_is_enabled_it_done(uint32_t channel)
{
	return (READ_BIT(DMA0->IER, channel) == channel);
}

/**
  * @brief  Check if DMA error interrupt is enabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_is_enabled_it_err_status(void)
{
	return (READ_BIT(DMA0->IER, DMA_IER_DMAERRIE_MSK) == DMA_IER_DMAERRIE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group20 CH_SELCON
  * @{
  */
/**
  * @brief  Set channel msel
  * @param  ch: This parameter can be one of the following values:
  *         - 0: Channel 0
  *         - 1: Channel 1
  *         - 2: Channel 2
  *         - 3: Channel 3
  *         - 4: Channel 4
  *         - 5: Channel 5
  * @param  msel: This parameter can be one of the @ref md_dma_msel_t
  * @retval None
  */
__STATIC_INLINE void md_dma_set_channel_msel(uint32_t ch, uint32_t msel)
{
	MODIFY_REG(DMA0->CH_SELCON[ch], DMA_CH0_SELCON_MSEL_MSK, msel << DMA_CH0_SELCON_MSEL_POSS);
}

/**
  * @brief  get channel msel
  * @param  channel: This parameter can be one of the following values:
  *         - 0: Channel 0
  *         - 1: Channel 1
  *         - 2: Channel 2
  *         - 3: Channel 3
  *         - 4: Channel 4
  *         - 5: Channel 5
  * @retval The msel, see @ref md_dma_msel_t
  */
__STATIC_INLINE uint32_t md_dma_get_channel_msel(uint32_t channel)
{
	return READ_BITS(DMA0->CH_SELCON[channel], DMA_CH0_SELCON_MSEL_MSK, DMA_CH0_SELCON_MSEL_POSS);
}

/**
  * @brief  Set channel msigsel
  * @param  ch: This parameter can be one of the following values:
  *         - 0: Channel 0
  *         - 1: Channel 1
  *         - 2: Channel 2
  *         - 3: Channel 3
  *         - 4: Channel 4
  *         - 5: Channel 5
  * @param  msigsel: This parameter can be one of the @ref md_dma_msigsel_t
  * @retval None
  */
__STATIC_INLINE void md_dma_set_channel_msigsel(uint32_t ch, uint32_t msigsel)
{
	MODIFY_REG(DMA0->CH_SELCON[ch], DMA_CH0_SELCON_MSIGSEL_MSK, msigsel << DMA_CH0_SELCON_MSIGSEL_POSS);
}

/**
  * @brief  get channel msigsel
  * @param  channel: This parameter can be one of the following values:
  *         - 0: Channel 0
  *         - 1: Channel 1
  *         - 2: Channel 2
  *         - 3: Channel 3
  *         - 4: Channel 4
  *         - 5: Channel 5
  * @retval The msigsel, see @ref md_dma_msigsel_t
  */
__STATIC_INLINE uint32_t md_dma_get_channel_msigsel(uint32_t channel)
{
	return READ_BITS(DMA0->CH_SELCON[channel], DMA_CH0_SELCON_MSIGSEL_MSK, DMA_CH0_SELCON_MSIGSEL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_DMA_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_dma_reset(DMA_TypeDef *DMAx);
extern void md_dma_config_base(DMA_TypeDef *DMAx, md_dma_cycle_ctrl_t mode, md_dma_config_t *p);
extern void md_dma_config_struct(md_dma_config_t *p);
extern void md_dma_config_sg_alt_desc(md_dma_descriptor_t *desc, md_dma_config_t *config, uint8_t memory);
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
