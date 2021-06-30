set(target driver)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/*.c)

add_library(${target} STATIC ${${target}_src})

target_link_libraries(${target} PUBLIC system)

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Inc
	${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Inc/Legacy
	${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F1xx/Include
	${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
