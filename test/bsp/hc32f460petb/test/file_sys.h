/* CH376оƬ �ļ�ϵͳ�� V1.0 */
/* �ṩ�ļ�ϵͳ�����ӳ���,�ṩ������ */
/* ��ʹ�õ��ӳ������ע�͵�,�Ӷ���Լ��Ƭ���ĳ���ROM�ռ������RAM�ռ� */
/* ������ӳ�����ͨ�������еı������ݲ���,��������϶�,Ϊ�˽�ԼRAM,Ҳ���Բο�CH375�ӳ����ĳ�ͨ��ͬһȫ�ֱ���/���ϽṹCH376_CMD_DATA���� */

/* name ������ָ���ļ���, ���԰�����Ŀ¼��, ��������·���ָ���, �ܳ��Ȳ�����1+8+1+3+1�ֽ� */
/* PathName ������ָȫ·���Ķ��ļ���, ������Ŀ¼�����༶��Ŀ¼��·���ָ������ļ���/Ŀ¼�� */
/* LongName ������ָ���ļ���, ��UNICODEС��˳�����, ������0�ֽڽ���, ʹ�ó��ļ����ӳ�������ȶ���ȫ�ֻ�����GlobalBuf, ���Ȳ�С��64�ֽ�, �����������ӳ����� */

/* ���� NO_DEFAULT_CH376_INT ���ڽ�ֹĬ�ϵ�Wait376Interrupt�ӳ���,��ֹ��,Ӧ�ó���������ж���һ��ͬ���ӳ��� */
/* ���� DEF_INT_TIMEOUT ��������Ĭ�ϵ�Wait376Interrupt�ӳ����еĵȴ��жϵĳ�ʱʱ��/ѭ������ֵ, 0�򲻼�鳬ʱ��һֱ�ȴ� */
/* ���� EN_DIR_CREATE �����ṩ�½��༶��Ŀ¼���ӳ���,Ĭ���ǲ��ṩ */
/* ���� EN_DISK_QUERY �����ṩ����������ѯ��ʣ��ռ��ѯ���ӳ���,Ĭ���ǲ��ṩ */
/* ���� EN_SECTOR_ACCESS �����ṩ������Ϊ��λ��д�ļ����ӳ���,Ĭ���ǲ��ṩ */
/* ���� EN_LONG_NAME �����ṩ֧�ֳ��ļ������ӳ���,Ĭ���ǲ��ṩ */

#ifndef	__CH376_FS_H__
#define __CH376_FS_H__

//#include	"HAL.H"
#include "bsp_ch376_spi.h"

#define		EN_DISK_QUERY		 1	/* ���ô��̲�ѯ */
#define		EN_SECTOR_ACCESS	 1	/* ����������д */

#define	STRUCT_OFFSET( s, m )	( (uint8_t)( & ((s *)0) -> m ) )	/* �����ȡ�ṹ��Ա���ƫ�Ƶ�ַ�ĺ� */

#ifdef	EN_LONG_NAME
#ifndef	LONG_NAME_BUF_LEN
#define	LONG_NAME_BUF_LEN	( LONG_NAME_PER_DIR * 20 )	/* ���ж���ĳ��ļ�������������,��СֵΪLONG_NAME_PER_DIR*1 */
#endif
#endif


uint8_t	CH376ReadBlock( uint8_t * buf );  /* �ӵ�ǰ�����˵�Ľ��ջ�������ȡ���ݿ�,���س��� */

uint8_t	CH376WriteReqBlock( uint8_t * buf );  /* ���ڲ�ָ��������д����������ݿ�,���س��� */

void	CH376WriteHostBlock( uint8_t * buf, uint8_t len );  /* ��USB�����˵�ķ��ͻ�����д�����ݿ� */

void	CH376WriteOfsBlock( uint8_t * buf, uint8_t ofs, uint8_t len );  /* ���ڲ�������ָ��ƫ�Ƶ�ַд�����ݿ� */

void	CH376SetFileName( uint8_t * name );  /* ���ý�Ҫ�������ļ����ļ��� */

uint32_t	CH376Read32bitDat( void );  /* ��CH376оƬ��ȡ32λ�����ݲ��������� */

uint8_t	CH376ReadVar8( uint8_t var );  /* ��CH376оƬ�ڲ���8λ���� */

void	CH376WriteVar8( uint8_t var, uint8_t dat );  /* дCH376оƬ�ڲ���8λ���� */

uint32_t	CH376ReadVar32( uint8_t var );  /* ��CH376оƬ�ڲ���32λ���� */

void	CH376WriteVar32( uint8_t var, uint32_t dat );  /* дCH376оƬ�ڲ���32λ���� */

void	CH376EndDirInfo( void );  /* �ڵ���CH376DirInfoRead��ȡFAT_DIR_INFO�ṹ֮��Ӧ��֪ͨCH376���� */

uint32_t	CH376GetFileSize( void );  /* ��ȡ��ǰ�ļ����� */

uint8_t	CH376GetDiskStatus( void );  /* ��ȡ���̺��ļ�ϵͳ�Ĺ���״̬ */

uint8_t	CH376GetIntStatus( void );  /* ��ȡ�ж�״̬��ȡ���ж����� */

#ifndef	NO_DEFAULT_CH376_INT
uint8_t	Wait376Interrupt( void );  /* �ȴ�CH376�ж�(INT#�͵�ƽ)�������ж�״̬��, ��ʱ�򷵻�ERR_USB_UNKNOWN */
#endif

uint8_t	CH376SendCmdWaitInt( uint8_t mCmd );  /* �����������,�ȴ��ж� */

uint8_t	CH376SendCmdDatWaitInt( uint8_t mCmd, uint8_t mDat );  /* �����������һ�ֽ����ݺ�,�ȴ��ж� */

uint8_t	CH376DiskReqSense( void );  /* ���USB�洢������ */

uint8_t	CH376DiskConnect( void );  /* ���U���Ƿ�����,��֧��SD�� */

uint8_t	CH376DiskMount( void );  /* ��ʼ�����̲����Դ����Ƿ���� */

uint8_t	CH376FileOpen( uint8_t * name );  /* �ڸ�Ŀ¼���ߵ�ǰĿ¼�´��ļ�����Ŀ¼(�ļ���) */

uint8_t	CH376FileCreate( uint8_t * name );  /* �ڸ�Ŀ¼���ߵ�ǰĿ¼���½��ļ�,����ļ��Ѿ�������ô��ɾ�� */

uint8_t	CH376DirCreate( uint8_t * name );  /* �ڸ�Ŀ¼���½�Ŀ¼(�ļ���)����,���Ŀ¼�Ѿ�������ôֱ�Ӵ� */

uint8_t	CH376SeparatePath( uint8_t * path );  /* ��·���з�������һ���ļ�������Ŀ¼(�ļ���)��,�������һ���ļ�������Ŀ¼�����ֽ�ƫ�� */

uint8_t	CH376FileOpenDir( uint8_t * PathName, uint8_t StopName );  /* �򿪶༶Ŀ¼�µ��ļ�����Ŀ¼���ϼ�Ŀ¼,֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */
/* StopName ָ�����һ���ļ�������Ŀ¼�� */

uint8_t	CH376FileOpenPath( uint8_t * PathName );  /* �򿪶༶Ŀ¼�µ��ļ�����Ŀ¼(�ļ���),֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */

uint8_t	CH376FileCreatePath( uint8_t * PathName );  /* �½��༶Ŀ¼�µ��ļ�,֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */

#ifdef	EN_DIR_CREATE
uint8_t	CH376DirCreatePath( uint8_t * PathName );  /* �½��༶Ŀ¼�µ�Ŀ¼(�ļ���)����,֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */
#endif

uint8_t	CH376FileErase( uint8_t * PathName );  /* ɾ���ļ�,����Ѿ�����ֱ��ɾ��,��������ļ����ȴ���ɾ��,֧�ֶ༶Ŀ¼·�� */

uint8_t	CH376FileClose( uint8_t UpdateSz );  /* �رյ�ǰ�Ѿ��򿪵��ļ�����Ŀ¼(�ļ���) */

uint8_t	CH376DirInfoRead( void );  /* ��ȡ��ǰ�ļ���Ŀ¼��Ϣ */

uint8_t	CH376DirInfoSave( void );  /* �����ļ���Ŀ¼��Ϣ */

uint8_t	CH376ByteLocate( uint32_t offset );  /* ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */

uint8_t	CH376ByteRead( uint8_t * buf, uint16_t ReqCount, uint16_t * RealCount );  /* ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */

uint8_t	CH376ByteWrite( uint8_t * buf, uint16_t ReqCount, uint16_t * RealCount );  /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */

#ifdef	EN_DISK_QUERY

uint8_t	CH376DiskCapacity( uint32_t * DiskCap );  /* ��ѯ������������,������ */

uint8_t	CH376DiskQuery( uint32_t * DiskFre );  /* ��ѯ����ʣ��ռ���Ϣ,������ */

#endif

uint8_t	CH376SecLocate( uint32_t offset );  /* ������Ϊ��λ�ƶ���ǰ�ļ�ָ�� */

#ifdef	EN_SECTOR_ACCESS

uint8_t	CH376DiskReadSec( uint8_t * buf, uint32_t iLbaStart, uint8_t iSectorCount );  /* ��U�̶�ȡ������������ݿ鵽������,��֧��SD�� */

uint8_t	CH376DiskWriteSec( uint8_t * buf, uint32_t iLbaStart, uint8_t iSectorCount );  /* ���������еĶ�����������ݿ�д��U��,��֧��SD�� */

uint8_t	CH376SecRead( uint8_t * buf, uint8_t ReqCount, uint8_t * RealCount );  /* ������Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ�,��֧��SD�� */

uint8_t	CH376SecWrite( uint8_t * buf, uint8_t ReqCount, uint8_t * RealCount );  /* ������Ϊ��λ�ڵ�ǰλ��д�����ݿ�,��֧��SD�� */

#endif

#ifdef	EN_LONG_NAME

uint8_t	CH376LongNameWrite( uint8_t * buf, uint16_t ReqCount );  /* ���ļ���ר�õ��ֽ�д�ӳ��� */

uint8_t	CH376CheckNameSum( uint8_t * DirName );  /* ���㳤�ļ����Ķ��ļ��������,����Ϊ��С����ָ����Ĺ̶�11�ֽڸ�ʽ */

uint8_t	CH376LocateInUpDir( uint8_t * PathName );  /* ���ϼ�Ŀ¼(�ļ���)���ƶ��ļ�ָ�뵽��ǰ�ļ�Ŀ¼��Ϣ���ڵ����� */
/* ����,˳�㽫��ǰ�ļ�Ŀ¼��Ϣ���ڵ�������ǰһ��������LBA��ַд��CH376�ڲ�VAR_FAT_DIR_LBA����(Ϊ�˷����ռ����ļ���ʱ��ǰ����,����Ҫ���ƶ�һ��) */
/* ʹ����ȫ�ֻ�����GlobalBuf��ǰ12���ֽ� */

uint8_t	CH376GetLongName( uint8_t * PathName, uint8_t * LongName );  /* �ɶ��ļ�������Ŀ¼(�ļ���)�������Ӧ�ĳ��ļ��� */
/* ��Ҫ������ļ���������·��PathName,��Ҫ�ṩ���������ճ��ļ���LongName(��UNICODEС�˱���,��˫0����) */
/* ʹ����ȫ�ֻ�����GlobalBuf��ǰ34���ֽ�,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)+2 */

uint8_t	CH376CreateLongName( uint8_t * PathName, uint8_t * LongName );  /* �½����г��ļ������ļ�,�ر��ļ��󷵻�,LongName����·��������RAM�� */
/* ��Ҫ������ļ���������·��PathName(�����Ȳο�FAT�淶�ɳ��ļ������в���),��Ҫ������UNICODEС�˱������˫0�����ĳ��ļ���LongName */
/* ʹ����ȫ�ֻ�����GlobalBuf��ǰ64���ֽ�,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)*2 */

#endif

#endif
