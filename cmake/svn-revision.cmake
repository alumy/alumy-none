# in case SVN is not available, we default to "unknown"
set(SVN_REVISION 0)

# find svn revision 
if(EXISTS "${CMAKE_SOURCE_DIR}/.svn/")
    find_package(Subversion)

    if(SUBVERSION_FOUND)
        Subversion_WC_INFO(${CMAKE_SOURCE_DIR} PROJ)
        set(SVN_REVISION ${PROJ_WC_REVISION})
    endif(SUBVERSION_FOUND)
endif(EXISTS "${CMAKE_SOURCE_DIR}/.svn/")

message(STATUS "SVN revision is ${SVN_REVISION}")

# generate file version.hpp based on version.hpp.in
configure_file(
    ${CMAKE_SOURCE_DIR}/include/alumy/svn_revision.h.in
    ${CMAKE_SOURCE_DIR}/include/alumy/svn_revision.h
    @ONLY)

