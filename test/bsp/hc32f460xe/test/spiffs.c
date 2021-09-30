#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "alumy/test_init.h"
#include "alumy.h"
#include "hc32_ddl.h"

__BEGIN_DECLS

#if AL_TEST_DRIVER

/* SPI_SCK Port/Pin definition */
#define SPI_SCK_PORT                    (PortE)
#define SPI_SCK_PIN                     (Pin00)
#define SPI_SCK_FUNC                    (Func_Spi3_Sck)

/* SPI_NSS Port/Pin definition */
#define SPI_NSS_PORT                    (PortB)
#define SPI_NSS_PIN                     (Pin08)
#define SPI_NSS_HIGH()                  (PORT_SetBits(SPI_NSS_PORT, SPI_NSS_PIN))
#define SPI_NSS_LOW()                   (PORT_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN))

/* SPI_MOSI Port/Pin definition */
#define SPI_MOSI_PORT                   (PortE)
#define SPI_MOSI_PIN                    (Pin01)
#define SPI_MOSI_FUNC                   (Func_Spi3_Mosi)

/* SPI_MISO Port/Pin definition */
#define SPI_MISO_PORT                   (PortB)
#define SPI_MISO_PIN                    (Pin09)
#define SPI_MISO_FUNC                   (Func_Spi3_Miso)

/* SPI unit and clock definition */
#define SPI_UNIT                        (M4_SPI3)
#define SPI_UNIT_CLOCK                  (PWC_FCG1_PERIPH_SPI3)

/* FLASH parameters */
#define FLASH_PAGE_SIZE                 (0x100u)
#define FLASH_SECTOR_SIZE               (0x1000u)
#define FLASH_MAX_ADDR                  (0x800000ul)
#define FLASH_DUMMY_BYTE_VALUE          (0xffu)
#define FLASH_BUSY_BIT_MASK             (0x01u)

/* FLASH instruction */
#define FLASH_INSTR_WRITE_ENABLE        (0x06u)
#define FLASH_INSTR_PAGE_PROGRAM        (0x02u)
#define FLASH_INSTR_STANDARD_READ       (0x03u)
#define FLASH_INSTR_ERASE_4KB_SECTOR    (0x20u)
#define FLASH_INSTR_READ_SR1            (0x05u)

#define SPIFLASH_CFG_CONFIG_PHYS_ADDR               (0x000000ul)
#define SPIFLASH_CFG_CONFIG_PHYS_SZ                 (0x100000ul)

#define SPIFLASH_CFG_CONFIG_BACKUP_PHYS_ADDR        (0x100000ul)
#define SPIFLASH_CFG_CONFIG_BACKUP_PHYS_SZ          (0x100000ul)

#define SPIFLASH_CFG_RECORD_PHYS_ADDR               (0x200000ul)
#define SPIFLASH_CFG_RECORD_PHYS_SZ                 (0x600000ul)

#define SPIFLASH_CFG_PHYS_ADDR          0
#define SPIFLASH_CFG_PHYS_SZ            (0x800000ul)

#define SPIFLASH_CFG_PHYS_ERASE_SZ      FLASH_SECTOR_SIZE
#define SPIFLASH_CFG_LOG_PAGE_SZ        FLASH_PAGE_SIZE
#define SPIFLASH_CFG_LOG_BLOCK_SZ       0xFFFF

typedef struct file_system {
    char name[16];
    spiffs fs;
    u8_t work[SPIFLASH_CFG_LOG_PAGE_SZ * 2];
    u8_t fd_space[32 * 4];
    u8_t cache[(SPIFLASH_CFG_LOG_PAGE_SZ + 32)* 4];
} file_system_t;

file_system_t config_fs;
file_system_t config_backup_fs;
file_system_t record_fs;

static void Spi_Config(void)
{
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

/**
 *******************************************************************************
 ** \brief SPI flash write byte function
 **
 ** \param [in] u8Data                      SPI write data to flash
 **
 ** \retval uint8_t                         SPI receive data from flash
 **
 ******************************************************************************/
static uint8_t SpiFlash_WriteReadByte(uint8_t u8Data)
{
    uint8_t u8Byte;

    /* Wait tx buffer empty */
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSendBufferEmpty))
    {
    }
    /* Send data */
    SPI_SendData8(SPI_UNIT, u8Data);
    /* Wait rx buffer full */
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagReceiveBufferFull))
    {
    }
    /* Receive data */
    u8Byte = SPI_ReceiveData8(SPI_UNIT);

    return u8Byte;
}

/**
 *******************************************************************************
 ** \brief SPI flash write enable function
 **
 ** \param [in] None
 **
 ** \retval None
 **
 ******************************************************************************/
void SpiFlash_WriteEnable(void)
{
    SPI_NSS_LOW();
    SpiFlash_WriteReadByte(FLASH_INSTR_WRITE_ENABLE);
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle))
    {
    }
    SPI_NSS_HIGH();
}

/**
 *******************************************************************************
 ** \brief SPI flash wait for write operation end function
 **
 ** \param [in] None
 **
 ** \retval Ok                              Flash internal operation finish
 ** \retval ErrorTimeout                    Flash internal operation timeout
 **
 ******************************************************************************/
en_result_t SpiFlash_WaitForWriteEnd(void)
{
    en_result_t enRet = Ok;
    uint8_t u8Status = 0u;
    uint32_t u32Timeout;
    stc_clk_freq_t stcClkFreq;

    CLK_GetClockFreq(&stcClkFreq);
    u32Timeout = stcClkFreq.sysclkFreq / 1000u;
    SPI_NSS_LOW();
    SpiFlash_WriteReadByte(FLASH_INSTR_READ_SR1);
    do
    {
        u8Status = SpiFlash_WriteReadByte(FLASH_DUMMY_BYTE_VALUE);
        u32Timeout--;
    } while ((u32Timeout != 0ul) &&
             ((u8Status & FLASH_BUSY_BIT_MASK) == FLASH_BUSY_BIT_MASK));

    if (FLASH_BUSY_BIT_MASK == u8Status)
    {
        enRet = ErrorTimeout;
    }
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle))
    {
    }
    SPI_NSS_HIGH();

    return enRet;
}

/**
 *******************************************************************************
 ** \brief SPI flash page write program function
 **
 ** \param [in] u32Addr                     Valid flash address
 **
 ** \param [in] pData                       Pointer to send data buffer
 **
 ** \param [in] len                         Send data length
 **
 ** \retval Error                           Page write program failed
 ** \retval Ok                              Page write program success
 **
 ******************************************************************************/
static en_result_t SpiFlash_WritePage(uint32_t u32Addr, const uint8_t pData[], uint16_t len)
{
    en_result_t enRet = Ok;
    uint16_t u16Index = 0u;

    BUG_ON(len <= FLASH_PAGE_SIZE);

    if ((u32Addr > FLASH_MAX_ADDR) || (NULL == pData) || (len > FLASH_PAGE_SIZE))
    {
        enRet = Error;
    }
    else
    {
        SpiFlash_WriteEnable();
        /* Send data to flash */
        SPI_NSS_LOW();
        SpiFlash_WriteReadByte(FLASH_INSTR_PAGE_PROGRAM);
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF0000ul) >> 16u));
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF00u) >> 8u));
        SpiFlash_WriteReadByte((uint8_t)(u32Addr & 0xFFu));
        while (len--)
        {
            SpiFlash_WriteReadByte(pData[u16Index]);
            u16Index++;
        }
        while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle))
        {
        }
        SPI_NSS_HIGH();
        /* Wait for flash idle */
        enRet = SpiFlash_WaitForWriteEnd();
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief SPI flash read data function
 **
 ** \param [in] u32Addr                     Valid flash address
 **
 ** \param [out] pData                      Pointer to receive data buffer
 **
 ** \param [in] len                         Read data length
 **
 ** \retval Error                           Read data program failed
 ** \retval Ok                              Read data program success
 **
 ******************************************************************************/
static en_result_t SpiFlash_ReadData(uint32_t u32Addr, uint8_t pData[], uint16_t len)
{
    en_result_t enRet = Ok;
    uint16_t u16Index = 0u;

    if ((u32Addr > FLASH_MAX_ADDR) || (NULL == pData))
    {
        enRet = Error;
    }
    else
    {
        SpiFlash_WriteEnable();
        /* Send data to flash */
        SPI_NSS_LOW();
        SpiFlash_WriteReadByte(FLASH_INSTR_STANDARD_READ);
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF0000ul) >> 16u));
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF00u) >> 8u));
        SpiFlash_WriteReadByte((uint8_t)(u32Addr & 0xFFu));
        while (len--)
        {
            pData[u16Index] = SpiFlash_WriteReadByte(FLASH_DUMMY_BYTE_VALUE);
            u16Index++;
        }
        while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle))
        {
        }
        SPI_NSS_HIGH();
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief SPI flash erase 4Kb sector function
 **
 ** \param [in] u32Addr                     Valid flash address
 **
 ** \retval Error                           Sector erase failed
 ** \retval Ok                              Sector erase success
 **
 ******************************************************************************/
static en_result_t SpiFlash_Erase4KbSector(uint32_t u32Addr)
{
    en_result_t enRet = Ok;

    BUG_ON(!AL_IS_ALIGNED(u32Addr, FLASH_SECTOR_SIZE));

    if (u32Addr >= FLASH_MAX_ADDR)
    {
        enRet =  Error;
    }
    else
    {
        SpiFlash_WriteEnable();
        /* Send instruction to flash */
        SPI_NSS_LOW();
        SpiFlash_WriteReadByte(FLASH_INSTR_ERASE_4KB_SECTOR);
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF0000ul) >> 16u));
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF00u) >> 8u));
        SpiFlash_WriteReadByte((uint8_t)(u32Addr & 0xFFu));
        while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle))
        {
        }
        SPI_NSS_HIGH();
        /* Wait for flash idle */
        enRet = SpiFlash_WaitForWriteEnd();
    }

    return enRet;
}

static s32_t spi_flash_read(u32_t addr,u32_t len,u8_t *buf)
{
    uint32_t wp = 0;

    SpiFlash_WriteEnable();
    /* Send data to flash */
    SPI_NSS_LOW();
    SpiFlash_WriteReadByte(FLASH_INSTR_STANDARD_READ);
    SpiFlash_WriteReadByte((uint8_t)((addr & 0xFF0000ul) >> 16u));
    SpiFlash_WriteReadByte((uint8_t)((addr & 0xFF00u) >> 8u));
    SpiFlash_WriteReadByte((uint8_t)(addr & 0xFFu));

    while (len--) {
        buf[wp++] = SpiFlash_WriteReadByte(FLASH_DUMMY_BYTE_VALUE);
    }

    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle));

    SPI_NSS_HIGH();

    return 0;
}

static s32_t spi_flash_write(u32_t addr, u32_t len, u8_t *data)
{
    uint32_t rp = 0;

    BUG_ON(data == NULL);

    SpiFlash_WriteEnable();

    /* Send data to flash */
    SPI_NSS_LOW();
    SpiFlash_WriteReadByte(FLASH_INSTR_PAGE_PROGRAM);
    SpiFlash_WriteReadByte((uint8_t)((addr & 0xFF0000ul) >> 16u));
    SpiFlash_WriteReadByte((uint8_t)((addr & 0xFF00u) >> 8u));
    SpiFlash_WriteReadByte((uint8_t)(addr & 0xFFu));

    while (len--) {
        SpiFlash_WriteReadByte(data[rp++]);
    }

    while (SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle) == Reset);

    SPI_NSS_HIGH();

    /* Wait for flash idle */
    if(SpiFlash_WaitForWriteEnd() != Ok) {
        return -1;
    }

    return 0;
}

static s32_t spi_flash_erase(u32_t addr, u32_t size)
{
    BUG_ON(!AL_IS_ALIGNED(size, FLASH_SECTOR_SIZE));

    int32_t num = size >> 12;

    for (int32_t i = 0; i < num; ++i) {
        if (SpiFlash_Erase4KbSector(addr) != Ok) {
            return -1;
        }

        addr += FLASH_SECTOR_SIZE;
    }

    return 0;
}

static int32_t spi_flash_init(void)
{
    stc_port_init_t stcPortInit;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcPortInit);

    /* Flash NSS */
    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(SPI_NSS_PORT, SPI_NSS_PIN, &stcPortInit);
    SPI_NSS_HIGH();

    /* Configure SPI */
    Spi_Config();

    return 0;
}

static int32_t file_system_init(file_system_t *fs, const char *name,
                                uint32_t addr, size_t size)
{
    int32_t ret;
    spiffs_config config;

    strlcpy(fs->name, name, sizeof(fs->name));

    config.phys_addr = addr;
    config.phys_size = size;
    config.phys_erase_block = SPIFLASH_CFG_PHYS_ERASE_SZ;
    config.log_block_size = SPIFLASH_CFG_LOG_BLOCK_SZ;
    config.log_page_size = SPIFLASH_CFG_LOG_PAGE_SZ;

    config.hal_read_f = spi_flash_read;
    config.hal_write_f = spi_flash_write;
    config.hal_erase_f = spi_flash_erase;

    ret = SPIFFS_mount(&fs->fs, &config, fs->work,
                       fs->fd_space, sizeof(fs->fd_space),
                       fs->cache, sizeof(fs->cache), NULL);
    if (ret != SPIFFS_OK) {
        AL_WARN(1, "%s, %s, SPIFFS_mount failed, errno = %d",
                __func__, fs->name, SPIFFS_errno(&fs->fs));

        AL_WARN(1, "%s, SPIFFS format", fs->name);

        if (SPIFFS_format(&fs->fs) != SPIFFS_OK) {
            AL_ERROR(1, "%s, %s, SPIFFS_format failed, errno = %d",
                     __func__, fs->name, SPIFFS_errno(&fs->fs));
            return -1;
        }

        ret = SPIFFS_mount(&fs->fs, &config, fs->work,
                           fs->fd_space, sizeof(fs->fd_space),
                           fs->cache, sizeof(fs->cache), NULL);

        if (ret != SPIFFS_OK) {
            AL_WARN(1, "%s, %s, SPIFFS_mount failed, errno = %d",
                    __func__, fs->name, SPIFFS_errno(&fs->fs));
            return -1;
        }
    }

    u32_t total, used;

    ret = SPIFFS_info(&fs->fs, &total, &used);
    if ((ret == SPIFFS_OK) && (used > total)) {
        AL_WARN(1, "do spiffs check");

        if (SPIFFS_check(&fs->fs) != SPIFFS_OK) {
            AL_ERROR(1, "%s, %s, SPIFFS_check failed, errno = %d",
                     __func__, fs->name, SPIFFS_errno(&fs->fs));
            return -1;
        }
    }

    return 0;
}

static int32_t file_system_final(file_system_t *fs)
{
    SPIFFS_unmount(&fs->fs);

    return 0;
}

static int spiffs_suite_init(void)
{
    printf("\n");

    spi_flash_init();

    return 0;
}

static int spiffs_suite_clean(void)
{
    file_system_final(&config_fs);
    file_system_final(&config_backup_fs);
    file_system_final(&record_fs);

    return 0;
}

static int32_t spi_flash_write_all(uint8_t byte)
{
    uint32_t flashAddr = 0u;
    uint16_t bufferLen = 0u;
    char txBuffer[FLASH_PAGE_SIZE];
    char rxBuffer[FLASH_PAGE_SIZE];

    /* Get tx buffer length */
    bufferLen = (uint16_t)sizeof(txBuffer);

    while (flashAddr < FLASH_MAX_ADDR) {
        memset(txBuffer, byte, sizeof(txBuffer));
        memset(rxBuffer, 0, sizeof(rxBuffer));

        /* Erase sector */
        SpiFlash_Erase4KbSector(flashAddr);

        for (int32_t i = 0; i < FLASH_SECTOR_SIZE / FLASH_PAGE_SIZE; ++i) {
            /* Write data to flash */
            SpiFlash_WritePage(flashAddr, (uint8_t *)&txBuffer[0], bufferLen);
            /* Read data from flash */
            SpiFlash_ReadData(flashAddr, (uint8_t *)&rxBuffer[0], bufferLen);

            /* Compare txBuffer and rxBuffer */
            if (memcmp(txBuffer, rxBuffer, (uint32_t)bufferLen) != 0) {
                return -1;
            }

            /* Flash address offset */
            flashAddr += FLASH_PAGE_SIZE;
        }
    }

    return 0;
}

static int32_t __file_system_init_test(file_system_t *fs, const char *name,
                                       uint32_t addr, size_t size)
{
    /*
     * 1. all are 0xFF
     * 2. all are 0x00
     * 3. all are random
     * 4. already format
     * 5. corrupted
     */
    AL_DEBUG(1, "test 1: all are 0xFF");
    CU_ASSERT(spi_flash_write_all(0xFF) == 0);
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);
    SPIFFS_unmount(&fs->fs);

    AL_DEBUG(1, "test 2: all are 0x00");
    CU_ASSERT(spi_flash_write_all(0x00) == 0);
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);
    SPIFFS_unmount(&fs->fs);

    AL_DEBUG(1, "test 3: all are random");
    CU_ASSERT(spi_flash_write_all(rand()) == 0);
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);
    SPIFFS_unmount(&fs->fs);

    AL_DEBUG(1, "test4: already format");
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);
    SPIFFS_unmount(&fs->fs);
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);
    SPIFFS_unmount(&fs->fs);

    AL_DEBUG(1, "test5: corrupted");
    uint8_t data[FLASH_PAGE_SIZE] = { 0 };

    CU_ASSERT(SpiFlash_WritePage(addr + (size / 2),
                                 data, sizeof(data)) == Ok);
    CU_ASSERT(SpiFlash_WritePage(addr + size - FLASH_PAGE_SIZE,
                                 data, sizeof(data)) == Ok);
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);

    return 0;
}

static void file_system_init_test(void)
{
    printf("\n");

    __file_system_init_test(&config_fs, "config",
                            SPIFLASH_CFG_CONFIG_PHYS_ADDR,
                            SPIFLASH_CFG_CONFIG_PHYS_SZ);

    __file_system_init_test(&config_backup_fs, "config_backup",
                            SPIFLASH_CFG_CONFIG_BACKUP_PHYS_ADDR,
                            SPIFLASH_CFG_CONFIG_BACKUP_PHYS_SZ);

    __file_system_init_test(&record_fs, "record",
                            SPIFLASH_CFG_RECORD_PHYS_ADDR,
                            SPIFLASH_CFG_RECORD_PHYS_SZ);
}

static int32_t __file_system_unmount_test(file_system_t *fs, const char *name,
                                          uint32_t addr, size_t size)
{
    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);

    file_system_final(fs);

    CU_ASSERT(SPIFFS_mounted(&fs->fs) == 0);

    return 0;
}

static void file_system_unmount_test(void)
{
    printf("\n");

    __file_system_unmount_test(&config_fs, "config",
                            SPIFLASH_CFG_CONFIG_PHYS_ADDR,
                            SPIFLASH_CFG_CONFIG_PHYS_SZ);

    __file_system_unmount_test(&config_backup_fs, "config_backup",
                            SPIFLASH_CFG_CONFIG_BACKUP_PHYS_ADDR,
                            SPIFLASH_CFG_CONFIG_BACKUP_PHYS_SZ);

    __file_system_unmount_test(&record_fs, "record",
                            SPIFLASH_CFG_RECORD_PHYS_ADDR,
                            SPIFLASH_CFG_RECORD_PHYS_SZ);
}

static int32_t __file_system_read_write_test(file_system_t *fs,
                                             const char *name,
                                             uint32_t addr, size_t size)
{
    uint8_t wr_data[1024], rd_data[1024];

    for (int32_t i = 0; i < sizeof(wr_data); ++i) {
        wr_data[i] = rand();
    }

    memset(rd_data, 0, sizeof(rd_data));

    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);

    spiffs_file fd = SPIFFS_open(&fs->fs, "/test",
                                 SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);
    CU_ASSERT(fd >= 0);

    CU_ASSERT(SPIFFS_write(&fs->fs, fd,
                           wr_data, sizeof(wr_data)) == sizeof(wr_data));

    CU_ASSERT(SPIFFS_fflush(&fs->fs, fd) == 0);
    CU_ASSERT(SPIFFS_close(&fs->fs, fd) == 0);

    CU_ASSERT(SPIFFS_open(&fs->fs, "/test", SPIFFS_RDWR, 0) >= 0);

    CU_ASSERT(SPIFFS_read(&fs->fs, fd,
                          rd_data, sizeof(rd_data)) == sizeof(rd_data));

    CU_ASSERT(memcmp(wr_data, rd_data, sizeof(wr_data)) == 0);

    CU_ASSERT(SPIFFS_close(&fs->fs, fd) == 0);
}

static void file_system_read_write_test(void)
{
    printf("\n");

    __file_system_read_write_test(&config_fs, "config",
                                  SPIFLASH_CFG_CONFIG_PHYS_ADDR,
                                  SPIFLASH_CFG_CONFIG_PHYS_SZ);

    __file_system_read_write_test(&config_backup_fs, "config_backup",
                                  SPIFLASH_CFG_CONFIG_BACKUP_PHYS_ADDR,
                                  SPIFLASH_CFG_CONFIG_BACKUP_PHYS_SZ);

    __file_system_read_write_test(&record_fs, "record",
                                  SPIFLASH_CFG_RECORD_PHYS_ADDR,
                                  SPIFLASH_CFG_RECORD_PHYS_SZ);
}

static int32_t __spiffs_info_test(file_system_t *fs, const char *name,
                                  uint32_t addr, size_t size)
{
    u32_t total, used;

    CU_ASSERT(file_system_init(fs, name, addr, size) == 0);
    CU_ASSERT(SPIFFS_info(&fs->fs, &total, &used) == 0);

    AL_INFO(1, "spiffs usage, %s, total = %u, used = %u\n", name, total, used);

    CU_ASSERT(used <= total);
}

static void file_system_usage_test(void)
{
    printf("\n");

    __spiffs_info_test(&config_fs, "config",
                       SPIFLASH_CFG_CONFIG_PHYS_ADDR,
                       SPIFLASH_CFG_CONFIG_PHYS_SZ);

    __spiffs_info_test(&config_backup_fs, "config_backup",
                       SPIFLASH_CFG_CONFIG_BACKUP_PHYS_ADDR,
                       SPIFLASH_CFG_CONFIG_BACKUP_PHYS_SZ);

    __spiffs_info_test(&record_fs, "record",
                       SPIFLASH_CFG_RECORD_PHYS_ADDR,
                       SPIFLASH_CFG_RECORD_PHYS_SZ);
}

__used static void spi_flash_test(void)
{
    uint32_t flashAddr = 0u;
    uint16_t bufferLen = 0u;
    char txBuffer[128];
    char rxBuffer[128];

    /* Get tx buffer length */
    bufferLen = (uint16_t)sizeof(txBuffer);

    while (flashAddr < FLASH_MAX_ADDR) {
        for (int32_t i = 0; i < sizeof(txBuffer); ++i) {
            txBuffer[i] = rand();
        }

        memset(rxBuffer, 0, sizeof(rxBuffer));

        /* Erase sector */
        SpiFlash_Erase4KbSector(flashAddr);
        /* Write data to flash */
        SpiFlash_WritePage(flashAddr, (uint8_t *)&txBuffer[0], bufferLen);
        /* Read data from flash */
        SpiFlash_ReadData(flashAddr, (uint8_t *)&rxBuffer[0], bufferLen);
        /* Compare txBuffer and rxBuffer */
        CU_ASSERT(memcmp(txBuffer, rxBuffer, (uint32_t)bufferLen) == 0);

        /* Flash address offset */
        flashAddr += FLASH_SECTOR_SIZE;
    }
}

static int32_t add_spiffs_tests(void)
{
    CU_pSuite suite;

    suite = CU_add_suite("spiffs", spiffs_suite_init, spiffs_suite_clean);

    CU_add_test(suite, "spi_flash_test", spi_flash_test);
    CU_add_test(suite, "file_system_init_test", file_system_init_test);
    CU_add_test(suite, "file_system_unmount_test", file_system_unmount_test);
    CU_add_test(suite,
                "file_system_read_write_test", file_system_read_write_test);
    CU_add_test(suite, "file_system_usage_test", file_system_usage_test);

    return 0;
}

al_test_suite_init(add_spiffs_tests);

#endif

__END_DECLS

