set(target driver)

FILE (GLOB_RECURSE ${target}_src
    ${CMAKE_CURRENT_SOURCE_DIR}/ALD/ES32F065x/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/MD/ES32F065x/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/EastSoft/ES32F065x/System/*.c)

add_library(${target} STATIC ${${target}_src})

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ALD/ES32F065x/Include
	${CMAKE_CURRENT_SOURCE_DIR}/MD/ES32F065x/Include
	${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include
	${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/EastSoft/ES32F065x/Include)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
