/**
  *********************************************************************************
  *
  * @file    md_usart.h
  * @brief   Header file of USART module driver.
  *
  * @version V1.0
  * @date    19 Nov 2018
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */


#ifndef __MD_USART_H__
#define __MD_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */
/** @defgroup MD_USART USART
  * @brief USART micro driver
  * @{
  */
/** @defgroup MD_USART_Public_Types USART Public Types
  * @{
  */
/**
  * @brief USART Mode
  */
typedef enum {
	MD_USART_MODE_NONE  = 0x0U,	/**< Transmitter and Receiver are disabled */
	MD_USART_MODE_RX    = 0x4U,	/**< Transmitter is disabled and Receiver is enabled */
	MD_USART_MODE_TX    = 0x8U,	/**< Transmitter is enabled and Receiver is disabled */
	MD_USART_MODE_TX_RX = 0xCU,	/**< Transmitter and Receiver are enabled */
} md_usart_mode_t;

/**
  * @brief USART Parity
  */
typedef enum {
	MD_USART_PARITY_NONE = 0x0U,	/**< Parity control disabled */
	MD_USART_PARITY_EVEN = 0x400U,	/**< Even Parity is selected */
	MD_USART_PARITY_ODD  = 0x600U,	/**< Odd Parity is selected */
} md_usart_parity_t;

/**
  * @brief USART Word Length
  */
typedef enum {
	MD_USART_WORD_LENGTH_8B = 0x0U,		/**< 8 bits word length*/
	MD_USART_WORD_LENGTH_9B = 0x1000U,	/**< 9 bits word length*/
} md_usart_word_length_t;

/**
  * @brief USART Stop Bits
  */
typedef enum {
	MD_USART_STOP_BITS_0_5 = 0x1000U,	/**< 0.5 stop bit */
	MD_USART_STOP_BITS_1   = 0x0U,		/**< 1 stop bit */
	MD_USART_STOP_BITS_1_5 = 0x3000U,	/**< 1.5 stop bits */
	MD_USART_STOP_BITS_2   = 0x2000U,	/**< 2 stop bits */
} md_usart_stop_bits_t;

/**
  * @brief USART Hardware Flow Control
  */
typedef enum {
	MD_USART_HW_FLOW_CTL_NONE    = 0x0U,	/**< CTS and RTS disabled */
	MD_USART_HW_FLOW_CTL_RTS     = 0x100U,	/**< RTS mode enabled */
	MD_USART_HW_FLOW_CTL_CTS     = 0x200U,	/**< CTS mode enabled */
	MD_USART_HW_FLOW_CTL_RTS_CTS = 0x300U,	/**< CTS and RTS enabled */
} md_usart_hw_flow_ctl_t;

/**
  * @brief USART Wakeup Mode
  */
typedef enum {
	MD_USART_WAKEUP_IDLE = 0x0U,	/**< Idle wakeup */
	MD_USART_WAKEUP_ADDR = 0x800U,	/**< Address wakeup */
} md_usart_wakeup_t;

/**
  * @brief usart init structure definition
  */
typedef struct {
	uint32_t baud;				/**< This member configures the Usart communication baud rate. */
	md_usart_word_length_t word_length;	/**< Specifies the number of data bits transmitted or received in a frame. */
	md_usart_stop_bits_t stop_bits;		/**< Specifies the number of stop bits transmitted. */
	md_usart_parity_t parity;		/**< Specifies the parity mode.
						     @note When parity is enabled, the computed parity is inserted
 					                at the MSB position of the transmitted data (9th bit when
 					                the word length is set to 9 data bits; 8th bit when the
					                word length is set to 8 data bits). */
	md_usart_mode_t mode;			/**< Specifies wether the Receive or Transmit mode is enabled or disabled. */
	md_usart_hw_flow_ctl_t fctl;		/**< Specifies wether the hardware flow control mode is enabled or disabled. */
} md_usart_init_t;

/**
  * @brief USART Clock
  */
typedef enum {
	MD_USART_CLOCK_DISABLE = 0x0U,	/**< Clock signal disable */
	MD_USART_CLOCK_ENABLE  = 0x800U,	/**< Clock signal enable */
} md_usart_clock_t;

/**
  * @brief USART Last Bit
  */
typedef enum {
	MD_USART_LAST_BIT_DISABLE = 0x0U,	/**< Last data bit is not output */
	MD_USART_LAST_BIT_ENABLE  = 0x100U,	/**< Last data bit is output */
} md_usart_last_bit_t;

/**
  * @brief USART Phase
  */
typedef enum {
	MD_USART_CPHA_1EDGE = 0x0U,	/**< Clock phase first edge */
	MD_USART_CPHA_2EDGE = 0x200U,	/**< Clock phase second edge */
} md_usart_cpha_t;

/**
  * @brief USART Polarity
  */
typedef enum {
	MD_USART_CPOL_LOW  = 0x0U,	/**< Clock polarity low */
	MD_USART_CPOL_HIGH = 0x400U,	/**< Clock polarity high */
} md_usart_cpol_t;


/**
  * @brief USART clock init structure definition
  */
typedef struct {
	md_usart_clock_t clk;		/**< Pecifies whether the USART clock is enable or disable. */
	md_usart_cpol_t polarity;	/**< Specifies the steady state of the serial clock. */
	md_usart_cpha_t phase;		/**< Specifies the clock transition on which the bit capture is made. */
	md_usart_last_bit_t last_bit;	/**< Specifies whether the clock pulse corresponding to the last transmitted
				               data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} md_usart_clock_init_t;
/**
  * @}
  */

/** @defgroup MD_USART_Public_Functions USART Public Functions
  * @{
  */
/** @defgroup MD_USART_Public_Functions_Group2 STAT
  * @{
  */
/**
  * @brief  Check if the USART Parity Error Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_perr(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_PERRIF_MSK) == (USART_STAT_PERRIF_MSK));
}

/**
  * @brief  Check if the USART Framing Error Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_ferr(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_FERRIF_MSK) == (USART_STAT_FERRIF_MSK));
}

/**
  * @brief  Check if the USART Noise error detected Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_ndet(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_NDETIF_MSK) == (USART_STAT_NDETIF_MSK));
}

/**
  * @brief  Check if the USART OverRun Error Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_ovr(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_OVRIF_MSK) == (USART_STAT_OVRIF_MSK));
}

/**
  * @brief  Check if the USART IDLE line detected Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_idle(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_IDLEIF_MSK) == (USART_STAT_IDLEIF_MSK));
}

/**
  * @brief  Check if the USART Read Data Register Not Empty Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_rxne(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_RXNEIF_MSK) == (USART_STAT_RXNEIF_MSK));
}

/**
  * @brief  Check if the USART Transmission Complete Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_txc(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_TXCIF_MSK) == (USART_STAT_TXCIF_MSK));
}

/**
  * @brief  Check if the USART Transmit Data Register Empty Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_txemp(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_TXEMPIF_MSK) == (USART_STAT_TXEMPIF_MSK));
}

/**
  * @brief  Check if the USART CTS Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_cts(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->STAT, USART_STAT_CTSIF_MSK) == (USART_STAT_CTSIF_MSK));
}

/**
  * @brief  Clear Transmission Complete Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_txc(USART_TypeDef *USARTx)
{
	WRITE_REG(USARTx->STAT, ~(USART_STAT_TXCIF_MSK));
}

/**
  * @brief  Clear RX Not Empty Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_rxne(USART_TypeDef *USARTx)
{
	WRITE_REG(USARTx->STAT, ~(USART_STAT_RXNEIF_MSK));
}

/**
  * @brief  Clear CTS Interrupt Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_cts(USART_TypeDef *USARTx)
{
	WRITE_REG(USARTx->STAT, ~(USART_STAT_CTSIF_MSK));
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group3 DATA
  * @{
  */
/**
  * @brief  Get the data register address used for DMA transfer
  * @param  USARTx: USART Peripheral
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t md_usart_get_dma_regaddr(USART_TypeDef *USARTx)
{
	return ((uint32_t)&(USARTx->DATA));
}

/**
  * @brief  Read Receiver Data.
  * @param  USARTx: USART Peripheral
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t md_usart_recv_data8(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->DATA, USART_DATA_VAL_MSK));
}

/**
  * @brief  Read Receiver Data register (Receive Data value, 9 bits)
  * @param  USARTx: USART Peripheral
  * @retval Value between Min_Data=0x00 and Max_Data=0x1FF
  */
__STATIC_INLINE uint16_t md_usart_recv_data9(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->DATA, USART_DATA_VAL_MSK));
}

/**
  * @brief  Write in Transmitter Data
  * @param  USARTx: USART Peripheral
  * @param  value: Between Min_Data=0x00 and Max_Data=0xFF
  * @retval NONE
  */
__STATIC_INLINE void md_usart_send_data8(USART_TypeDef *USARTx, uint8_t value)
{
	USARTx->DATA = value;
}

/**
  * @brief  Write in Transmitter Data
  * @param  USARTx: USART Peripheral
  * @param  value: Between Min_Data=0x00 and Max_Data=0x1FF
  * @retval NONE
  */
__STATIC_INLINE void md_usart_send_data9(USART_TypeDef *USARTx, uint16_t value)
{
	USARTx->DATA = value & 0x1FFU;
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group4 BAUDCON
  * @{
  */
/**
  * @brief  Return current BAUDCON register value,
  * @param  USARTx: USART Peripheral
  * @retval The value of BAUDCON register
  */
__STATIC_INLINE uint32_t md_usart_get_baud(USART_TypeDef *USARTx)
{
	return READ_REG(USARTx->BAUDCON);
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group5 CON0
  * @{
  */
/**
  * @brief  USART Enable
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_EN_MSK);
}

/**
  * @brief  USART Disable
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_EN_MSK);
}

/**
  * @brief  Indicate if USART is enabled
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_EN_MSK) == (USART_CON0_EN_MSK));
}

/**
  * @brief  Receiver Enable
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_rx(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_RXEN_MSK);
}

/**
  * @brief  Receiver Disable
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_rx(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_RXEN_MSK);
}

/**
  * @brief  Transmitter Enable
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_tx(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_TXEN_MSK);
}

/**
  * @brief  Transmitter Disable
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_tx(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_TXEN_MSK);
}

/**
  * @brief  Enable Transmitter and Receiver
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_rx_tx(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_RXEN_MSK | USART_CON0_TXEN_MSK);
}

/**
  * @brief  Disable Transmitter and Receiver
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_rx_tx(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_RXEN_MSK | USART_CON0_TXEN_MSK);
}

/**
  * @brief  Return enabled/disabled states of Transmitter and Receiver
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_MODE_NONE
  *         @arg @ref MD_USART_MODE_RX
  *         @arg @ref MD_USART_MODE_TX
  *         @arg @ref MD_USART_MODE_TX_RX
  */
__STATIC_INLINE uint32_t md_usart_get_mode(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_RXEN_MSK | USART_CON0_TXEN_MSK));
}

/**
  * @brief  Configure Parity.
  * @param  USARTx: USART Peripheral
  * @param  parity This parameter can be one of the following values:
  *         @arg @ref MD_USART_PARITY_NONE
  *         @arg @ref MD_USART_PARITY_EVEN
  *         @arg @ref MD_USART_PARITY_ODD
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_parity(USART_TypeDef *USARTx, uint32_t parity)
{
	MODIFY_REG(USARTx->CON0, USART_CON0_PEN_MSK | USART_CON0_PSEL_MSK, parity);
}

/**
  * @brief  Return Parity configuration
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_PARITY_NONE
  *         @arg @ref MD_USART_PARITY_EVEN
  *         @arg @ref MD_USART_PARITY_ODD
  */
__STATIC_INLINE uint32_t md_usart_get_parity(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_PEN_MSK | USART_CON0_PSEL_MSK));
}

/**
  * @brief  Set Receiver Wake Up mode from Mute mode.
  * @param  USARTx: USART Peripheral
  * @param  mode: This parameter can be one of the following values:
  *         @arg @ref MD_USART_WAKEUP_IDLE
  *         @arg @ref MD_USART_WAKEUP_ADDR
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_wakeup_mode(USART_TypeDef *USARTx, uint32_t mode)
{
	MODIFY_REG(USARTx->CON0, USART_CON0_WKMOD_MSK, mode);
}

/**
  * @brief  Return Receiver Wake Up mode from Mute mode
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_WAKEUP_IDLE
  *         @arg @ref MD_USART_WAKEUP_ADDR
  */
__STATIC_INLINE uint32_t md_usart_get_wakeup_mode(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_WKMOD_MSK));
}

/**
  * @brief  Set Word length
  * @param  USARTx: USART Peripheral
  * @param  word_length: This parameter can be one of the following values:
  *         @arg @ref MD_USART_WORD_LENGTH_8B
  *         @arg @ref MD_USART_WORD_LENGTH_9B
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_word_length(USART_TypeDef *USARTx, uint32_t word_length)
{
	MODIFY_REG(USARTx->CON0, USART_CON0_DLEN_MSK, word_length);
}

/**
  * @brief  Return Word length
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_WORD_LENGTH_8B
  *         @arg @ref MD_USART_WORD_LENGTH_9B
  */
__STATIC_INLINE uint32_t md_usart_get_word_length(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_DLEN_MSK));
}

/**
  * @brief  Check if the USART Receive Wake Up from mute mode Flag is set or not
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_active_flag_rxwk(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_RXWK_MSK) == (USART_CON0_RXWK_MSK));
}

/**
  * @brief  Enable IDLE Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_idle(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_IDLEIE_MSK);
}

/**
  * @brief  Enable RX Not Empty Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_rxne(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_RXNEIE_MSK);
}

/**
  * @brief  Enable Transmission Complete Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_txc(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_TXCIE_MSK);
}

/**
  * @brief  Enable TX Empty Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_txemp(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_TXEMPIE_MSK);
}

/**
  * @brief  Enable Parity Error Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_perr(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_PERRIE_MSK);
}

/**
  * @brief  Disable IDLE Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_idle(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_IDLEIE_MSK);
}

/**
  * @brief  Disable RX Not Empty Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_rxne(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_RXNEIE_MSK);
}

/**
  * @brief  Disable Transmission Complete Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_txc(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_TXCIE_MSK);
}

/**
  * @brief  Disable TX Empty Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_txemp(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_TXEMPIE_MSK);
}

/**
  * @brief  Disable Parity Error Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_perr(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_PERRIE_MSK);
}

/**
  * @brief  Check if the USART IDLE Interrupt  source is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_idle(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_IDLEIE_MSK) == (USART_CON0_IDLEIE_MSK));
}

/**
  * @brief  Check if the USART RX Not Empty Interrupt is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_rxne(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_RXNEIE_MSK) == (USART_CON0_RXNEIE_MSK));
}

/**
  * @brief  Check if the USART Transmission Complete Interrupt is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_txc(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_TXCIE_MSK) == (USART_CON0_TXCIE_MSK));
}

/**
  * @brief  Check if the USART TX Empty Interrupt is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_txemp(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_TXEMPIE_MSK) == (USART_CON0_TXEMPIE_MSK));
}

/**
  * @brief  Check if the USART Parity Error Interrupt is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_perr(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON0, USART_CON0_PERRIE_MSK) == (USART_CON0_PERRIE_MSK));
}

/**
  * @brief  Put USART in Mute mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enter_mute_mode(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON0, USART_CON0_RXWK_MSK);
}

/**
  * @brief  Put USART in Active mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_exit_mute_mode(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON0, USART_CON0_RXWK_MSK);
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group6 CON1
  * @{
  */
/**
  * @brief  Configure if Clock pulse of the last data bit is output
  * @param  USARTx: USART Peripheral
  * @param  last_bit: This parameter can be one of the following values:
  *         @arg @ref MD_USART_LAST_BIT_DISABLE
  *         @arg @ref MD_USART_LAST_BIT_ENABLE
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_last_bit_mode(USART_TypeDef *USARTx, uint32_t last_bit)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_LBCP_MSK, last_bit);
}

/**
  * @brief  Retrieve Clock pulse of the last data bit output configuration
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_LAST_BIT_DISABLE
  *         @arg @ref MD_USART_LAST_BIT_ENABLE
  */
__STATIC_INLINE uint32_t md_usart_get_last_bit_mode(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON1, USART_CON1_LBCP_MSK));
}

/**
  * @brief  Select the phase of the clock output on the SCLK pin in synchronous mode
  * @param  USARTx: USART Peripheral
  * @param  phase: This parameter can be one of the following values:
  *         @arg @ref MD_USART_CPHA_1EDGE
  *         @arg @ref MD_USART_CPHA_2EDGE
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_clock_phase(USART_TypeDef *USARTx, uint32_t phase)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_SCKPHA_MSK, phase);
}

/**
  * @brief  Return phase of the clock output on the SCLK pin in synchronous mode
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_CPHA_1EDGE
  *         @arg @ref MD_USART_CPHA_2EDGE
  */
__STATIC_INLINE uint32_t md_usart_get_clock_phase(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON1, USART_CON1_SCKPHA_MSK));
}

/**
  * @brief  Select the polarity of the clock output on the SCLK pin in synchronous mode
  * @param  USARTx USART Peripheral
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref MD_USART_CPOL_LOW
  *         @arg @ref MD_USART_CPOL_HIGH
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_clock_polarity(USART_TypeDef *USARTx, uint32_t polarity)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_SCKPOL_MSK, polarity);
}

/**
  * @brief  Return polarity of the clock output on the SCLK pin in synchronous mode
  *         Synchronous mode is supported by the USARTx instance.
  * @param  USARTx USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_CPOL_LOW
  *         @arg @ref MD_USART_CPOL_HIGH
  */
__STATIC_INLINE uint32_t md_usart_get_clock_polarity(USART_TypeDef *USARTx)
{
	return (uint32_t)(READ_BIT(USARTx->CON1, USART_CON1_SCKPOL_MSK));
}

/**
  * @brief  Configure Clock signal format
  * @param  USARTx: USART Peripheral
  * @param  phase: the phase of the clock output.
  * @param  polarity: Select the polarity of the clock output.
  * @param  last_bit: Configure the last data bit is/not output
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_clock(USART_TypeDef *USARTx, uint32_t phase, uint32_t polarity, uint32_t last_bit)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_LBCP_MSK | USART_CON1_SCKPHA_MSK | USART_CON1_SCKPOL_MSK, phase | polarity | last_bit);
}

/**
  * @brief  Enable Clock output on SCLK pin
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_clock(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK);
}

/**
  * @brief  Disable Clock output on SCLK pin
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_clock(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK);
}

/**
  * @brief  Indicate if Clock output on SCLK pin is enabled
  * @param  USARTx USART Peripheral
  * @retval State
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_clock(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK) == (USART_CON1_SCKEN_MSK));
}

/**
  * @brief  Set the length of the stop bits
  * @param  USARTx: USART Peripheral
  * @param  stop_bits This parameter can be one of the following values:
  *         @arg @ref MD_USART_STOP_BITS_1
  *         @arg @ref MD_USART_STOP_BITS_0_5
  *         @arg @ref MD_USART_STOP_BITS_2
  *         @arg @ref MD_USART_STOP_BITS_1_5
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_stop_bits(USART_TypeDef *USARTx, uint32_t stop_bits)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_STPLEN_MSK, stop_bits);
}

/**
  * @brief  Retrieve the length of the stop bits
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_STOP_BITS_1
  *         @arg @ref MD_USART_STOP_BITS_0_5
  *         @arg @ref MD_USART_STOP_BITS_2
  *         @arg @ref MD_USART_STOP_BITS_1_5
  */
__STATIC_INLINE uint32_t md_usart_get_stop_bits(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON1, USART_CON1_STPLEN_MSK));
}

/**
  * @brief  Set Address of the USART node.
  * @param  USARTx: USART Peripheral
  * @param  addr: 4 bit Address of the USART node.
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_addr(USART_TypeDef *USARTx, uint32_t addr)
{
	MODIFY_REG(USARTx->CON1, USART_CON1_ADDR_MSK, (addr & USART_CON1_ADDR_MSK));
}

/**
  * @brief  Return 4 bit Address of the USART node.
  * @param  USARTx: USART Peripheral
  * @retval Address of the USART node
  */
__STATIC_INLINE uint32_t md_usart_get_addr(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON1, USART_CON1_ADDR_MSK));
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group7 CON2
  * @{
  */
/**
  * @brief  Enable RTS HW Flow Control
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_rts(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_RTSEN_MSK);
}

/**
  * @brief  Disable RTS HW Flow Control
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_rts(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_RTSEN_MSK);
}

/**
  * @brief  Enable CTS HW Flow Control
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_cts(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_CTSEN_MSK);
}

/**
  * @brief  Disable CTS HW Flow Control
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_cts(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_CTSEN_MSK);
}

/**
  * @brief  Enable CTS and RTS HW Flow Control
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_rts_cts(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_CTSEN_MSK | USART_CON2_RTSEN_MSK);
}

/**
  * @brief  Disable CTS and RTS HW Flow Control
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_rts_cts(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_CTSEN_MSK | USART_CON2_RTSEN_MSK);
}

/**
  * @brief  Return HW Flow Control configuration (both CTS and RTS)
  * @param  USARTx: USART Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_USART_HW_FLOW_CTL_NONE
  *         @arg @ref MD_USART_HW_FLOW_CTL_RTS
  *         @arg @ref MD_USART_HW_FLOW_CTL_CTS
  *         @arg @ref MD_USART_HW_FLOW_CTL_RTS_CTS
  */
__STATIC_INLINE uint32_t md_usart_get_flow_ctl(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_RTSEN_MSK | USART_CON2_CTSEN_MSK));
}

/**
  * @brief  Enable IrDA mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_irda(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_IREN_MSK);
}

/**
  * @brief  Disable IrDA mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_irda(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_IREN_MSK);
}

/**
  * @brief  Indicate if IrDA mode is enabled
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_irda(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_IREN_MSK) == (USART_CON2_IREN_MSK));
}

/**
  * @brief  Enable Smartcard NACK transmission
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_smartcard_nack(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_NACK_MSK);
}

/**
  * @brief  Disable Smartcard NACK transmission
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_smartcard_nack(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_NACK_MSK);
}

/**
  * @brief  Indicate if Smartcard NACK transmission is enabled
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_smartcard_nack(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_NACK_MSK) == (USART_CON2_NACK_MSK));
}

/**
  * @brief  Enable Smartcard mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_smartcard(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_SMARTEN_MSK);
}

/**
  * @brief  Disable Smartcard mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_smartcard(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_SMARTEN_MSK);
}

/**
  * @brief  Indicate if Smartcard mode is enabled
  * @param  USARTx: USART Peripheral
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_smartcard(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_SMARTEN_MSK) == (USART_CON2_SMARTEN_MSK));
}

/**
  * @brief  Enable Single Wire Half-Duplex mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_half_duplex(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_HDPSEL_MSK);
}

/**
  * @brief  Disable Single Wire Half-Duplex mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_half_duplex(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_HDPSEL_MSK);
}

/**
  * @brief  Indicate if Single Wire Half-Duplex mode is enabled
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_half_duplex(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_HDPSEL_MSK) == (USART_CON2_HDPSEL_MSK));
}

/**
  * @brief  Enable Error Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_err(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_ERRIE_MSK);
}

/**
  * @brief  Enable CTS Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_it_cts(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_CTSIE_MSK);
}


/**
  * @brief  Disable Error Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_err(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_ERRIE_MSK);
}

/**
  * @brief  Disable CTS Interrupt
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_it_cts(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_CTSIE_MSK);
}

/**
  * @brief  Check if the USART Error Interrupt is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_err(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_ERRIE_MSK) == (USART_CON2_ERRIE_MSK));
}

/**
  * @brief  Check if the USART CTS Interrupt is enabled or disabled.
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_it_cts(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_CTSIE_MSK) == (USART_CON2_CTSIE_MSK));
}

/**
  * @brief  Enable DMA Mode for reception
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_dma_req_rx(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_RXDMAEN_MSK);
}

/**
  * @brief  Disable DMA Mode for reception
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_dma_req_rx(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_RXDMAEN_MSK);
}

/**
  * @brief  Check if DMA Mode is enabled for reception
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_dma_req_rx(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_RXDMAEN_MSK) == (USART_CON2_RXDMAEN_MSK));
}

/**
  * @brief  Enable DMA Mode for transmission
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_enable_dma_req_tx(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CON2, USART_CON2_TXDMAEN_MSK);
}

/**
  * @brief  Disable DMA Mode for transmission
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_disable_dma_req_tx(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, USART_CON2_TXDMAEN_MSK);
}

/**
  * @brief  Check if DMA Mode is enabled for transmission
  * @param  USARTx: USART Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_usart_is_enabled_dma_req_tx(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->CON2, USART_CON2_TXDMAEN_MSK) == (USART_CON2_TXDMAEN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group8 GP
  * @{
  */
/**
  * @brief  Set Irda prescaler value.
  * @param  USARTx: USART Peripheral
  * @param  value: Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_irda_psc(USART_TypeDef *USARTx, uint32_t value)
{
	MODIFY_REG(USARTx->GP, USART_GP_PSC_MSK, value);
}

/**
  * @brief  Return Irda prescaler value
  * @param  USARTx: USART Peripheral
  * @retval Irda prescaler value (Value between Min_Data=0x00 and Max_Data=0xFF)
  */
__STATIC_INLINE uint32_t md_usart_get_irda_psc(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->GP, USART_GP_PSC_MSK));
}

/**
  * @brief  Set Smartcard prescaler value.
  * @param  USARTx: USART Peripheral
  * @param  psc Value between Min_Data=0 and Max_Data=31
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_smartcard_psc(USART_TypeDef *USARTx, uint32_t psc)
{
	MODIFY_REG(USARTx->GP, USART_GP_PSC_MSK, psc);
}

/**
  * @brief  Return Smartcard prescaler value.
  * @param  USARTx: USART Peripheral
  * @retval Smartcard prescaler value (Value between Min_Data=0 and Max_Data=31)
  */
__STATIC_INLINE uint32_t md_usart_get_smartcard_psc(USART_TypeDef *USARTx)
{
	return (READ_BIT(USARTx->GP, USART_GP_PSC_MSK));
}

/**
  * @brief  Set Smartcard Guard time value.
  * @param  USARTx: USART Peripheral
  * @param  gt Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval NONE
  */
__STATIC_INLINE void md_usart_set_smartcard_gt(USART_TypeDef *USARTx, uint32_t gt)
{
	MODIFY_REG(USARTx->GP, USART_GP_GTVAL_MSK, gt << USART_GP_GTVAL_POSS);
}

/**
  * @brief  Return Smartcard Guard time value.
  * @param  USARTx: USART Peripheral
  * @retval Smartcard Guard time value (Value between Min_Data=0x00 and Max_Data=0xFF)
  */
__STATIC_INLINE uint32_t md_usart_get_smartcard_gt(USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->GP, USART_GP_GTVAL_MSK) >> USART_GP_GTVAL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group9 Configure
  * @{
  */
/**
  * @brief  USART using in Asynchronous Mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_async(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK);
	CLEAR_BIT(USARTx->CON2, (USART_CON2_SMARTEN_MSK | USART_CON2_IREN_MSK | USART_CON2_HDPSEL_MSK));
}

/**
  * @brief  USART using in Synchronous Mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_sync(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, (USART_CON2_SMARTEN_MSK | USART_CON2_IREN_MSK | USART_CON2_HDPSEL_MSK));
	SET_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK);
}

/**
  * @brief  USART using in Half Duplex Mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_half_duplex(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK);
	CLEAR_BIT(USARTx->CON2, (USART_CON2_SMARTEN_MSK | USART_CON2_IREN_MSK));
	SET_BIT(USARTx->CON2, USART_CON2_HDPSEL_MSK);
}

/**
  * @brief  USART using in Smartcard Mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_smartcard(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON2, (USART_CON2_IREN_MSK | USART_CON2_HDPSEL_MSK));
	SET_BIT(USARTx->CON1, (USART_CON1_STPLEN_MSK | USART_CON1_SCKEN_MSK));
	SET_BIT(USARTx->CON2, USART_CON2_SMARTEN_MSK);
}

/**
  * @brief  USART using in Irda Mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_irda(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON1, (USART_CON1_SCKEN_MSK | USART_CON1_STPLEN_MSK));
	CLEAR_BIT(USARTx->CON2, (USART_CON2_SMARTEN_MSK | USART_CON2_HDPSEL_MSK));
	SET_BIT(USARTx->CON2, USART_CON2_IREN_MSK);
}

/**
  * @brief  USART using in Multi processor Mode
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_config_multi_process(USART_TypeDef *USARTx)
{
	CLEAR_BIT(USARTx->CON1, USART_CON1_SCKEN_MSK);
	CLEAR_BIT(USARTx->CON2, (USART_CON2_SMARTEN_MSK | USART_CON2_HDPSEL_MSK | USART_CON2_IREN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group10 Clear
  * @{
  */
/**
  * @brief  Clear Parity Error Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_perr(USART_TypeDef *USARTx)
{
	__IO uint32_t tmpreg;

	tmpreg = USARTx->STAT;
	tmpreg = USARTx->DATA;
	(void)tmpreg;
}

/**
  * @brief  Clear Framing Error Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_ferr(USART_TypeDef *USARTx)
{
	__IO uint32_t tmpreg;

	tmpreg = USARTx->STAT;
	tmpreg = USARTx->DATA;
	(void)tmpreg;
}

/**
  * @brief  Clear Noise detected Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_ndet(USART_TypeDef *USARTx)
{
	__IO uint32_t tmpreg;

	tmpreg = USARTx->STAT;
	tmpreg = USARTx->DATA;
	(void)tmpreg;
}

/**
  * @brief  Clear OverRun Error Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_ovr(USART_TypeDef *USARTx)
{
	__IO uint32_t tmpreg;

	tmpreg = USARTx->STAT;
	tmpreg = USARTx->DATA;
	(void)tmpreg;
}

/**
  * @brief  Clear IDLE line detected Flag
  * @param  USARTx: USART Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_usart_clear_flag_idle(USART_TypeDef *USARTx)
{
	__IO uint32_t tmpreg;

	tmpreg = USARTx->STAT;
	tmpreg = USARTx->DATA;
	(void)tmpreg;
}
/**
  * @}
  */
/** @defgroup MD_USART_Public_Functions_Group1 Initialization
  * @{
  */
void md_usart_reset(USART_TypeDef *USARTx);
void md_usart_init(USART_TypeDef *USARTx, md_usart_init_t *init);
void md_usart_init_struct(md_usart_init_t *init);
void md_usart_clock_init(USART_TypeDef *USARTx, md_usart_clock_init_t *init);
void md_usart_clock_init_struct(md_usart_clock_init_t *init);
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
