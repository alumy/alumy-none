set(target bsp)

FILE(GLOB_RECURSE ${target}_src 
	${CMAKE_CURRENT_SOURCE_DIR}/bsp/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/driver/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/mcu/common/*.c)
	
set(${target}_src ${${target}_src} 
	${CMAKE_CURRENT_SOURCE_DIR}/startup/startup_hc32f460_gcc.S
	${CMAKE_CURRENT_SOURCE_DIR}/syscalls/syscalls.c)

set(${target}_src ${${target}_src} 
	${CMAKE_CURRENT_SOURCE_DIR}/segger/RTT/SEGGER_RTT.c
	${CMAKE_CURRENT_SOURCE_DIR}/segger/RTT/SEGGER_RTT_printf.c)

add_definitions(-DXTAL_VALUE=12000000ul)
add_definitions(-DAL_TEST_DRIVER=1)

add_library(${target} STATIC ${${target}_src})
target_link_libraries(${target} PRIVATE unity cmock)

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/segger/RTT
	${CMAKE_CURRENT_SOURCE_DIR}/bsp/include
	${CMAKE_CURRENT_SOURCE_DIR}/driver/inc
	${CMAKE_CURRENT_SOURCE_DIR}/mcu/common
	${CMAKE_CURRENT_SOURCE_DIR}/mcu/GCC/CMSIS/Core/Include)

debug(${PROJECT_NAME}-test)
gdbserver("HC32F460XE")
jflash("HC32F460XE" ${PROJECT_NAME}-test)
flash("HC32F460XE" ${PROJECT_NAME}-test)

