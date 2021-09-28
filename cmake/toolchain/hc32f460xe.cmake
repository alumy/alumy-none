cmake_minimum_required(VERSION 2.8)

set(CPU "-mcpu=cortex-m4" CACHE STRING "" FORCE)
set(FPU "-mfpu=fpv4-sp-d16" CACHE STRING "" FORCE)
set(FLOAT-ABI "-mfloat-abi=hard" CACHE STRING "" FORCE)
set(MCU "${CPU} -mthumb ${FPU} ${FLOAT-ABI}" CACHE STRING "" FORCE)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/test/bsp/hc32f460xe/hc32f460xe_flash.ld CACHE STRING "" FORCE)
set(BSP_DIR ${PROJECT_SOURCE_DIR}/test/bsp/hc32f460xe CACHE STRING "" FORCE)

add_definitions(-DUSE_DEVICE_DRIVER_LIB)
add_definitions(-DHC32F460)
add_definitions(-DCMB_CPU_PLATFORM_TYPE=CMB_CPU_ARM_CORTEX_M4)
add_definitions(-DAL_HAVE_SYS_CDEFS=1)
add_definitions(-DAL_HAVE_SYS_TYPES=1)
add_definitions(-DAL_USE_ERRNO=0)

include(${CMAKE_CURRENT_LIST_DIR}/hc32/hc32.cmake)

