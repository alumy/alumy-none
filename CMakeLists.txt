#############################################################################
# Toolchain file
#############################################################################
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

cmake_minimum_required(VERSION 3.5)

project(alumy C ASM)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION_TWEAK 10)
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

include(GNUInstallDirs)
include(${PROJECT_SOURCE_DIR}/cmake/message.cmake)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

if(EXISTS "${PROJECT_SOURCE_DIR}/.svn/")
	find_package(Subversion)
	
	if(SUBVERSION_FOUND)
		Subversion_WC_INFO(${PROJECT_SOURCE_DIR} PROJ)
		set(SVN_VERSION ${PROJ_WC_REVISION})
	endif(SUBVERSION_FOUND)
endif(EXISTS "${PROJECT_SOURCE_DIR}/.svn/")

configure_file(
	${PROJECT_SOURCE_DIR}/include/alumy/version.h.in
	${PROJECT_SOURCE_DIR}/include/alumy/version.h)

add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DALUMY_USE_DEFAULT_CONFIG)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	link_libraries(rt)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/crc)
add_subdirectory(${PROJECT_SOURCE_DIR}/mem)
add_subdirectory(${PROJECT_SOURCE_DIR}/string)
add_subdirectory(${PROJECT_SOURCE_DIR}/bcd)
add_subdirectory(${PROJECT_SOURCE_DIR}/base64)
add_subdirectory(${PROJECT_SOURCE_DIR}/unity)
add_subdirectory(${PROJECT_SOURCE_DIR}/cunit)
add_subdirectory(${PROJECT_SOURCE_DIR}/sys)
add_subdirectory(${PROJECT_SOURCE_DIR}/cjson)

#############################################################################
# libalumy
#############################################################################

set(objs 
		$<TARGET_OBJECTS:unity>
		$<TARGET_OBJECTS:cunit>
		$<TARGET_OBJECTS:crc>
		$<TARGET_OBJECTS:mem>
		$<TARGET_OBJECTS:string>
		$<TARGET_OBJECTS:bcd>
		$<TARGET_OBJECTS:sys>
		$<TARGET_OBJECTS:base64>
		$<TARGET_OBJECTS:cjson>)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_src)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	message(STATUS "Building static library for Linux")

	add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_src} ${objs})
	
	set_target_properties(${PROJECT_NAME} PROPERTIES 
			VERSION "${PROJECT_VERSION}"
			SOVERSION "${PROJECT_VERSION_MAJOR}")

	install(TARGETS "${PROJECT_NAME}" 
			DESTINATION "${CMAKE_INSTALL_LIBDIR}" 
			EXPORT "${PROJECT_NAME}")
endif()

add_library("${PROJECT_NAME}-static" STATIC ${${PROJECT_NAME}_src} ${objs})
# target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
# target_compile_options(<target> [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

set_target_properties("${PROJECT_NAME}-static" PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
set_target_properties("${PROJECT_NAME}-static" PROPERTIES PREFIX "lib")

install(TARGETS "${PROJECT_NAME}-static" 
		DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
		DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
		FILES_MATCHING PATTERN "*.h")

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR alumy)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/gpl-3.0.txt")
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

add_subdirectory(${PROJECT_SOURCE_DIR}/test)

