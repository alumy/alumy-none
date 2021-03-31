/**
  *********************************************************************************
  *
  * @file    md_crypt.h
  * @brief   Header file of CRYPT module driver.
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


#ifndef __MD_CRYPT_H__
#define __MD_CRYPT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */
/** @defgroup MD_CRYPT CRYPT
  * @brief CRYPT micro driver
  * @{
  */
/**
  * @defgroup MD_CRYPT_Public_Macros CRYPT Public Macros
  * @{
  */
/**
  * @brief CRYPT keys of tdes
  */
typedef enum {
	MD_CRYPT_TDES_KEY_2 = 0x0U,	/**< 2 key for des */
	MD_CRYPT_TDES_KEY_3 = 0x800U,	/**< 3 key for des */
} md_crypt_tdes_key_t;

/**
  * @brief CRYPT FIFO order
  */
typedef enum {
	MD_CRYPT_FIFO_ORDER_0 = 0x0U,		/**< Byte0 is first */
	MD_CRYPT_FIFO_ORDER_3 = 0x2000U,	/**< Byte3 is first */
} md_crypt_fifo_order_t;

/**
  * @brief CRYPT data type
  */
typedef enum {
	MD_CRYPT_TYPE_32 = 0x0U,	/**< 32-bits */
	MD_CRYPT_TYPE_16 = 0x100U,	/**< 16-bits */
	MD_CRYPT_TYPE_8  = 0x200U,	/**< 8-bits */
	MD_CRYPT_TYPE_1  = 0x300U,	/**< 1-bits */
} md_crypt_type_t;

/**
  * @brief CRYPT mode
  */
typedef enum {
	MD_CRYPT_MODE_ECB = 0x0U,	/**< Mode ECB */
	MD_CRYPT_MODE_CBC = 0x10U,	/**< Mode CBC */
	MD_CRYPT_MODE_CTR = 0x20U,	/**< Mode CTR */
	MD_CRYPT_MODE_GCM = 0x30U,	/**< Mode GCM */
} md_crypt_mode_t;

/**
  * @brief CRYPT direction choose
  */
typedef enum {
	MD_CRYPT_SEL_DECRYPT = 0x0U,	/**< Decrypt */
	MD_CRYPT_SEL_ENCRYPT = 0x2U,	/**< Encrypt */
} md_crypt_sel_t;
/**
  * @}
  */

/** @defgroup MD_CRYPT_Pubulic_Types CRYPT Pubulic Types
  * @{
  */
/**
  * @brief CRYPT init structure definition
  */
typedef struct {
	uint32_t mode;	/**< CRYPT mode */
	uint32_t type;	/**< Data type select */
	uint32_t order;	/**< FIFO orders */
	uint32_t encs;	/**< Encrypt or Decrypt*/
} md_crypt_init_t;
/**
  * @}
  */

/** @defgroup MD_CRYPT_Public_Functions CRYPT Public Functions
  * @{
  */
/** @defgroup MD_CRYPT_Public_Functions_Group2 DATA0
  * @{
  */
/**
  * @brief  set DATA0
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data0(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
	WRITE_REG(CRYPTx->DATA[0], data);
}

/**
  * @brief  Get DATA0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data0
  */
__STATIC_INLINE uint32_t md_crypt_get_data0(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->DATA[0]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group3 DATA1
  * @{
  */
/**
  * @brief  set DATA1
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data1(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
	WRITE_REG(CRYPTx->DATA[1], data);
}

/**
  * @brief  Get DATA1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data1
  */
__STATIC_INLINE uint32_t md_crypt_get_data1(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->DATA[1]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group4 DATA2
  * @{
  */
/**
  * @brief  set DATA2
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data2(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
	WRITE_REG(CRYPTx->DATA[2], data);
}

/**
  * @brief  Get DATA2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data2
  */
__STATIC_INLINE uint32_t md_crypt_get_data2(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->DATA[2]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group5 DATA3
  * @{
  */
/**
  * @brief  set DATA3
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data3(CRYPT_TypeDef *CRYPTx, uint32_t data)
{
	WRITE_REG(CRYPTx->DATA[3], data);
}

/**
  * @brief  Get DATA3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval data3
  */
__STATIC_INLINE uint32_t md_crypt_get_data3(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->DATA[3]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group6 KEY0
  * @{
  */
/**
  * @brief  set KEY0
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key0(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
	WRITE_REG(CRYPTx->KEY[0], key);
}

/**
  * @brief  Get KEY0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key0
  */
__STATIC_INLINE uint32_t md_crypt_get_key0(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->KEY[0]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group7 KEY1
  * @{
  */
/**
  * @brief  set KEY1
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key1(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
	WRITE_REG(CRYPTx->KEY[1], key);
}

/**
  * @brief  Get KEY1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key1
  */
__STATIC_INLINE uint32_t md_crypt_get_key1(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->KEY[1]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group8 KEY2
  * @{
  */
/**
  * @brief  set KEY2
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key2(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
	WRITE_REG(CRYPTx->KEY[2], key);
}

/**
  * @brief  Get KEY2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key2
  */
__STATIC_INLINE uint32_t md_crypt_get_key2(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->KEY[2]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group9 KEY3
  * @{
  */
/**
  * @brief  set KEY3
  * @param  CRYPTx: CRYPT Peripheral
  * @param  key: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_key3(CRYPT_TypeDef *CRYPTx, uint32_t key)
{
	WRITE_REG(CRYPTx->KEY[3], key);
}

/**
  * @brief  Get KEY3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval key3
  */
__STATIC_INLINE uint32_t md_crypt_get_key3(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->KEY[3]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group10 IV0
  * @{
  */
/**
  * @brief  set IV0
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv0(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
	WRITE_REG(CRYPTx->IV[0], iv);
}

/**
  * @brief  Get IV0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv0
  */
__STATIC_INLINE uint32_t md_crypt_get_iv0(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->IV[0]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group11 IV1
  * @{
  */
/**
  * @brief  set IV1
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv1(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
	WRITE_REG(CRYPTx->IV[1], iv);
}

/**
  * @brief  Get IV1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv1
  */
__STATIC_INLINE uint32_t md_crypt_get_iv1(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->IV[1]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group12 IV2
  * @{
  */
/**
  * @brief  set IV2
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv2(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
	WRITE_REG(CRYPTx->IV[2], iv);
}

/**
  * @brief  Get IV2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv2
  */
__STATIC_INLINE uint32_t md_crypt_get_iv2(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->IV[2]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group13 IV3
  * @{
  */
/**
  * @brief  set IV3
  * @param  CRYPTx: CRYPT Peripheral
  * @param  iv: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_iv3(CRYPT_TypeDef *CRYPTx, uint32_t iv)
{
	WRITE_REG(CRYPTx->IV[3], iv);
}

/**
  * @brief  Get IV3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval iv3
  */
__STATIC_INLINE uint32_t md_crypt_get_iv3(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->IV[3]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group14 RES0
  * @{
  */
/**
  * @brief  Get RESULT0
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result0
  */
__STATIC_INLINE uint32_t md_crypt_get_result0(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->RES[0]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group15 RES1
  * @{
  */
/**
  * @brief  Get RESULT1
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result1
  */
__STATIC_INLINE uint32_t md_crypt_get_result1(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->RES[1]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group16 RES2
  * @{
  */
/**
  * @brief  Get RESULT2
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result2
  */
__STATIC_INLINE uint32_t md_crypt_get_result2(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->RES[2]);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group17 RES3
  * @{
  */
/**
  * @brief  Get RESULT3
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Result3
  */
__STATIC_INLINE uint32_t md_crypt_get_result3(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->RES[3]);
}
 /**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group18 CON
  * @{
  */
/**
  * @brief  start CRYPT 
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_go(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_GO_MSK);
}

/**
  * @brief  select the action of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  encs This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_SEL_ENCRYPT
  *         @arg @ref MD_CRYPT_SEL_DECRYPT
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_encs(CRYPT_TypeDef *CRYPTx, uint32_t encs)
{
	MODIFY_REG(CRYPTx->CON, CRYPT_CON_ENCS_MSK, encs);
}

/**
  * @brief  Retrieve the checksum byte order of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_SEL_ENCRYPT
  *         @arg @ref MD_CRYPT_SEL_DECRYPT
  */
__STATIC_INLINE uint32_t md_crypt_get_encs(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_ENCS_MSK));
}

/**
  * @brief  set the mode of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  mode: This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_MODE_ECB
  *         @arg @ref MD_CRYPT_MODE_CBC
  *         @arg @ref MD_CRYPT_MODE_CTR
  *         @arg @ref MD_CRYPT_MODE_GCM
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_mode(CRYPT_TypeDef *CRYPTx, uint32_t mode)
{
	MODIFY_REG(CRYPTx->CON, CRYPT_CON_MODE_MSK, mode);
}

/**
  * @brief  Retrieve the key bits of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_MODE_ECB
  *         @arg @ref MD_CRYPT_MODE_CBC
  *         @arg @ref MD_CRYPT_MODE_CTR
  *         @arg @ref MD_CRYPT_MODE_GCM
  */
__STATIC_INLINE uint32_t md_crypt_get_mode(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_MODE_MSK));
}

/**
  * @brief  CRYPT IV Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_iv(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_IVEN_MSK);
}

/**
  * @brief  CRYPT IV Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_iv(CRYPT_TypeDef *CRYPTx)
{
	CLEAR_BIT(CRYPTx->CON, CRYPT_CON_IVEN_MSK);
}

/**
  * @brief  Indicate if CRYPT IV is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_iv(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_IVEN_MSK) == (CRYPT_CON_IVEN_MSK));
}

/**
  * @brief  CRYPT interrupt Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_interrupt(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_IE_MSK);
}

/**
  * @brief  CRYPT interrupt Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_interrupt(CRYPT_TypeDef *CRYPTx)
{
	CLEAR_BIT(CRYPTx->CON, CRYPT_CON_IE_MSK);
}

/**
  * @brief  Indicate if CRYPT interrupt is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_interrupt(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_IE_MSK) == (CRYPT_CON_IE_MSK));
}

/**
  * @brief  set the data type of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  data_type: This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_TYPE_32
  *         @arg @ref MD_CRYPT_TYPE_16
  *         @arg @ref MD_CRYPT_TYPE_8
  *         @arg @ref MD_CRYPT_TYPE_1
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_data_type(CRYPT_TypeDef *CRYPTx, uint32_t data_type)
{
	MODIFY_REG(CRYPTx->CON, CRYPT_CON_TYPE_MSK, data_type);
}

/**
  * @brief  Retrieve the key bits of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_TYPE_32
  *         @arg @ref MD_CRYPT_TYPE_16
  *         @arg @ref MD_CRYPT_TYPE_8
  *         @arg @ref MD_CRYPT_TYPE_1
  */
__STATIC_INLINE uint32_t md_crypt_get_data_type(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_TYPE_MSK));
}

/**
  * @brief  CRYPT TDES Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_tdes(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_TDES_MSK);
}

/**
  * @brief  CRYPT interrupt Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_tdes(CRYPT_TypeDef *CRYPTx)
{
	CLEAR_BIT(CRYPTx->CON, CRYPT_CON_TDES_MSK);
}

/**
  * @brief  Indicate if CRYPT tdes is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_tdes(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_TDES_MSK) == (CRYPT_CON_TDES_MSK));
}

/**
  * @brief  select the keys of TDES
  * @param  CRYPTx: CRYPT Peripheral
  * @param  tdes_key: This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_TDES_KEY_2
  *         @arg @ref MD_CRYPT_TDES_KEY_3
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_tdes_key(CRYPT_TypeDef *CRYPTx, uint32_t tdes_key)
{
	MODIFY_REG(CRYPTx->CON, CRYPT_CON_DESKS_MSK, tdes_key);
}

/**
  * @brief  Retrieve the keys of TDES
  * @param  CRYPTx: CRYPT Peripheral
  * @retval  Returned value can be one of the following values:
  *         @arg @ref MD_CRYPT_TDES_KEY_2
  *         @arg @ref MD_CRYPT_TDES_KEY_3
  */
__STATIC_INLINE uint32_t md_crypt_get_tdes_key(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_DESKS_MSK));
}

/**
  * @brief  CRYPT FIFO Enable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_fifo(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_FIFOEN_MSK);
}

/**
  * @brief  CRYPT FIFO Disable
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_fifo(CRYPT_TypeDef *CRYPTx)
{
	CLEAR_BIT(CRYPTx->CON, CRYPT_CON_FIFOEN_MSK);
}

/**
  * @brief  Indicate if CRYPT FIFO is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_fifo(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_FIFOEN_MSK) == (CRYPT_CON_FIFOEN_MSK));
}

/**
  * @brief  select the FIFO order of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  fifo_order This parameter can be one of the following values:
  *         @arg @ref MD_CRYPT_FIFO_ORDER_0
  *         @arg @ref MD_CRYPT_FIFO_ORDER_3
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_fifo_order(CRYPT_TypeDef *CRYPTx, uint32_t fifo_order)
{
	MODIFY_REG(CRYPTx->CON, CRYPT_CON_FIFOODR_MSK, fifo_order);
}

/**
  * @brief  the FIFO order of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_crypt_get_fifo_order(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_FIFOODR_MSK));
}

/**
  * @brief  CRYPT DMA Enable request
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_enable_dma_req(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_DMAEN_MSK);
}

/**
  * @brief  CRYPT DMA Disable request
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_disable_dma_req(CRYPT_TypeDef *CRYPTx)
{
	CLEAR_BIT(CRYPTx->CON, CRYPT_CON_DMAEN_MSK);
}

/**
  * @brief  Indicate if CRYPT DMA request is enabled
  * @param  CRYPTx: CRYPT Peripheral
  * @retval State.
  */
__STATIC_INLINE uint32_t md_crypt_is_enabled_dma_req(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->CON, CRYPT_CON_DMAEN_MSK) == (CRYPT_CON_DMAEN_MSK));
}

/**
  * @brief  clear result of CRYPT 
  * @param  CRYPTx: CRYPT Peripheral
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_clear_result(CRYPT_TypeDef *CRYPTx)
{
	SET_BIT(CRYPTx->CON, CRYPT_CON_RESCLR_MSK);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group19 IF
  * @{
  */
/**
  * @brief  Get the AES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_aes(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->IF, CRYPT_IF_AESIF_MSK) == CRYPT_IF_AESIF_MSK);
}

/**
  * @brief  Get the DES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_des(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->IF, CRYPT_IF_DESIF_MSK) == CRYPT_IF_DESIF_MSK);
}

/**
  * @brief  Get the MULTH interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_multh(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->IF, CRYPT_IF_MULTHIF_MSK) == CRYPT_IF_MULTHIF_MSK);
}

/**
  * @brief  Get the Finish flag
  * @param  CRYPTx: CRYPT Peripheral
  * @retval Status.
  */
__STATIC_INLINE uint32_t md_crypt_get_flag_done(CRYPT_TypeDef *CRYPTx)
{
	return (READ_BIT(CRYPTx->IF, CRYPT_IF_DONE_MSK) == CRYPT_IF_DONE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group20 IFC
  * @{
  */
/**
  * @brief  Clear the AES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_aes(CRYPT_TypeDef *CRYPTx)
{
	WRITE_REG(CRYPTx->IFC, CRYPT_IFC_AESIFC_MSK);
}

/**
  * @brief  Clear the DES interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_des(CRYPT_TypeDef *CRYPTx)
{
	WRITE_REG(CRYPTx->IFC, CRYPT_IFC_DESIFC_MSK);
}

/**
  * @brief  Clear the MULTH interrupt flag
  * @param  CRYPTx: CRYPT Peripheral
  */
__STATIC_INLINE void md_crypt_clear_flag_multh(CRYPT_TypeDef *CRYPTx)
{
	WRITE_REG(CRYPTx->IFC, CRYPT_IFC_MULTHIFC_MSK);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group21 FIFO
  * @{
  */
/**
  * @brief  set FIFO data of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @param  fifo_data: This parameter can be 0~0xFFFFFFFF
  * @retval NONE
  */
__STATIC_INLINE void md_crypt_set_fifo_data(CRYPT_TypeDef *CRYPTx, uint32_t fifo_data)
{
	WRITE_REG(CRYPTx->FIFO, fifo_data);
}

/**
  * @brief  Get the FIFO data of CRYPT
  * @param  CRYPTx: CRYPT Peripheral
  * @retval FIFO data
  */
__STATIC_INLINE uint32_t md_crypt_get_fifo_data(CRYPT_TypeDef *CRYPTx)
{
	return READ_REG(CRYPTx->FIFO);
}
/**
  * @}
  */
/** @defgroup MD_CRYPT_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_crypt_reset(void);
extern void md_crypt_init(md_crypt_init_t *init);
extern void md_crypt_init_struct(md_crypt_init_t *init);

extern md_status_t md_crypt_encrypt(md_crypt_init_t *hperh, uint8_t *plain_text, uint8_t *cipher_text, uint32_t size);
extern md_status_t md_crypt_decrypt(md_crypt_init_t *hperh, uint8_t *cipher_text, uint8_t *plain_text, uint32_t size);
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
