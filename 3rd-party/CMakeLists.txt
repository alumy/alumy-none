set(target 3rd-party)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library/*.c)

add_library(${target} OBJECT ${${target}_src})

target_include_directories(${target}
	PUBLIC	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src>
		$<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/include>
		$<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src>
    	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library)

