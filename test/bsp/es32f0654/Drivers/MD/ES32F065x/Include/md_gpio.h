/**
  *********************************************************************************
  *
  * @file    md_gpio.h
  * @brief   Header file of GPIO module driver.
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


#ifndef __MD_GPIO_H__
#define __MD_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_GPIO GPIO
  * @brief GPIO micro driver
  * @{
  */

/**
  * @defgroup MD_GPIO_Public_Macros GPIO Public Macros
  * @{
  */
#define MD_GPIO_PIN_0	0x0001U
#define MD_GPIO_PIN_1	0x0002U
#define MD_GPIO_PIN_2	0x0004U
#define MD_GPIO_PIN_3	0x0008U
#define MD_GPIO_PIN_4	0x0010U
#define MD_GPIO_PIN_5	0x0020U
#define MD_GPIO_PIN_6	0x0040U
#define MD_GPIO_PIN_7	0x0080U
#define MD_GPIO_PIN_8	0x0100U
#define MD_GPIO_PIN_9	0x0200U
#define MD_GPIO_PIN_10	0x0400U
#define MD_GPIO_PIN_11	0x0800U
#define MD_GPIO_PIN_12	0x1000U
#define MD_GPIO_PIN_13	0x2000U
#define MD_GPIO_PIN_14	0x4000U
#define MD_GPIO_PIN_15	0x8000U

/* Toggle IO */
#define MD_GPIOA_TOGGLE_PIN(x)  (GPIOA->BIR = (x))
#define MD_GPIOB_TOGGLE_PIN(x)  (GPIOB->BIR = (x))
#define MD_GPIOC_TOGGLE_PIN(x)  (GPIOC->BIR = (x))
#define MD_GPIOD_TOGGLE_PIN(x)  (GPIOD->BIR = (x))
#define MD_GPIOE_TOGGLE_PIN(x)  (GPIOE->BIR = (x))
#define MD_GPIOF_TOGGLE_PIN(x)  (GPIOF->BIR = (x))
#define MD_GPIOG_TOGGLE_PIN(x)  (GPIOG->BIR = (x))
#define MD_GPIOH_TOGGLE_PIN(x)  (GPIOH->BIR = (x))

/* Read IO level */
#define MD_GPIOA_READ_PIN(x)  ((GPIOA->DIN & (x)) ? 1 : 0)
#define MD_GPIOB_READ_PIN(x)  ((GPIOB->DIN & (x)) ? 1 : 0)
#define MD_GPIOC_READ_PIN(x)  ((GPIOC->DIN & (x)) ? 1 : 0)
#define MD_GPIOD_READ_PIN(x)  ((GPIOD->DIN & (x)) ? 1 : 0)
#define MD_GPIOE_READ_PIN(x)  ((GPIOE->DIN & (x)) ? 1 : 0)
#define MD_GPIOF_READ_PIN(x)  ((GPIOF->DIN & (x)) ? 1 : 0)
#define MD_GPIOG_READ_PIN(x)  ((GPIOG->DIN & (x)) ? 1 : 0)
#define MD_GPIOH_READ_PIN(x)  ((GPIOH->DIN & (x)) ? 1 : 0)

/* Set IO as hight */
#define MD_GPIOA_SET_PIN(x)  (GPIOA->BSRR = (x))
#define MD_GPIOB_SET_PIN(x)  (GPIOB->BSRR = (x))
#define MD_GPIOC_SET_PIN(x)  (GPIOC->BSRR = (x))
#define MD_GPIOD_SET_PIN(x)  (GPIOD->BSRR = (x))
#define MD_GPIOE_SET_PIN(x)  (GPIOE->BSRR = (x))
#define MD_GPIOF_SET_PIN(x)  (GPIOF->BSRR = (x))
#define MD_GPIOG_SET_PIN(x)  (GPIOG->BSRR = (x))
#define MD_GPIOH_SET_PIN(x)  (GPIOH->BSRR = (x))

/* Set IO as low */
#define MD_GPIOA_RESET_PIN(x)  (GPIOA->BSRR = ((x) << 16))
#define MD_GPIOB_RESET_PIN(x)  (GPIOB->BSRR = ((x) << 16))
#define MD_GPIOC_RESET_PIN(x)  (GPIOC->BSRR = ((x) << 16))
#define MD_GPIOD_RESET_PIN(x)  (GPIOD->BSRR = ((x) << 16))
#define MD_GPIOE_RESET_PIN(x)  (GPIOE->BSRR = ((x) << 16))
#define MD_GPIOF_RESET_PIN(x)  (GPIOF->BSRR = ((x) << 16))
#define MD_GPIOG_RESET_PIN(x)  (GPIOG->BSRR = ((x) << 16))
#define MD_GPIOH_RESET_PIN(x)  (GPIOH->BSRR = ((x) << 16))

#define MD_GPIO_PIN_MUL(pin)		((pin) * (pin))
#define MD_GPIO_PIN_TWO_0_MSK(pin)	(MD_GPIO_PIN_MUL(pin))
#define MD_GPIO_PIN_TWO_1_MSK(pin)	(MD_GPIO_PIN_MUL(pin) << 1)
#define MD_GPIO_PIN_TWO_MSK(pin)	((MD_GPIO_PIN_TWO_0_MSK(pin)) | (MD_GPIO_PIN_TWO_1_MSK(pin)))
/**
  * @}
  */
/**
  * @defgroup MD_GPIO_Public_Types GPIO Public Types
  * @{
  */

/**
  * @brief GPIO mode
  */
typedef enum {
	MD_GPIO_MODE_CLOSE  = 0x0U,	/**< Digital close  Analog open */
	MD_GPIO_MODE_INPUT  = 0x1U,	/**< Input */
	MD_GPIO_MODE_OUTPUT = 0x2U,	/**< Output */
} md_gpio_mode_t;

/**
  * @brief GPIO open-drain or push-pull
  */
typedef enum {
	MD_GPIO_PUSH_PULL   = 0x0U,	/**< Push-Pull */
	MD_GPIO_OPEN_DRAIN  = 0x2U,	/**< Open-Drain. Can't output high level */
	MD_GPIO_OPEN_SOURCE = 0x3U,	/**< Open-Source. Can't output low level */
} md_gpio_odos_t;

/**
  * @brief GPIO push-up or push-down
  */
typedef enum {
	MD_GPIO_FLOATING     = 0x0U,	/**< Floating */
	MD_GPIO_PUSH_UP      = 0x1U,	/**< Push-Up */
	MD_GPIO_PUSH_DOWN    = 0x2U,	/**< Push-Down */
	MD_GPIO_PUSH_UP_DOWN = 0x3U,	/**< Push-Up and Push-Down */
} md_gpio_push_t;

/**
  * @brief GPIO output drive
  */
typedef enum {
	MD_GPIO_OUT_DRIVE_NORMAL = 0x0U,	/**< Normal current flow */
	MD_GPIO_OUT_DRIVE_STRONG = 0x1U,	/**< Strong current flow */
} md_gpio_out_drive_t;

/**
  * @brief GPIO filter
  */
typedef enum {
	MD_GPIO_FILTER_DISABLE = 0x0U,	/**< Disable filter */
	MD_GPIO_FILTER_ENABLE  = 0x1U,	/**< Enable filter */
} md_gpio_filter_t;

/**
  * @brief GPIO type
  */
typedef enum {
	MD_GPIO_TYPE_CMOS = 0x0U,	/**< CMOS Type */
	MD_GPIO_TYPE_TTL  = 0x1U,	/**< TTL Type */
} md_gpio_type_t;

/**
  * @brief GPIO functions
  */
typedef enum {
	MD_GPIO_FUNC_0 = 0U,	/**< function #0 */
	MD_GPIO_FUNC_1 = 1U,	/**< function #1 */
	MD_GPIO_FUNC_2 = 2U,	/**< function #2 */
	MD_GPIO_FUNC_3 = 3U,	/**< function #3 */
	MD_GPIO_FUNC_4 = 4U,	/**< function #4 */
	MD_GPIO_FUNC_5 = 5U,	/**< function #5 */
	MD_GPIO_FUNC_6 = 6U,	/**< function #6 */
	MD_GPIO_FUNC_7 = 7U,	/**< function #7 */
} md_gpio_func_t;


/**
  * @brief GPIO Init Structure definition
  */
typedef struct {
	md_gpio_mode_t mode;	/**< Specifies the operating mode for the selected pins.
				     This parameter can be any value of @ref md_gpio_mode_t */
	md_gpio_odos_t odos;	/**< Specifies the Open-Drain or Push-Pull for the selected pins.
				     This parameter can be a value of @ref md_gpio_odos_t */
	md_gpio_push_t pupd;	/**< Specifies the Pull-up or Pull-Down for the selected pins.
				     This parameter can be a value of @ref md_gpio_push_t */
	md_gpio_out_drive_t odrv;	/**< Specifies the output driver for the selected pins.
				     This parameter can be a value of @ref md_gpio_out_drive_t */
	md_gpio_filter_t flt;	/**< Specifies the input filter for the selected pins.
				     This parameter can be a value of @ref md_gpio_filter_t */
	md_gpio_type_t type;	/**< Specifies the type for the selected pins.
				     This parameter can be a value of @ref md_gpio_type_t */
	md_gpio_func_t func;	/**< Specifies the function for the selected pins.
				     This parameter can be a value of @ref md_gpio_func_t */
} md_gpio_init_t;

/**
  * @}
  */

/** @defgroup MD_GPIO_Public_Functions GPIO Public Functions
  * @{
  */
/** @defgroup MD_GPIO_Public_Functions_Group2 DIN
  * @{
  */
/**
  * @brief  Gets data of the pin when it's mode is input.
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Input data:
  *         - 0: Low level
  *         - 1: High level
  */
__STATIC_INLINE uint8_t md_gpio_get_input_data(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	return (READ_BIT(GPIOx->DIN, pin) == pin);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group3 DOUT
  * @{
  */
/**
  * @brief  Output high level
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_high(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->DOUT, pin);
}

/**
  * @brief  Output low level
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_low(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->DOUT, pin);
}

/**
  * @brief  Gets output level
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Output level:
  *         - 0: Low level
  *         - 1: High level
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_output_level(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	return (READ_BIT(GPIOx->DOUT, pin) == pin);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group4 BSRR
  * @{
  */
/**
  * @brief  Set GPIO Port
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_port_pin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->BSRR, pin);
}

/**
  * @brief  Reset GPIO Port
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_reset_port_pin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->BSRR, (pin << 16));
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group5 BIR
  * @{
  */
/**
  * @brief  Toggle output level
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_toggle_pin_output(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->BIR, pin);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group6 MODE
  * @{
  */
/**
  * @brief  Sets input mode of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_mode_input(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->MODE, MD_GPIO_PIN_TWO_1_MSK(pin));
	SET_BIT(GPIOx->MODE, MD_GPIO_PIN_TWO_0_MSK(pin));
}

/**
  * @brief  Sets output mode of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_mode_output(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->MODE, MD_GPIO_PIN_TWO_1_MSK(pin));
}

/**
  * @brief  Gets input/output mode of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Input/output mode, see @ref md_gpio_mode_t
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_mode(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if (READ_BIT(GPIOx->MODE, MD_GPIO_PIN_TWO_1_MSK(pin)))
		return MD_GPIO_MODE_OUTPUT;
	if (READ_BIT(GPIOx->MODE, MD_GPIO_PIN_TWO_0_MSK(pin)))
		return MD_GPIO_MODE_INPUT;

	return MD_GPIO_MODE_CLOSE;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group7 ODOS
  * @{
  */
/**
  * @brief  Sets Push-Pull of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_push_pull(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->ODOS, MD_GPIO_PIN_TWO_1_MSK(pin));
}

/**
  * @brief  Sets Open-Drain of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_open_drain(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->ODOS, MD_GPIO_PIN_TWO_1_MSK(pin));
	CLEAR_BIT(GPIOx->ODOS, MD_GPIO_PIN_TWO_0_MSK(pin));
}

/**
  * @brief  Sets Open-Source of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_open_source(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->ODOS, MD_GPIO_PIN_TWO_MSK(pin));
}

/**
  * @brief  Gets ODOS status of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ODOS status, see @ref md_gpio_odos_t
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_odos(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if (!(READ_BIT(GPIOx->ODOS, MD_GPIO_PIN_TWO_1_MSK(pin))))
		return MD_GPIO_PUSH_PULL;
	if (READ_BIT(GPIOx->ODOS, MD_GPIO_PIN_TWO_0_MSK(pin)))
		return MD_GPIO_OPEN_SOURCE;

	return MD_GPIO_OPEN_DRAIN;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group8 PUPD
  * @{
  */
/**
  * @brief  Sets Floating of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_floating(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_MSK(pin));
}

/**
  * @brief  Sets Push-Up of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_push_up(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_0_MSK(pin));
	CLEAR_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_1_MSK(pin));
}

/**
  * @brief  Sets Push-Down of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_push_down(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_1_MSK(pin));
	CLEAR_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_0_MSK(pin));
}

/**
  * @brief  Sets Push-Up and Push-Down of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_push_up_down(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_MSK(pin));
}

/**
  * @brief  Gets PUPD status of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval PUPD status, see @ref md_gpio_push_t
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_pupd(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if ((!(READ_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_1_MSK(pin))))
				&& (!(READ_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_0_MSK(pin)))))
		return MD_GPIO_FLOATING;
	if ((!(READ_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_1_MSK(pin))))
				&& (READ_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_0_MSK(pin))))
		return MD_GPIO_PUSH_UP;
	if ((READ_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_1_MSK(pin)))
				&& (!(READ_BIT(GPIOx->PUPD, MD_GPIO_PIN_TWO_0_MSK(pin)))))
		return MD_GPIO_PUSH_DOWN;

	return MD_GPIO_PUSH_UP_DOWN;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group9 ODRV
  * @{
  */
/**
  * @brief  Sets Normal-Drive of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_drive_normal(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_MSK(pin));
}

/**
  * @brief  Sets Strong-Drive of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_drive_strong(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_1_MSK(pin));
	SET_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_0_MSK(pin));
}

/**
  * @brief  Gets ODRV status of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ODRV status, see @ref md_gpio_out_drive_t
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_odrv(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if ((!(READ_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_1_MSK(pin))))
				&& (!(READ_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_0_MSK(pin)))))
		return MD_GPIO_OUT_DRIVE_NORMAL;
	if ((!(READ_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_1_MSK(pin))))
				&& (READ_BIT(GPIOx->ODRV, MD_GPIO_PIN_TWO_0_MSK(pin))))
		return MD_GPIO_OUT_DRIVE_STRONG;

	return MD_GPIO_OUT_DRIVE_NORMAL;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group10 FLT
  * @{
  */
/**
  * @brief  Enable filter
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_enable_pin_filter(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->FLT, pin);
}

/**
  * @brief  Disable filter
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_disable_pin_filter(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->FLT, pin);
}

/**
  * @brief  Check if the filter is enabled
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ENABLE/DISABLE
  */
__STATIC_INLINE uint8_t md_gpio_is_enabled_pin_filter(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if (READ_BIT(GPIOx->FLT, pin) == pin)
		return ENABLE;
	return DISABLE;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group11 TYPE
  * @{
  */
/**
  * @brief  Sets CMOS type
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_type_cmos(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	CLEAR_BIT(GPIOx->TYPE, pin);
}

/**
  * @brief  Sets TTL type
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_type_ttl(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	SET_BIT(GPIOx->TYPE, pin);
}

/**
  * @brief  Gets type of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ODRV status, see @ref md_gpio_type_t
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_type(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if (READ_BIT(GPIOx->TYPE, pin) == pin)
		return MD_GPIO_TYPE_TTL;
	return MD_GPIO_TYPE_CMOS;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group12 FUNC
  * @{
  */
/**
  * @brief  Sets function of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  func: Function of the pin, see @ref md_gpio_func_t.
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_function(GPIO_TypeDef *GPIOx, uint32_t pin, md_gpio_func_t func)
{
	uint32_t i, pos, mask, tmp;

	for (i = 0; i < 16; ++i) {
		if (((pin >> i) & 0x1) == 1)
			break;
	}

	if (i == 16)
		return;

	pos  = i < 8 ? (i << 2) : ((i - 8) << 2);
	mask = 0xF << pos;
	tmp  = i < 8 ? READ_REG(GPIOx->FUNC0) : READ_REG(GPIOx->FUNC1);
	tmp &= ~mask;
	tmp |= (func << pos);
	i < 8 ? WRITE_REG(GPIOx->FUNC0, tmp) : WRITE_REG(GPIOx->FUNC1, tmp);
}

/**
  * @brief  Gets Function of the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Function, see @ref md_gpio_func_t
  */
__STATIC_INLINE uint8_t md_gpio_get_pin_function(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	uint32_t i, pos, mask;

	for (i = 0; i < 16; ++i) {
		if (((pin >> i) & 0x1) == 1)
			break;
	}

	pos  = i < 8 ? (i << 2) : ((i - 8) << 2);
	pos  = pos > 28 ? 28 : pos;
	mask = 0xF << pos;

	if (i < 8)
		return READ_BITS(GPIOx->FUNC0, mask, pos);
	else
		return READ_BITS(GPIOx->FUNC1, mask, pos);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group13 LOCK
  * @{
  */
/**
  * @brief  Lock the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_lock_pin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	MODIFY_REG(GPIOx->LOCK, GPIO_LOCK_KEY_MSK, 0x55AA << GPIO_LOCK_KEY_POSS);
	SET_BIT(GPIOx->LOCK, pin);
}

/**
  * @brief  Gets Lock status the pin
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Lock status:
  *         - 0: Unlock
  *         - 1: Lock
  */
__STATIC_INLINE uint8_t md_gpio_get_lock(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	if (READ_BIT(GPIOx->LOCK, pin) == pin)
		return 1;
	return 0;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group14 EXTIRER
  * @{
  */
/**
  * @brief  Enable trigger rising edge
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_enable_riging_edge_trigger(uint32_t pin)
{
	SET_BIT(EXTI->EXTIRER, pin);
}

/**
  * @brief  Disable trigger rising edge
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_disable_riging_edge_trigger(uint32_t pin)
{
	CLEAR_BIT(EXTI->EXTIRER, pin);
}

/**
  * @brief  Check if rising edge trigger is enabled
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ENABLE/DISABLE
  */
__STATIC_INLINE uint8_t md_gpio_is_enabled_riging_edge_trigger(uint32_t pin)
{
	if (READ_BIT(EXTI->EXTIRER, pin) == pin)
		return ENABLE;
	return DISABLE;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group15 EXTIFER
  * @{
  */
/**
  * @brief  Enable trigger trailing edge
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_enable_trailing_edge_trigger(uint32_t pin)
{
	SET_BIT(EXTI->EXTIFER, pin);
}

/**
  * @brief  Disable trigger trailing edge
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_disable_trailing_edge_trigger(uint32_t pin)
{
	CLEAR_BIT(EXTI->EXTIFER, pin);
}

/**
  * @brief  Check if trailing edge trigger is enabled
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ENABLE/DISABLE
  */
__STATIC_INLINE uint8_t md_gpio_is_enabled_trailing_edge_trigger(uint32_t pin)
{
	if (READ_BIT(EXTI->EXTIFER, pin) == pin)
		return ENABLE;
	return DISABLE;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group16 EXTIEN
  * @{
  */
/**
  * @brief  Enable external interrupt
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_enable_external_interrupt(uint32_t pin)
{
	SET_BIT(EXTI->EXTIEN, pin);
}

/**
  * @brief  Disable external interrupt
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_disable_external_interrupt(uint32_t pin)
{
	CLEAR_BIT(EXTI->EXTIEN, pin);
}

/**
  * @brief  Check if external interrupt is enabled
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval ENABLE/DISABLE
  */
__STATIC_INLINE uint8_t md_gpio_is_enabled_external_interrupt(uint32_t pin)
{
	if (READ_BIT(EXTI->EXTIEN, pin) == pin)
		return ENABLE;
	return DISABLE;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group17 EXTIFLAG
  * @{
  */
/**
  * @brief  Gets status of flag
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Status.
  */
__STATIC_INLINE uint8_t md_gpio_get_flag(uint32_t pin)
{
	if (READ_BIT(EXTI->EXTIFLAG, pin) == pin)
		return 1;
	return 0;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group18 EXTISFR
  * @{
  */
/**
  * @brief  Set status of flag
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Status.
  */
__STATIC_INLINE void md_gpio_set_flag(uint32_t pin)
{
	WRITE_REG(EXTI->EXTISFR, pin);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group19 EXTICFR
  * @{
  */
/**
  * @brief  Clear status of flag
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Status.
  */
__STATIC_INLINE void md_gpio_clear_flag(uint32_t pin)
{
	WRITE_REG(EXTI->EXTICFR, pin);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group20 EXTIPSR
  * @{
  */
/**
  * @brief  Sets port of the interrup
  * @param  GPIOx: GPIO Port
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_interrupt_port(GPIO_TypeDef *GPIOx, uint32_t pin)
{
	uint8_t i, port;

	if (GPIOx == GPIOA)
		port = 0x0;
	else if (GPIOx == GPIOB)
		port = 0x1;
	else if (GPIOx == GPIOC)
		port = 2;
	else if (GPIOx == GPIOD)
		port = 3;
	else if (GPIOx == GPIOE)
		port = 4;
	else if (GPIOx == GPIOF)
		port = 5;
	else if (GPIOx == GPIOG)
		port = 6;
	else if (GPIOx == GPIOH)
		port = 7;
	else
		port = 0;

	/* Get Pin index */
	for (i = 0; i < 16; ++i) {
		if (((pin >> i) & 0x1) == 0x1)
			break;
	}

	if (i <= 7) {
		EXTI->EXTIPSR0 &= ~(0x7U << (i * 4));
		EXTI->EXTIPSR0 |= (port << (i * 4));
	}
	else {
		i -= 8;
		EXTI->EXTIPSR1 &= ~(0x7U << (i * 4));
		EXTI->EXTIPSR1 |= (port << (i * 4));
	}
}

/**
  * @brief  Gets port of the interrup
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval GPIO port:
  *         - 0x0: GPIOA
  *         - 0X1: GPIOB
  *         - 0x2: GPIOC
  *         - 0X3: GPIOD
  *         - 0x4: GPIOE
  *         - 0X5: GPIOF
  *         - 0x6: GPIOG
  *         - 0X7: GPIOH
  */
__STATIC_INLINE uint8_t md_gpio_get_interrupt_port(uint32_t pin)
{
	uint8_t i, port;

	/* Get Pin index */
	for (i = 0; i < 16; ++i) {
		if (((pin >> i) & 0x1) == 0x1)
			break;
	}

	if (i <= 7) {
		port = READ_BITS(EXTI->EXTIPSR0, (0x7 << (i * 4)), (i * 4));
	}
	else {
		i -= 8;
		port = READ_BITS(EXTI->EXTIPSR1, (0x7 << (i * 4)), (i * 4));
	}

	return port;
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group21 EXTIFLTCR
  * @{
  */
/**
  * @brief  Enable filter
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_interrupt_filter_enable(uint32_t pin)
{
	SET_BIT(EXTI->EXTIFLTCR, pin);
}

/**
  * @brief  Disable filter
  * @param  pin: This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void md_gpio_interrupt_filter_disable(uint32_t pin)
{
	CLEAR_BIT(EXTI->EXTIFLTCR, pin);
}

/**
  * @brief  Check if filter is enabled or disabled.
  * @retval Status:
  *           - 0: Disable
  *           - NOT_0: Enable
  */
__STATIC_INLINE uint32_t md_gpio_interrupt_filter_is_enable(uint32_t pin)
{
	return (READ_BIT(EXTI->EXTIFLTCR, pin) == pin);
}

/**
  * @brief  Set filter time
  * @param  time: Filter time, ((time + 1) * 2)CLOCK
  * @retval None
  */
__STATIC_INLINE void md_giop_interrupt_filter_time_set(uint8_t time)
{
	MODIFY_REG(EXTI->EXTIFLTCR, GPIO_EXTIFLTCR_FLTSEL_MSK, time << GPIO_EXTIFLTCR_FLTSEL_POSS);
}

/**
  * @brief  Get filter time
  * @retval Filter time
  */
__STATIC_INLINE uint32_t md_giop_interrupt_filter_time_get(void)
{
	return READ_BITS(EXTI->EXTIFLTCR, GPIO_EXTIFLTCR_FLTSEL_MSK, GPIO_EXTIFLTCR_FLTSEL_POSS);
}

/**
  * @brief  Select filter clock
  * @param  clock: 0-ULRC(10KHz), 1-LRC(32KHz)
  * @retval None
  */
__STATIC_INLINE void md_giop_interrupt_filter_clock_select(uint8_t clock)
{
	MODIFY_REG(EXTI->EXTIFLTCR, GPIO_EXTIFLTCR_FLTCKS_MSK, clock << GPIO_EXTIFLTCR_FLTCKS_POSS);
}
/**
  * @}
  */
/** @defgroup MD_GPIO_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_gpio_init(GPIO_TypeDef *GPIOx, uint16_t pin, md_gpio_init_t *init);
extern void md_gpio_init_struct(md_gpio_init_t *init);
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
