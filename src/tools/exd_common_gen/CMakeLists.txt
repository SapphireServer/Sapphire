cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Tool_ExdCommonGen)

set(SAPPHIRE_BOOST_VER 1.63.0)
set(SAPPHIRE_BOOST_FOLDER_NAME boost_1_63_0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/../bin/")

include_directories("../../lib/ChaiScript-6.0.0/include/")

include_directories("../../sapphire/datReader/")
include_directories("../../sapphire/")
include_directories("../")

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")


if(UNIX)
  include_directories("/usr/include/mysql/")
  message(STATUS "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m32")
  
else()
  add_definitions(-D_WIN32_WINNT=0x601)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../lib/MySQL/")
  message(STATUS "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

endif()

include_directories(${Boost_INCLUDE_DIR})

link_directories(${BOOST_LIBRARYDIR})
link_directories(${SERVER_COMMON_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../sapphire/datReader/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../lib/MySQL)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../lib/zlib)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
add_executable(exd_common_gen ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

set_target_properties(exd_common_gen PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
)

if (UNIX)
  target_link_libraries (exd_common_gen Common xivdat pthread mysqlclient dl z)
else()
  target_link_libraries (exd_common_gen Common xivdat libmysql zlib1)
endif()

target_link_libraries(exd_common_gen ${Boost_LIBRARIES} ${Boost_LIBRARIES})

