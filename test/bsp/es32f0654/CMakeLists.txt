
include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_subdirectory(bsp)
add_subdirectory(Drivers)
add_subdirectory(startup)