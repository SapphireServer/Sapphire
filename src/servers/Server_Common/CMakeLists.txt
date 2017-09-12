cmake_minimum_required(VERSION 2.6)
project(Sapphire)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sapphire/datReader/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQLpp/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/ChaiScript-6.0.0/include/")

if(UNIX)
  include_directories("/usr/include/mysql/")
  message(STATUS "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m32")

else()
  add_definitions(-D_WIN32_WINNT=0x601)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/")
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQLpp/")
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQLpp/includes/")
  message(STATUS "Using boost in /libraries/external")
  message(STATUS "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

endif()


file(GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB UTILS_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Crypt/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Exd/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Logging/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/PacketDef/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Script/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp")


link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sapphire/datReader/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Common ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} Network/PacketDef/Lobby/ServerLobbyDef.h)

set_target_properties(Common PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
)

if (UNIX)
  target_link_libraries( Common xivdat mysqlclient )
else()
  target_link_libraries( Common xivdat libmysql )
endif()
