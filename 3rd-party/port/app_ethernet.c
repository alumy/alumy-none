/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Src/app_ethernet.c 
  * @author  MCD Application Team
  * @brief   Ethernet specefic module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#if LWIP_DHCP
#include "lwip/dhcp.h"
#endif
#include "app_ethernet.h"
#include "ethernetif.h"
#include "alumy.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


#if LWIP_DHCP
#define MAX_DHCP_TRIES  4
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Notify the User about the network interface config status
  * @param  netif: the network interface
  * @retval None
  */
__weak void ethernet_link_status_updated(struct netif *netif)
{

}

#if LWIP_NETIF_LINK_CALLBACK
/**
  * @brief  Ethernet Link periodic check
  * @param  netif
  * @retval None
  */
__weak void Ethernet_Link_Periodic_Handle(struct netif *netif)
{

}

#endif

#if LWIP_DHCP
/**
  * @brief  DHCP_Process_Handle
  * @param  None
  * @retval None
  */
__weak void DHCP_Process(struct netif *netif)
{

}

/**
  * @brief  DHCP periodic check
  * @param  netif
  * @retval None
  */
__weak void DHCP_Periodic_Handle(struct netif *netif)
{

}

#endif
