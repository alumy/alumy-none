/**
  *********************************************************************************
  *
  * @file    md_spi.h
  * @brief   Header file of SPI module driver.
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

#ifndef __MD_SPI_H__
#define __MD_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_SPI SPI
  * @brief SPI micro driver
  * @{
  */
/** @defgroup MD_SPI_Public_Types SPI Public Types
  * @{
  */
/**
  * @brief clock phase
  */
typedef enum {
	MD_SPI_CPHA_FIRST  = 0U,	/**< Transiting data in the first edge */
	MD_SPI_CPHA_SECOND = 1U,	/**< Transiting data in the seconde edge */
} md_spi_cpha_t;

/**
  * @brief clock polarity
  */
typedef enum {
	MD_SPI_CPOL_LOW  = 0U,	/**< Polarity hold low when spi-bus is idle */
	MD_SPI_CPOL_HIGH = 1U,	/**< Polarity hold high when spi-bus is idle */
} md_spi_cpol_t;

/**
  * @brief master selection
  */
typedef enum {
	MD_SPI_MODE_SLAVER = 0U,	/**< Slave mode */
	MD_SPI_MODE_MASTER = 1U,	/**< Master mode */
} md_spi_mode_t;

/**
  * @brief baud rate control
  */
typedef enum {
	MD_SPI_BAUD_2   = 0U,	/**< fpclk/2 */
	MD_SPI_BAUD_4   = 1U,	/**< fpclk/4 */
	MD_SPI_BAUD_8   = 2U,	/**< fpclk/8 */
	MD_SPI_BAUD_16  = 3U,	/**< fpclk/16 */
	MD_SPI_BAUD_32  = 4U,	/**< fpclk/32 */
	MD_SPI_BAUD_64  = 5U,	/**< fpclk/64 */
	MD_SPI_BAUD_128 = 6U,	/**< fpclk/128 */
	MD_SPI_BAUD_256 = 7U,	/**< fpclk/256 */
} md_spi_baud_t;

/**
  * @brief frame format
  */
typedef enum {
	MD_SPI_FIRSTBIT_MSB = 0U,	/**< MSB transmitted first */
	MD_SPI_FIRSTBIT_LSB = 1U,	/**< LSB transmitted first */
} md_spi_firstbit_t;

/**
  * @brief data frame format
  */
typedef enum {
	MD_SPI_DATA_SIZE_8  = 0U,	/**< 8-bit data frame format is selected for transmission/reception */
	MD_SPI_DATA_SIZE_16 = 1U,	/**< 16-bit data frame format is selected for transmission/reception */
} md_spi_datasize_t;

/**
  * @brief interrupt control
  */
typedef enum {
	MD_SPI_IT_ERR   = (1U << 5),	/**< error interrupt */
	MD_SPI_IT_RXBNE = (1U << 6),	/**< rx buffer not empty interrupt */
	MD_SPI_IT_TXBE  = (1U << 7),	/**< tx buffer empty interrupt */
} md_spi_it_t;

/**
  * @brief interrupt flag
  */
typedef enum {
	MD_SPI_IF_RXBNE  = (1U << 0),	/**< receive buffer not empty */
	MD_SPI_IF_TXBE   = (1U << 1),	/**< transmit buffer empty */
	MD_SPI_IF_CRCERR = (1U << 4),	/**< crc error flag */
	MD_SPI_IF_MODF   = (1U << 5),	/**< mode fault */
	MD_SPI_IF_OVE    = (1U << 6),	/**< overrun flag */
	MD_SPI_IF_BUSY   = (1U << 7),	/**< busy flag */
} md_spi_flag_t;

/**
  * @brief SPI error status
  */
typedef enum {
	MD_SPI_ERROR_NONE = 0U,		/**< none */
	MD_SPI_ERROR_MODF = 1U,		/**< mode fault */
	MD_SPI_ERROR_CRC  = 2U,		/**< crc error */
	MD_SPI_ERROR_OVE  = 4U,		/**< overrun error */
	MD_SPI_ERROR_DMA  = 8U,		/**< dma error  */
	MD_SPI_ERROR_FLAG = 0x10U,	/**< interrupt flag error */
} md_spi_error_t;

/**
  * @brief SPI state structures definition
  */
typedef enum {
	MD_SPI_STATE_RESET      = 0x00U,	/**< Peripheral is not initialized */
	MD_SPI_STATE_READY      = 0x01U,	/**< Peripheral Initialized and ready for use */
	MD_SPI_STATE_BUSY       = 0x02U,	/**< an internal process is ongoing */
	MD_SPI_STATE_BUSY_TX    = 0x11U,	/**< transmit is ongoing */
	MD_SPI_STATE_BUSY_RX    = 0x21U,	/**< receive is ongoing */
	MD_SPI_STATE_BUSY_TX_RX = 0x31U,	/**< transmit and receive are ongoing */
	MD_SPI_STATE_TIMEOUT    = 0x03U,	/**< Timeout state */
	MD_SPI_STATE_ERROR      = 0x04U,	/**< Error */
} md_spi_state_t;

/**
  * @brief SPI direction definition
  */
typedef enum {
	MD_SPI_DIRECTION_2LINES        = 0U,	/**< 2 lines */
	MD_SPI_DIRECTION_2LINES_RXONLY = 1U,	/**< 2 lines only rx */
	MD_SPI_DIRECTION_1LINE         = 2U,	/**< 1 line */
	MD_SPI_DIRECTION_1LINE_RX      = 3U,	/**< 1 line only rx */
} md_spi_direction_t;

/**
  * @brief SPI dma request definition
  */
typedef enum {
	MD_SPI_DMA_REQ_TX = 0U,	/**< TX dma request */
	MD_SPI_DMA_REQ_RX = 1U,	/**< RX dma request */
} md_spi_dma_req_t;

/**
  * @brief SPI TXE/RXNE status definition
  */
typedef enum {
	MD_SPI_SR_TXBE       = 0U,	/**< SR.TXE set */
	MD_SPI_SR_RXBNE      = 1U,	/**< SR.RXNE set */
	MD_SPI_SR_TXBE_RXBNE = 2U,	/**< SR.TXE and SR.RXNE set */
} md_spi_sr_status_t;

/**
  * @brief SPI init structure definition
  */
typedef struct {
	md_spi_mode_t mode;		/**< SPI mode */
	md_spi_direction_t dir;		/**< SPI direction */
	md_spi_datasize_t data_size;	/**< SPI data size */
	md_spi_baud_t baud;		/**< SPI baudrate prescaler */
	md_spi_cpha_t phase;		/**< SPI clock phase */
	md_spi_cpol_t polarity;		/**< SPI clock polarity */
	md_spi_firstbit_t first_bit;	/**< SPI first bit */
	type_func_t ss_en;		/**< SPI ssm enable or disable */
	type_func_t crc_calc;		/**< SPI crc calculation */
	uint16_t crc_poly;		/**< SPI crc polynomial */
} md_spi_init_t;
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions SPI Public Functions
  * @{
  */
/** @defgroup MD_SPI_Public_Functions_Group2 CON1
  * @{
  */
/**
  * @brief  Set spi duplex line simplex direction commumication.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_set_duplex_line_simplex(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK);
}

/**
  * @brief  Set spi simplex line duplex direction commumication.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_set_simplex_line_duplex(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK);
}

/**
  * @brief  Check if spi is Enable duplex line simplex direction commumication.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t md_spi_is_enable_duplex_line_simplex(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK) != SPI_CON1_BIDEN_MSK);
}

/**
  * @brief  Check if spi is Enable simplex line duplex direction commumication
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t md_spi_is_enable_simplex_line_duplex(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_BIDEN_MSK) == SPI_CON1_BIDEN_MSK);
}

/**
  * @brief  Enable spi duplex line mode data transmit.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_simplex_line_tx(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_BIDOEN_MSK);
}

/**
  * @brief  Enable spi duplex line mode data receive.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_simplex_line_rx(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_BIDOEN_MSK);
}

/**
  * @brief  Enable spi crc by hardware.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_crc_hardware(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_CRCEN_MSK);
}

/**
  * @brief  Disable spi crc by hardware.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_crc_hardware(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_CRCEN_MSK);
}

/**
  * @brief  Check if spi is enable crc by hardware.
  * @param  SPIx: SPI Instance.
  * @retval State for 1 or 0.
  */
__STATIC_INLINE uint32_t md_spi_is_enable_crc_hardware(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_CRCEN_MSK) == SPI_CON1_CRCEN_MSK);
}

/**
  * @brief  Enable spi next time transmit is crc.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_next_crc_transmit(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_NXTCRC_MSK);
}

/**
  * @brief  Disable spi next time transmit is crc.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_disable_next_crc_transmit(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_NXTCRC_MSK);
}

/**
  * @brief  Check if spi is enable next time transmit is crc.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_next_crc_transmit(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_NXTCRC_MSK) == SPI_CON1_NXTCRC_MSK);
}

/**
  * @brief  Enable spi 16 bytes commumication data .
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_16_byte_commumication(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_FLEN_MSK);
}

/**
  * @brief  Enable spi 8 bytes commumication data .
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_8_byte_commumication(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_FLEN_MSK);
}

/**
  * @brief  Check if spi is enable 16 bytes commumication data.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_16_byte_commumication(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_FLEN_MSK) == SPI_CON1_FLEN_MSK);
}

/**
  * @brief  Check if spi is enable 8 bytes commumication data.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_8_byte_commumication(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_FLEN_MSK) != SPI_CON1_FLEN_MSK);
}

/**
  * @brief  Enable spi only receive mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_recv_only(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_RXO_MSK);
}

/**
  * @brief  Disable spi only receive mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_recv_only(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_RXO_MSK);
}

/**
  * @brief  Check if spi is enable only receive mode.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t md_spi_is_enable_recv_only(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_RXO_MSK) == SPI_CON1_RXO_MSK);
}

/**
  * @brief  Enable spi control slave device by software.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_control_slave(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_SSEN_MSK);
}

/**
  * @brief  Disable spi control slave device by software.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_control_slave(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_SSEN_MSK);
}

/**
  * @brief  Check if spi is enable control slave device by software.
  * @param  SPIx: SPI Instance.
  * @retval State for bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_control_slave(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_SSEN_MSK) == SPI_CON1_SSEN_MSK);
}

/**
  * @brief  Enable spi chip select output high.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_ss_output_high(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_SSOUT_MSK);
}

/**
  * @brief  Enable spi chip select output low.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_ss_output_low(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_SSOUT_MSK);
}

/**
  * @brief  Check if spi is enable chip select output high.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_ss_output_high(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_SSOUT_MSK) == SPI_CON1_SSOUT_MSK);
}

/**
  * @brief  Enable spi data first transmit MSB.
  * @param  SPIx: SPI Instance.
  * @retval None
  */
__STATIC_INLINE void md_spi_enable_first_transmit_msb(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_LSBFST_MSK);
}

/**
  * @brief  Enable spi data first transmit LSB.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_first_transmit_lsb(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_LSBFST_MSK);
}

/**
  * @brief  Check if spi is enable data first transmit MSB.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_first_transmit_msb(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_LSBFST_MSK) != SPI_CON1_LSBFST_MSK);
}

/**
  * @brief  Enable SPI module.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_SPIEN_MSK);
}

/**
  * @brief  Disable SPI module.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_SPIEN_MSK);
}

/**
  * @brief  Check if is enable spi.
  * @param  SPIx: SPI Instance.
  * @retval State for bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_SPIEN_MSK) == SPI_CON1_SPIEN_MSK);
}

/**
  * @brief  Set spi commumication baudrate.
  * @param  SPIx: SPI Instance.
  * @param  baud: specific commumication rate @see md_spi_baud_t.
  * @retval None.
  */
__STATIC_INLINE void md_spi_set_commumication_baud(SPI_TypeDef *SPIx, md_spi_baud_t baud)
{
	MODIFY_REG(SPIx->CON1, SPI_CON1_BAUD_MSK, baud << SPI_CON1_BAUD_POSS);
}

/**
  * @brief  Get spi commumication baudrate.
  * @param  SPIx: SPI Instance.
  * @retval specific commumication rate @see md_spi_baud_t.
  */
__STATIC_INLINE uint32_t md_spi_get_commumication_baud(SPI_TypeDef *SPIx)
{
	return READ_BITS(SPIx->CON1, SPI_CON1_BAUD_MSK, SPI_CON1_BAUD_POSS);
}

/**
  * @brief  Enable spi master mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_master_mode(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_MSTREN_MSK);
}

/**
  * @brief  Enable spi slave mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_slave_mode(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_MSTREN_MSK);
}
/**
  * @brief  Check if spi is enable master mode.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_master_mode(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_MSTREN_MSK) == SPI_CON1_CPOL_MSK);
}

/**
  * @brief  Enable spi sck bus keep high polarity in idle mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_sck_high_idle(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_CPOL_MSK);
}

/**
  * @brief  Enable spi sck bus keep low polarity in idle mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_sck_low_idle(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_CPOL_MSK);
}

/**
  * @brief  Check if spi is enable sck keep high in idle.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_sck_high_idle(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_CPOL_MSK) == SPI_CON1_CPOL_MSK);
}

/**
  * @brief  Enable spi sample data in seconde time edge.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_sample_sec_edge(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON1, SPI_CON1_CPHA_MSK);
}

/**
  * @param  SPIx: SPI Instance.
  * @brief  Enable spi sample data in first time edge.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_sample_first_edge(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON1, SPI_CON1_CPHA_MSK);
}

/**
  * @brief  Check is spi is enable sample data in seconde time edge.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (0 or 1).
  */
__STATIC_INLINE uint32_t md_spi_set_sram_read_time(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON1, SPI_CON1_CPHA_MSK) == SPI_CON1_CPHA_MSK);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group3 CON2
  * @{
  */
/**
  * @brief  Enable spi transmit fifo empty interrupt.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_txe_interrupt(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON2, SPI_CON2_TXBEIE_MSK);
}

/**
  * @brief  Disable spi transmit fifo empty interrupt.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_txe_interrupt(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON2, SPI_CON2_TXBEIE_MSK);
}

/**
  * @brief  Check if spi is enable transmit fifo empty interrupt.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_txe_interrupt(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON2, SPI_CON2_TXBEIE_MSK) == SPI_CON2_TXBEIE_MSK);
}

/**
  * @brief  Enable spi receive fifo not empty interrupt.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_rxne_interrupt(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON2, SPI_CON2_RXBNEIE_MSK);
}

/**
  * @brief  Disable spi receive fifo not empty interrupt.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_rxne_interrupt(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON2, SPI_CON2_RXBNEIE_MSK);
}

/**
  * @brief  Check if spi is enable transmit fifo empty interrupt.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_rxne_interrupt(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON2, SPI_CON2_RXBNEIE_MSK) == SPI_CON2_RXBNEIE_MSK);
}

/**
  * @brief  Enable spi error interrupt.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_error_interrupt(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON2, SPI_CON2_ERRIE_MSK);
}

/**
  * @brief  Disable spi error interrupt.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_error_interrupt(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON2, SPI_CON2_ERRIE_MSK);
}

/**
  * @brief  Check if spi is enable error interrupt.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_error_interrupt(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON2, SPI_CON2_ERRIE_MSK) == SPI_CON2_ERRIE_MSK);
}

/**
  * @brief  Enable spi nss output in multi-host mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_nss_output_multi_host(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON2, SPI_CON2_NSSOE_MSK);
}

/**
  * @brief  Disable spi nss output in multi-host mode.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_nss_output_multi_host(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON2, SPI_CON2_NSSOE_MSK);
}

/**
  * @brief  Check if spi is enable nss output in multi-host mode.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_nss_output_multi_host(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON2, SPI_CON2_NSSOE_MSK) == SPI_CON2_NSSOE_MSK);
}

/**
  * @brief  Enable spi transmit dma.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_tx_dma(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON2, SPI_CON2_TXDMA_MSK);
}

/**
  * @brief  Disable spi transmit dma.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_tx_dma(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON2, SPI_CON2_TXDMA_MSK);
}

/**
  * @brief  Check if spi is enable transmit dma.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_tx_dma(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON2, SPI_CON2_TXDMA_MSK) == SPI_CON2_TXDMA_MSK);
}

/**
  * @brief  Enable spi receive dma.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_enable_rx_dma(SPI_TypeDef *SPIx)
{
	SET_BIT(SPIx->CON2, SPI_CON2_RXDMA_MSK);
}

/**
  * @brief  Disable spi receive dma.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_disable_rx_dma(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->CON2, SPI_CON2_RXDMA_MSK);
}

/**
  * @brief  Check if spi is enable transmit dma.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_enable_rx_dma(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->CON2, SPI_CON2_RXDMA_MSK) == SPI_CON2_RXDMA_MSK);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group4 STAT
  * @{
  */
/**
  * @brief  Get spi busy flag.
  * @param  SPIx: SPI Instance.
  * @retval State for bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_busy(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->STAT, SPI_STAT_BUSY_MSK) == SPI_STAT_BUSY_MSK);
}

/**
  * @brief  Get spi overr flag.
  * @param  SPIx: SPI Instance.
  * @retval State for bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_overr(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->STAT, SPI_STAT_OVERR_MSK) == SPI_STAT_OVERR_MSK);
}

/**
  * @brief  Get spi moderr flag.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_moderr(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->STAT, SPI_STAT_MODERR_MSK) == SPI_STAT_MODERR_MSK);
}

/**
  * @brief  Get spi crc by hardware flag.
  * @param  SPIx: SPI Instance. 
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_crcerr(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->STAT, SPI_STAT_CRCERR_MSK) == SPI_STAT_CRCERR_MSK);
}

/**
  * @brief  Clear spi crc by hardware flag.
  * @param  SPIx: SPI Instance.
  * @retval None.
  */
__STATIC_INLINE void md_spi_clear_flag_crcerr(SPI_TypeDef *SPIx)
{
	CLEAR_BIT(SPIx->STAT, SPI_STAT_CRCERR_MSK);
}

/**
  * @brief  Get spi transmit buffer empty flag.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_txbe(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->STAT, SPI_STAT_TXBE_MSK) == SPI_STAT_TXBE_MSK);
}

/**
  * @brief  Get spi receive buffer not empty flag.
  * @param  SPIx: SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_spi_is_active_flag_rxbne(SPI_TypeDef *SPIx)
{
	return (READ_BIT(SPIx->STAT, SPI_STAT_RXBNE_MSK) == SPI_STAT_RXBNE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group5 DATA
  * @{
  */
/**
  * @brief  Set spi data register value.
  * @param  SPIx: SPI Instance.
  * @param  data: tx data.
  * @retval None.
  */
__STATIC_INLINE void md_spi_set_data_reg(SPI_TypeDef *SPIx, uint32_t data)
{
	WRITE_REG(SPIx->DATA, data);
}

/**
  * @brief  Get spi data register value.
  * @param  SPIx: SPI Instance.
  * @retval data: value for data register.
  */
__STATIC_INLINE uint32_t md_spi_get_data_reg_value(SPI_TypeDef *SPIx)
{
	return READ_REG(SPIx->DATA);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group6 CRCPOLY
  * @{
  */
/**
  * @brief  Set spi crc register value.
  * @param  SPIx: SPI Instance.
  * @param  data: crc data.
  * @retval None.
  */
__STATIC_INLINE void md_spi_set_crc_reg_value(SPI_TypeDef *SPIx, uint32_t data)
{
	WRITE_REG(SPIx->CRCPOLY, data);
}

/**
  * @brief  Get spi crc register value.
  * @param  SPIx: SPI Instance.
  * @retval data: value for crc register.
  */
__STATIC_INLINE uint32_t md_spi_get_crc_reg_value(SPI_TypeDef *SPIx)
{
	return READ_REG(SPIx->CRCPOLY);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group7 RXCRC
  * @{
  */
/**
  * @brief  Get spi receive data crc value.
  * @param  SPIx: SPI Instance.
  * @retval data: value for receive crc.
  */
__STATIC_INLINE uint32_t md_spi_get_rx_data_crc(SPI_TypeDef *SPIx)
{
	return READ_REG(SPIx->RXCRC);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group8 TXCRC
  * @{
  */
/**
  * @brief  Get spi transmit data crc value.
  * @param  SPIx: SPI Instance.
  * @retval data: value for transmit crc.
  */
__STATIC_INLINE uint32_t md_spi_get_tx_data_crc(SPI_TypeDef *SPIx)
{
	return READ_REG(SPIx->TXCRC);
}
/**
  * @}
  */
/** @defgroup MD_SPI_Public_Functions_Group1 Initialization
  * @{
  */
extern md_status_t md_spi_init(SPI_TypeDef *SPIx, md_spi_init_t *init);
extern void md_spi_reset(SPI_TypeDef *SPIx);
extern void md_spi_struct_init(md_spi_init_t *init);
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
