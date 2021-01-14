set(target cunit)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/Automated/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/Basic/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/Console/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/Framework/*.c)

add_library(${target} OBJECT ${${target}_src})

target_compile_options(${target} PRIVATE -Wno-format)
