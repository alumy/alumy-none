set(target cmock)

set(${target}_src ${CMAKE_CURRENT_SOURCE_DIR}/CMock/src/cmock.c)

add_library(${target} STATIC ${${target}_src})

target_link_libraries(${target} PUBLIC unity)

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/CMock/src/)

