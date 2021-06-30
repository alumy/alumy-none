set(target driver)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_library(${target} STATIC ${${target}_src})

target_link_libraries(${target} PUBLIC mcu)

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
