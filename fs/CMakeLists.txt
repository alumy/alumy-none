set(target fs)

set(${target}_src
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_cache.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_check.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_hydrogen.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_nucleus.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_gc.c
		${CMAKE_CURRENT_SOURCE_DIR}/interface/lfs_file.c
		${CMAKE_CURRENT_SOURCE_DIR}/interface/lfs_space.c)

add_library(${target} OBJECT ${${target}_src})

target_link_libraries(${target} PRIVATE 3rd-party)

target_compile_options(${target} PRIVATE -Wno-unused-function -Wno-format)
