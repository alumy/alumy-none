set(target protobuf-c)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${target}_src)

add_library(${target} OBJECT ${${target}_src})
target_compile_options(${target} PRIVATE
	-Wno-format -Wno-strict-aliasing -Wno-unused-but-set-variable)
