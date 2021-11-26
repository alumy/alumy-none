/* CH376芯片 文件系统层 V1.0 */
/* 提供文件系统常用子程序,提供命令打包 */
/* 不使用的子程序可以注释掉,从而节约单片机的程序ROM空间和数据RAM空间 */
/* 这里的子程序是通过括号中的变量传递参数,如果参数较多,为了节约RAM,也可以参考CH375子程序库改成通过同一全局变量/联合结构CH376_CMD_DATA传递 */

/* name 参数是指短文件名, 可以包括根目录符, 但不含有路径分隔符, 总长度不超过1+8+1+3+1字节 */
/* PathName 参数是指全路径的短文件名, 包括根目录符、多级子目录及路径分隔符、文件名/目录名 */
/* LongName 参数是指长文件名, 以UNICODE小端顺序编码, 以两个0字节结束, 使用长文件名子程序必须先定义全局缓冲区GlobalBuf, 长度不小于64字节, 可以与其它子程序共用 */

/* 定义 NO_DEFAULT_CH376_INT 用于禁止默认的Wait376Interrupt子程序,禁止后,应用程序必须自行定义一个同名子程序 */
/* 定义 DEF_INT_TIMEOUT 用于设置默认的Wait376Interrupt子程序中的等待中断的超时时间/循环计数值, 0则不检查超时而一直等待 */
/* 定义 EN_DIR_CREATE 用于提供新建多级子目录的子程序,默认是不提供 */
/* 定义 EN_DISK_QUERY 用于提供磁盘容量查询和剩余空间查询的子程序,默认是不提供 */
/* 定义 EN_SECTOR_ACCESS 用于提供以扇区为单位读写文件的子程序,默认是不提供 */
/* 定义 EN_LONG_NAME 用于提供支持长文件名的子程序,默认是不提供 */

#ifndef	__CH376_FS_H__
#define __CH376_FS_H__

//#include	"HAL.H"
#include "bsp_ch376_spi.h"

#define		EN_DISK_QUERY		 1	/* 启用磁盘查询 */
#define		EN_SECTOR_ACCESS	 1	/* 启用扇区读写 */

#define	STRUCT_OFFSET( s, m )	( (uint8_t)( & ((s *)0) -> m ) )	/* 定义获取结构成员相对偏移地址的宏 */

#ifdef	EN_LONG_NAME
#ifndef	LONG_NAME_BUF_LEN
#define	LONG_NAME_BUF_LEN	( LONG_NAME_PER_DIR * 20 )	/* 自行定义的长文件名缓冲区长度,最小值为LONG_NAME_PER_DIR*1 */
#endif
#endif


uint8_t	CH376ReadBlock( uint8_t * buf );  /* 从当前主机端点的接收缓冲区读取数据块,返回长度 */

uint8_t	CH376WriteReqBlock( uint8_t * buf );  /* 向内部指定缓冲区写入请求的数据块,返回长度 */

void	CH376WriteHostBlock( uint8_t * buf, uint8_t len );  /* 向USB主机端点的发送缓冲区写入数据块 */

void	CH376WriteOfsBlock( uint8_t * buf, uint8_t ofs, uint8_t len );  /* 向内部缓冲区指定偏移地址写入数据块 */

void	CH376SetFileName( uint8_t * name );  /* 设置将要操作的文件的文件名 */

uint32_t	CH376Read32bitDat( void );  /* 从CH376芯片读取32位的数据并结束命令 */

uint8_t	CH376ReadVar8( uint8_t var );  /* 读CH376芯片内部的8位变量 */

void	CH376WriteVar8( uint8_t var, uint8_t dat );  /* 写CH376芯片内部的8位变量 */

uint32_t	CH376ReadVar32( uint8_t var );  /* 读CH376芯片内部的32位变量 */

void	CH376WriteVar32( uint8_t var, uint32_t dat );  /* 写CH376芯片内部的32位变量 */

void	CH376EndDirInfo( void );  /* 在调用CH376DirInfoRead获取FAT_DIR_INFO结构之后应该通知CH376结束 */

uint32_t	CH376GetFileSize( void );  /* 读取当前文件长度 */

uint8_t	CH376GetDiskStatus( void );  /* 获取磁盘和文件系统的工作状态 */

uint8_t	CH376GetIntStatus( void );  /* 获取中断状态并取消中断请求 */

#ifndef	NO_DEFAULT_CH376_INT
uint8_t	Wait376Interrupt( void );  /* 等待CH376中断(INT#低电平)，返回中断状态码, 超时则返回ERR_USB_UNKNOWN */
#endif

uint8_t	CH376SendCmdWaitInt( uint8_t mCmd );  /* 发出命令码后,等待中断 */

uint8_t	CH376SendCmdDatWaitInt( uint8_t mCmd, uint8_t mDat );  /* 发出命令码和一字节数据后,等待中断 */

uint8_t	CH376DiskReqSense( void );  /* 检查USB存储器错误 */

uint8_t	CH376DiskConnect( void );  /* 检查U盘是否连接,不支持SD卡 */

uint8_t	CH376DiskMount( void );  /* 初始化磁盘并测试磁盘是否就绪 */

uint8_t	CH376FileOpen( uint8_t * name );  /* 在根目录或者当前目录下打开文件或者目录(文件夹) */

uint8_t	CH376FileCreate( uint8_t * name );  /* 在根目录或者当前目录下新建文件,如果文件已经存在那么先删除 */

uint8_t	CH376DirCreate( uint8_t * name );  /* 在根目录下新建目录(文件夹)并打开,如果目录已经存在那么直接打开 */

uint8_t	CH376SeparatePath( uint8_t * path );  /* 从路径中分离出最后一级文件名或者目录(文件夹)名,返回最后一级文件名或者目录名的字节偏移 */

uint8_t	CH376FileOpenDir( uint8_t * PathName, uint8_t StopName );  /* 打开多级目录下的文件或者目录的上级目录,支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */
/* StopName 指向最后一级文件名或者目录名 */

uint8_t	CH376FileOpenPath( uint8_t * PathName );  /* 打开多级目录下的文件或者目录(文件夹),支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */

uint8_t	CH376FileCreatePath( uint8_t * PathName );  /* 新建多级目录下的文件,支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */

#ifdef	EN_DIR_CREATE
uint8_t	CH376DirCreatePath( uint8_t * PathName );  /* 新建多级目录下的目录(文件夹)并打开,支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */
#endif

uint8_t	CH376FileErase( uint8_t * PathName );  /* 删除文件,如果已经打开则直接删除,否则对于文件会先打开再删除,支持多级目录路径 */

uint8_t	CH376FileClose( uint8_t UpdateSz );  /* 关闭当前已经打开的文件或者目录(文件夹) */

uint8_t	CH376DirInfoRead( void );  /* 读取当前文件的目录信息 */

uint8_t	CH376DirInfoSave( void );  /* 保存文件的目录信息 */

uint8_t	CH376ByteLocate( uint32_t offset );  /* 以字节为单位移动当前文件指针 */

uint8_t	CH376ByteRead( uint8_t * buf, uint16_t ReqCount, uint16_t * RealCount );  /* 以字节为单位从当前位置读取数据块 */

uint8_t	CH376ByteWrite( uint8_t * buf, uint16_t ReqCount, uint16_t * RealCount );  /* 以字节为单位向当前位置写入数据块 */

#ifdef	EN_DISK_QUERY

uint8_t	CH376DiskCapacity( uint32_t * DiskCap );  /* 查询磁盘物理容量,扇区数 */

uint8_t	CH376DiskQuery( uint32_t * DiskFre );  /* 查询磁盘剩余空间信息,扇区数 */

#endif

uint8_t	CH376SecLocate( uint32_t offset );  /* 以扇区为单位移动当前文件指针 */

#ifdef	EN_SECTOR_ACCESS

uint8_t	CH376DiskReadSec( uint8_t * buf, uint32_t iLbaStart, uint8_t iSectorCount );  /* 从U盘读取多个扇区的数据块到缓冲区,不支持SD卡 */

uint8_t	CH376DiskWriteSec( uint8_t * buf, uint32_t iLbaStart, uint8_t iSectorCount );  /* 将缓冲区中的多个扇区的数据块写入U盘,不支持SD卡 */

uint8_t	CH376SecRead( uint8_t * buf, uint8_t ReqCount, uint8_t * RealCount );  /* 以扇区为单位从当前位置读取数据块,不支持SD卡 */

uint8_t	CH376SecWrite( uint8_t * buf, uint8_t ReqCount, uint8_t * RealCount );  /* 以扇区为单位在当前位置写入数据块,不支持SD卡 */

#endif

#ifdef	EN_LONG_NAME

uint8_t	CH376LongNameWrite( uint8_t * buf, uint16_t ReqCount );  /* 长文件名专用的字节写子程序 */

uint8_t	CH376CheckNameSum( uint8_t * DirName );  /* 计算长文件名的短文件名检验和,输入为无小数点分隔符的固定11字节格式 */

uint8_t	CH376LocateInUpDir( uint8_t * PathName );  /* 在上级目录(文件夹)中移动文件指针到当前文件目录信息所在的扇区 */
/* 另外,顺便将当前文件目录信息所在的扇区的前一个扇区的LBA地址写入CH376内部VAR_FAT_DIR_LBA变量(为了方便收集长文件名时向前搜索,否则要多移动一次) */
/* 使用了全局缓冲区GlobalBuf的前12个字节 */

uint8_t	CH376GetLongName( uint8_t * PathName, uint8_t * LongName );  /* 由短文件名或者目录(文件夹)名获得相应的长文件名 */
/* 需要输入短文件名的完整路径PathName,需要提供缓冲区接收长文件名LongName(以UNICODE小端编码,以双0结束) */
/* 使用了全局缓冲区GlobalBuf的前34个字节,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)+2 */

uint8_t	CH376CreateLongName( uint8_t * PathName, uint8_t * LongName );  /* 新建具有长文件名的文件,关闭文件后返回,LongName输入路径必须在RAM中 */
/* 需要输入短文件名的完整路径PathName(请事先参考FAT规范由长文件名自行产生),需要输入以UNICODE小端编码的以双0结束的长文件名LongName */
/* 使用了全局缓冲区GlobalBuf的前64个字节,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)*2 */

#endif

#endif
