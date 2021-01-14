#############################################################################
# Toolchain file
#############################################################################
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

cmake_minimum_required(VERSION 2.8)

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

#############################################################################
# Parameter for compile
#############################################################################
# Project root directory
set(ROOT_DIR ${PROJECT_SOURCE_DIR}/../..)

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

if(EXISTS "${ROOT_DIR}/.svn/")
	find_package(Subversion)
	
	if(SUBVERSION_FOUND)
		Subversion_WC_INFO(${ROOT_DIR} PROJ)
		set(SVN_VERSION ${PROJ_WC_REVISION})
	endif(SUBVERSION_FOUND)
endif(EXISTS "${ROOT_DIR}/.svn/")

configure_file(
	${PROJECT_SOURCE_DIR}/include/alumy/version.h.in
	${PROJECT_SOURCE_DIR}/include/alumy/version.h)

add_definitions(-D__STDC_FORMAT_MACROS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	include_directories(${ROOTFS_DIR}/usr/include)
	include_directories(${ROOTFS_DIR}/usr/local/include)

	link_directories(
			${ROOTFS_DIR}/usr/lib
			${ROOTFS_DIR}/usr/lib64
			${ROOTFS_DIR}/usr/local/lib
			${ROOTFS_DIR}/usr/local/lib64)

	link_libraries(cunit rt curl)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/crc)
add_subdirectory(${PROJECT_SOURCE_DIR}/mem)
add_subdirectory(${PROJECT_SOURCE_DIR}/string)
add_subdirectory(${PROJECT_SOURCE_DIR}/bcd)
add_subdirectory(${PROJECT_SOURCE_DIR}/base64)
add_subdirectory(${PROJECT_SOURCE_DIR}/unity)
add_subdirectory(${PROJECT_SOURCE_DIR}/sys)

#############################################################################
# libalumy
#############################################################################

set(objs 
		$<TARGET_OBJECTS:unity>
		$<TARGET_OBJECTS:crc>
		$<TARGET_OBJECTS:mem>
		$<TARGET_OBJECTS:string>
		$<TARGET_OBJECTS:bcd>
		$<TARGET_OBJECTS:sys>
		$<TARGET_OBJECTS:base64>)

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

#############################################################################
# test for libalumy
#############################################################################
if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	message(STATUS "Building test for Linux")
	
	aux_source_directory(${PROJECT_SOURCE_DIR}/test test_src)

	add_executable(${PROJECT_NAME}-test ${test_src} ${${PROJECT_NAME}_src})

	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/tools/covgen.sh .
			COMMENT "Copying covgen.sh to calculate coverage")

	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/tools/cunit/xml/* .
			COMMENT "Copying cunit resources")
		
	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/config/* .
			COMMENT "Copying configurations")

	target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})

	enable_testing()

	add_test(test_alumy alumy-test)
	add_test(test_cov "${CMAKE_CURRENT_BINARY_DIR}/covgen.sh")
	# set_tests_properties (test_cov
	#	PROPERTIES PASS_REGULAR_EXPRESSION "Test coverage")
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Generic)
	message(STATUS "Building test for Generic")
	
	aux_source_directory(${PROJECT_SOURCE_DIR}/test test_src)

	add_executable(${PROJECT_NAME}-test.elf ${test_src} ${${PROJECT_NAME}_src})
	
	target_link_libraries(${PROJECT_NAME}-test.elf ${PROJECT_NAME}-static)

	 add_custom_command(TARGET ${PROJECT_NAME}-test.elf
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/covgen.sh ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying covgen.sh to calculate coverage")

	add_custom_command(TARGET ${PROJECT_NAME}-test.elf
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/cunit/xml/* ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying cunit resources")
			
	add_custom_command(TARGET ${PROJECT_NAME}-test.elf
			POST_BUILD
			COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}-test.elf ${PROJECT_NAME}-test.bin
			COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}-test.elf ${PROJECT_NAME}-test.hex
			COMMENT "Building ${PROJECT_NAME}-test.bin and ${PROJECT_NAME}-test.hex")
			
	add_custom_command(TARGET ${PROJECT_NAME}-test.elf
			POST_BUILD
			COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}-test.elf ${PROJECT_NAME}-test.hex
			COMMENT "Parsing program size:")
		
	add_custom_command(TARGET ${PROJECT_NAME}-test.elf
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/* ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying configurations")

	#enable_testing()

	#add_test(test_alumy alumy-test.elf)
	#add_test(test_cov "${CMAKE_CURRENT_BINARY_DIR}/covgen.sh")
	# set_tests_properties (test_cov
	#	PROPERTIES PASS_REGULAR_EXPRESSION "Test coverage")
endif()
