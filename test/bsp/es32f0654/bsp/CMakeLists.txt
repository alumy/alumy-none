#############################################################################
# PUBLIC: for all components that called this module
# PRIVATE: only for self
#############################################################################

set(target bsp)

FILE (GLOB_RECURSE ${target}_src ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(${target} STATIC ${${target}_src})
target_link_libraries(${target} PUBLIC driver)

target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Compile options for this component
# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
