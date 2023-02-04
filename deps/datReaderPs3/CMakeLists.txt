cmake_minimum_required(VERSION 3.0.2)
project(Sapphire)

include_directories( "../" )

file( GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*" )
file( GLOB UTILS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*" )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( xivdatps3 ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

if (UNIX)
    target_link_libraries( xivdatps3 PUBLIC dl )
    target_link_libraries( xivdatps3 PUBLIC z )
else()
    target_link_libraries( xivdatps3 PUBLIC zlib )
endif()
target_include_directories( xivdatps3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
#cotire( xivdat )
