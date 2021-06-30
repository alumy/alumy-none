
include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_subdirectory(bsp)
add_subdirectory(Drivers)
add_subdirectory(startup)
add_subdirectory(system)

es32_make_flash(${CMAKE_BINARY_DIR}/${PROJECT_NAME}-test.hex ${PROJECT_NAME}-test)

