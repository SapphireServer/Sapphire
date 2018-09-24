cmake_minimum_required( VERSION 3.0.2 )
project( Sapphire )

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

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( common ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

set_target_properties( common PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
)

target_link_libraries( common PUBLIC ${Boost_LIBRARIES} )
target_link_libraries( common PUBLIC xivdat )

target_link_libraries( common PUBLIC mysqlConnector )
if( UNIX )

  target_link_libraries( common PUBLIC mysqlclient )
  target_link_libraries( common PUBLIC pthread )

else()
  target_link_libraries( common
                           PUBLIC
                             libmysql )
endif()

target_include_directories( common
                              PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}/"
                              PRIVATE
                                "${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/" )

