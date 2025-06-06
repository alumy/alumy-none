#############################################################################
# Toolchain file
#############################################################################
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

cmake_minimum_required(VERSION 3.5)

project(alumy C ASM)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 9)
set(PROJECT_VERSION_TWEAK 20)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

#############################################################################
# Check for linux
#############################################################################
include(${PROJECT_SOURCE_DIR}/cmake/linux_check.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/generic_check.cmake)

#############################################################################
# Parameter for compile
#############################################################################

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "64 bits cpu")
    set(CMAKE_INSTALL_LIBDIR lib64)
else()
    message(STATUS "32 bits cpu")
    set(CMAKE_INSTALL_LIBDIR lib)
endif()

if(UNIT_TEST EQUAL 1)
	add_definitions(-DAL_UT)
endif()

include(GNUInstallDirs)
include(${PROJECT_SOURCE_DIR}/cmake/message.cmake)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

configure_file(
    ${PROJECT_SOURCE_DIR}/include/alumy/version.h.in
    ${PROJECT_SOURCE_DIR}/include/alumy/version.h)

#######################################################################
# get svn revision
#######################################################################
add_custom_command(
    OUTPUT ${PROJECT_SOURCE_DIR}/include/alumy/svn_revision.h
    ALL
    COMMAND ${CMAKE_COMMAND} -D TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/cmake/svn-revision.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# rebuild svn_revision.h every time
add_custom_target(get_svn_revision
    ALL
    DEPENDS ${PROJECT_SOURCE_DIR}/include/alumy/svn_revision.h
)

#####################################################################
# get git hash
#####################################################################
add_custom_command(
    OUTPUT ${PROJECT_SOURCE_DIR}/include/alumy/git_hash.h
    ALL
    COMMAND ${CMAKE_COMMAND} -D TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${PROJECT_SOURCE_DIR}/cmake/git-hash.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# rebuild git_hash.h every time
add_custom_target(get_git_hash
    ALL
    DEPENDS ${PROJECT_SOURCE_DIR}/include/alumy/git_hash.h
)

add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DAL_USE_DEFAULT_CONFIG)
add_definitions(-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/mbedtls-3.2.1/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/letter-shell-3.1.2/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/lwip-2.1.3/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/freemodbus/modbus/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/littlefs-2.9.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/qpn/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/port/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/tinyprintf)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/protobuf-c/protobuf-c)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    link_libraries(rt)
endif()

link_libraries(m)

add_subdirectory(${PROJECT_SOURCE_DIR}/3rd-party)
add_subdirectory(${PROJECT_SOURCE_DIR}/crypto)
add_subdirectory(${PROJECT_SOURCE_DIR}/crc)
add_subdirectory(${PROJECT_SOURCE_DIR}/lrc)
add_subdirectory(${PROJECT_SOURCE_DIR}/mem)
add_subdirectory(${PROJECT_SOURCE_DIR}/math)
add_subdirectory(${PROJECT_SOURCE_DIR}/sys)
add_subdirectory(${PROJECT_SOURCE_DIR}/filter)
add_subdirectory(${PROJECT_SOURCE_DIR}/string)
add_subdirectory(${PROJECT_SOURCE_DIR}/bcd)
add_subdirectory(${PROJECT_SOURCE_DIR}/base64)
add_subdirectory(${PROJECT_SOURCE_DIR}/unity)
add_subdirectory(${PROJECT_SOURCE_DIR}/cmock)
add_subdirectory(${PROJECT_SOURCE_DIR}/cunit)
add_subdirectory(${PROJECT_SOURCE_DIR}/cjson)
add_subdirectory(${PROJECT_SOURCE_DIR}/fs)
add_subdirectory(${PROJECT_SOURCE_DIR}/driver)
add_subdirectory(${PROJECT_SOURCE_DIR}/libcsv)
add_subdirectory(${PROJECT_SOURCE_DIR}/pid)
add_subdirectory(${PROJECT_SOURCE_DIR}/lzma)
add_subdirectory(${PROJECT_SOURCE_DIR}/xyzmodem)
add_subdirectory(${PROJECT_SOURCE_DIR}/time)
add_subdirectory(${PROJECT_SOURCE_DIR}/net)
add_subdirectory(${PROJECT_SOURCE_DIR}/expect)
add_subdirectory(${PROJECT_SOURCE_DIR}/bitops)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)

#############################################################################
# libalumy
#############################################################################

set(objs
		$<TARGET_OBJECTS:3rd-party>
		$<TARGET_OBJECTS:sys>
		$<TARGET_OBJECTS:crypto>
		$<TARGET_OBJECTS:cunit>
		$<TARGET_OBJECTS:crc>
		$<TARGET_OBJECTS:lrc>
		$<TARGET_OBJECTS:mem>
		$<TARGET_OBJECTS:math>
		$<TARGET_OBJECTS:filter>
		$<TARGET_OBJECTS:string>
		$<TARGET_OBJECTS:bcd>
		$<TARGET_OBJECTS:base64>
		$<TARGET_OBJECTS:cjson>
		$<TARGET_OBJECTS:driver>
		$<TARGET_OBJECTS:libcsv>
		$<TARGET_OBJECTS:fs>
		$<TARGET_OBJECTS:pid>
		$<TARGET_OBJECTS:lzma>
		$<TARGET_OBJECTS:xyzmodem>
		$<TARGET_OBJECTS:time>
		$<TARGET_OBJECTS:net>
		$<TARGET_OBJECTS:expect>
		$<TARGET_OBJECTS:lib>
		$<TARGET_OBJECTS:bitops>)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_src)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    message(STATUS "Building static library for Linux")

    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_src} ${objs})

    add_dependencies(${PROJECT_NAME} get_git_hash)
    add_dependencies(${PROJECT_NAME} get_svn_revision)

    set_target_properties(${PROJECT_NAME} PROPERTIES
            VERSION "${PROJECT_VERSION}"
            SOVERSION "${PROJECT_VERSION_MAJOR}")

    install(TARGETS "${PROJECT_NAME}"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            EXPORT "${PROJECT_NAME}")
endif()

add_library("${PROJECT_NAME}-static" STATIC ${${PROJECT_NAME}_src} ${objs})

add_dependencies("${PROJECT_NAME}-static" get_git_hash)
add_dependencies("${PROJECT_NAME}-static" get_svn_revision)

# target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
# target_compile_options(<target> [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

set_target_properties("${PROJECT_NAME}-static" PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
set_target_properties("${PROJECT_NAME}-static" PROPERTIES PREFIX "lib")

install(TARGETS "${PROJECT_NAME}-static"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h")
		
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/letter-shell-3.1.2/src/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/letter-shell"
        FILES_MATCHING PATTERN "*.h")
		
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/mbedtls-3.2.1/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/mbedtls"
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/lwip-2.1.3/src/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/lwip"
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/contrib-2.1.0/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/contrib"
        FILES_MATCHING
		PATTERN "*.h"
		PATTERN "ports" EXCLUDE
		PATTERN "examples" EXCLUDE
		PATTERN "Coverity" EXCLUDE
		PATTERN "apps/LwipMibCompiler" EXCLUDE)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/port/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/port"
        FILES_MATCHING PATTERN "*.h")
		
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/freemodbus/modbus/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/freemodbus"
        FILES_MATCHING 
		PATTERN "*.h"
		PATTERN "port/port.h")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/freemodbus/port/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/freemodbus"
        FILES_MATCHING PATTERN "port.h")
		
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/qpn/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "qepn.h" PATTERN "qpn_conf.h" PATTERN "qassert.h")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/paho.mqtt.embedded-c-1.1.0/MQTTPacket/src/
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MQTTPacket"
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/tinyprintf/
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/protobuf-c/protobuf-c/
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h")

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR alumy)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CHECKSUM "SHA256")
set(CPACK_GENERATOR "STGZ;TGZ;TZ")

set(CPACK_SOURCE_IGNORE_FILES
    ${PROJECT_SOURCE_DIR}/build
    ${PROJECT_SOURCE_DIR}/pack
    ${PROJECT_SOURCE_DIR}/.svn)
set(CPACK_SOURCE_GENERATOR "TGZ")

include(CPack)

if(UNIT_TEST EQUAL 1)
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()


