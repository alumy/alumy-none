/**
  *********************************************************************************
  *
  * @file    main.h
  * @brief   Header file for DEMO
  *
  * @version V1.0
  * @date    17 Nov 2017
  * @author  AE Team
  * @note   
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */ 

#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "utils.h"
#include "ald_uart.h"

#define UART1_TX_PORT	GPIOC
#define UART1_TX_PIN	GPIO_PIN_10
#define UART1_RX_PORT	GPIOC
#define UART1_RX_PIN	GPIO_PIN_11

extern uart_handle_t h_uart;
#endif
