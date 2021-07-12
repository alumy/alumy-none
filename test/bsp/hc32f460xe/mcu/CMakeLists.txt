set(target mcu)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/common/*.c)

add_library(${target} STATIC ${${target}_src})

target_link_libraries(${target} PRIVATE driver)

target_include_directories(${target} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/common
	${CMAKE_CURRENT_SOURCE_DIR}/GCC/CMSIS/Core/Include)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
