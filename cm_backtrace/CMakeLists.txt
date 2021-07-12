set(target cm_backtrace)

set(${target}_src
	${CMAKE_CURRENT_SOURCE_DIR}/cm_backtrace.c
	${CMAKE_CURRENT_SOURCE_DIR}/fault_handler/gcc/cmb_fault.S)

add_library(${target} OBJECT ${${target}_src})
