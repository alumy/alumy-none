/**
  *********************************************************************************
  *
  * @file    md_i2c.h
  * @brief   Header file of I2C module driver.
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

#ifndef __MD_I2C_H__
#define __MD_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** 
  * @addtogroup Micro_Driver
  * @{
  */

/**
  * @defgroup MD_I2C I2C
  * @brief I2C micro driver
  * @{
  */

/**
  * @defgroup MD_I2C_Public_Macros I2C Public Macros
  * @{
  */
#define MD_I2C_ENABLE(x)  (SET_BIT((x)->CON1, I2C_CON1_PEN_MSK))
#define MD_I2C_DISABLE(x) (CLEAR_BIT((x)->CON1, I2C_CON1_PEN_MSK))

#define MD_I2C_RISE_TIME(x, u)	(((u) <= MD_I2C_STANDARD_MODE_MAX_CLK) ? ((x) + 1) :\
        ((((x) * 300) / 1000) + 1))
/**
  * @}
  */

/** @defgroup MD_I2C_Public_Types I2C Public Types
  * @{
  */  
/**
  * @brief I2C Clock
  */
typedef enum {
	MD_I2C_STANDARD_MODE_MAX_CLK = 100000U,	/**< Standard mode clock */
	MD_I2C_FAST_MODE_MAX_CLK     = 400000U,	/**< Fast mode clock */
} md_i2c_clock_t;

/**
  * @brief I2C Addressing Mode
  */
typedef enum {
	MD_I2C_ADDR_7BIT  = 0x0U,	/**< 7 bit address */
	MD_I2C_ADDR_10BIT = 0x8000U,	/**< 10 bit address */
} md_i2c_addr_t;

/**
  * @brief I2C General Call Addressing mode
  */
typedef enum {
	MD_I2C_GENERALCALL_DISABLE = 0x0U, 	/**< feneral call address is disable */
	MD_I2C_GENERALCALL_ENABLE  = 0x40U,	/**< feneral call address is enable */
} md_i2c_general_addr_t;

/**
  * @brief I2C Nostretch Mode
  */
typedef enum {
	MD_I2C_NOSTRETCH_DISABLE = 0x0U, 	/**< Nostretch disable */
	MD_I2C_NOSTRETCH_ENABLE  = 0x80U,	/**< Nostretch enable */
} md_i2c_nostretch_t;


/**
  * @brief I2C Duty Cycle
  */
typedef enum {
	MD_I2C_DUTYCYCLE_2    = 0x0U,   	/**< duty cycle is 2 */
	MD_I2C_DUTYCYCLE_16_9 = 0x4000U,	/**< duty cycle is 16/9 */
} md_i2c_duty_t;


/**
  * @brief I2C Dual Addressing Mode
  */
typedef enum {
	MD_I2C_DUALADDR_DISABLE = 0x0U,	/**< dual address is disable */
	MD_I2C_DUALADDR_ENABLE  = 0x1U,	/**< dual address is enable */
} md_i2c_dual_addr_t;

/**
  * @brief I2C CKCFG Register
  */
typedef enum {
	MD_I2C_CKCFG_CLKSET =  0xFFFU,    	/**< CLKSET BITS */
	MD_I2C_CKCFG_DUTY   = (1U << 14),	/**< DUTY BIT */
	MD_I2C_CKCFG_CLKMOD = (1U << 15),	/**< CLKMOD BIT */
} md_i2c_ckcfg_t;

/**
 * @brief I2C Configuration Structure definition
 */
typedef struct {
	uint32_t clk_speed;			/**< Specifies the clock frequency */
	md_i2c_duty_t duty;			/**< Specifies the I2C fast mode duty cycle */
	uint32_t own_addr1;			/**< Specifies the first device own address */
	md_i2c_addr_t addr_mode;		/**< Specifies addressing mode */
	md_i2c_dual_addr_t dual_addr;		/**< Specifies if dual addressing mode is selected */
	uint32_t own_addr2;			/**< Specifies the second device own address */
	md_i2c_general_addr_t general_call;	/**< Specifies if general call mode is selected */
	md_i2c_nostretch_t no_stretch;		/**< Specifies if nostretch mode is selected */
} md_i2c_init_t;

/**
  * @}
  */

/** @defgroup MD_I2C_Public_Functions I2C Public Functions
  * @{
  */

/** @defgroup MD_I2C_Public_Functions_Group2 CON1
  * @{
  */
/**
  * @brief  Enable Reset of I2C peripheral.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_reset(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_SRST_MSK);
}

/**
  * @brief  Disable Reset of I2C peripheral.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_reset(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_SRST_MSK);
}

/**
  * @brief  Check if the I2C peripheral is under reset state or not.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_reset(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_SRST_MSK) == (I2C_CON1_SRST_MSK));
}

/**
  * @brief  Enable SMBus alert (Host or Device mode)
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_alert(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_ALARM_MSK);
}

/**
  * @brief  Disable SMBus alert (Host or Device mode)
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_smbus_alert(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_ALARM_MSK);
}

/**
  * @brief  Check if SMBus alert (Host or Device mode) is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_smbus_alert(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_ALARM_MSK) == (I2C_CON1_ALARM_MSK));
}

/**
  * @brief  Enable transmit pack error verify
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_transfer_pec(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_TRPEC_MSK);
}

/**
  * @brief  Disable transmit pack error verify
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_transfer_pec(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_TRPEC_MSK);
}

/**
  * @brief  Check if i2c transmit pack error verify is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_transfer_pec(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_TRPEC_MSK) == (I2C_CON1_TRPEC_MSK));
}

/**
  * @brief  Enable bit POS (master/host mode).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_bit_pos(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_POSAP_MSK);
}

/**
  * @brief  Disable bit POS (master/host mode).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_bit_pos(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_POSAP_MSK);
}

/**
  * @brief  Check if bit POS  is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_bit_pos(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_POSAP_MSK) == (I2C_CON1_POSAP_MSK));
}

/**
  * @brief  Enable I2C received acknowledgement.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_ack(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_ACKEN_MSK);
}

/**
  * @brief  Disable I2C received acknowledgement.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_ack(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_ACKEN_MSK);
}

/**
  * @brief  Check if is enabled I2C received acknowledgement.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_rx_ack(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_ACKEN_MSK) == (I2C_CON1_ACKEN_MSK));
}

/**
  * @brief  Generate a STOP condition after the current byte transfer (master mode).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_generate_stop_condition_by_master(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_STOP_MSK);
}

/**
  * @brief  Relase bus after the current byte transfer (master mode).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_relase_bus_by_slave(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_STOP_MSK);
}

/**
  * @brief  Generate a START or RESTART condition
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_generate_start_condition(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_START_MSK);
}

/**
  * @brief  Enable Clock stretching.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_clock_stretching(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_DISCS_MSK);
}

/**
  * @brief  Disable Clock stretching.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_clock_stretching(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_DISCS_MSK);
}

/**
  * @brief  Check if Clock stretching is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_clock_stretching(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_DISCS_MSK) != (I2C_CON1_DISCS_MSK));
}

/**
  * @brief  Enable General Call.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_general_call(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_GCEN_MSK);
}

/**
  * @brief  Disable General Call.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_general_call(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_GCEN_MSK);
}

/**
  * @brief  Check if General CaMD is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_general_call(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_GCEN_MSK) == (I2C_CON1_GCEN_MSK));
}

/**
  * @brief  Enable SMBus Packet Error Calculation (PEC).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_pec(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_PECEN_MSK);
}

/**
  * @brief  Disable SMBus Packet Error Calculation (PEC).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_smbus_pec(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_PECEN_MSK);
}

/**
  * @brief  Check if SMBus Packet Error Calculation (PEC) is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_smbus_pec(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_PECEN_MSK) == (I2C_CON1_PECEN_MSK));
}

/**
  * @brief  Enable I2C ARP.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_arp(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_ARPEN_MSK);
}

/**
  * @brief  Disable I2C ARP.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_arp(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_ARPEN_MSK);
}

/**
  * @brief  Check if ARP is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_arp(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_ARPEN_MSK) == (I2C_CON1_ARPEN_MSK));
}

/**
  * @brief  Enable I2C module.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_i2c_module(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_PMOD_MSK);
}

/**
  * @brief  enable I2C SMBUS module.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_smbus_module(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_PMOD_MSK);
}

/**
  * @brief  Check if the I2C module is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_i2c_module(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_PMOD_MSK) == (I2C_CON1_PMOD_MSK));
}

/**
  * @brief  Enable I2C peripheral (PE = 1).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_pe(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON1, I2C_CON1_PEN_MSK);
}

/**
  * @brief  Disable I2C peripheral (PE = 0).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_pe(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON1, I2C_CON1_PEN_MSK);
}

/**
  * @brief  Check if the I2C peripheral is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_pe(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON1, I2C_CON1_PEN_MSK) == (I2C_CON1_PEN_MSK));
}

/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group3 CON2
  * @{
  */
/**
  * @brief  Enable DMA last transfer.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_last_dma(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON2, I2C_CON2_LDMA_MSK);
}

/**
  * @brief  Disable DMA last transfer.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_last_dma(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON2, I2C_CON2_LDMA_MSK);
}

/**
  * @brief  Check if DMA last transfer is enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enabled_last_dma(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON2, I2C_CON2_LDMA_MSK) == (I2C_CON2_LDMA_MSK));
}

/**
  * @brief  Enable DMA transmission requests.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_dma_req_tx(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON2, I2C_CON2_DMAEN_MSK);
}

/**
  * @brief  Disable DMA transmission requests.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_dma_req_tx(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON2, I2C_CON2_DMAEN_MSK);
}

/**
  * @brief  Check if DMA transmission requests are enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_dma_req_tx(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON2, I2C_CON2_DMAEN_MSK) == (I2C_CON2_DMAEN_MSK));
}

/**
  * @brief  Enable Buffer interrupts.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_buf(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON2, I2C_CON2_BUFIE_MSK);
}

/**
  * @brief  Disable Buffer interrupts.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_buf(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON2, I2C_CON2_BUFIE_MSK);
}

/**
  * @brief  Check if Buffer interrupts are enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_buf(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON2, I2C_CON2_BUFIE_MSK) == (I2C_CON2_BUFIE_MSK));
}

/**
  * @brief  Enable Events interrupts.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_evt(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON2, I2C_CON2_EVTIE_MSK);
}

/**
  * @brief  Disable Events interrupts.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_evt(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON2, I2C_CON2_EVTIE_MSK);
}

/**
  * @brief  Check if Events interrupts are enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_evt(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON2, I2C_CON2_EVTIE_MSK) == (I2C_CON2_EVTIE_MSK));
}

/**
  * @brief  Enable Error interrupts.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_it_err(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CON2, I2C_CON2_ERRIE_MSK);
}

/**
  * @brief  Disable Error interrupts.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_it_err(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CON2, I2C_CON2_ERRIE_MSK);
}

/**
  * @brief  Check if Error interrupts are enabled or disabled.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_it_err(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->CON2, I2C_CON2_ERRIE_MSK) == (I2C_CON2_ERRIE_MSK));
}

/**
  * @brief  Configure the Peripheral clock frequency.
  * @param  i2c I2C Instance.
  * @param  PeriphClock Peripheral Clock (in Hz)
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_periph_clock(I2C_TypeDef *i2c, uint32_t PeriphClock)
{
	MODIFY_REG(i2c->CON2, I2C_CON2_CLKF_MSK, ((uint32_t)((PeriphClock) / 1000000U) << I2C_CON2_CLKF_POSS));
}

/**
  * @brief  Get the Peripheral clock frequency.
  * @param  i2c I2C Instance.
  * @retval Value of Peripheral Clock (in Hz)
  */
__STATIC_INLINE uint32_t md_i2c_get_periph_clock(I2C_TypeDef *i2c)
{
	return (uint32_t)(((READ_BITS(i2c->CON2, I2C_CON2_CLKF_MSK, I2C_CON2_CLKF_POSS))*1000000U));
}

/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group4 ADDR1
  * @{
  */
/**
  * @brief  Enable 10-bit address mode.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_addr_10_bit(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->ADDR1, I2C_ADDR1_ADDTYPE_MSK);
}

/**
  * @brief  Enable 7-bit address mode.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_addr_7_bit(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->ADDR1, I2C_ADDR1_ADDTYPE_MSK);
}

/**
  * @brief  Check if is enabled 10-bit address mode.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_addr_10_bit(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->ADDR1, I2C_ADDR1_ADDTYPE_MSK) == (I2C_ADDR1_ADDTYPE_MSK));
}

/**
  * @brief  Set 10-bit address mode address 9:8 bit value.
  * @param  i2c I2C Instance.
  * @param  addr: address 9:8 bit value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr_9_8_bit(I2C_TypeDef *i2c, uint32_t addr)
{
	MODIFY_REG(i2c->ADDR1, I2C_ADDR1_ADDH_MSK, (addr << I2C_ADDR1_ADDH_POSS));
}

/**
  * @brief  Get 10-bit address mode address 9:8 bit value.
  * @param  i2c I2C Instance.
  * @retval address 9:8 bit value.
  */
__STATIC_INLINE uint32_t md_i2c_get_addr_9_8_bit(I2C_TypeDef *i2c)
{
	return (READ_BITS(i2c->ADDR1, I2C_ADDR1_ADDH_MSK, I2C_ADDR1_ADDH_POSS));
}

/**
  * @brief  Set address 1:7 bit value.
  * @param  i2c I2C Instance.
  * @param  addr: address 1:7 bit value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr_1_7_bit(I2C_TypeDef *i2c, uint32_t addr)
{
	MODIFY_REG(i2c->ADDR1, I2C_ADDR1_ADD_MSK, (addr << I2C_ADDR1_ADD_POSS));
}

/**
  * @brief  Get 10-bit address mode address 1:7 bit value.
  * @param  i2c I2C Instance.
  * @retval address 1:7 bit value.
  */
__STATIC_INLINE uint32_t md_i2c_get_addr_1_7_bit(I2C_TypeDef *i2c)
{
	return (READ_BITS(i2c->ADDR1, I2C_ADDR1_ADD_MSK, I2C_ADDR1_ADD_POSS));
}

/**
  * @brief  Set 10-bit address mode address 0 bit value.
  * @param  i2c I2C Instance.
  * @param  bit: 0 bit value.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_addr_0_bit(I2C_TypeDef *i2c, uint32_t bit)
{
	MODIFY_REG(i2c->ADDR1, I2C_ADDR1_ADDLSB_MSK, (bit << I2C_ADDR1_ADDLSB_POS));
}

/**
  * @brief  Get 10-bit address mode address 0 bit value.
  * @param  i2c I2C Instance.
  * @retval address 0 bit value. 
  */
__STATIC_INLINE uint32_t md_i2c_get_addr_0_bit(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->ADDR1, I2C_ADDR1_ADDLSB_MSK) == I2C_ADDR1_ADDLSB_MSK);
}

/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group5 ADDR2
  * @{
  */
/**
  * @brief  Set the 7bits Own Address2.
  * @param  i2c I2C Instance.
  * @param  OwnAddress2 This parameter must be a value between Min_Data=0 and Max_Data=0x7F.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_own_address2(I2C_TypeDef *i2c, uint32_t OwnAddress2)
{
	MODIFY_REG(i2c->ADDR2, I2C_ADDR2_ADD_MSK, (OwnAddress2 << I2C_ADDR2_ADD_POSS));
}

/**
  * @brief  Get the 7bits Own Address2 value.
  * @param  i2c I2C Instance.
  * @retval Own Address2 value.
  */
__STATIC_INLINE uint32_t md_i2c_get_own_address2(I2C_TypeDef *i2c)
{
	return (READ_BITS(i2c->ADDR2, I2C_ADDR2_ADD_MSK, I2C_ADDR2_ADD_POSS));
}

/**
  * @brief  Enable acknowledge on Own Address2 match address.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_enable_own_address2(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->ADDR2, I2C_ADDR2_DUALEN_MSK);
}

/**
  * @brief  Disable acknowledge on Own Address2 match address.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_disable_own_address2(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->ADDR2, I2C_ADDR2_DUALEN_MSK);
}

/**
  * @brief  Check if is enable acknowledge on Own Address2 match address.
  * @param  i2c I2C Instance.
  * @retval State of bit (0 or 1).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_own_address2(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->ADDR2, I2C_ADDR2_DUALEN_MSK) == I2C_ADDR2_DUALEN_MSK);
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group6 DATA
  * @{
  */
/**
  * @brief  Read Receive Data register.
  * @param  i2c I2C Instance.
  * @retval Value between Min_Data=0x0 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t md_i2c_receive_data8(I2C_TypeDef *i2c)
{
	return (uint8_t)(READ_BIT(i2c->DATA, I2C_DATA_TRBUF_MSK));
}

/**
  * @brief  Write in Transmit Data Register .
  * @param  i2c I2C Instance.
  * @param  Data Value between Min_Data=0x0 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void md_i2c_transmit_data8(I2C_TypeDef *i2c, uint8_t Data)
{
	MODIFY_REG(i2c->DATA, I2C_DATA_TRBUF_MSK, (Data << I2C_DATA_TRBUF_POSS));
}

/**
  * @brief  Get the data register address used for DMA transfer.
  * @param  i2c I2C Instance.
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t md_i2c_dma_get_reg_addr(I2C_TypeDef *i2c)
{
	return (uint32_t) & (i2c->DATA);
}

/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group7 STAT1
  * @{
  */
/**
  * @brief  Indicate the status of SMBus alert flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_smbus_flag_alert(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_SMBALARM_MSK) == (I2C_STAT1_SMBALARM_MSK));
}
/**
  * @brief  Indicate the status of SMBus Timeout detection flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_smbus_flag_timeout(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_SMBTO_MSK) == (I2C_STAT1_SMBTO_MSK));
}

/**
  * @brief  Clear SMBus Timeout detection flag.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_smbus_flag_timeout(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->STAT1, I2C_STAT1_SMBTO_MSK);
}

/**
  * @brief  Indicate the status of SMBus PEC error flag in reception.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_smbus_flag_pecerr(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_PECERR_MSK) == (I2C_STAT1_PECERR_MSK));
}
/**
  * @brief  Clear SMBus PEC error flag.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_smbus_flag_pecerr(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->STAT1, I2C_STAT1_PECERR_MSK);
}
/**
  * @brief  Indicate the status of Overrun/Underrun flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_ovr(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_ROUERR_MSK) == (I2C_STAT1_ROUERR_MSK));
}

/**
  * @brief  Clear Overrun/Underrun flag.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_flag_ovr(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->STAT1, I2C_STAT1_ROUERR_MSK);
}

/**
  * @brief  Indicate the status of Acknowledge failure flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_af(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_ACKERR_MSK) == (I2C_STAT1_ACKERR_MSK));
}

/**
  * @brief  Clear Acknowledge failure flag.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_flag_af(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->STAT1, I2C_STAT1_ACKERR_MSK);
}

/**
  * @brief  Indicate the status of Arbitration lost flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_arlo(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_LARB_MSK) == (I2C_STAT1_LARB_MSK));
}

/**
  * @brief  Clear Arbitration lost flag.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_flag_arlo(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->STAT1, I2C_STAT1_LARB_MSK);
}
/**
  * @brief  Indicate the status of Bus error flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_berr(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_BUSERR_MSK) == (I2C_STAT1_BUSERR_MSK));
}

/**
  * @brief  Clear Bus error flag.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_clear_flag_berr(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->STAT1, I2C_STAT1_BUSERR_MSK);
}
  /**
  * @brief  Indicate the status of Transmit data register empty flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_txbe(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_TXBE_MSK) == (I2C_STAT1_TXBE_MSK));
}

/**
  * @brief  Indicate the status of Receive data register not empty flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_rxne(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_RXBNE_MSK) == (I2C_STAT1_RXBNE_MSK));
}
/**
  * @brief  Indicate the status of Stop detection flag (slave mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_stop(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_DETSTP_MSK) == (I2C_STAT1_DETSTP_MSK));
}

/**
  * @brief  Indicate the status of Start Bit (master mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_sb(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_SENDSTR_MSK) == (I2C_STAT1_SENDSTR_MSK));
}
/**
  * @brief  Indicate the status of Byte Transfer Finished flag.
  *         RESET: When Data byte transfer not done.
  *         SET: When Data byte transfer succeeded.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_btf(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_BTC_MSK) == (I2C_STAT1_BTC_MSK));
}
/**
  * @brief  Indicate the status of Address sent (master mode) or Address matched flag (slave mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_addr(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_ADDR_MSK) == (I2C_STAT1_ADDR_MSK));
}

/**
  * @brief  Indicate the status of 10-bit header sent (master mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_add10(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT1, I2C_STAT1_SENDADD10_MSK) == (I2C_STAT1_SENDADD10_MSK));
}

/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group8 STAT2
  * @{
  */
/**
  * @brief  Get the SMBus Packet Error byte calculated.
  * @param  i2c I2C Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t md_i2c_get_smbus_pec(I2C_TypeDef *i2c)
{
	return (uint32_t)(READ_BITS(i2c->STAT2, I2C_STAT2_PECV_MSK, I2C_STAT2_PECV_POSS));
}

/**
  * @brief  Indicate the status of Dual flag.
  *         SET: Received address matched with OAR2.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_dual(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT2, I2C_STAT2_DMF_MSK) == (I2C_STAT2_DMF_MSK));
}

/**
  * @brief  Indicate the status of SMBus Host address reception (Slave mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_smbus_flag_smbhost(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT2, I2C_STAT2_SMBHH_MSK) == (I2C_STAT2_SMBHH_MSK));
}

/**
  * @brief  Indicate the status of SMBus Device default address reception (Slave mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_smbus_flag_smbdefault(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT2, I2C_STAT2_SMBDEF_MSK) == (I2C_STAT2_SMBDEF_MSK));
}

/**
  * @brief  Indicate the status of General call address reception (Slave mode).
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_gencamd(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT2, I2C_STAT2_RXGCF_MSK) == (I2C_STAT2_RXGCF_MSK));
}

/**
  * @brief  Indicate the value of transfer direction.
  * @param  i2c I2C Instance.
  * @retval Returned value can be one of the following values:
  *         - 0x00: direction read	
  *         - 0x01: direction write
  */
__STATIC_INLINE uint32_t md_i2c_get_transfer_direction(I2C_TypeDef *i2c)
{
	return (uint32_t)(READ_BIT(i2c->STAT2, I2C_STAT2_TRF_MSK));
}

 /**
  * @brief  Indicate the status of Bus Busy flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_busy(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT2, I2C_STAT2_BSYF_MSK) == (I2C_STAT2_BSYF_MSK));
}
/**
  * @brief  Indicate the status of Master/Slave flag.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_active_flag_msl(I2C_TypeDef *i2c)
{
	return (READ_BIT(i2c->STAT2, I2C_STAT2_MASTER_MSK) == (I2C_STAT2_MASTER_MSK));
}
/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group9 CKCFG
  * @{
  */  
  /**
  * @brief  Set the I2C master clock speed Standard mode.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_standard_speed_mode(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CKCFG, I2C_CKCFG_CLKMOD_MSK);
}

/**
  * @brief  Set the I2C master clock speed FAST mode.
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_fast_speed_mode(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CKCFG, I2C_CKCFG_CLKMOD_MSK);
}

/**
  * @brief  Check if is enable the I2C master clock speed FAST mode.
  * @param  i2c I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_i2c_is_enable_speed_fast_mode(I2C_TypeDef *i2c)
{
	return (SET_BIT(i2c->CKCFG, I2C_CKCFG_CLKMOD_MSK) == I2C_CKCFG_CLKMOD_MSK);
}

/**
  * @brief  Configure the Duty cycle 16/9(Fast mode only).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_duty_cycle_16_9(I2C_TypeDef *i2c)
{
	SET_BIT(i2c->CKCFG, I2C_CKCFG_DUTY_MSK);
}

/**
  * @brief  Configure the Duty cycle (Fast mode only).
  * @param  i2c I2C Instance.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_duty_cycle_2(I2C_TypeDef *i2c)
{
	CLEAR_BIT(i2c->CKCFG, I2C_CKCFG_DUTY_MSK);
}

/**
  * @brief  Get the Duty cycle (Fast mode only).
  * @param  i2c I2C Instance.
  */
__STATIC_INLINE uint32_t md_i2c_get_duty_cycle(I2C_TypeDef *i2c)
{
	return (uint32_t)(READ_BIT(i2c->CKCFG, I2C_CKCFG_DUTY_MSK) == I2C_CKCFG_DUTY_MSK);
}

  /**
  * @brief  Configure the SCL high and low period.
  * @param  i2c I2C Instance.
  * @param  ClockPeriod This parameter must be a value between Min_Data=0x004 and Max_Data=0xFFF, except in FAST DUTY mode where Min_Data=0x001.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_clock_period(I2C_TypeDef *i2c, uint32_t ClockPeriod)
{
	MODIFY_REG(i2c->CKCFG, I2C_CKCFG_CLKSET_MSK, (ClockPeriod << I2C_CKCFG_CLKSET_POSS));
}

/**
  * @brief  Get the SCL high and low period.
  * @param  i2c I2C Instance.
  * @retval Value between Min_Data=0x004 and Max_Data=0xFFF, except in FAST DUTY mode where Min_Data=0x001.
  */
__STATIC_INLINE uint32_t md_i2c_get_clock_period(I2C_TypeDef *i2c)
{
	return (uint32_t)(READ_BITS(i2c->CKCFG, I2C_CKCFG_CLKSET_MSK, I2C_CKCFG_CLKSET_POSS));
}

/**
  * @}
  */
/** @defgroup MD_I2C_Public_Functions_Group10 RT
  * @{
  */  

/**
  * @brief  Configure the SCL, SDA rising time.
  * @param  i2c I2C Instance.
  * @param  RiseTime This parameter must be a value between Min_Data=0x02 and Max_Data=0x3F.
  * @retval None
  */
__STATIC_INLINE void md_i2c_set_rise_time(I2C_TypeDef *i2c, uint32_t RiseTime)
{
	MODIFY_REG(i2c->RT, I2C_RT_RISET_MSK, (RiseTime << I2C_RT_RISET_POSS));
}

/**
  * @brief  Get the SCL, SDA rising time.
  * @param  i2c I2C Instance.
  * @retval Value between Min_Data=0x02 and Max_Data=0x3F
  */
__STATIC_INLINE uint32_t md_i2c_get_rise_time(I2C_TypeDef *i2c)
{
	return (uint32_t)(READ_BITS(i2c->RT, I2C_RT_RISET_MSK, I2C_RT_RISET_POSS));
}
/**
  * @}
  */

/** @defgroup MD_I2C_Public_Functions_Group1 Initialization
  * @{
  */
extern md_status_t md_i2c_init(I2C_TypeDef *I2Cx, md_i2c_init_t *hperh);
extern void md_i2c_struct_init(md_i2c_init_t *init);

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

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
