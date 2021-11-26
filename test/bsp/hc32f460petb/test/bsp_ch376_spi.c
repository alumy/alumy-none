/*
##########################################################################################
#								���ļ���CH376 spiͨѶ�ĵײ�����
#
#
##########################################################################################
*/


/*
*
***************************************************************************************
*											ͷ�ļ�����							
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
*										��CH376������spi1��ʼ��							
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
*										��CH376�������ж����ų�ʼ��							
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
*												CH376��ʼ��SPI�����ݴ���ģʽ							
*					
****************************************************************************************
*/
void CH376_SPI_Init(void)
{
	SPI1_Init();								//SPI�˿ڳ�ʼ��
	CH376_INT_PIN_Init();			//CH376�ж����ų�ʼ��
}
#if 1
/*******************************************************************************
* ��  ��  ��      : CH376_PORT_INIT
* ��      ��      : ����ʹ�����ģ��SPI��дʱ��,���Խ��г�ʼ��.
*                   �����Ӳ��SPI�ӿ�,��ô��ʹ��mode3(CPOL=1&CPHA=1)��
*                   mode0(CPOL=0&CPHA=0),CH376��ʱ�������ز�������,�½������,��
*                   ��λ�Ǹ�λ��ǰ.
*		������SCK���ĸ����ű��ز�������
*******************************************************************************/
void	CH376_PORT_INIT( void )
{
	
}
#endif


/*
*
***************************************************************************************
*									SPI���8��λ����					
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
*									SPI����8��λ����			
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
*										��CH376������SPI1��дһ�ֽ�����							
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
 * Function: ��ʼ��CH376��SPI IO��
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
uint8_t mWaitInterrupt( void ) 
{								/* �ȴ�CH376�жϲ���ȡ״̬,�����˵ȴ��������,���ز���״̬ */
    while ( Query376Interrupt( ) == FALSE );       /* һֱ���ж� */
    xWriteCH376Cmd( CMD_GET_STATUS );              /* ������������ж�,��ȡ�ж�״̬ */
    return( xReadCH376Data( ) );
}


/*
****************************************************
 * Name:     xWriteCH376Cmd
 * Function: д���CH376ȥ
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
void	xWriteCH376Cmd( uint8_t mCmd )  /* ��CH376д���� */
{
    /* ��ֹ֮ǰδͨ��xEndCH376Cmd��ֹSPIƬѡ */
        SPI_NSS_HIGH();
        mDelay0_5uS( );
        /* ����˫��I/O����ģ��SPI�ӿ�,��ô����ȷ���Ѿ�����SPI_SCS,SPI_SCK,SPI_SDIΪ�������,SPI_SDOΪ���뷽�� */

        /* SPIƬѡ��Ч */
        SPI_NSS_LOW();
        #if 0
        CH376_ReadWrite(mCmd);
        #endif
        Spi376OutByte( mCmd );

        /* ��ʱ1.5uSȷ����д���ڴ���1.5uS,����������һ�е�״̬��ѯ���� */

        /*ע��:�������ʱʱ�����������ӵ����ݷ��ͼĴ�����8λ���ݷ��͵�ʱ�䣬
        Ӧ���ݾ����������ڣ���ʱʱ��̫��Ӱ�췢���ֽڵ�����*/
        mDelay0_5uS( );
        mDelay0_5uS( );
        //mDelay0_5uS( );
		

}

/*
****************************************************
 * Name:     xWriteCH376Data
 * Function: д1�ֽ����ݵ�CH376
 * Input: 	 no
 * Output:   no 
 * Author:   PowerAVR / 2009-12-19
 * Update:   	
****************************************************
*/
void	xWriteCH376Data( uint8_t mData )  /* ��CH376д���� */
{
    #if 0
    CH376_ReadWrite( mData );
    //mDelayuS(20 );  /* ȷ����д���ڴ���0.6uS */
    #endif
    Spi376OutByte( mData );
        /*ע��:�������ʱʱ�����������ӵ����ݷ��ͼĴ�����8λ���ݷ��͵�ʱ�䣬
    Ӧ���ݾ����������ڣ���ʱʱ��̫��Ӱ�췢���ֽڵ�����*/
    //  mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
    //mDelay0_5uS( );
    mDelay0_5uS( );
    mDelay0_5uS( );

}


/*
****************************************************
 * Name:     xReadCH376Data
 * Function: ��CH376��ȡ1�ֽ�����
 * Input: 	 no
 * Output:   no 
 * Author:   yyl
 * Update:   	
****************************************************
*/
uint8_t	xReadCH376Data( void )  /* ��CH376������ */
{
        #if 0
    //mDelayuS(10 );  /* ȷ����д���ڴ���0.6uS */
    return( CH376_ReadWrite( 0xff) );       //����0xFF�ư��ֽڣ�ֻ�з����ư��ֽڲ�������ʱ��
    #endif
    //  mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
    return( Spi376InByte( ) );

}

/*
****************************************************
 * Name:     Query376Interrupt
 * Function: ��ѯCH376�ж�(INT#�͵�ƽ)
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
* Function: ��ʼ��CH376
* Input: 	 no
* Output:   no 
* Author:   yyl
* Update:   	
****************************************************
*/
uint8_t mInitCH376Host( void )  
{
	 uint8_t res;
	 
	 CH376_PORT_INIT( );           /* �ӿ�Ӳ����ʼ��---����Ϊģʽ3 */
	 /*��ʱ200ms�ȴ��˿ڳ�ʼ��*/
	 mDelaymS(200);
	 mDelaymS(200);
	 mDelaymS(200);

	 xWriteCH376Cmd( CMD11_CHECK_EXIST );  			/* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
	 
	 xWriteCH376Data( 0x65 );
	 
	 res = xReadCH376Data( );
	 
	 //printf("xReadCH376Data=%x \r\n",res);
	 
	 xEndCH376Cmd( );								// ����ͨ�Ų���
	 
	 if ( res != 0x9A ) 
	 {
	 	//USART1_SendByte(0xe1);
		printf("ch376 initialize failed !\r\n");
	 	return( ERR_USB_UNKNOWN );  				/* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
	 }
	 xWriteCH376Cmd( CMD11_SET_USB_MODE );  		/* �豸USB����ģʽ */
	 xWriteCH376Data( 0x06 );						// ģʽ����Ϊ0x06,��ʾ�л��������õ�USB������ʽ���Զ�����SOF��
	 res = xReadCH376Data( );						// ���ز���״̬
	 
	 mDelayuS( 20 );										//�ȴ�CH376SоƬ����Ϊ������ʽ������SOF��
	 xEndCH376Cmd( );							    // ����ģʽ���ý���

	 xWriteCH376Cmd( CMD20_SET_SDO_INT );  			/* ����SPI��SDO���ŵ��жϷ�ʽ */
	 xWriteCH376Data( 0x16 );
	 xWriteCH376Data( 0x90 );  						/* SDO������SCSƬѡ��Чʱ�����ж�������� */
	 xEndCH376Cmd( );							    // ��������SDO���ŷ�ʽ


	 if ( res == CMD_RET_SUCCESS ) 
	 {
			printf( "Set USB host mode Success !\r\n" );
			return( USB_INT_SUCCESS );
	 }
	 	
	 else 
	 {
	 	//USART1_SendByte(0xe2);
		printf("Set USB host mode Fail !!\r\n");

	 	return( ERR_USB_UNKNOWN );  				/* ����ģʽ���� */
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
	if ( iError == USB_INT_SUCCESS ) return;  /* �����ɹ� */
	printf( "Error: %02x\n", (UINT16)iError );  /* ��ʾ���� */
	while ( 1 ) {
/*		LED_OUT_ACT( );*/  /* LED��˸ */
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
void	mDelay0_5uS( void )  /* ������ʱ0.5uS,���ݵ�Ƭ����Ƶ���� */
{
 uint8_t i;
 i=20;
 while(i--);
}


