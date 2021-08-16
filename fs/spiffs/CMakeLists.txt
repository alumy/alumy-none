set(target spiffs)

set(${target}_src
		${CMAKE_CURRENT_SOURCE_DIR}/src/spiffs_check.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/spiffs_check.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/spiffs_hydrogen.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/spiffs_nucleus.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/spiffs_gc.c)

add_library(${target} STATIC ${${target}_src})

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
