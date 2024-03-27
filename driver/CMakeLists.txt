set(target driver)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/eeprom/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/net/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/lora/llc68/*.c)

add_library(${target} OBJECT ${${target}_src})
