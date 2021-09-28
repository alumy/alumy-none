set(target fs)

set(${target}_src
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_cache.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_check.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_hydrogen.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_nucleus.c
		${CMAKE_CURRENT_SOURCE_DIR}/spiffs/src/spiffs_gc.c)

add_library(${target} OBJECT ${${target}_src})

