/*
##########################################################################################
#								本文件是CH376 spi通讯的底层驱动
#
#
##########################################################################################
*/


/*
*
***************************************************************************************
*											头文件包含							
*
****************************************************************************************
*/
#include <stdio.h>
#include <stdint.h>
#include "bsp_ch376_spi.h"
#include "hc32_ddl.h"

/* SPI_SCK Port/Pin definition */
#define SPI_SCK_PORT                    (PortC)
#define SPI_SCK_PIN                     (Pin10)
#define SPI_SCK_FUNC                    (Func_Spi2_Sck)

/* SPI_NSS Port/Pin definition */
#define SPI_NSS_PORT                    (PortA)
#define SPI_NSS_PIN                     (Pin15)
#define SPI_NSS_HIGH()                  (PORT_SetBits(SPI_NSS_PORT, SPI_NSS_PIN))
#define SPI_NSS_LOW()                   (PORT_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN))

/* SPI_MOSI Port/Pin definition */
#define SPI_MOSI_PORT                   (PortC)
#define SPI_MOSI_PIN                    (Pin12)
#define SPI_MOSI_FUNC                   (Func_Spi2_Mosi)

/* SPI_MISO Port/Pin definition */
#define SPI_MISO_PORT                   (PortC)
#define SPI_MISO_PIN                    (Pin11)
#define SPI_MISO_FUNC                   (Func_Spi2_Miso)

/* SPI unit and clock definition */
#define SPI_UNIT                        (M4_SPI2)
#define SPI_UNIT_CLOCK                  (PWC_FCG1_PERIPH_SPI2)

#define INT_PORT                    (PortD)
#define INT_PIN                     (Pin00)


/*
*
***************************************************************************************
*										与CH376相连的spi1初始化							
*
****************************************************************************************
*/
void SPI1_Init(void)
{
    stc_port_init_t stcPortInit;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcPortInit);

    /* Flash NSS */
    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(SPI_NSS_PORT, SPI_NSS_PIN, &stcPortInit);
    SPI_NSS_HIGH();

    stc_spi_init_t stcSpiInit;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcSpiInit);

    /* Configuration peripheral clock */
    PWC_Fcg1PeriphClockCmd(SPI_UNIT_CLOCK, Enable);

    /* Configuration SPI pin */
    PORT_SetFunc(SPI_SCK_PORT, SPI_SCK_PIN, SPI_SCK_FUNC, Disable);
    PORT_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_MOSI_FUNC, Disable);
    PORT_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC, Disable);

    /* Configuration SPI structure */
    stcSpiInit.enClkDiv = SpiClkDiv8;
    stcSpiInit.enFrameNumber = SpiFrameNumber1;
    stcSpiInit.enDataLength = SpiDataLengthBit8;
    stcSpiInit.enFirstBitPosition = SpiFirstBitPositionMSB;
    stcSpiInit.enSckPolarity = SpiSckIdleLevelLow;
    stcSpiInit.enSckPhase = SpiSckOddSampleEvenChange;
    stcSpiInit.enReadBufferObject = SpiReadReceiverBuffer;
    stcSpiInit.enWorkMode = SpiWorkMode3Line;
    stcSpiInit.enTransMode = SpiTransFullDuplex;
    stcSpiInit.enCommAutoSuspendEn = Disable;
    stcSpiInit.enModeFaultErrorDetectEn = Disable;
    stcSpiInit.enParitySelfDetectEn = Disable;
    stcSpiInit.enParityEn = Disable;
    stcSpiInit.enParity = SpiParityEven;
    stcSpiInit.enMasterSlaveMode = SpiModeMaster;
    stcSpiInit.stcDelayConfig.enSsSetupDelayOption = SpiSsSetupDelayCustomValue;
    stcSpiInit.stcDelayConfig.enSsSetupDelayTime = SpiSsSetupDelaySck1;
    stcSpiInit.stcDelayConfig.enSsHoldDelayOption = SpiSsHoldDelayCustomValue;
    stcSpiInit.stcDelayConfig.enSsHoldDelayTime = SpiSsHoldDelaySck1;
    stcSpiInit.stcDelayConfig.enSsIntervalTimeOption = SpiSsIntervalCustomValue;
    stcSpiInit.stcDelayConfig.enSsIntervalTime = SpiSsIntervalSck6PlusPck2;

    SPI_Init(SPI_UNIT, &stcSpiInit);
    SPI_Cmd(SPI_UNIT, Enable);
}
/*
*
***************************************************************************************
*										与CH376相连的中断引脚初始化							
*
****************************************************************************************
*/
void CH376_INT_PIN_Init(void)
{
    stc_port_init_t stcPortInit;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcPortInit);

    stcPortInit.enPinMode = Pin_Mode_In;
    stcPortInit.enPullUp = Enable;
    PORT_Init(INT_PORT, INT_PIN, &stcPortInit);
}
/*
*
***************************************************************************************
*												CH376初始化SPI的数据传输模式							
*					
****************************************************************************************
*/
void CH376_SPI_Init(void)
{
	SPI1_Init();								//SPI端口初始化
	CH376_INT_PIN_Init();			//CH376中断引脚初始化
}
#if 1
/*******************************************************************************
* 函  数  名      : CH376_PORT_INIT
* 描      述      : 由于使用软件模拟SPI读写时序,所以进行初始化.
*                   如果是硬件SPI接口,那么可使用mode3(CPOL=1&CPHA=1)或
*                   mode0(CPOL=0&CPHA=0),CH376在时钟上升沿采样输入,下降沿输出,数
*                   据位是高位在前.
*		配置在SCK的哪个引脚边沿采样数据
*******************************************************************************/
void	CH376_PORT_INIT( void )
{
	
}
#endif


/*
*
***************************************************************************************
*									SPI输出8个位数据					
*
****************************************************************************************
*/
void Spi376OutByte(uint16_t d)  
{
    /* Wait tx buffer empty */
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSendBufferEmpty))
    {
    }
    /* Send data */
    SPI_SendData8(SPI_UNIT, d);
}

/*
*
***************************************************************************************
*									SPI输入8个位数据			
*
****************************************************************************************
*/
uint8_t Spi376InByte( void )
{  
    uint8_t u8Byte;

    /* Wait rx buffer full */
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagReceiveBufferFull))
    {
    }
    /* Receive data */
    u8Byte = SPI_ReceiveData8(SPI_UNIT);

    return u8Byte;
}

#if 0
/*
*
***************************************************************************************
*										与CH376相连的SPI1读写一字节数据							
*
****************************************************************************************
*/
unsigned char SPI1_ReadWrite(unsigned char writedat)
{
	
}
#endif
/*
****************************************************
 * Name:     CH376_PORT_INIT
 * Function: 初始化CH376的SPI IO！
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
uint8_t mWaitInterrupt( void ) 
{								/* 等待CH376中断并获取状态,主机端等待操作完成,返回操作状态 */
    while ( Query376Interrupt( ) == FALSE );       /* 一直等中断 */
    xWriteCH376Cmd( CMD_GET_STATUS );              /* 产生操作完成中断,获取中断状态 */
    return( xReadCH376Data( ) );
}


/*
****************************************************
 * Name:     xWriteCH376Cmd
 * Function: 写命令到CH376去
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
void	xWriteCH376Cmd( uint8_t mCmd )  /* 向CH376写命令 */
{
    /* 防止之前未通过xEndCH376Cmd禁止SPI片选 */
        SPI_NSS_HIGH();
        mDelay0_5uS( );
        /* 对于双向I/O引脚模拟SPI接口,那么必须确保已经设置SPI_SCS,SPI_SCK,SPI_SDI为输出方向,SPI_SDO为输入方向 */

        /* SPI片选有效 */
        SPI_NSS_LOW();
        #if 0
        CH376_ReadWrite(mCmd);
        #endif
        Spi376OutByte( mCmd );

        /* 延时1.5uS确保读写周期大于1.5uS,或者用上面一行的状态查询代替 */

        /*注意:这里的延时时间上是数据扔到数据发送寄存器后，8位数据发送的时间，
        应根据具体的情况调节，延时时间太长影响发送字节的速率*/
        mDelay0_5uS( );
        mDelay0_5uS( );
        //mDelay0_5uS( );
		

}

/*
****************************************************
 * Name:     xWriteCH376Data
 * Function: 写1字节数据到CH376
 * Input: 	 no
 * Output:   no 
 * Author:   PowerAVR / 2009-12-19
 * Update:   	
****************************************************
*/
void	xWriteCH376Data( uint8_t mData )  /* 向CH376写数据 */
{
    #if 0
    CH376_ReadWrite( mData );
    //mDelayuS(20 );  /* 确保读写周期大于0.6uS */
    #endif
    Spi376OutByte( mData );
        /*注意:这里的延时时间上是数据扔到数据发送寄存器后，8位数据发送的时间，
    应根据具体的情况调节，延时时间太长影响发送字节的速率*/
    //  mDelay0_5uS( );  /* 确保读写周期大于0.6uS */
    //mDelay0_5uS( );
    mDelay0_5uS( );
    mDelay0_5uS( );

}


/*
****************************************************
 * Name:     xReadCH376Data
 * Function: 从CH376读取1字节数据
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
uint8_t	xReadCH376Data( void )  /* 从CH376读数据 */
{
        #if 0
    //mDelayuS(10 );  /* 确保读写周期大于0.6uS */
    return( CH376_ReadWrite( 0xff) );       //发送0xFF哑巴字节，只有发送哑巴字节才能驱动时钟
    #endif
    //  mDelay0_5uS( );  /* 确保读写周期大于0.6uS */
    return( Spi376InByte( ) );

}

/*
****************************************************
 * Name:     Query376Interrupt
 * Function: 查询CH376中断(INT#低电平)
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
uint8_t	Query376Interrupt( void )
{	
    return( PORT_GetBit(INT_PORT, INT_PIN) == Reset);
}


/*
****************************************************
* Name:     mInitCH376Host
* Function: 初始化CH376
* Input: 	 no
* Output:   no 
* Author:   yyl
* Update:   	
****************************************************
*/
uint8_t mInitCH376Host( void )  
{
	 uint8_t res;
	 
	 CH376_PORT_INIT( );           /* 接口硬件初始化---配置为模式3 */
	 /*延时200ms等待端口初始化*/
	 mDelaymS(200);
	 mDelaymS(200);
	 mDelaymS(200);

	 xWriteCH376Cmd( CMD11_CHECK_EXIST );  			/* 测试单片机与CH376之间的通讯接口 */
	 
	 xWriteCH376Data( 0x65 );
	 
	 res = xReadCH376Data( );
	 
	 //printf("xReadCH376Data=%x \r\n",res);
	 
	 xEndCH376Cmd( );								// 结束通信测试
	 
	 if ( res != 0x9A ) 
	 {
	 	//USART1_SendByte(0xe1);
		printf("ch376 initialize failed !\r\n");
	 	return( ERR_USB_UNKNOWN );  				/* 通讯接口不正常,可能原因有:接口连接异常,其它设备影响(片选不唯一),串口波特率,一直在复位,晶振不工作 */
	 }
	 xWriteCH376Cmd( CMD11_SET_USB_MODE );  		/* 设备USB工作模式 */
	 xWriteCH376Data( 0x06 );						// 模式代码为0x06,表示切换到已启用的USB主机方式，自动产生SOF包
	 res = xReadCH376Data( );						// 返回操作状态
	 
	 mDelayuS( 20 );										//等待CH376S芯片设置为主机方式并产生SOF包
	 xEndCH376Cmd( );							    // 工作模式设置结束

	 xWriteCH376Cmd( CMD20_SET_SDO_INT );  			/* 设置SPI的SDO引脚的中断方式 */
	 xWriteCH376Data( 0x16 );
	 xWriteCH376Data( 0x90 );  						/* SDO引脚在SCS片选无效时兼做中断请求输出 */
	 xEndCH376Cmd( );							    // 结束设置SDO引脚方式


	 if ( res == CMD_RET_SUCCESS ) 
	 {
			printf( "Set USB host mode Success !\r\n" );
			return( USB_INT_SUCCESS );
	 }
	 	
	 else 
	 {
	 	//USART1_SendByte(0xe2);
		printf("Set USB host mode Fail !!\r\n");

	 	return( ERR_USB_UNKNOWN );  				/* 设置模式错误 */
	 }	
}

/*
****************************************************
 * Name:     mStopIfError
 * Function: error disposal
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
void	mStopIfError( uint8_t iError )
{
	if ( iError == USB_INT_SUCCESS ) return;  /* 操作成功 */
	printf( "Error: %02x\n", (UINT16)iError );  /* 显示错误 */
	while ( 1 ) {
/*		LED_OUT_ACT( );*/  /* LED闪烁 */
		mDelaymS( 200 );
/*		LED_OUT_INACT( );*/
		mDelaymS( 200 );
	}
}




/*
****************************************************
 * Name:     mDelayuS
 * Function: delay
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
void mDelayuS(uint8_t us)
{
 while(us--);
}

/*
****************************************************
 * Name:     mDelayuS
 * Function: delay
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
void mDelaymS(uint8_t ms)
{
 unsigned int i;
 for(;ms>0;ms--)
     for(i=0;i<940;i++);
}

/*
****************************************************
 * Name:     mDelayuS
 * Function: delay
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
void	mDelay0_5uS( void )  /* 至少延时0.5uS,根据单片机主频调整 */
{
 uint8_t i;
 i=20;
 while(i--);
}


