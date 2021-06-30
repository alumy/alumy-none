cmake_minimum_required(VERSION 2.8)

set(CPU "-mcpu=cortex-m3" CACHE STRING "" FORCE)
set(MCU "${CPU} -mthumb" CACHE STRING "" FORCE)

set(FLASH_SIZE "262144" CACHE STRING "" FORCE)
set(IAP_CORE "Cortex-M3" CACHE STRING "" FORCE)
set(IAP_HEX ${PROJECT_SOURCE_DIR}/cmake/toolchain/es32/iap/ES32F065x.hex CACHE STRING "" FORCE)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/test/bsp/es32f0654/es32f0654lt.ld CACHE STRING "" FORCE)
set(BSP_DIR ${PROJECT_SOURCE_DIR}/test/bsp/es32f0654 CACHE STRING "" FORCE)

add_definitions(-DES32F065x)

include(${CMAKE_CURRENT_LIST_DIR}/es32/es32.cmake)


