/**
  *********************************************************************************
  *
  * @file    md_uart.h
  * @brief   Header file of UART module driver.
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


#ifndef __MD_UART_H__
#define __MD_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_UART UART
  * @brief UART micro driver
  * @{
  */
/**
  * @defgroup MD_UART_Public_Macros UART Public Macros
  * @{
  */
/**
  * @brief Word length
  */
typedef enum {
	MD_UART_WORD_LENGTH_5B = 0x0U,	/**< 5-bits */
	MD_UART_WORD_LENGTH_6B = 0x1U,	/**< 6-bits */
	MD_UART_WORD_LENGTH_7B = 0x2U,	/**< 7-bits */
	MD_UART_WORD_LENGTH_8B = 0x3U,	/**< 8-bits */
} md_uart_word_length_t;

/**
  * @brief Stop bits
  */
typedef enum {
	MD_UART_STOP_BITS_1 = 0x0U,	/**< 1-bits */
	MD_UART_STOP_BITS_2 = 0x4U,	/**< 2-bits */
} md_uart_stop_bit_t;

/**
  * @brief parity
  */
typedef enum {
	MD_UART_PARITY_NONE = 0x0U, 	/**< Not parity */
	MD_UART_PARITY_ODD  = 0x8U, 	/**< Odd parity */
	MD_UART_PARITY_EVEN = 0x18U,	/**< Even parity */
} md_uart_parity_t;

/**
  * @brief UART hardware flow control
  */
typedef enum {
	MD_UART_FLOW_CTL_DISABLE = 0x0U,	/**< Auto-flow-control disable */
	MD_UART_FLOW_CTL_ENABLE  = 0x4U,	/**< Auto-flow-control enable */
} md_uart_flow_ctl_t;
/**
  * @}
  */
/**
  * @defgroup MD_UART_Public_Types UART Public Types
  * @{
  */
/**
  * @brief UART init structure definition
  */
typedef struct {
	uint32_t baud;				/**< Specifies the uart communication baud rate */
	md_uart_word_length_t word_length;	/**< Specifies the number of data bits transmitted or received in a frame */
	md_uart_stop_bit_t stop_bits;		/**< Specifies the number of stop bits transmitted */
	md_uart_parity_t parity;		/**< Specifies the parity mode */
	md_uart_flow_ctl_t fctl;		/**< Specifies wether the hardware flow control mode is enabled or disabled */
} md_uart_init_t;

/**
  * @brief LIN detection break length
  */
typedef enum {
	MD_LIN_BREAK_LEN_10B = 0x0U,	/**< 10-bit break */
	MD_LIN_BREAK_LEN_11B = 0x1U,	/**< 11-bit break */
} md_uart_lin_break_len_t;

/**
  * @brief UART TXFIFO size
  */
typedef enum {
	MD_UART_TXFIFO_EMPTY = 0x0U,	/**< Empty */
	MD_UART_TXFIFO_2BYTE = 0x1U,	/**< 2-Bytes */
	MD_UART_TXFIFO_4BYTE = 0x2U,	/**< 4-Bytes */
	MD_UART_TXFIFO_8BYTE = 0x3U,	/**< 8-Bytes */
} md_uart_txfifo_t;

/**
  * @brief UART RXFIFO size
  */
typedef enum {
	MD_UART_RXFIFO_1BYTE  = 0x0U,	/**< 1-Byte */
	MD_UART_RXFIFO_4BYTE  = 0x1U,	/**< 4-Bytes */
	MD_UART_RXFIFO_8BYTE  = 0x2U,	/**< 8-Bytes */
	MD_UART_RXFIFO_14BYTE = 0x3U,	/**< 14-Bytes */
} md_uart_rxfifo_t;

/**
  * @brief UART auto-baud mode
  */
typedef enum {
	MD_UART_ABRMOD_1_TO_0 = 0x0U,	/**< Detect bit0:1, bit1:0 */
	MD_UART_ABRMOD_1      = 0x1U,	/**< Detect bit0:1 */
	MD_UART_ABRMOD_0_TO_1 = 0x2U,	/**< Detect bit0:0, bit1:1 */
} md_uart_auto_baud_mode_t;

/**
  * @brief UART status types
  */
typedef enum {
	MD_UART_STATUS_DR   = (1U << 0),	/**< Data ready */
	MD_UART_STATUS_OE   = (1U << 1),	/**< Overrun error */
	MD_UART_STATUS_PE   = (1U << 2),	/**< Parity error */
	MD_UART_STATUS_FE   = (1U << 3),	/**< Framing error */
	MD_UART_STATUS_BI   = (1U << 4),	/**< Break interrupt */
	MD_UART_STATUS_TBEM = (1U << 5),	/**< Transmit buffer empty */
	MD_UART_STATUS_TEM  = (1U << 6),	/**< Transmitter empty */
	MD_UART_STATUS_RFE  = (1U << 7),	/**< Reveiver FIFO data error */
	MD_UART_STATUS_BUSY = (1U << 8),	/**< UART busy */
	MD_UART_STATUS_TFNF = (1U << 9),	/**< Transmit FIFO not full */
	MD_UART_STATUS_TFEM = (1U << 10),	/**< Transmit FIFO not empty */
	MD_UART_STATUS_RFNE = (1U << 11),	/**< Receive FIFO not empty */
	MD_UART_STATUS_RFF  = (1U << 12),	/**< Receive FIFO full */
	MD_UART_STATUS_DCTS = (1U << 14),	/**< Delta clear to send */
	MD_UART_STATUS_CTS  = (1U << 15),	/**< Clear to send */
} md_uart_status_t;

/**
  * @brief UART interrupt types
  */
typedef enum {
	MD_UART_IT_RXRD  = (1U << 0),	/**< Receive data available */
	MD_UART_IT_TXS   = (1U << 1),	/**< Tx empty status */
	MD_UART_IT_RXS   = (1U << 2),	/**< Rx line status */
	MD_UART_IT_MDS   = (1U << 3),	/**< Modem status */
	MD_UART_IT_RTO   = (1U << 4),	/**< Receiver timeout */
	MD_UART_IT_BZ    = (1U << 5),	/**< Busy status */
	MD_UART_IT_ABE   = (1U << 6),	/**< Auto-baud rate detection end */
	MD_UART_IT_ABTO  = (1U << 7),	/**< Auto-baud rate detection timeout */
	MD_UART_IT_LINBK = (1U << 8),	/**< Lin break detection */
	MD_UART_IT_TC    = (1U << 9),	/**< Transmission complete */
	MD_UART_IT_EOB   = (1U << 10),	/**< End of block */
	MD_UART_IT_CM    = (1U << 11),	/**< Character match */
} md_uart_it_t;

/**
  * @brief UART flags types
  */
typedef enum {
	MD_UART_IF_RXRD  = (1U << 0),	/**<  Receive data available */
	MD_UART_IF_TXS   = (1U << 1),	/**<  Tx empty status */
	MD_UART_IF_RXS   = (1U << 2),	/**<  Rx line status */
	MD_UART_IF_MDS   = (1U << 3),	/**<  Modem status */
	MD_UART_IF_RTO   = (1U << 4),	/**<  Receiver timeout */
	MD_UART_IF_BZ    = (1U << 5),	/**<  Busy status */
	MD_UART_IF_ABE   = (1U << 6),	/**<  Auto-baud rate detection end */
	MD_UART_IF_ABTO  = (1U << 7),	/**<  Auto-baud rate detection timeout */
	MD_UART_IF_LINBK = (1U << 8),	/**<  Lin break detection */
	MD_UART_IF_TC    = (1U << 9),	/**<  Transmission complete */
	MD_UART_IF_EOB   = (1U << 10),	/**<  End of block */
	MD_UART_IF_CM    = (1U << 11),	/**<  Character match */
} md_uart_flag_t;
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions UART Public Functions
  * @{
  */
/** @defgroup MD_UART_Public_Functions_Group2 RBR
  * @{
  */
/**
  * @brief  Get the data Rx register address used for DMA transfer
  * @param  UARTx UART Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t md_uart_get_dma_rx_regaddr(UART_TypeDef *UARTx)
{
	return (uint32_t)(&UARTx->RBR);
}

/**
  * @brief  Read 8-Bits in the data register
  * @param  UARTx UART Instance
  * @retval Data Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t md_uart_recv_data8(UART_TypeDef *UARTx)
{
	return (uint8_t)(READ_REG(UARTx->RBR));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group3 TBR
  * @{
  */
/**
  * @brief  Get the data Tx register address used for DMA transfer
  * @param  UARTx UART Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t md_uart_get_dma_tx_regaddr(UART_TypeDef *UARTx)
{
	return (uint32_t)(&UARTx->TBR);
}

/**
  * @brief  Write data in the data register
  * @param  UARTx UART Instance
  * @param  data Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void md_uart_send_data8(UART_TypeDef *UARTx, uint8_t data)
{
	UARTx->TBR = (uint8_t)data;
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group4 BRR
  * @{
  */
/**
  * @brief  Set UART baud rate
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @param  buadrate UART buad rate value
  * @param  uartclk UART clock
  * @retval None
  */
__STATIC_INLINE void md_uart_set_baudrate(UART_TypeDef *UARTx, uint32_t buadrate, uint32_t uartclk)
{
	if (buadrate == 0)
		return;

	WRITE_REG(UARTx->BRR, uartclk / buadrate);
}

/**
  * @brief  Get UART baud rate
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @param  uartclk UART clock
  * @retval Buad rate value
  */
__STATIC_INLINE uint32_t md_uart_get_baudrate(UART_TypeDef *UARTx, uint32_t uartclk)
{
	return ((uartclk) / (READ_REG(UARTx->BRR)));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group5 LCR
  * @{
  */
/**
  * @brief  UART Rx Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_rx(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_RXEN_MSK);
}

/**
  * @brief  UART Rx Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_rx(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->LCR, UART_LCR_RXEN_MSK);
}

/**
  * @brief  Indicate if UART Rx is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rx(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_RXEN_MSK) == (UART_LCR_RXEN_MSK));
}

/**
  * @brief  Enable UART swap TX/RX pins
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_swap(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_SWAP_MSK);
}

/**
  * @brief  Disable UART swap TX/RX pins
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_swap(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->LCR, UART_LCR_SWAP_MSK);
}

/**
  * @brief  Indicate if UART TX/RX pins is swaped
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_swap(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_SWAP_MSK) == (UART_LCR_SWAP_MSK));
}

/**
  * @brief  UART TX pin active level inversion
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_txinv(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_TXINV_MSK);
}

/**
  * @brief  Indicate if UART TX pin active level is invered
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_txinv(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->LCR, UART_LCR_TXINV_MSK) == (UART_LCR_TXINV_MSK));
}

/**
  * @brief  UART RX pin active level inversion
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_rxinv(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_RXINV_MSK);
}

/**
  * @brief  Indicate if UART RX pin active level is invered
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rxinv(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->LCR, UART_LCR_RXINV_MSK) == (UART_LCR_RXINV_MSK));
}

/**
  * @brief  UART Binary data inversion
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_datainv(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_RXINV_MSK);
}

/**
  * @brief  Indicate if UART Binary data is invered
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_datainv(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->LCR, UART_LCR_DATAINV_MSK) == (UART_LCR_DATAINV_MSK));
}

/**
  * @brief  Set UART Binary data bit order
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_set_bitorder(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_MSBFIRST_MSK);
}

/**
  * @brief  Get UART Binary data bit order
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval The retval:
  *         - 0: LSB first
  *         - 0: MSB first
  */
__STATIC_INLINE uint32_t md_uart_get_bitorder(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->LCR, UART_LCR_MSBFIRST_MSK, UART_LCR_MSBFIRST_POS);
}

/**
  * @brief  Enable RX timeout 
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_rto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_RTOEN_MSK);
}

/**
  * @brief  Disable RX timeout
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_rto(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->LCR, UART_LCR_RTOEN_MSK);
}

/**
  * @brief  Indicate if RTO is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rto(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_RTOEN_MSK) == (UART_LCR_RTOEN_MSK));
}

/**
  * @brief  Enable BRR write 
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_brw(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_BRWEN_MSK);
}

/**
  * @brief  Disable BRR write 
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_brw(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->LCR, UART_LCR_BRWEN_MSK);
}

/**
  * @brief  Indicate if BRR write is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_brw(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_BRWEN_MSK) == (UART_LCR_BRWEN_MSK));
}

/**
  * @brief  Set break
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_set_break(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->LCR, UART_LCR_BC_MSK);
}

/**
  * @brief  Set UART data parity
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @param  parity This parameter can be one of the following values:
  *         @arg @ref MD_UART_PARITY_NONE
  *         @arg @ref MD_UART_PARITY_ODD
  *         @arg @ref MD_UART_PARITY_EVEN
  * @retval None
  */
__STATIC_INLINE void md_uart_set_parity(UART_TypeDef *UARTx, uint32_t parity)
{
	MODIFY_REG(UARTx->LCR, UART_LCR_PEN_MSK | UART_LCR_PS_MSK, parity);
}

/**
  * @brief  Get UART data parity
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_PARITY_NONE
  *         @arg @ref MD_UART_PARITY_ODD
  *         @arg @ref MD_UART_PARITY_EVEN
  */
__STATIC_INLINE uint32_t md_uart_get_parity(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_PEN_MSK | UART_LCR_PS_MSK));
}

/**
  * @brief  Set UART data stop bit
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @param  stop This parameter can be one of the following values:
  *         @arg @ref MD_UART_STOP_BITS_1
  *         @arg @ref MD_UART_STOP_BITS_2
  * @retval None
  */
__STATIC_INLINE void md_uart_set_stop(UART_TypeDef *UARTx, uint32_t stop)
{
	MODIFY_REG(UARTx->LCR, UART_LCR_STOP_MSK, stop);
}

/**
  * @brief  Get UART data stop bit
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_STOP_BITS_1
  *         @arg @ref MD_UART_STOP_BITS_2
  */
__STATIC_INLINE uint32_t md_uart_get_stop(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_STOP_MSK));
}

/**
  * @brief  Set UART data width
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @param  width This parameter can be one of the following values:
  *         @arg @ref MD_UART_WORD_LENGTH_5B
  *         @arg @ref MD_UART_WORD_LENGTH_6B
  *         @arg @ref MD_UART_WORD_LENGTH_7B
  *         @arg @ref MD_UART_WORD_LENGTH_8B
  * @retval None
  */
__STATIC_INLINE void md_uart_set_datawidth(UART_TypeDef *UARTx, uint32_t width)
{
	MODIFY_REG(UARTx->LCR, UART_LCR_DLS_MSK, width);
}

/**
  * @brief  Get UART data stop bit
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_UART_WORD_LENGTH_5B
  *         @arg @ref MD_UART_WORD_LENGTH_6B
  *         @arg @ref MD_UART_WORD_LENGTH_7B
  *         @arg @ref MD_UART_WORD_LENGTH_8B
  */
__STATIC_INLINE uint32_t md_uart_get_datawidth(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->LCR, UART_LCR_DLS_MSK));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group6 MCR
  * @{
  */
/**
  * @brief  Set UART auto baud-rate mode
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @param  mode This parameter can be one of the following values:
  *         - 0: MODE0
  *         - 1: MODE1
  *         - 2: MODE2
  * @retval None
  */
__STATIC_INLINE void md_uart_set_abrmod(UART_TypeDef *UARTx, uint32_t mode)
{
	MODIFY_REG(UARTx->MCR, UART_MCR_ABRMOD_MSK, mode);
}

/**
  * @brief  Get UART auto baud-rate mode
  * @note   This bit can only be written when UART is disabled(TXEN and RXEN=0)
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         - 0: MODE0
  *         - 1: MODE1
  *         - 2: MODE2
  */
__STATIC_INLINE uint32_t md_uart_get_abrmod(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->MCR, UART_MCR_ABRMOD_MSK, UART_MCR_ABRMOD_POSS);
}

/**
  * @brief  Enable auto-baud 
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_abr(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_ABREN_MSK);
}

/**
  * @brief  Disable auto-baud 
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_abr(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_ABREN_MSK);
}

/**
  * @brief  Indicate if auto-baud  is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_abr(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->MCR, UART_MCR_ABREN_MSK) == (UART_MCR_ABREN_MSK));
}

/**
  * @brief  UART auto baud rate detection repeat Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_abrrept(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_ABRRS_MSK);
}

/**
  * @brief  UART auto baud rate detection repeat Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_abrrept(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_ABRRS_MSK);
}

/**
  * @brief  Indicate if UART auto baud rate detection repeat is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_abrrept(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_ABRRS_MSK) == (UART_MCR_ABRRS_MSK));
}

/**
  * @brief  UART half-duplex Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_half_duplex(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_HDSEL_MSK);
}

/**
  * @brief  UART half-duplex Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_half_duplex(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_HDSEL_MSK);
}

/**
  * @brief  Indicate if UART half-duplex is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_half_duplex(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_HDSEL_MSK) == (UART_MCR_HDSEL_MSK));
}

/**
  * @brief  UART Irda Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_irda(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_IREN_MSK);
}

/**
  * @brief  UART Irda Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_irda(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_IREN_MSK);
}

/**
  * @brief  Indicate if UART Irda is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_irda(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_IREN_MSK) == (UART_MCR_IREN_MSK));
}

/**
  * @brief  UART auto flow control Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_auto_flow(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_AFCEN_MSK);
}

/**
  * @brief  UART auto flow control Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_auto_flow(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_AFCEN_MSK);
}

/**
  * @brief  Indicate if UART auto flow control is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_auto_flow(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_AFCEN_MSK) == (UART_MCR_AFCEN_MSK));
}

/**
  * @brief  Set UART RTSn pin level
  * @note   This bit is set and cleared by software when auto flow disabled
  * @param  UARTx UART Instance
  * @param  level This parameter can be one of the following values:
  *         - 0: Low level
  *         - 1: High level
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rtsset(UART_TypeDef *UARTx, uint32_t level)
{
	MODIFY_REG(UARTx->MCR, UART_MCR_RTSCTRL_MSK, level << UART_MCR_RTSCTRL_POS);
}

/**
  * @brief  Get UART RTSn pin level
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         - 0: Low level
  *         - 1: High level
  */
__STATIC_INLINE uint32_t md_uart_get_rtsset(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->MCR, UART_MCR_RTSCTRL_MSK, UART_MCR_RTSCTRL_POS);
}

/**
  * @brief  UART loopback mode Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_loopback(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_LBEN_MSK);
}

/**
  * @brief  UART loopback mode Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_loopback(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_LBEN_MSK);
}

/**
  * @brief  Indicate if UART loopback mode is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_loopback(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_LBEN_MSK) == (UART_MCR_LBEN_MSK));
}

/**
  * @brief  Set UART RS485 automatic address detection invertion
  * @param  UARTx UART Instance
  * @param  aadinv can be one of the following value:
  *         - 0: Low
  *         - 0: High
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rs485_auto_addr_invert(UART_TypeDef *UARTx, uint32_t aadinv)
{
	MODIFY_REG(UARTx->MCR, UART_MCR_AADINV_MSK, aadinv << UART_MCR_AADINV_POS);
}

/**
  * @brief  Get UART RS485 automatic address detection invertion
  * @param  UARTx UART Instance
  * @retval The status.
  */
__STATIC_INLINE uint32_t md_uart_get_rs485_auto_addr_invert(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->MCR, UART_MCR_AADINV_MSK, UART_MCR_AADINV_POS);
}

/**
  * @brief  UART auto address detection auto-control Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_rs485_auto_addr_autocontrol(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_AADEN_MSK);
}

/**
  * @brief  UART auto address detection auto-control Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_rs485_auto_addr_autocontrol(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_AADEN_MSK);
}

/**
  * @brief  Indicate if auto address detection auto-control is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_rs485_auto_addr_autocontrol(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_AADEN_MSK) == (UART_MCR_AADEN_MSK));
}

/**
  * @brief  UART auto address detection normal mode Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_autoaddr_normal_mode(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_AADNOR_MSK);
}

/**
  * @brief  UART auto address detection normal mode Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_autoaddr_normal_mode(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_AADNOR_MSK);
}

/**
  * @brief  Indicate if auto address detection normal mode is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_autoaddr_normal_mode(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_AADNOR_MSK) == (UART_MCR_AADNOR_MSK));
}

/**
  * @brief  UART auto direction mode Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_auto_dir_mode(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_AADDIR_MSK);
}

/**
  * @brief  UART auto direction mode Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_auto_dir_mode(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_AADDIR_MSK);
}

/**
  * @brief  Indicate if auto direction mode is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_autodir_mode(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_AADDIR_MSK) == (UART_MCR_AADDIR_MSK));
}

/**
  * @brief  Send UART LIN mode break request
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_set_lin_break_request(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_BKREQ_MSK);
}

/**
  * @brief  Set UART LIN break detection length
  * @param  UARTx UART Instance
  * @param  length This parameter can be one of the following values:
  *         - 0: 10-bits
  *         - 1: 11-bits
  * @retval None
  */
__STATIC_INLINE void md_uart_set_lin_break_detection_length(UART_TypeDef *UARTx, uint32_t length)
{
	MODIFY_REG(UARTx->MCR, UART_MCR_LINBDL_MSK, length << UART_MCR_LINBDL_POS);
}

/**
  * @brief  Get UART smartcard auto-retry count
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         - 0: 10-bits
  *         - 1: 11-bits
  */
__STATIC_INLINE uint32_t md_uart_get_lin_break_detection_length(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->MCR, UART_MCR_LINBDL_MSK, UART_MCR_LINBDL_POS);
}

/**
  * @brief  UART LIN mode Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_lin(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_LINEN_MSK);
}

/**
  * @brief  UART LIN mode Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_lin(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_LINEN_MSK);
}

/**
  * @brief  Indicate UART LIN mode is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_lin(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_LINEN_MSK) == (UART_MCR_LINEN_MSK));
}
/**
  * @brief  Enable DMA request
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_dmareq(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->MCR, UART_MCR_DMAEN_MSK);
}

/**
  * @brief  Disable DMA request
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_dmareq(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->MCR, UART_MCR_DMAEN_MSK);
}

/**
  * @brief  Check if DMA request is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_dmareq(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->MCR, UART_MCR_DMAEN_MSK) == (UART_MCR_DMAEN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group7 CR
  * @{
  */
/**
  * @brief  Set UART direction control RTSn delay value
  * @param  UARTx UART Instance
  * @param  delay UART direction control RTSn delay value
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rs485_dly(UART_TypeDef *UARTx, uint32_t delay)
{
	MODIFY_REG(UARTx->CR, UART_CR_DLY_MSK, delay << UART_CR_DLY_POSS);
}

/**
  * @brief  Get UART direction control RTSn delay value
  * @param  UARTx UART Instance
  * @retval UART delay value
  */
__STATIC_INLINE uint32_t md_uart_get_rs485_dly(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->CR, UART_CR_DLY_MSK, UART_CR_DLY_POSS);
}

/**
  * @brief  Set UART RS485 address value
  * @param  UARTx UART Instance
  * @param  address UART match address value
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rs485_addr(UART_TypeDef *UARTx, uint32_t address)
{
	MODIFY_REG(UARTx->CR, UART_CR_ADDR_MSK, address);
}

/**
  * @brief  Get UART RS485 address value
  * @param  UARTx UART Instance
  * @retval UART match address value
  */
__STATIC_INLINE uint32_t md_uart_get_rs485_addr(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->CR, UART_CR_ADDR_MSK));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group8 RTOR
  * @{
  */
/**
  * @brief  Set UART receiver timeout value and enable receiver timeout
  * @param  UARTx UART Instance
  * @param  timeout UART timeout value
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rec_timeout(UART_TypeDef *UARTx, uint32_t timeout)
{
	MODIFY_REG(UARTx->RTOR, UART_RTOR_RTO_MSK, timeout);
}

/**
  * @brief  Get UART receiver timeout value
  * @param  UARTx UART Instance
  * @retval UART timeout value
  */
__STATIC_INLINE uint32_t md_uart_get_rec_timeout(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RTOR, UART_RTOR_RTO_MSK));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group9 FCR
  * @{
  */
/**
  * @brief  Set UART Tx FIFO trigger threshold 
  * @param  UARTx UART Instance
  * @param  level This parameter can be one of the following values:
  *         - 0: Empty
  *         - 1: 2 Bytes
  *         - 2: 1 Bytes
  *         - 3: 2 Bytes
  * @retval None
  */
__STATIC_INLINE void md_uart_set_tx_threshold(UART_TypeDef *UARTx, uint32_t level)
{
	MODIFY_REG(UARTx->FCR, UART_FCR_TXTL_MSK, level << UART_FCR_TXTL_POSS);
}

/**
  * @brief  Get UART Tx FIFO trigger threshold
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         - 0: Empty
  *         - 1: 2 Bytes
  *         - 2: 1 Bytes
  *         - 3: 2 Bytes
  */
__STATIC_INLINE uint32_t md_uart_get_tx_threshold(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->FCR, UART_FCR_TXTL_MSK, UART_FCR_TXTL_POSS);
}

/**
  * @brief  Set UART Rx FIFO trigger threshold 
  * @param  UARTx UART Instance
  * @param  level This parameter can be one of the following values:
  *         - 0: 1 Bytes
  *         - 1: 1 Bytes
  *         - 2: 2 Bytes
  *         - 3: 2 Bytes
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rx_threshold(UART_TypeDef *UARTx, uint32_t level)
{
	MODIFY_REG(UARTx->FCR, UART_FCR_RXTL_MSK, level << UART_FCR_RXTL_POSS);
}

/**
  * @brief  Get UART Rx FIFO trigger threshold
  * @param  UARTx UART Instance
  * @retval The retval can be one of the following values:
  *         - 0: 1 Bytes
  *         - 1: 1 Bytes
  *         - 2: 2 Bytes
  *         - 3: 2 Bytes
  */
__STATIC_INLINE uint32_t md_uart_get_rx_threshold(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->FCR, UART_FCR_RXTL_MSK, UART_FCR_RXTL_POSS);
}

/**
  * @brief  Get UART Tx FIFO level
  * @param  UARTx UART Instance
  * @retval The retval can be a value between 0 and 16
  */
__STATIC_INLINE uint32_t md_uart_get_tx_fifo_level(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->FCR, UART_FCR_TXFL_MSK, UART_FCR_TXFL_POSS);
}

/**
  * @brief  Get UART Rx FIFO level
  * @param  UARTx UART Instance
  * @retval The retval can be a value between 0 and 16
  */
__STATIC_INLINE uint32_t md_uart_get_rx_fifo_level(UART_TypeDef *UARTx)
{
	return READ_BITS(UARTx->FCR, UART_FCR_RXFL_MSK, UART_FCR_RXFL_POSS);
}

/**
  * @brief  Reset TX FIFO
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_set_tx_fifo_reset(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->FCR, UART_FCR_TFRST_MSK);
}

/**
  * @brief  Reset RX FIFO
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_set_rx_fifo_reset(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->FCR, UART_FCR_RFRST_MSK);
}

/**
  * @brief  UART FIFO Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_fifo(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->FCR, UART_FCR_FIFOEN_MSK);
}

/**
  * @brief  UART FIFO Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_fifo(UART_TypeDef *UARTx)
{
	CLEAR_BIT(UARTx->FCR, UART_FCR_FIFOEN_MSK);
}

/**
  * @brief  Indicate UART FIFO is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_fifo(UART_TypeDef *UARTx)
{
	return (uint32_t)(READ_BIT(UARTx->FCR, UART_FCR_FIFOEN_MSK) == (UART_FCR_FIFOEN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group10 Interrupt
  * @{
  */
/**
  * @brief  Get CM flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_cm(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_CMIF_MSK) == (UART_RIF_CMIF_MSK));
}

/**
  * @brief  Clear CM flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_cm(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_CMIC_MSK);
}

/**
  * @brief  Get EOB flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_eob(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_EOBIF_MSK) == (UART_RIF_EOBIF_MSK));
}

/**
  * @brief  Clear EOB flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_eob(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_EOBIC_MSK);
}

/**
  * @brief  Get TC flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_tc(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_TCIF_MSK) == (UART_RIF_TCIF_MSK));
}

/**
  * @brief  Clear TC flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_tc(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_TCIC_MSK);
}

/**
  * @brief  Get LINBK flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_linbk(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_LINBKIF_MSK) == (UART_RIF_LINBKIF_MSK));
}

/**
  * @brief  Clear LINBK flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_linbk(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_LINBKIC_MSK);
}

/**
  * @brief  Get ABTO flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_abto(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_ABTOIF_MSK) == (UART_RIF_ABTOIF_MSK));
}

/**
  * @brief  Clear ABTO flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_abto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_ABTOIC_MSK);
}

/**
  * @brief  Get ABE flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_abe(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_ABEIF_MSK) == (UART_RIF_ABEIF_MSK));
}

/**
  * @brief  Clear ABE flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_abe(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_ABEIC_MSK);
}

/**
  * @brief  Get BZ flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_bz(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_BZIF_MSK) == (UART_RIF_BZIF_MSK));
}

/**
  * @brief  Clear BZ flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_bz(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_BZIC_MSK);
}

/**
  * @brief  Get RTO flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rto(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_RTOIF_MSK) == (UART_RIF_RTOIF_MSK));
}

/**
  * @brief  Clear RTO flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_rto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_CHTOIC_MSK);
}

/**
  * @brief  Get MDS flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_mds(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_MDSIF_MSK) == (UART_RIF_MDSIF_MSK));
}

/**
  * @brief  Clear MDS flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_mds(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_MDSIC_MSK);
}

/**
  * @brief  Get RXS flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rxs(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_RXSIF_MSK) == (UART_RIF_RXSIF_MSK));
}

/**
  * @brief  Clear RXS flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_rxs(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_RXSIC_MSK);
}

/**
  * @brief  Get TXS flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_txs(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_TXSIF_MSK) == (UART_RIF_TXSIF_MSK));
}

/**
  * @brief  Clear TXS flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_txs(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_TXSIC_MSK);
}

/**
  * @brief  Get RXRD flag
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_active_flag_rxrd(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->RIF, UART_RIF_RXRDIF_MSK) == (UART_RIF_RXRDIF_MSK));
}

/**
  * @brief  Clear RXRD flag
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_clear_flag_rxrd(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->ICR, UART_ICR_RXRDIC_MSK);
}

/**
  * @brief  Enable CM interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_cm(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_CMIE_MSK);
}

/**
  * @brief  Disable CM interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_cm(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_CMID_MSK);
}

/**
  * @brief  Check if CM interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_cm(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_CMIS_MSK) == (UART_IVS_CMIS_MSK));
}

/**
  * @brief  Enable EOB interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_eob(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_EOBIE_MSK);
}

/**
  * @brief  Disable EOB interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_eob(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_EOBID_MSK);
}

/**
  * @brief  Check if EOB interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_eob(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_EOBIS_MSK) == (UART_IVS_EOBIS_MSK));
}

/**
  * @brief  Enable TC interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_tc(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_TCIE_MSK);
}

/**
  * @brief  Disable TC interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_tc(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_TCID_MSK);
}

/**
  * @brief  Check if TC interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_tc(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_TCIS_MSK) == (UART_IVS_TCIS_MSK));
}

/**
  * @brief  Enable LINBK interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_linbk(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_LINBKIE_MSK);
}

/**
  * @brief  Disable LINBK interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_linbk(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_LINBKID_MSK);
}

/**
  * @brief  Check if LINBK interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_linbk(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_LINBKIS_MSK) == (UART_IVS_LINBKIS_MSK));
}

/**
  * @brief  Enable ABTO interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_abto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_ABTOIE_MSK);
}

/**
  * @brief  Disable ABTO interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_abto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_ABTOID_MSK);
}

/**
  * @brief  Check if ABTO interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_abto(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_ABTOIS_MSK) == (UART_IVS_ABTOIS_MSK));
}

/**
  * @brief  Enable ABE interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_abe(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_ABEIE_MSK);
}

/**
  * @brief  Disable ABE interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_abe(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_ABEID_MSK);
}

/**
  * @brief  Check if ABE interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_abe(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_ABEIS_MSK) == (UART_IVS_ABEIS_MSK));
}

/**
  * @brief  Enable BZ interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_bz(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_BZIE_MSK);
}

/**
  * @brief  Disable BZ interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_bz(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_BZID_MSK);
}

/**
  * @brief  Check if BZ interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_bz(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_BZIS_MSK) == (UART_IVS_BZIS_MSK));
}

/**
  * @brief  Enable RTO interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_rto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_RTOIE_MSK);
}

/**
  * @brief  Disable RTO interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_rto(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_RTOID_MSK);
}

/**
  * @brief  Check if RTO interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_rto(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_RTOIS_MSK) == (UART_IVS_RTOIS_MSK));
}

/**
  * @brief  Enable MDS interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_mds(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_MDSIE_MSK);
}

/**
  * @brief  Disable MDS interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_mds(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_MDSID_MSK);
}

/**
  * @brief  Check if MDS interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_mds(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_MDSIS_MSK) == (UART_IVS_MDSIS_MSK));
}

/**
  * @brief  Enable RXS interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_rxs(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_RXSIE_MSK);
}

/**
  * @brief  Disable RXS interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_rxs(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_RXSID_MSK);
}

/**
  * @brief  Check if RXS interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_rxs(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_RXSIS_MSK) == (UART_IVS_RXSIS_MSK));
}

/**
  * @brief  Enable TXS interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_txs(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_TXSIE_MSK);
}

/**
  * @brief  Disable TXS interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_txs(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_TXSID_MSK);
}

/**
  * @brief  Check if TXS interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_txs(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_TXSIS_MSK) == (UART_IVS_TXSIS_MSK));
}

/**
  * @brief  Enable RXRD interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_enable_it_rxrd(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IER, UART_IER_RXRDIE_MSK);
}

/**
  * @brief  Disable RXRD interrupt
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void md_uart_disable_it_rxrd(UART_TypeDef *UARTx)
{
	SET_BIT(UARTx->IDR, UART_IDR_RXRDID_MSK);
}

/**
  * @brief  Check if RXRD interrupt is enabled
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_uart_is_enabled_it_rxrd(UART_TypeDef *UARTx)
{
	return (READ_BIT(UARTx->IVS, UART_IVS_RXRDIS_MSK) == (UART_IVS_RXRDIS_MSK));
}
/**
  * @}
  */
/** @defgroup MD_UART_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_uart_reset(UART_TypeDef *UARTx);
extern void md_uart_init(UART_TypeDef *UARTx, md_uart_init_t *init);
extern void md_uart_init_struct(md_uart_init_t *init);
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
