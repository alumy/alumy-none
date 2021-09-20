set(target driver)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/eeprom/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/rtc/*.c)

add_library(${target} OBJECT ${${target}_src})
