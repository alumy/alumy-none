#############################################################################
# test for libalumy
#############################################################################
if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	message(STATUS "Building test for Linux")
	
	aux_source_directory(${PROJECT_SOURCE_DIR}/test test_src)

	add_executable(${PROJECT_NAME}-test ${test_src} ${${PROJECT_NAME}_src})

	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/covgen.sh ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying covgen.sh to calculate coverage")

	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/cunit/xml/* ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying cunit resources")
		
	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/* ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying configurations")

	target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})

	enable_testing()

	add_test(test_alumy alumy-test)
	set_tests_properties (test_alumy PROPERTIES PASS_REGULAR_EXPRESSION 0)
		
	add_test(test_cov "${CMAKE_CURRENT_BINARY_DIR}/covgen.sh")
	set_tests_properties (test_cov PROPERTIES PASS_REGULAR_EXPRESSION 0)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Generic)
	message(STATUS "Building test for Generic")
	
	aux_source_directory(${PROJECT_SOURCE_DIR}/test test_src)

	add_executable(${PROJECT_NAME}-test ${test_src} ${${PROJECT_NAME}_src})

	target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME}-static)

	 add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/covgen.sh ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying covgen.sh to calculate coverage")

	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tools/cunit/xml/* ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying cunit resources")
			
	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}-test ${PROJECT_NAME}-test.bin
			COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}-test ${PROJECT_NAME}-test.hex
			COMMENT "Object copying to ${PROJECT_NAME}-test.bin and ${PROJECT_NAME}-test.hex")
			
	add_custom_command(TARGET ${PROJECT_NAME}-test
		POST_BUILD
		COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}-test ${PROJECT_NAME}-test.hex
		COMMENT "Parsing program size:")
		
	add_custom_command(TARGET ${PROJECT_NAME}-test
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/* ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Copying configurations")

	#enable_testing()

	#add_test(test_alumy alumy-test.elf)
	#add_test(test_cov "${CMAKE_CURRENT_BINARY_DIR}/covgen.sh")
	# set_tests_properties (test_cov
	#	PROPERTIES PASS_REGULAR_EXPRESSION "Test coverage")
endif()