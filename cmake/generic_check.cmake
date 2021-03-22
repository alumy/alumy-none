
if(${CMAKE_SYSTEM_NAME} STREQUAL "Generic")
	message(STATUS "Checking for generic ${LINKER_SCRIPT}")

	# throw error when the linker script not exist 
	if((NOT EXISTS ${LINKER_SCRIPT}) OR (IS_DIRECTORY ${LINKER_SCRIPT}))
		MESSAGE(FATAL_ERROR  "linker script must be specfied for generic")
	endif()
	
endif()

