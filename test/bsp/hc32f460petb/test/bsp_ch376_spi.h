/*
##########################################################################################
								本文件是CH376 spi通讯的底层驱动




##########################################################################################
*/
#ifndef bsp_ch376_spi_h
#define bsp_ch376_spi_h

#include <stdint.h>
#include "ch376inc.h"
#include "hc32_ddl.h"

/*
*
***************************************************************************************
*											头文件包含							
*
****************************************************************************************
*/


/*
*
***************************************************************************************
*										spi1 连接引脚宏定义							
*
****************************************************************************************
*/

#define  CH376_ReadWrite  SPI1_ReadWrite


/* 附加的USB操作状态定义 */
#define	ERR_USB_UNKNOWN		0xFA				/* 未知错误,不应该发生的情况,需检查硬件或者程序错误 */

/*
*
***************************************************************************************
*												SPI  函数宏定义
*
****************************************************************************************
*/
/* SPI_NSS Port/Pin definition */
#define SPI_NSS_PORT                    (PortA)
#define SPI_NSS_PIN                     (Pin15)
#define SPI_NSS_HIGH()                  (PORT_SetBits(SPI_NSS_PORT, SPI_NSS_PIN))
#define SPI_NSS_LOW()                   (PORT_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN))

#define xEndCH376Cmd()      SPI_NSS_HIGH()

/*
*
***************************************************************************************
*											C文件中需要导出到外部函数接口							
*
****************************************************************************************
*/
void SPI1_Init(void);			//与CH376通讯的SPI初始化

void CH376_INT_PIN_Init(void);//与CH376相连的中断引脚初始化

void CH376_SPI_Init(void);					//CH376初始化

unsigned char SPI1_ReadWrite(unsigned char writedat);//SPI读写一个数据

uint8_t mInitCH376Host( void );		//将CH376芯片设置为主机模式

uint8_t mWaitInterrupt( void );			//等待CH376中断

void xWriteCH376Cmd( uint8_t mCmd );		//向CH376写命令

void xWriteCH376Data( uint8_t mData );	//向CH376写数据

uint8_t xReadCH376Data( void );				//从CH376读数据

uint8_t Query376Interrupt( void );				//查询中断引脚

void	mStopIfError( uint8_t iError );

void mDelayuS(uint8_t us);								//延时微妙级延时

void mDelaymS(uint8_t ms);							//延时毫秒级延时

void mDelay0_5uS( void );						//延时微妙级延时



/*
*
***************************************************************************************
*												
*
****************************************************************************************
*/


#endif



