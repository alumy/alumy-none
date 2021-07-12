set(target startup)

set(${target}_src
	${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c
	${CMAKE_CURRENT_SOURCE_DIR}/startup_hc32f460_gcc.S)

add_library(${target} STATIC ${${target}_src})

# target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
