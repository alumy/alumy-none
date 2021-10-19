set(target unity)

set(${target}_src ${CMAKE_CURRENT_SOURCE_DIR}/unity/src/unity.c
	${CMAKE_CURRENT_SOURCE_DIR}/unity/extras/memory/src/unity_memory.c
	${CMAKE_CURRENT_SOURCE_DIR}/unity/extras/fixture/src/unity_fixture.c)

add_library(${target} STATIC ${${target}_src})

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/unity/src/
	${CMAKE_CURRENT_SOURCE_DIR}/unity/extras/fixture/src/
	${CMAKE_CURRENT_SOURCE_DIR}/unity/extras/memory/src/)

