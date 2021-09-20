
add_definitions(-DXTAL_VALUE=12000000ul)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_subdirectory(bsp)
add_subdirectory(driver)
add_subdirectory(startup)
add_subdirectory(mcu)

# jlink_burn_cmd_gen(${PROJECT_NAME}-test)
debug(${PROJECT_NAME}-test )
gdbserver("HC32F460XE")
jflash("HC32F460XE" ${PROJECT_NAME}-test)
flash("HC32F460XE" ${PROJECT_NAME}-test)

