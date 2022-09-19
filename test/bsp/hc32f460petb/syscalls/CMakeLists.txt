set(target syscalls)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(${target} STATIC ${${target}_src})

target_compile_options(${target} PRIVATE -flto -fno-builtin)

