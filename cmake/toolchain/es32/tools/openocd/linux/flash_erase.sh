#!/bin/bash

#xxx.hex or xxx.bin

#es32f0654lt
FLASH_ADDR=0x00000000
FLASH_SIZE=0x00020000 #256KB

CURRENT_DIR=$(cd $(dirname $0); pwd)

CONFIG=${CURRENT_DIR}/../target/es32f065x_cmsis_dap.cfg

ESLINKII_CONFIG=${CURRENT_DIR}/../eslink-ii.cfg

sudo openocd -s ${CURRENT_DIR}/../ -f ${ESLINKII_CONFIG} -f ${CONFIG} -c \
"   init;
    halt;
    reset halt;
    flash erase_address ${FLASH_ADDR} ${FLASH_SIZE};
    shutdown;
"

