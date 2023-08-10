set(target 3rd-party)

set(LWIP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lwip-2.1.3)
set(LWIP_CONTRIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib-2.1.0)
include(${CMAKE_CURRENT_SOURCE_DIR}/lwip.cmake)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/port/*.c)

add_library(${target} OBJECT ${${target}_src} ${lwipsrc} ${lwipcontribsrc})
target_compile_options(${target} PRIVATE
	-Wno-format -Wno-strict-aliasing -Wno-unused-const-variable -Wno-unused-function)

target_include_directories(${target}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lwip-2.1.3/src/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/port/include)
