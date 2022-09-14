set(target 3rd-party)

# set(LWIP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lwip-2.1.3)
# include(lwip.cmake)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library/*.c)

add_library(${target} OBJECT ${${target}_src})

target_include_directories(${target}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/include)

