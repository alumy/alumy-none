set(target bsp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/syscalls)

FILE(GLOB_RECURSE ${target}_src 
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/*.c)
	
set(${target}_src ${${target}_src} 
	${CMAKE_CURRENT_SOURCE_DIR}/startup/startup_stm32f411xe.s
	${CMAKE_CURRENT_SOURCE_DIR}/system/system_stm32f4xx.c)

set(${target}_src ${${target}_src} 
	${CMAKE_CURRENT_SOURCE_DIR}/segger/RTT/SEGGER_RTT.c
	${CMAKE_CURRENT_SOURCE_DIR}/segger/RTT/SEGGER_RTT_printf.c)

add_definitions(-DXTAL_VALUE=12000000ul)
add_definitions(-DAL_TEST_DRIVER=1)

add_library(${target} STATIC ${${target}_src})
target_link_libraries(${target} PRIVATE ${PROJECT_NAME}-static unity cmock)
target_compile_options(${target} PRIVATE
	-Wno-comment -Wno-format -Wno-strict-aliasing -Wno-unused-but-set-variable)

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/segger/RTT
	${CMAKE_CURRENT_SOURCE_DIR}/bsp/include
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include)

gdbinit(${PROJECT_NAME}-test)
debug(${PROJECT_NAME}-test)
gdbserver("STM32F411CE")
jflash("STM32F411CE" ${PROJECT_NAME}-test)
flash("STM32F411CE" ${PROJECT_NAME}-test)
