cmake_minimum_required( VERSION 3.0.2 )
project( Sapphire )

include( ExternalProject )

#############################################################################

set( MYSQLCONNECTOR_ROOT ${CMAKE_BINARY_DIR}/external/MysqlConnector )
set( MYSQLCONNECTOR_LIB_DIR ${MYSQLCONNECTOR_ROOT}/bin/lib )
set( MYSQLCONNECTOR_INCLUDE_DIR ${MYSQLCONNECTOR_ROOT}/bin/include )

if( UNIX )
  set( BUILD_EXEC make )
else()
  set( BUILD_EXEC nmake )
endif()

ExternalProject_Add( mysqlConnector_external
        PREFIX ${MYSQLCONNECTOR_ROOT}
        GIT_REPOSITORY "https://github.com/SapphireMordred/MysqlConnector.git"
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        PATCH_COMMAND ""
        BINARY_DIR ${MYSQLCONNECTOR_ROOT}/src/MysqlConnector
        SOURCE_DIR ${MYSQLCONNECTOR_ROOT}/src/MysqlConnector
        INSTALL_DIR ${MYSQLCONNECTOR_ROOT}/bin
        BUILD_COMMAND ${BUILD_EXEC} )

add_library( mysqlConnector STATIC IMPORTED )
set_target_properties( mysqlConnector PROPERTIES IMPORTED_LOCATION ${MYSQLCONNECTOR_LIB_DIR}/mysqlConnector.a )
add_dependencies( mysqlConnector mysqlConnector_external )

#############################################################################

set( XIVDAT_ROOT ${CMAKE_BINARY_DIR}/external/XivDat )
set( XIVDAT_LIB_DIR ${XIVDAT_ROOT}/bin/lib )
set( XIVDAT_INCLUDE_DIR ${XIVDAT_ROOT}/bin/include )

ExternalProject_Add( xivdat_external
        PREFIX ${XIVDAT_ROOT}
        GIT_REPOSITORY "https://github.com/SapphireMordred/XivDat.git"
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        PATCH_COMMAND ""
        BINARY_DIR ${XIVDAT_ROOT}/src/XivDat
        SOURCE_DIR ${XIVDAT_ROOT}/src/XivDat
        INSTALL_DIR ${XIVDAT_ROOT}/bin
        BUILD_COMMAND ${BUILD_EXEC} )

add_library( xivdat STATIC IMPORTED )
set_target_properties( xivdat PROPERTIES IMPORTED_LOCATION ${XIVDAT_LIB_DIR}/xivdat.a )
add_dependencies( xivdat xivdat_external )

#############################################################################

file(GLOB UTILS_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Crypt/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Exd/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Logging/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/PacketDef/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Script/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp")

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )


add_library( common ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

target_link_libraries( common PUBLIC xivdat )
target_link_libraries( common PUBLIC mysqlConnector )

target_include_directories( common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/"
                                          "${MYSQLCONNECTOR_ROOT}/src/MysqlConnector/src/"
                                          "${XIVDAT_ROOT}/src/XivDat/src/" )

target_include_directories( common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/")

