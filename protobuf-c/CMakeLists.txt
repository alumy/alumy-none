set(target protobuf-c)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${target}_src)

add_library(${target} OBJECT ${${target}_src})
