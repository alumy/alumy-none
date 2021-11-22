function(mock)
    set(options)
    set(single_value)
    set(multi_value MOCK_HEADER_FILES INCLUDE_DIRS REQUIRES)

    cmake_parse_arguments(_ "${options}" "${single_value}" "${multi_value}" ${ARGN})

    set(MOCK_GENERATED_HEADERS "")
    set(MOCK_GENERATED_SRCS "")
    set(MOCK_FILES "")
    set(CMOCK_DIR "${PROJECT_SOURCE_DIR}/cmock/CMock")
    set(MOCK_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    list(APPEND __INCLUDE_DIRS "${MOCK_GEN_DIR}/mocks")

    foreach(header_file ${__MOCK_HEADER_FILES})
        get_filename_component(file_without_dir ${header_file} NAME_WE)
        list(APPEND MOCK_GENERATED_HEADERS "${MOCK_GEN_DIR}/mocks/mock_${file_without_dir}.h")
        list(APPEND MOCK_GENERATED_SRCS "${MOCK_GEN_DIR}/mocks/mock_${file_without_dir}.c")
    endforeach()

    file(MAKE_DIRECTORY "${MOCK_GEN_DIR}/mocks")
	
    set(mock_src ${MOCK_GENERATED_SRCS} CACHE STRING "")
    set(mock_inc ${__INCLUDE_DIRS} CACHE STRING "")

    add_custom_command(
        OUTPUT ruby_found SYMBOLIC
        COMMAND "ruby" "-v"
        COMMENT "Try to find ruby. If this fails, you need to install ruby"
    )

    # This command builds the mocks.
    # First, environment variable UNITY_DIR is set. This is necessary to prevent unity from looking in its own submodule
    # which doesn't work in our CI yet...
    # The rest is a straight forward call to cmock.rb, consult cmock's documentation for more information.
    add_custom_command(
        OUTPUT ${MOCK_GENERATED_SRCS} ${MOCK_GENERATED_HEADERS}
        DEPENDS ruby_found
        COMMAND ${CMAKE_COMMAND} -E env "UNITY_DIR=${PROJECT_SOURCE_DIR}/unity/unity"
        ruby
        ${CMOCK_DIR}/lib/cmock.rb
                -o${PROJECT_SOURCE_DIR}/mock/mock_config.yaml
                ${__MOCK_HEADER_FILES}
      )
endfunction()

