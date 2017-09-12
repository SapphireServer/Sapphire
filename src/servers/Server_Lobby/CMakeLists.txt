cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Sapphire)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")

if(UNIX)
  include_directories("/usr/include/mysql/")
else()
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  # 32 bit link
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/x86)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/zlib/x86)
else()
  # 64 bit link
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/x64)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/zlib/x64)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/")

add_executable(server_lobby ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})
add_dependencies(server_lobby Common xivdat)

set_target_properties(server_lobby PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
)

if (UNIX)
  target_link_libraries(server_lobby Common xivdat pthread mysqlclient dl z)
else()
  target_link_libraries(server_lobby Common xivdat libmysql zlib1)
endif()

target_link_libraries(server_lobby ${Boost_LIBRARIES} ${Boost_LIBRARIES})
