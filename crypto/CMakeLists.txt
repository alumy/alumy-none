set(target crypto)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${target}_src)

add_library(${target} OBJECT ${${target}_src})
target_link_libraries(${target} 3rd-party)
