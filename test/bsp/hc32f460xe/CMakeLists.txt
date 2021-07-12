
add_definitions(-DXTAL_VALUE=12000000ul)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_subdirectory(bsp)
add_subdirectory(driver)
add_subdirectory(startup)
add_subdirectory(mcu)


