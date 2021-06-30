set(target startup)

FILE (GLOB_RECURSE ${target}_src
	${CMAKE_CURRENT_SOURCE_DIR}/*.s
	${CMAKE_CURRENT_SOURCE_DIR}/*.S
	${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(${target} STATIC ${${target}_src})

# target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
