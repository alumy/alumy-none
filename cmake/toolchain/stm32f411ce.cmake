# cmake_minimum_required(VERSION 2.8)

set(CPU "-mcpu=cortex-m4" CACHE STRING "" FORCE)
set(FPU "-mfpu=fpv4-sp-d16" CACHE STRING "" FORCE)
set(FLOAT-ABI "-mfloat-abi=hard" CACHE STRING "" FORCE)
set(MCU "${CPU} -mthumb ${FPU} ${FLOAT-ABI}" CACHE STRING "" FORCE)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/test/bsp/stm32f411ce/STM32F411CEUx_FLASH.ld CACHE STRING "" FORCE)
set(BSP_DIR ${PROJECT_SOURCE_DIR}/test/bsp/stm32f411ce CACHE STRING "" FORCE)
set(OSAL_DIR ${PROJECT_SOURCE_DIR}/osal/none CACHE STRING "" FORCE)

add_definitions(-DUSE_HAL_DRIVER)
add_definitions(-DSTM32F411xE)
add_definitions(-DCMB_CPU_PLATFORM_TYPE=CMB_CPU_ARM_CORTEX_M4)
add_definitions(-DAL_HAVE_SYS_CDEFS=1)
add_definitions(-DAL_HAVE_SYS_TYPES=1)
add_definitions(-DAL_PROVIDE_ERRNO=0)

include(${CMAKE_CURRENT_LIST_DIR}/stm32/stm32.cmake)

function(gdbinit proj_name)
add_custom_target(gdbinit
		COMMAND ${CMAKE_COMMAND} -E copy
			${PROJECT_SOURCE_DIR}/cmake/toolchain/stm32/stm32f411ce_gdb_cmd
			${CMAKE_BINARY_DIR}/.gdbinit
		DEPENDS ${proj_name})
endfunction(gdbinit)

