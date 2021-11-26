#include <stdio.h>
#include <string.h>
#include "file_sys.h"

uint8_t   buf[64];
uint16_t  total;      /* 记录当前缓冲在FILE_DATA_BUF中的数据长度 */
uint32_t NewSize; /* 临时变量 */
uint8_t   FileDataBuf[0x4000];    /*定义较大的数组---文件缓冲区,太小则速度慢 */

int ch376_test(void)
{
    uint8_t   month, date, hour;
    uint16_t  year, adc;

     //u8 res;
    uint8_t   i, s;

    /**/
    mDelaymS(200);
    mDelaymS(200);
    mDelaymS(200);

    CH376_SPI_Init();                           //CH376的SPI口初始化


    #if 0           //测试用代码
    printf( "\r\n CH376 start initialize !\r\n" );

    CH376_PORT_INIT( );           /* 接口硬件初始化---配置为模式3 */
    mDelaymS(200);
     mDelaymS(200);
     mDelaymS(200);
    // 结束通信测试
    xWriteCH376Cmd( 0x06 );             /* 测试单片机与CH376之间的通讯接口 CMD11_CHECK_EXIST*/
    //mDelaymS(200);
    xWriteCH376Data( 0x65 );
    //mDelaymS(200);

    res = xReadCH376Data( );
    //mDelaymS(200);
    //mDelaymS(200);
    //mDelaymS(200);
    mDelaymS(200);


    xEndCH376Cmd( );                                // 结束通信测试
    printf("xReadCH376Data=%x \r\n",res);

    while(1);

    #endif


    do {
        s = mInitCH376Host( );  /* 初始化CH376 */
    }while (s != USB_INT_SUCCESS);

    #if 1       //U盘读写程序

    mStopIfError( s );

    while(1)
    {
        /* 检查U盘是否连接,等待U盘插入,对于SD卡,可以由单片机直接查询SD卡座的插拔状态引脚 */
        while ( CH376DiskConnect( ) != USB_INT_SUCCESS )
        {
            //if ( IsKeyPress )
            {  /* 有键按下 */
                printf( "Wait Udisk/SD Inject!!!\r\n" );
                //return 0;
            }
            mDelaymS( 100 );  /* 没必要频繁查询 */
        }


        //LED_UDISK_IN;  /* LED亮 */
        mDelaymS( 200 );  /* 延时,可选操作,有的USB存储器需要几十毫秒的延时 实际时间间隔30.25ms*/



        /* 对于检测到USB设备的,最多等待100*50mS,主要针对有些MP3太慢,对于检测到USB设备并且连接DISK_MOUNTED的,最多等待5*50mS,主要针对DiskReady不过的 */
        for ( i = 0; i < 100; i ++ )  /* 最长等待时间,100*50mS */
        {
            mDelaymS( 50 );
            printf( "Ready ? \r\n" );
             /* 初始化磁盘并测试磁盘是否就绪 */
            s = CH376DiskMount( );

            if ( s == USB_INT_SUCCESS ) break;  /* 准备好 */
            else if ( s == ERR_DISK_DISCON ) break;  /* 检测到断开,重新检测并计时 */
            if ( CH376GetDiskStatus( ) >= DEF_DISK_MOUNTED && i >= 5 ) break;  /* 有的U盘总是返回未准备好,不过可以忽略,只要其建立连接MOUNTED且尝试5*50mS */
        }
        /* 检测到断开,重新检测并计时 */
        if ( s == ERR_DISK_DISCON )
        {
            printf( "Device gone\r\n" );
            continue;
        }
        if ( CH376GetDiskStatus( ) < DEF_DISK_MOUNTED ) {  /* 未知USB设备,例如USB键盘、打印机等 */
            printf( "Unknown device\r\n" );
            goto UnknownUsbDevice;
        }

        /* 如果需要,可以读取数据块CH376_CMD_DATA.DiskMountInq,返回长度 */
        i = CH376ReadBlock( buf );
        if ( i == sizeof( INQUIRY_DATA ) ) {  /* U盘的厂商和产品信息 */
            buf[ i ] = 0;
            printf( "UdiskInfo: %s\r\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
        }

        #if 0           //文件查找及枚举
        /* 读取原文件 */
        printf( "Open UDisk File!\r\n" );
        strcpy( (char*)buf, "\\C51\\CH376HFT.C" );  /* 源文件名,多级目录下的文件名和路径名必须复制到RAM中再处理,而根目录或者当前目录下的文件名可以在RAM或者ROM中 */
        s = CH376FileOpenPath( buf );  /* 打开文件,该文件在C51子目录下 */
        if ( s == ERR_MISS_DIR || s == ERR_MISS_FILE ) {  /* 没有找到目录或者没有找到文件 */
        /* 列出文件,完整枚举可以参考EXAM13全盘枚举 */
            if ( s == ERR_MISS_DIR ) strcpy( (char*)buf, "\\*" );  /* C51子目录不存在则列出根目录下的文件 */
            else strcpy( (char*)buf, "\\C51\\CH376*" );  /* CH376HFT.C文件不存在则列出\C51子目录下的以CH376开头的文件 */
            printf( "List file %s\r\n", buf );
            s = CH376FileOpenPath( buf );  /* 枚举多级目录下的文件或者目录,输入缓冲区必须在RAM中 */
            while ( s == USB_INT_DISK_READ ) {  /* 枚举到匹配的文件 */
                CH376ReadBlock( buf );  /* 读取枚举到的文件的FAT_DIR_INFO结构,返回长度总是sizeof( FAT_DIR_INFO ) */
                pDir = (P_FAT_DIR_INFO)buf;  /* 当前文件目录信息 */
                if ( pDir -> DIR_Name[0] != '.' ) {  /* 不是本级或者上级目录名则继续,否则必须丢弃不处理 */
                    if ( pDir -> DIR_Name[0] == 0x05 ) pDir -> DIR_Name[0] = 0xE5;  /* 特殊字符替换 */
                    pDir -> DIR_Attr = 0;  /* 强制文件名字符串结束以便打印输出 */
                    printf( "*** EnumName: %s\r\n", pDir -> DIR_Name );  /* 打印名称,原始8+3格式,未整理成含小数点分隔符 */
                }
                xWriteCH376Cmd( CMD0H_FILE_ENUM_GO );  /* 继续枚举文件和目录 */
                xEndCH376Cmd( );
                s = Wait376Interrupt( );
            }
            if ( s != ERR_MISS_FILE ) mStopIfError( s );  /* 操作出错 */
        }
        else {  /* 找到文件或者出错 */
            mStopIfError( s );
            TotalCount = 200;  /* 准备读取总长度 */
            printf( "从文件中读出的前%d个字符是:\r\n",(UINT16)TotalCount );
            while ( TotalCount ) {  /* 如果文件比较大,一次读不完,可以再调用CH376ByteRead继续读取,文件指针自动向后移动 */
                if ( TotalCount > sizeof(buf) ) i = sizeof(buf);  /* 剩余数据较多,限制单次读写的长度不能超过缓冲区大小 */
                else i = TotalCount;  /* 最后剩余的字节数 */
                s = CH376ByteRead( buf, i, &RealCount );  /* 以字节为单位读取数据块,单次读写的长度不能超过缓冲区大小,第二次调用时接着刚才的向后读 */
                mStopIfError( s );
                TotalCount -= (UINT8)RealCount;  /* 计数,减去当前实际已经读出的字符数 */
                for ( s=0; s!=RealCount; s++ ) printf( "%c", buf[s] );  /* 显示读出的字符 */
                if ( RealCount < i ) {  /* 实际读出的字符数少于要求读出的字符数,说明已经到文件的结尾 */
                    printf( "\n" );
                    printf( "文件已经结束\n" );
                    break;
                }
            }
            printf( "Close\n" );
            s = CH376FileClose( FALSE );  /* 关闭文件 */
            mStopIfError( s );
        }
        #endif

        #if 0           //扇区方式读写文件
        /* 检查U盘或者SD卡的剩余空间 */
        printf( "DiskQuery:\r\n " );
        s = CH376DiskQuery( (PUINT32)buf );  /* 查询磁盘剩余空间信息,扇区数 */
        mStopIfError( s );
        //      printf( "free cap = %ld MB\n", *(PUINT32)buf * DEF_SECTOR_SIZE / 1000000 );  /* 未用扇区数乘以扇区大小后,除以1M换算为兆字节单位 */
        printf( "free cap = %ld MB\r\n", *(PUINT32)buf / ( 1000000 / DEF_SECTOR_SIZE ) );  /* 上面一行的计算可能会溢出,换个顺序计算 */

        /* 如果MY_ADC.TXT文件已经存在则添加数据到尾部,如果不存在则新建文件 */
        printf( "Open File\r\n" );

         /* 打开文件,该文件在根目录下 */
        s = CH376FileOpen( "/MY_ADC.TXT" );
        if ( s == USB_INT_SUCCESS )
        {  /* 文件存在并且已经被打开,移动文件指针到尾部以便添加数据 */
                NewSize = CH376GetFileSize( );  /* 读取当前文件长度,如果没有零头数据,那么文件长度是DEF_SECTOR_SIZE的倍数 */
                printf( "File size = %ld\r\n", NewSize );

                printf( "Locate tail\r\n" );
                s = CH376SecLocate( 0xFFFFFFFF );  /* 以扇区为单位移到文件尾部,如果文件尾部有不足一个扇区的零头数据则被忽略,如果不做处理那么零头数据将可能被写入数据覆盖 */
                mStopIfError( s );

                total = NewSize & ( DEF_SECTOR_SIZE - 1 );  /* 上次保存文件时如果尾部有零头数据,那么先取得零头字节数,不满扇区长度的零碎数据 */
                printf( "Read last tail = %d Bytes\r\n", total );
                if ( total )
                {  /* 原尾部有零头数据,那么先调入内存,以便接着添加数据 */
                    s = CH376SecRead( FileDataBuf, 1, NULL );  /* 从文件读取尾部零头数据 */
                    mStopIfError( s );
                    s = CH376SecLocate( 0xFFFFFFFF );  /* 重新回到原文件的尾部,下面如果写入数据将覆盖原尾部零头数据,不过原零头数据刚才已经被读入内存,所以请放心 */
                    mStopIfError( s );
                }
        }
        /* 没有找到文件,必须新建文件 */
        else if ( s == ERR_MISS_FILE )
        {
                printf( "Create\r\n" );
                s = CH376FileCreate( NULL );  /* 新建文件并打开,如果文件已经存在则先删除后再新建,不必再提供文件名,刚才已经提供给CH376FileOpen */
                mStopIfError( s );
                total = 0;  /* 此前没有零头数据 */
                NewSize = 0;
        }
         /* 打开文件时出错 */
        else
        {
                mStopIfError( s );
        }



        printf( "Write begin!\r\n" );
        total += sprintf( (char*)FileDataBuf + total, "在本次添加数据之前,该文件已有数据的长度是 %ld 字节\xd\xa", NewSize );  /* 将新数据添加到缓冲区的尾部,累计缓冲区内的数据长度 */

        mFlushBufferToDisk( 0 );  /* 自动刷新缓冲区,检查缓冲区是否已满,满则写盘 */
        printf( "start write test data!\r\n" );

        #if 1
        //TR0=1;  /* 用定时器0的计数值代替ADC数据 */
        /* 因为测试板上没有实时时钟芯片,所以用循环方式模拟月份 */
        for ( month = 1; month != 12; month ++ )
        {
                /* 因为测试板上没有实时时钟芯片,所以用循环方式模拟日期 */
                for ( date = 1; date != 30; date ++ )
                {
                        year = 2004;  /* 假定为2004年 */
                        //hour = TL1 & 0x1F;  /* 因为测试板上没有实时时钟芯片,所以用定时器1的计数代替进行演示 */
                        hour = 12;  /* 因为测试板上没有实时时钟芯片,所以用定时器1的计数代替进行演示 */

                        /*  adc = get_adc_data( ); */
                        //adc = ( (UINT16)TH0 << 8 ) | TL0;  /* 因为测试板上没有ADC,所以用定时器0的计数代替ADC数据演示 */
                        adc = 0xaa;  /* 因为测试板上没有ADC,所以用定时器0的计数代替ADC数据演示 */

                        total += sprintf( (char*)FileDataBuf + total, "Year=%04d, Month=%02d, Date=%02d, Hour=%02d, ADC_data=%u\xd\xa", year, (UINT16)month, (UINT16)date, (UINT16)hour, adc );  /* 将二制制数据格式为一行字符串 */
                        if ( month == 6 && ( date & 0x0F ) == 0 )
                        {
                                printf( "Force Write Start!!\r\n" );  /* 用于监控检查 */
                                mFlushBufferToDisk( 1 );  /* 强制刷新缓冲区,定期强制刷新缓冲区,这样在突然断电后可以减少数据丢失 */
                        }
                        else
                        {
                                printf( "Auto Write Start!!\r\n" );  /* 用于监控检查 */

                                mFlushBufferToDisk( 0 );  /* 自动刷新缓冲区,检查缓冲区是否已满,满则写盘 */
                        }
                        printf( "Current total is %d\r\n", total );  /* 用于监控检查 */
                }
        }
        #endif

        printf( "Write end\r\n" );
        total += sprintf( (char*)FileDataBuf + total, " ********************************* " );  /* 将新数据添加到缓冲区的尾部,累计缓冲区内的数据长度 */
        total += sprintf( (char*)FileDataBuf + total, "这次的ADC数据到此结束,程序即将退出\xd\xa" );  /* 将新数据添加到缓冲区的尾部,累计缓冲区内的数据长度 */
        mFlushBufferToDisk( 1 );  /* 强制刷新缓冲区,因为系统要退出了,所以必须强制刷新 */

        printf( "Close\r\n" );
        s = CH376FileClose( FALSE );  /* 关闭文件,扇区模式通常不自动更新文件长度,因为强制刷新缓冲区时已经更新了文件长度,所以这里不需要自动更新文件长度 */
        mStopIfError( s );

        printf( "Please Take out UDisk!!!!\r\n" );
        while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* 检查U盘是否连接,等待U盘拔出 */
            mDelaymS( 100 );
        }
        mDelaymS( 200 );
        #endif


        #if 1
        /* 检查U盘或者SD卡的剩余空间 */
        printf( "DiskQuery:\r\n " );
        s = CH376DiskQuery( (PUINT32)buf );  /* 查询磁盘剩余空间信息,扇区数 */
        mStopIfError( s );
        //      printf( "free cap = %ld MB\n", *(PUINT32)buf * DEF_SECTOR_SIZE / 1000000 );  /* 未用扇区数乘以扇区大小后,除以1M换算为兆字节单位 */
        printf( "free cap = %ld MB\r\n", *(PUINT32)buf / ( 1000000 / DEF_SECTOR_SIZE ) );  /* 上面一行的计算可能会溢出,换个顺序计算 */

        /* 如果MY_ADC.TXT文件已经存在则添加数据到尾部,如果不存在则新建文件 */
        printf( "Open File!!\r\n" );
        /* 打开文件,该文件在根目录下 */
        s = CH376FileOpen( "/MY_ADC.TXT" );

        /* 文件存在并且已经被打开,移动文件指针到尾部以便添加数据 */
        if ( s == USB_INT_SUCCESS )
        {
            printf( "File size = %ld\r\n", CH376GetFileSize( ) );  /* 读取当前文件长度 */
            printf( "Locate tail\r\n" );
            s = CH376ByteLocate( 0xFFFFFFFF );  /* 移到文件的尾部 */
            mStopIfError( s );
        }
         /* 没有找到文件,必须新建文件 */
        else if ( s == ERR_MISS_FILE )
        {
            printf( "Create File\r\n" );
            s = CH376FileCreate( NULL );  /* 新建文件并打开,如果文件已经存在则先删除后再新建,不必再提供文件名,刚才已经提供给CH376FileOpen */
            mStopIfError( s );
        }
        /* 打开文件时出错 */
        else
        {
                mStopIfError( s );
                printf( "Open File Error!!\r\n" );
        }

        printf( "Write begin\r\n" );
        s = sprintf((char*)buf, "此前文件长度= %ld 字节\xd\xa", CH376GetFileSize( ) );  /* 注意字符串长度不能溢出buf,否则加大缓冲区或者分多次写入 */
        s = CH376ByteWrite( buf, s, NULL );  /* 以字节为单位向文件写入数据 */
        mStopIfError( s );

        printf( "Start Write data!!\r\n" );

        #if 1
        //TR0=1;  /* 用定时器0的计数值代替ADC数据 */
        /* 用循环方式添加12行数据 */
        for ( hour = 8; hour != 20; hour ++  )
        {
            month = 5;  /* 假定是5月 */
            date = 29;  /* 因为测试板上没有实时时钟芯片,所以用定时器1的计数代替进行演示 */
            /*          adc = get_adc_data( ); */
            //adc = ( (UINT16)TH0 << 8 ) | TL0;  /* 因为测试板上没有ADC,所以用定时器0的计数代替ADC数据演示 */
            adc = 0;  /* 因为测试板上没有ADC,所以用定时器0的计数代替ADC数据演示 */

            s = sprintf( (char*)buf, "Year=%04d, Month=%02d, Date=%02d, Hour=%02d, ADC_data=%u\xd\xa", year, (UINT16)month, (UINT16)date, (UINT16)hour, adc  );  /* 将二制制数据格式为一行字符串 */
            s = CH376ByteWrite( buf, s, NULL );  /* 以字节为单位向文件写入数据 */
            /* 有些U盘可能会要求在写数据后等待一会才能继续操作,所以,如果在某些U盘中发生数据丢失现象,建议在每次写入数据后稍作延时再继续 */
            mStopIfError( s );
            printf( "Current offset ( file point ) is %ld\r\n", CH376ReadVar32( VAR_CURRENT_OFFSET ) );  /* 读取当前文件指针 */
        }
        //      CH376ByteWrite( buf, 0, NULL );  /* 以字节为单位向文件写入数据,因为是0字节写入,所以只用于更新文件的长度,当阶段性写入数据后,可以用这种办法更新文件长度 */
        printf( "Write end\r\n" );
        strcpy((char*)buf, "今天的ADC数据到此结束\xd\xa" );
        s = CH376ByteWrite( buf, strlen((const char*)buf ), NULL );  /* 以字节为单位向文件写入数据 */
        mStopIfError( s );
        /* 如果实际产品中有实时时钟,可以根据需要将文件的日期和时间修改为实际值,参考EXAM10用CH376DirInfoRead/CH376DirInfoSave实现 */
        #endif

        printf( "Close File\r\n" );
        s = CH376FileClose( TRUE );  /* 关闭文件,自动计算文件长度,以字节为单位写文件,建议让程序库关闭文件以便自动更新文件长度 */
        mStopIfError( s );

        printf( "Please Take out UDisk!!\r\n" );
        /* 检查U盘是否连接,等待U盘拔出 */
        while ( CH376DiskConnect( ) == USB_INT_SUCCESS )
        {
            mDelaymS( 100 );
        }
        mDelaymS( 200 );
        #endif

    UnknownUsbDevice:
        printf( "Take out\n" );
        while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* 检查U盘是否连接,等待U盘拔出 */
            mDelaymS( 100 );
        }
        //LED_UDISK_OUT;  /* LED灭 */
        mDelaymS( 100 );
    }
    #endif


}

