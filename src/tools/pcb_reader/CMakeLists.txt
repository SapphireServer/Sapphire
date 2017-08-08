set( CMAKE_CXX_FLAGS "-std=c++11 -m32")

include_directories("../../")
include_directories("../")

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.cpp")

SET(Boost_USE_STATIC_LIBS ON)
set(Boost_INCLUDE_DIR /opt/build_libs/boost_1_60_0)
set(Boost_LIBRARY_DIR /opt/build_libs/boost_1_60_0/stage/lib)
set(SERVER_COMMON_DIR ../../servers/Server_Common)
find_package(Boost COMPONENTS log log_setup thread date_time filesystem system  REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIR})
link_directories(${SERVER_COMMON_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
add_executable(pcb_parser2 ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries (pcb_parser2 server_common.a pthread mysqlclient dl z)
target_link_libraries(pcb_parser2 ${Boost_LIBRARIES} ${Boost_LIBRARIES})

