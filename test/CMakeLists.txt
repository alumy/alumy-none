#############################################################################
# test for libalumy
#############################################################################
include(${PROJECT_SOURCE_DIR}/cmake/cmock.cmake)

# mock
# mock(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
#     MOCK_HEADER_FILES ${PROJECT_SOURCE_DIR}/include/alumy/bcd.h)

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    message(STATUS "Building test for Linux")
	
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/portal)

    aux_source_directory(${PROJECT_SOURCE_DIR}/test test_src)

    add_executable(${PROJECT_NAME}-test ${test_src} ${mock_src})

    target_link_libraries(${PROJECT_NAME}-test PRIVATE portal unity cmock)
    target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}-static)
	
    target_include_directories(${PROJECT_NAME}-test PUBLIC ${mock_inc})
 
    add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/covgen.sh ${CMAKE_BINARY_DIR}
        COMMENT "Copying covgen.sh to calculate coverage")

    add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/cunit/xml/* ${CMAKE_BINARY_DIR}
        COMMENT "Copying cunit resources")
		
    add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/* ${CMAKE_BINARY_DIR}
        COMMENT "Copying configurations")
	
	add_test(NAME test_alumy COMMAND ${PROJECT_NAME}-test)
	set_tests_properties(test_alumy PROPERTIES PASS_REGULAR_EXPRESSION 0)

    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
	add_test(NAME test_cov COMMAND ${CMAKE_BINARY_DIR}/covgen.sh ${CMAKE_BINARY_DIR})
        set_tests_properties (test_cov PROPERTIES PASS_REGULAR_EXPRESSION 0)
    endif()

endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Generic)
    message(STATUS "Building test for Generic")

    add_subdirectory(${BSP_DIR})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/portal)

    aux_source_directory(${PROJECT_SOURCE_DIR}/test test_src)

    add_executable(${PROJECT_NAME}-test ${test_src})
    add_dependencies(${PROJECT_NAME}-test mock)

    target_link_libraries(${PROJECT_NAME}-test PRIVATE 
                          -Wl,--whole-archive
                          bsp  portal
                          -Wl,--no-whole-archive)

    target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}-static)

    add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/covgen.sh ${CMAKE_BINARY_DIR}
        COMMENT "Copying covgen.sh to calculate coverage")

	add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/cunit/xml/* ${CMAKE_BINARY_DIR}
        COMMENT "Copying cunit resources")
			
	add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test.hex
        COMMENT "Object copying to ${PROJECT_NAME}-test.bin and ${PROJECT_NAME}-test.hex")

	add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_SIZE} --format=berkeley ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test.hex
        COMMENT "Parsing program size:")
		
	add_custom_command(TARGET ${PROJECT_NAME}-test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/* ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Copying configurations")
endif()

