cmake_minimum_required(VERSION 2.8)

set(CPU "-mcpu=cortex-m3" CACHE STRING "" FORCE)
set(MCU "${CPU} -mthumb" CACHE STRING "" FORCE)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/test/bsp/stm32f103c8tx/STM32F103C8Tx_FLASH.ld CACHE STRING "" FORCE)
set(BSP_DIR ${PROJECT_SOURCE_DIR}/test/bsp/stm32f103c8tx CACHE STRING "" FORCE)
set(OSAL_DIR ${PROJECT_SOURCE_DIR}/osal/none CACHE STRING "" FORCE)

add_definitions(-DUSE_HAL_DRIVER)
add_definitions(-DSTM32F103xB)

include(${CMAKE_CURRENT_LIST_DIR}/stm32/stm32.cmake)
